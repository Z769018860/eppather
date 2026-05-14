//! 管理AST的模块

use std::{
    borrow::Borrow,
    cell::RefCell,
    collections::HashMap,
    path::{Path, PathBuf},
};

use anyhow::Result;
use clang::{
    sonar::{find_functions, Declaration},
    Index, TranslationUnit,
};

use crate::csa::{db::Database, report::Report};

/// AST管理器，具有缓存机制
/// TODO: 未实现缓存机制
pub struct Manager<'a> {
    /// 数据库
    pub db: Database,

    /// Clang的Index
    index: &'a Index<'a>,
}

impl<'a> Manager<'a> {
    pub fn new(db: Database, index: &'a Index<'a>) -> Self {
        Manager { db, index }
    }

    /// 根据文件路径获取编译单元
    pub fn get_translation_unit(&self, file: impl AsRef<Path>) -> Result<TranslationUnit<'a>> {
        self.db.get_translation_unit(file, self.index)
    }
}

#[cfg(test)]
mod tests {
    use serial_test::serial;

    use super::*;

    const BUGS_ROOT: &str = "resources/bugs";

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_get_tu() {
        let clang = crate::ClangWrapper::new().unwrap();
        let index = clang.get_index();
        let mut manager = Manager::new(
            Database::load(PathBuf::from(BUGS_ROOT), false, false).unwrap(),
            &index,
        );
        for file in manager.db.get_files() {
            let tu = manager.get_translation_unit(file).unwrap();
            println!("tu: {:?}", tu);
        }
    }

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_get_func() {
        let clang = crate::ClangWrapper::new().unwrap();
        let index = clang.get_index();
        let mut manager = Manager::new(
            Database::load(PathBuf::from(BUGS_ROOT), false, false).unwrap(),
            &index,
        );
        let file = manager
            .db
            .get_files()
            .into_iter()
            .filter(|f| f.to_str().unwrap().contains("vec"))
            .next()
            .unwrap();
        let func_names = vec!["vec1", "vec2"];
        let tu = manager.get_translation_unit(&file).unwrap();
        for func_name in func_names {
            let func = find_functions(tu.get_entity().get_children()).find(|f| f.name == func_name);
            println!("func: {:?}", func);
        }
    }
}
