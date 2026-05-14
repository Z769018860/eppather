use std::cmp::PartialEq;
use std::path::{Path, PathBuf};

/// The file, line, column, and character offset of a source location.
#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct Location {
    /// The file of the source location, if it has any.
    pub file: Option<PathBuf>,
    /// The line of the source location.
    pub line: u32,
    /// The column of the source location.
    pub column: u32,
    /// The character offset of the source location.
    pub offset: u32,
}

/// The file, line, column, and character offset of a source location.
#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct Range {
    /// The start location of the range.
    pub start: Location,
    /// The end location of the range.
    pub end: Location,
}

impl Location {
    pub fn new<F>(file: F, line: u32, column: u32, offset: u32) -> Location
    where
        F: AsRef<Path>,
    {
        Location {
            file: Some(file.as_ref().to_path_buf()),
            line,
            column,
            offset,
        }
    }
}

// XXX: 文件不同时的比较
impl PartialOrd for Location {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        if self.file.is_none() || self.file != other.file {
            return None;
        }

        Some((self.line, self.column).cmp(&(other.line, other.column)))
    }
}

impl From<clang::source::SourceLocation<'_>> for Location {
    fn from(source_location: clang::source::SourceLocation) -> Self {
        let loc = source_location.get_spelling_location();
        Location {
            file: loc.file.map(|f| f.get_path()),
            line: loc.line,
            column: loc.column,
            offset: loc.offset,
        }
    }
}

impl Range {
    pub fn new(start: Location, end: Location) -> Range {
        Range { start, end }
    }

    pub fn contains(&self, loc: &Location) -> bool {
        self.start <= *loc && *loc <= self.end
    }
}

impl From<clang::source::SourceRange<'_>> for Range {
    fn from(source_range: clang::source::SourceRange) -> Self {
        Range {
            start: source_range.get_start().into(),
            end: source_range.get_end().into(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_range() {
        let start = Location {
            file: Some("a.c".into()),
            line: 1,
            column: 2,
            offset: 0,
        };
        let end = Location {
            file: Some("a.c".into()),
            line: 4,
            column: 5,
            offset: 0,
        };
        let range = Range::new(start.clone(), end.clone());
        assert_eq!(range.contains(&start), true);
        assert_eq!(range.contains(&end), true);
        let loc1 = Location {
            file: Some("a.c".into()),
            line: 1,
            column: 6,
            offset: 0,
        };
        let loc2 = Location {
            file: None,
            ..loc1.clone()
        };
        let loc3 = Location {
            line: 5,
            ..loc1.clone()
        };
        assert_eq!(range.contains(&loc1), true);
        assert_eq!(range.contains(&loc2), false);
        assert_eq!(range.contains(&loc3), false);
    }
}
