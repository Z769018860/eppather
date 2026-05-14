//! AST遍历器
//! TODO: 实现Rust式的AST绑定

use std::{ops::ControlFlow, process::Child};

use clang::{sonar::Declaration, Entity, EntityKind, TranslationUnit};

use crate::{
    ast::{format_entity, visit},
    try_visit, walk_list,
};

use super::node::{Expr, Stmt};

pub trait Visitor: Sized {
    type Result: VisitorResult;

    fn visit_entity(&mut self, entity: Entity) -> Self::Result {
        walk_entity(self, entity)
    }
    fn visit_expr(&mut self, expr: &Expr) -> Self::Result {
        walk_expr(self, expr)
    }
    fn visit_stmt(&mut self, stmt: &Stmt) -> Self::Result {
        walk_stmt(self, stmt)
    }
    fn visit_func(&mut self, func: Entity) -> Self::Result {
        walk_func(self, func)
    }
}

pub fn walk_entity<V: Visitor>(visitor: &mut V, entity: Entity) -> V::Result {
    // println!(
    //     "entity: {:?}, {:?}",
    //     format_entity(&entity),
    //     entity.get_kind()
    // );

    if entity.is_statement() {
        let stmt = Stmt::new(entity);
        visitor.visit_stmt(&stmt)
    } else {
        walk_list!(visitor, visit_entity, entity.get_children());
        V::Result::output()
    }
}

pub fn walk_expr<V: Visitor>(visitor: &mut V, expr: &Expr) -> V::Result {
    walk_list!(visitor, visit_entity, expr.entity.get_children());
    V::Result::output()
}

pub fn walk_stmt<V: Visitor>(visitor: &mut V, stmt: &Stmt) -> V::Result {
    walk_list!(visitor, visit_entity, stmt.entity.get_children());
    V::Result::output()
}

pub fn walk_func<V: Visitor>(visitor: &mut V, func: Entity) -> V::Result {
    visitor.visit_entity(func)
}

#[cfg(test)]
mod tests {
    use std::path::PathBuf;

    use clang::sonar::find_functions;
    use serial_test::serial;

    use super::*;

    const BUGS_ROOT: &str = "resources/bugs";

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_visitor() {
        let clang = crate::ClangWrapper::new().unwrap();
        let index = clang.get_index();
        let mut manager = crate::ast::Manager::new(
            crate::csa::db::Database::load(PathBuf::from(BUGS_ROOT), false, false).unwrap(),
            &index,
        );

        let flt_file = manager
            .db
            .get_files()
            .into_iter()
            .filter(|f| f.to_str().unwrap().contains("flt"))
            .next()
            .unwrap();
        let tu = manager.get_translation_unit(&flt_file).unwrap();

        let flt_func = find_functions(tu.get_entity().get_children())
            .find(|f| f.name == "ret_flt")
            .unwrap();

        struct MyVisitor;
        impl Visitor for MyVisitor {
            type Result = ();
        }
        let mut visitor = MyVisitor;

        visitor.visit_entity(flt_func.entity);
    }
}

// from https://github.com/rust-lang/rust/blob/master/compiler/rustc_ast_ir/src/visit.rs
pub trait VisitorResult {
    type Residual;
    fn output() -> Self;
    fn from_residual(residual: Self::Residual) -> Self;
    fn from_branch(b: ControlFlow<Self::Residual>) -> Self;
    fn branch(self) -> ControlFlow<Self::Residual>;
}

impl VisitorResult for () {
    type Residual = core::convert::Infallible;

    fn output() -> Self {}
    fn from_residual(_: Self::Residual) -> Self {}
    fn from_branch(_: ControlFlow<Self::Residual>) -> Self {}
    fn branch(self) -> ControlFlow<Self::Residual> {
        ControlFlow::Continue(())
    }
}

impl<T> VisitorResult for ControlFlow<T> {
    type Residual = T;

    fn output() -> Self {
        ControlFlow::Continue(())
    }
    fn from_residual(residual: Self::Residual) -> Self {
        ControlFlow::Break(residual)
    }
    fn from_branch(b: Self) -> Self {
        b
    }
    fn branch(self) -> Self {
        self
    }
}

#[macro_export]
macro_rules! try_visit {
    ($e:expr) => {
        match $crate::ast::visit::VisitorResult::branch($e) {
            core::ops::ControlFlow::Continue(()) => (),
            #[allow(unreachable_code)]
            core::ops::ControlFlow::Break(r) => {
                return $crate::ast::visit::VisitorResult::from_residual(r);
            }
        }
    };
}

#[macro_export]
macro_rules! visit_opt {
    ($visitor: expr, $method: ident, $opt: expr $(, $($extra_args: expr),* )?) => {
        if let Some(x) = $opt {
            $crate::try_visit!($visitor.$method(x $(, $($extra_args,)* )?));
        }
    }
}

#[macro_export]
macro_rules! walk_list {
    ($visitor: expr, $method: ident, $list: expr $(, $($extra_args: expr),* )?) => {
        for elem in $list {
            $crate::try_visit!($visitor.$method(elem $(, $($extra_args,)* )?));
        }
    }
}

#[macro_export]
macro_rules! walk_visitable_list {
    ($visitor: expr, $list: expr $(, $($extra_args: expr),* )?) => {
        for elem in $list {
            $crate::try_visit!(elem.visit_with($visitor $(, $($extra_args,)* )?));
        }
    }
}
