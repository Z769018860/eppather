//! 符号执行引擎

use std::{cell::RefCell, collections::btree_map::Range, ops::ControlFlow};

use anyhow::{anyhow, Context, Ok, Result};
use clang::{
    sonar::{find_functions, Declaration},
    source, Entity, EntityKind,
};

use crate::{
    ast::{
        self, format_entity,
        node::{Stmt, StmtKind},
        visit::{self, walk_stmt, Visitor, VisitorResult},
    },
    csa, try_visit,
};

struct Engine<'a> {
    manager: ast::Manager<'a>,
    state: EngineState,
}

struct EngineState {
    pub(self) ctrl_flow: Box<dyn Iterator<Item = csa::Msg>>,
    pub(self) diagnostic: Vec<String>,
}

impl EngineState {
    pub(self) fn new() -> Self {
        EngineState {
            ctrl_flow: Box::new(std::iter::empty()),
            diagnostic: Vec::new(),
        }
    }

    pub(self) fn add_diagnostic(&mut self, msg: String) {
        self.diagnostic.push(msg);
    }
}

impl<'a> Engine<'a> {
    pub fn new(manager: ast::Manager<'a>) -> Self {
        Engine {
            manager,
            state: EngineState::new(),
        }
    }

    /// 对路径进行符号执行
    /// XXX: 临时代码，后续实现Path结构体，Branch trait等，为Msg实现Branch trait
    pub fn exec_rpt(&mut self, rpt: csa::Report) -> Result<EngineResult> {
        let start = rpt
            .get_start_position()
            .ok_or(anyhow!("Can not get the start position"))?;
        let start_file = start
            .file
            .as_ref()
            .ok_or(anyhow!("Can not get the start file"))?;
        let start_tu = self
            .manager
            .get_translation_unit(start_file)
            .with_context(|| anyhow!("Can not get the start translation unit"))?;
        let start_func = find_functions(start_tu.get_entity().get_children())
            .filter(|f| {
                if let Some(range) = f.entity.get_range() {
                    ast::Range::from(range).contains(&start)
                } else {
                    false
                }
            })
            .collect::<Vec<_>>();

        // XXX: 有多个时记录
        let start_func = start_func
            .first()
            .ok_or(anyhow!("Can not get the start function"))?;
        let mut iter_ctrl = rpt.iter_ctrl();
        self.state.ctrl_flow = Box::new(iter_ctrl);

        // self.exec_func(start_func)
        match self.visit_func(start_func.entity) {
            ControlFlow::Continue(()) => Ok(EngineResult::Feasible),
            ControlFlow::Break(res) => Ok(res),
        }
    }
}

impl Visitor for Engine<'_> {
    type Result = ControlFlow<EngineResult>;

    fn visit_stmt(&mut self, stmt: &Stmt) -> Self::Result {
        // println!("stmt: {:?}, {:?}", stmt.get_display_name(), stmt.get_kind());
        // println!("stmt: {:?}", format_entity(&stmt.entity));
        let Stmt { entity, kind } = stmt;

        match kind {
            StmtKind::If(cond, then, opt_else) => {
                let flow = match self.state.ctrl_flow.next() {
                    Some(flow) => flow,
                    None => {
                        self.state.add_diagnostic(format!(
                            "No ctrl flow for if stmt at {:?}",
                            stmt.entity.get_range()
                        ));
                        return ControlFlow::Break(EngineResult::Unknown);
                    }
                };
                let branch = match flow.get_branch() {
                    Some(branch) => branch,
                    None => {
                        self.state.add_diagnostic(format!(
                            "Error ctrl flow for if stmt at {:?}, with msg: {:?}",
                            stmt.entity.get_range(),
                            flow
                        ));
                        return ControlFlow::Break(EngineResult::Unknown);
                    }
                };
                try_visit!(self.visit_expr(cond));
                if branch {
                    try_visit!(self.visit_stmt(then));
                } else {
                    if let Some(else_) = opt_else {
                        try_visit!(self.visit_stmt(else_));
                    }
                }

                Self::Result::output()
            }
            StmtKind::Other() => walk_stmt(self, stmt),
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum EngineResult {
    Feasible,
    Infeasible,
    Unknown,
}

#[cfg(test)]
mod tests {
    use std::path::PathBuf;

    use serial_test::serial;

    use super::*;

    const BUGS_ROOT: &str = "resources/bugs";

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_engine() -> Result<()> {
        let clang = crate::ClangWrapper::new()?;
        let index = clang.get_index();
        let manager = ast::Manager::new(
            csa::db::Database::load(PathBuf::from(BUGS_ROOT), true, false)?,
            &index,
        );
        let mut engine = Engine::new(manager);

        let rpts = engine.manager.db.get_csa_reports();
        let flt_rpt = rpts
            .into_iter()
            .find(|rpt| {
                rpt.get_file()
                    .map_or(false, |f| f.to_str().unwrap().contains("flt"))
            })
            .unwrap();
        let res = engine.exec_rpt(flt_rpt)?;
        println!("res: {:?}", res);

        Ok(())
    }

    #[test]
    fn test_tmp() {
        use std::cell::RefCell;

        #[derive(Debug)]
        enum State {
            A,
            B,
        }

        struct StateMachine {
            state: RefCell<State>,
        }

        impl StateMachine {
            fn transition_a(&self) {
                {
                    let mut state = self.state.borrow_mut();
                    // 可以修改状态
                    *state = State::A;
                }

                // 可以调用其他方法
                self.some_other_method();
            }

            fn some_other_method(&self) {
                let mut state = self.state.borrow_mut();
                // 再次修改状态
                *state = State::B;
            }
        }

        let state_machine = StateMachine {
            state: RefCell::new(State::A),
        };

        state_machine.transition_a();
        println!("state: {:?}", state_machine.state);
    }
}
