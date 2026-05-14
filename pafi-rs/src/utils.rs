//! pafi-rs的工具函数集

use std::{
    any, env,
    path::{Path, PathBuf},
    process::Command,
};

use anyhow::{anyhow, Result};

pub fn run_command(cmd: &mut Command) -> Result<String> {
    let out = cmd.output()?;

    if out.status.success() {
        Ok(String::from_utf8_lossy(&out.stdout).to_string())
    } else {
        Err(anyhow!(
            "Command failed with status {}: {}",
            out.status,
            String::from_utf8_lossy(&out.stderr)
        ))
    }
}

pub fn run_command_at(cmd: &mut Command, path: impl AsRef<Path>) -> Result<String> {
    let guard = WorkingDirectoryGuard::new()?;
    env::set_current_dir(path)?;

    run_command(cmd)
}

/// 保护工作目录
pub struct WorkingDirectoryGuard {
    original_dir: PathBuf,
}

impl WorkingDirectoryGuard {
    fn new() -> Result<Self> {
        let original_dir = env::current_dir()?;

        Ok(Self { original_dir })
    }
}

impl Drop for WorkingDirectoryGuard {
    fn drop(&mut self) {
        // XXX: 错误处理
        let _ = env::set_current_dir(&self.original_dir);
    }
}

#[cfg(test)]
mod tests {
    use serial_test::serial;

    use super::*;

    #[test]
    #[serial(WorkingDirectoryGuard)]
    fn test_wd_guard_1() {
        let cur_dir = env::current_dir().unwrap();
        {
            let guard = WorkingDirectoryGuard::new().unwrap();
            env::set_current_dir("/").unwrap();
        }
        assert_eq!(env::current_dir().unwrap(), cur_dir);
    }

    #[test]
    #[serial(WorkingDirectoryGuard)]
    fn test_wd_guard_2() {
        let cur_dir = env::current_dir().unwrap();
        {
            let guard = WorkingDirectoryGuard::new().unwrap();
            env::set_current_dir("/app").unwrap();
        }
        assert_eq!(env::current_dir().unwrap(), cur_dir);
    }
}
