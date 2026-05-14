//! 调用CSA的driver

use std::{
    env,
    ffi::OsStr,
    fs,
    path::{Path, PathBuf},
    process::{Command, Output},
};

use anyhow::{anyhow, Result};

use crate::utils::run_command_at;

const DRIVER_ROOT: &str = "/app/csa-driver";
const CCJSON: &str = "compile_commands.json";

/// 根据项目目录下的build文件夹生成CSA缓存
/// 返回分析缓存目录
pub(super) fn analyze_project(
    project_root: impl AsRef<Path>,
    analyze: bool,
    reanalyze: bool,
) -> Result<PathBuf> {
    let root = project_root.as_ref();
    let root = root
        .canonicalize()
        .map_err(|_| anyhow!("invalid project path {:?}", root))?;

    // 生成构建项目和编译命令
    let build_dir = root.join("build");
    let ccjson = build_dir.join("compile_commands.json");

    if reanalyze || !ccjson.exists() {
        generate_ccjson(&root)?;
    }

    // 分析项目
    let analyze_dir = root.join("analyze");
    let analyze_rpt_dir = analyze_dir.join("cache").join("rpt");
    if reanalyze || !analyze_dir.exists() || (analyze && !analyze_rpt_dir.exists()) {
        run_command_at(
            Command::new("python").args(
                vec![
                    "driver",
                    ccjson.to_str().unwrap(),
                    "--output",
                    analyze_dir.to_str().unwrap(),
                    "--solver",
                    "crosscheck",
                    if analyze { "" } else { "--no-analyze" },
                ]
                .into_iter()
                .filter(|&x| !x.is_empty()),
            ),
            DRIVER_ROOT,
        )?;
    }

    Ok(analyze_dir)
}

/// 为项目生成 `build` 目录和编译命令 `compile_commands.json`
/// 返回生成的 `compile_commands.json` 的路径
fn generate_ccjson(project_root: impl AsRef<Path>) -> Result<PathBuf> {
    let root = project_root.as_ref();
    let root = root
        .canonicalize()
        .map_err(|_| anyhow!("invalid project path {:?}", root))?;

    let build_dir = root.join("build");
    if !build_dir.exists() {
        fs::create_dir_all(&build_dir)?;
    }
    run_command_at(
        Command::new("cmake")
            .arg("-DCMAKE_EXPORT_COMPILE_COMMANDS=ON")
            .arg(".."),
        &build_dir,
    )?;

    Ok(build_dir.join(CCJSON))
}

#[cfg(test)]
mod tests {
    use serial_test::serial;

    use super::*;

    const BUGS_ROOT: &str = "resources/bugs";

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_cmake() -> Result<()> {
        let root = Path::new(BUGS_ROOT);
        generate_ccjson(root)?;

        Ok(())
    }

    #[test]
    #[serial(WorkingDirectoryGuard, BUGS_ROOT)]
    fn test_csa() -> Result<()> {
        let root = Path::new(BUGS_ROOT);
        analyze_project(root, true, false)?;

        Ok(())
    }
}
