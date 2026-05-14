//! 处理AST的模块

use std::{
    borrow::Borrow,
    cell::RefCell,
    collections::HashMap,
    path::{Path, PathBuf},
};

use anyhow::Result;
use clang::{
    sonar::{find_functions, Declaration},
    source::SourceRange,
    Entity, EntityVisitResult, Index, TranslationUnit,
};

use crate::csa::db::Database;

pub mod manager;
pub mod node;
pub mod printer;
pub mod source;
pub mod visit;

pub use manager::Manager;
pub use source::{Location, Range};

const BUGS_ROOT: &str = "resources/bugs";

/// 临时代码，模拟执行
#[deprecated]
pub fn tmp_code() -> Result<()> {
    let clang = crate::ClangWrapper::new()?;
    let index = clang.get_index();
    let mut manager = Manager::new(
        crate::csa::db::Database::load(PathBuf::from(BUGS_ROOT), true, false)?,
        &index,
    );
    let rpts = manager.db.get_csa_reports();
    let flt_rpt = rpts
        .into_iter()
        .find(|rpt| {
            rpt.get_file()
                .map_or(false, |f| f.to_str().unwrap().contains("flt"))
        })
        .unwrap();

    let file = flt_rpt.get_file().unwrap();

    let tu = manager.get_translation_unit(&file).unwrap();
    let cur_func = find_functions(tu.get_entity().get_children())
        .find(|f| f.name == "ret_flt")
        .unwrap();

    // dfs(&cur_func);

    fn print_entity(entity: &Entity, parent: &Entity) -> EntityVisitResult {
        println!(
            "parent: {:?}, kind: {:?}",
            parent.get_name(),
            parent.get_kind()
        );
        println!(
            "entity: {:?}, kind: {:?}",
            entity.get_name(),
            entity.get_kind()
        );
        // println!("{}", format_entity(&entity).unwrap());
        entity.visit_children(|entity, parent| print_entity(&entity, &parent));

        EntityVisitResult::Continue
    }

    cur_func
        .entity
        .visit_children(|entity, parent| print_entity_ast(&entity));

    // 打印对应的路径
    // TODO: report里面获得入口函数
    let mut iter_ctrl = flt_rpt.iter_ctrl();
    for msg in iter_ctrl {
        // dbg!(&msg);
    }

    Ok(())
}

/// 临时代码，深度优先搜索AST
fn dfs(entity: &Entity) {
    println!("entity: {}", format_entity(entity).unwrap());
}

pub fn print_entity_ast(entity: &Entity) -> EntityVisitResult {
    let kind = entity.get_kind();
    let name = entity.get_name();

    let loc = entity.get_location().unwrap().get_spelling_location();
    let file = loc.file.unwrap().get_path();

    println!(
        "kind: {:?}, name: {:?}, file: {:?}:{}:{}",
        kind, name, file, loc.line, loc.column
    );

    entity.visit_children(|entity, parent| print_entity_ast(&entity));

    EntityVisitResult::Continue
}

/// 格式化entity
pub fn format_entity(entity: &Entity) -> Option<String> {
    Some(format_range(&entity.get_range()?))
}

/// 格式化source range
pub fn format_range(range: &SourceRange) -> String {
    format_tokens(&range.tokenize())
}

/// 格式化token流，token流必须连续
pub fn format_tokens(tokens: &[clang::token::Token]) -> String {
    let mut ret = String::new();
    let mut row = 0u32; // clang的行数从1开始
    let mut col = 0u32;
    for token in tokens {
        let start = token.get_location().get_spelling_location();
        let (new_row, new_col) = (start.line, start.column);
        if new_row != row {
            if row != 0 {
                ret.push('\n');
            }
            col = 1;
        }
        ret += &" ".repeat(if new_col > col {
            (new_col - col) as usize
        } else {
            0
        });
        ret += &token.get_spelling();
        let end = token.get_range().get_end().get_spelling_location();
        (row, col) = (end.line, end.column);
    }

    ret
}

#[cfg(test)]
mod tests {
    use serial_test::serial;

    use super::*;

    const BUGS_ROOT: &str = "resources/bugs";
    // const BUGS_ROOT: &str = "/app/sources/bugs";

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_print_tokens() {
        let expected = r#"
float ret_flt(float x, float z) {
    float *y = 0;
    if (x * x < 0.0f) {
        return *y;
    } else {
        return 0.0f;
    }
}"#
        .trim();

        let clang = crate::ClangWrapper::new().unwrap();
        let index = clang.get_index();
        let mut manager = Manager::new(
            crate::csa::db::Database::load(PathBuf::from(BUGS_ROOT), false, false).unwrap(),
            &index,
        );

        let vec_file = manager
            .db
            .get_files()
            .into_iter()
            .filter(|f| f.to_str().unwrap().contains("flt"))
            .next()
            .unwrap();

        let tu = manager.get_translation_unit(vec_file).unwrap();
        // println!("children: {:?}", tu.get_entity().get_children());
        // for child in tu.get_entity().get_children() {
        //     println!("child: {}", format_entity(&child).unwrap());
        // }
        // return ();
        let vec1 = find_functions(tu.get_entity().get_children())
            .find(|f| f.name == "ret_flt")
            .unwrap();
        let tokens = vec1.entity.get_range().unwrap().tokenize();

        assert_eq!(format_tokens(&tokens), expected);
    }

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_pretty_printer() {
        // XXX: 临时代码
        let expected = r#"
float ret_flt(float x) {
    float *y = 0;
    if (x * x < 0.0f) {
        return *y;
    } else {
        return 0.0f;
    }
}"#
        .trim();

        let clang = crate::ClangWrapper::new().unwrap();
        let index = clang.get_index();
        let mut manager = Manager::new(
            crate::csa::db::Database::load(PathBuf::from(BUGS_ROOT), false, false).unwrap(),
            &index,
        );

        let vec_file = manager
            .db
            .get_files()
            .into_iter()
            .filter(|f| f.to_str().unwrap().contains("flt"))
            .next()
            .unwrap();

        let tu = manager.get_translation_unit(vec_file).unwrap();
        let vec1 = find_functions(tu.get_entity().get_children())
            .find(|f| f.name == "ret_flt")
            .unwrap();
        println!("vec1.entity.kind: {:?}", vec1.entity.get_kind());
        let tokens = vec1.entity.get_range().unwrap().tokenize();

        let ret = vec1.entity.get_pretty_printer().print();
        println!("ret: {}", ret);
    }
}
