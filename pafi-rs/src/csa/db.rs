use std::{
    collections::HashMap,
    ffi::OsString,
    fs,
    path::{Path, PathBuf},
};

use anyhow::{anyhow, Result};
use clang::{Index, TranslationUnit};

use super::report::Report;

pub struct Database {
    root: PathBuf,
}

impl Database {
    /// 加载并分析项目  
    ///  
    /// # 功能流程  
    /// 1. 准备项目构建环境  
    ///    - 使用 `CMake` 生成构建目录 `build`
    ///    - 生成编译命令 `compile_commands.json`  
    ///  
    /// 2. 分析项目  
    ///    - 使用 `csa-driver` 扫描项目  
    ///    - 生成分析结果到 `analyze` 目录  
    ///
    /// 3. 加载分析结果  
    ///    - 从 `analyze` 目录加载分析结果
    ///  
    /// # 参数  
    /// - `root`: 项目根目录路径  
    /// - `analyze`: 是否执行完整代码分析  
    ///   - `true`: 执行完整分析  
    ///   - `false`: 仅生成语法缓存  
    /// - `reanalyze`: 是否强制重新分析  
    ///   - `true`: 忽略已存在的分析结果，重新分析  
    ///   - `false`: 如果分析结果已存在，则跳过该步骤  
    pub fn load(root: impl AsRef<Path>, analyze: bool, reanalyze: bool) -> Result<Self> {
        let analyze_dir = super::driver::analyze_project(root, analyze, reanalyze)?;

        Self::load_analyze(analyze_dir)
    }

    /// 读取数据库，路径为analyze目录
    pub fn load_analyze(root: impl AsRef<Path>) -> Result<Self> {
        let root = root.as_ref();
        let root = root.canonicalize()?;
        // .map_err(|_| anyhow!("{} does not exist", root.display()))?;

        Ok(Self { root })
    }

    pub fn get_files(&self) -> Vec<PathBuf> {
        let ast_cache_path = self.root.join("cache/ast");
        // XXX: 筛选.ast文件
        Self::collect_files(&ast_cache_path, true)
    }

    pub fn get_edm(&self) -> Result<HashMap<String, String>> {
        // XXX: 临时代码，获取符号名称和对应的路径的映射
        let edm_path = self.root.join("cache").join("externalDefMap.txt");
        let edm = fs::read_to_string(edm_path)?
            .lines()
            .filter_map(|line| {
                let mut parts = line.split(' ');
                let name = parts.next()?;
                let path = parts.next()?;
                Some((
                    name.split("@").last()?.to_string(),
                    path.strip_prefix("ast")?.strip_suffix(".ast")?.to_string(),
                ))
            })
            .collect();
        Ok(edm)
    }

    pub fn get_translation_unit<'index>(
        &self,
        file: impl AsRef<Path>,
        index: &'index Index,
    ) -> Result<TranslationUnit<'index>> {
        self.read_translation_unit(file, index)
    }

    /// 输入为源文件路径
    pub fn read_translation_unit<'index>(
        &self,
        file: impl AsRef<Path>,
        index: &'index Index,
    ) -> Result<TranslationUnit<'index>> {
        let file = file.as_ref();
        let ext = if let Some(ext) = file.extension() {
            let mut ext = OsString::from(ext);
            ext.push(".ast");
            ext
        } else {
            ".ast".into()
        };

        let ast_file = self
            .root
            .join("cache/ast")
            .join(file.strip_prefix("/").unwrap_or(file).with_extension(ext));
        TranslationUnit::from_ast(index, &ast_file)
            .map_err(|_| anyhow!("Failed to read ast file: {:?}", ast_file))
    }

    pub fn get_csa_reports(&self) -> Vec<Report> {
        let rpt_cache_path = self.root.join("cache/rpt");
        let files = Self::collect_files(&rpt_cache_path, false);

        // XXX: 筛选.rpt文件
        files.iter().filter_map(|f| Report::new(f).ok()).collect()
    }

    fn collect_files(root: &Path, strip: bool) -> Vec<PathBuf> {
        fn _collect_files(path: &Path, root: &Path, files: &mut Vec<PathBuf>, strip: bool) {
            if let Ok(entries) = path.read_dir() {
                for entry in entries.flatten() {
                    let path = entry.path();
                    if path.is_dir() {
                        _collect_files(&path, root, files, strip);
                    } else {
                        let path = if strip {
                            if let Ok(path) = path.strip_prefix(root) {
                                // FIXME: 这里获得的路径前面少个'/'
                                // Path::new("/").join(path).with_extension("")
                                path.with_extension("")
                            } else {
                                path
                            }
                        } else {
                            path
                        };

                        files.push(path);
                    }
                }
            }
        }

        let mut files = vec![];
        _collect_files(root, root, &mut files, strip);
        files
    }
}

#[cfg(test)]
mod tests {
    use serial_test::serial;

    use crate::ClangWrapper;

    use super::*;

    const BUGS_ROOT: &str = "resources/bugs";

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_get_files() {
        let root = Path::new(BUGS_ROOT);
        let db = Database::load(root, false, false).unwrap();
        let files = db.get_files();
        assert_eq!(files.len(), 3);
    }

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_get_edm() {
        let root = Path::new(BUGS_ROOT);
        let db = Database::load(root, false, false).unwrap();
        let edm = db.get_edm().unwrap();
        assert_eq!(edm.len(), 6);
    }

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_get_tu() {
        let root = Path::new(BUGS_ROOT);
        let db = Database::load(root, false, false).unwrap();
        let clang = ClangWrapper::new().unwrap();
        let index = clang.get_index();
        for file in db.get_files() {
            let tu = db.get_translation_unit(&file, &index).unwrap();
        }
    }

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_get_csa_reports() {
        let root = Path::new(BUGS_ROOT);
        let db = Database::load(root, true, false).unwrap();
        let rpts = db.get_csa_reports();
        assert_eq!(rpts.len(), 3);
    }
}
