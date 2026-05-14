use std::{
    fmt::Debug,
    iter::Iterator,
    path::{Path, PathBuf},
};

use anyhow::Result;
use scraper::{selectable::Selectable, ElementRef, Html, Selector};

use crate::ast::source::Location;

#[derive(Debug)]
pub struct Report {
    rpt_file: PathBuf,     // 报告的路径
    file: Option<PathBuf>, // 报告中bug所在的文件
    msgs: Vec<Msg>,        // 报告中的消息列表，按照idx排序
                           // start: Option<Location>, // 报告开始的位置
                           // end: Option<Location>,   // 报告结束的位置
}

#[derive(Debug, Clone)]
pub struct Msg {
    pub kind: MsgKind,
    pub idx: u32,
    pub msg: String,
    pub loc: Option<Location>,
}

impl Msg {
    pub fn get_branch(&self) -> Option<bool> {
        if self.msg == "Taking true branch" {
            Some(true)
        } else if self.msg == "Taking false branch" {
            Some(false)
        } else {
            None
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MsgKind {
    Control,
    Event,
}

impl Report {
    pub fn new<F: AsRef<Path>>(file: F) -> Result<Report> {
        let mut ret = Report {
            rpt_file: file.as_ref().to_path_buf(),
            file: None,
            msgs: vec![],
        };

        ret.read_report()?;

        Ok(ret)
    }

    // XXX: 可能有多个文件
    // pub fn get_source(&self) -> Result<String> {
    // }

    /// 获取报告中包含的所有文件
    pub fn get_files(&self) -> Vec<PathBuf> {
        // FIXME: 报告涉及多个文件时
        vec![self.file.clone().unwrap()]
    }

    /// 临时函数：获取报告中包含的文件
    pub fn get_file(&self) -> Option<PathBuf> {
        self.file.clone()
    }

    pub fn get_start_position(&self) -> Option<Location> {
        self.msgs.first().and_then(|msg| msg.loc.clone())
    }

    pub fn get_end_position(&self) -> Option<Location> {
        self.msgs.last().and_then(|msg| msg.loc.clone())
    }

    pub fn iter_ctrl(&self) -> impl Iterator<Item = Msg> {
        self.msgs
            .clone()
            .into_iter()
            .filter(|msg| msg.kind == MsgKind::Control)
    }

    /// 内部函数，读取报告产生缓存
    fn read_report(&mut self) -> Result<()> {
        // 预定义的selector
        let td = Selector::parse("td").unwrap();
        let div_msg = Selector::parse("div.msg").unwrap();
        let table_simple = Selector::parse("table.simpletable").unwrap();

        let text = std::fs::read_to_string(&self.rpt_file)?;
        let document = Html::parse_document(&text);

        // 获取文件名
        let table = document.select(&table_simple).next().unwrap();
        let file = table.select(&td).nth(1).unwrap().text().next().unwrap();
        self.file = Some(file.into());

        // 获取所有的msg
        for msg in document.select(&div_msg) {
            // FIXME: 从html报告中只能获取到行号
            // XXX: 单元测试
            let tr = msg.parent().unwrap().parent().unwrap();
            let mut sibling = tr.prev_sibling();
            let line = loop {
                if let Some(sibling_node) = sibling {
                    if let Some(element) = ElementRef::wrap(sibling_node) {
                        if let Some(line) = element.attr("data-linenumber") {
                            break Some(line); // 退出循环并返回 line 的值
                        }
                    }
                    sibling = sibling_node.prev_sibling();
                } else {
                    break None; // 如果没有更多的兄弟节点，退出循环并返回 None
                }
            };
            let loc = line.and_then(|line| {
                if let Ok(line) = line.parse::<u32>() {
                    Some(Location {
                        file: self.file.clone(), // FIXME: 报告中多文件名时
                        line,
                        column: 0, // FIXME: HTML报告中只有行号
                        offset: 0,
                    })
                } else {
                    None
                }
            });
            let mut text = msg.text();
            let class = msg.attr("class").unwrap();
            let kind = if class.ends_with("l") {
                MsgKind::Control
            } else {
                MsgKind::Event
            };
            let idx = text.next().unwrap();
            let idx = idx.parse::<u32>()?;
            let msg = if idx == 1 { text.nth(0) } else { text.nth(1) };
            let msg = msg.unwrap().to_string();
            self.msgs.push(Msg {
                kind,
                idx,
                msg,
                loc,
            });
        }

        self.msgs.sort_by_key(|msg| msg.idx);

        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use std::env;

    use super::*;

    #[test]
    fn test_read_report() -> Result<()> {
        Ok(())
    }

    // XXX: 更多读取报告的测试

    #[test]
    fn test_scraper() -> Result<()> {
        let html = r#"  
        <div>  
            <p>First paragraph</p>  
            <p>Second paragraph</p>  
            <p>Third paragraph</p>  
        </div>  
        "#;

        // 解析 HTML 文档
        let document = Html::parse_fragment(html);

        // 定义选择器，用于选择第一个 <p> 元素
        let selector = Selector::parse("p").unwrap();

        // 查找第一个 <p> 元素
        if let Some(first_paragraph) = document.select(&selector).next() {
            // 打印第一个 <p> 元素的文本
            println!(
                "First paragraph: {}",
                first_paragraph.text().collect::<Vec<_>>().join("")
            );

            // 获取并打印所有后续兄弟节点
            let mut sibling = first_paragraph.next_sibling();
            while let Some(sibling_node) = sibling {
                if let Some(element) = ElementRef::wrap(sibling_node) {
                    if element.value().name() == "p" {
                        println!(
                            "Next paragraph: {}",
                            element.text().collect::<Vec<_>>().join("")
                        );
                    }
                }
                sibling = sibling_node.next_sibling();
            }
        }

        Ok(())
    }
}
