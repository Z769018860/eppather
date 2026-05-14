//! pafi-rs的顶层文件

#![allow(dead_code, unused_variables, unused_imports, unused_mut)]

use std::sync::{Condvar, Mutex};

use anyhow::{anyhow, Result};
use clang::{Clang, Index};
use lazy_static::lazy_static;

pub mod ast;
pub mod csa;
pub mod engine;
pub mod utils;

// Clang不可发送，因此不能直接加锁
lazy_static! {
    static ref CLANG_STATE: (Mutex<bool>, Condvar) = (Mutex::new(false), Condvar::new());
}

/// Clang的包装
pub struct ClangWrapper {
    clang: Clang,
}

impl ClangWrapper {
    /// 获取clang，会加锁和等待资源
    pub fn new() -> Result<ClangWrapper> {
        let (lock, cvar) = &*CLANG_STATE;

        let mut guard = lock.lock().unwrap();
        while *guard {
            guard = cvar.wait(guard).unwrap();
        }

        let clang = Clang::new().map_err(|msg| anyhow!(msg))?;

        *guard = true;

        Ok(Self { clang })
    }

    pub fn get_clang(&self) -> &Clang {
        &self.clang
    }

    pub fn get_index(&self) -> Index<'_> {
        Index::new(&self.clang, false, false)
    }
}

impl Drop for ClangWrapper {
    fn drop(&mut self) {
        let (lock, cvar) = &*CLANG_STATE;
        let mut guard = lock.lock().unwrap();
        *guard = false;
        cvar.notify_one();
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_clang_1() {
        let clang = ClangWrapper::new().unwrap();
        let index = clang.get_index();
    }

    #[test]
    fn test_clang_2() {
        {
            let clang = ClangWrapper::new().unwrap();
            let index = clang.get_index();
        }

        let clang = ClangWrapper::new().unwrap();
        let index = clang.get_index();
    }
}
