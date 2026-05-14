//! AST的节点定义

use clang::{Entity, EntityKind};

type P<T> = Box<T>;

pub struct Func<'a> {
    entity: Entity<'a>,
}

#[derive(Clone, Debug)]
pub struct Stmt<'a> {
    pub entity: Entity<'a>,
    pub kind: StmtKind<'a>,
}

impl<'a> Stmt<'a> {
    pub fn new(stmt: Entity<'a>) -> Self {
        assert!(stmt.is_statement());

        Self {
            entity: stmt,
            kind: StmtKind::new(stmt),
        }
    }
}

#[derive(Clone, Debug)]
pub enum StmtKind<'a> {
    If(P<Expr<'a>>, P<Stmt<'a>>, Option<P<Stmt<'a>>>),
    // more stmt
    Other(),
}

#[derive(Clone, Debug)]
pub struct Expr<'a> {
    pub entity: Entity<'a>,
    pub kind: ExprKind<'a>,
}

impl<'a> Expr<'a> {
    pub fn new(expr: Entity<'a>) -> Self {
        assert!(expr.is_expression());

        Self {
            entity: expr,
            kind: ExprKind::new(expr),
        }
    }
}

#[derive(Clone, Debug)]
pub enum ExprKind<'a> {
    // 我设定的表达式
    Assign(P<Expr<'a>>, P<Expr<'a>>),
    // 二元表达式
    Binary(P<Expr<'a>>, P<Expr<'a>>, String),
    // more expr
    Other(),
}

impl<'a> StmtKind<'a> {
    pub fn new(stmt: Entity<'a>) -> Self {
        match stmt.get_kind() {
            EntityKind::IfStmt => Self::new_if(stmt),
            _ => StmtKind::Other(),
        }
    }

    pub fn new_if(if_stmt: Entity<'a>) -> Self {
        let children = if_stmt.get_children();

        match children.len() {
            2 => StmtKind::If(
                P::new(Expr::new(children[0])),
                P::new(Stmt::new(children[1])),
                None,
            ),
            3 => StmtKind::If(
                P::new(Expr::new(children[0])),
                P::new(Stmt::new(children[1])),
                Some(P::new(Stmt::new(children[2]))),
            ),
            _ => panic!("Invalid number of children for IfStmt: {}", children.len()),
        }
    }
}

impl<'a> ExprKind<'a> {
    pub fn new(expr: Entity<'a>) -> Self {
        match expr.get_kind() {
            EntityKind::BinaryOperator => Self::new_binary_operator(expr),
            _ => ExprKind::Other(),
        }
    }

    pub fn new_binary_operator(binary_operator: Entity<'a>) -> Self {
        let op = match binary_operator.get_display_name() {
            Some(op) => op,
            None => panic!("BinaryOperator has no display name"),
        };
        let children = binary_operator.get_children();
        match children.len() {
            2 => {
                if "=" == op {
                    ExprKind::Assign(
                        P::new(Expr::new(children[0])),
                        P::new(Expr::new(children[1])),
                    )
                } else {
                    ExprKind::Binary(
                        P::new(Expr::new(children[0])),
                        P::new(Expr::new(children[1])),
                        op,
                    )
                }
            }
            _ => panic!(
                "Invalid number of children for BinaryOperator: {}",
                children.len()
            ),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
}
