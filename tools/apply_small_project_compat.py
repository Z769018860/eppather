#!/usr/bin/env python3
from pathlib import Path

ROOT = Path.cwd()
EPAT = ROOT / "C" / "syntax" / "EpatRunner.cpp"

def read(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="ignore")

def write(path: Path, text: str) -> None:
    path.write_text(text, encoding="utf-8")

def main() -> int:
    if not (ROOT / "CMakeLists.txt").exists():
        raise SystemExit("Please run from the eppather repository root.")

    s = read(EPAT)

    old = 'if (containsAny(line, {"->", "(*", "?", "[", "]"})) {'
    new = 'if (containsAny(line, {"->", "?"})) {'
    if old in s:
        s = s.replace(old, new, 1)

    old_block = '''    if (line.find("typedef") != std::string::npos ||
        line.find("struct ") != std::string::npos ||
        line.find("union ") != std::string::npos ||
        line.find("enum ") != std::string::npos ||
        line.find("*") != std::string::npos ||
        line.find("[") != std::string::npos ||
        line.find("]") != std::string::npos ||
        line.find("->") != std::string::npos ||
        line.find(".") != std::string::npos ||
        line.find("(") != std::string::npos ||
        line.find(")") != std::string::npos) {
        return false;
    }
'''
    new_block = '''    if (line.find("typedef") != std::string::npos ||
        line.find("struct ") != std::string::npos ||
        line.find("union ") != std::string::npos ||
        line.find("enum ") != std::string::npos ||
        line.find("->") != std::string::npos ||
        line.find(".") != std::string::npos ||
        line.find("(") != std::string::npos ||
        line.find(")") != std::string::npos) {
        return false;
    }
'''
    if old_block in s:
        s = s.replace(old_block, new_block, 1)

    if "sanitizePrefixForEpat" not in s:
        raise SystemExit(
            "sanitizePrefixForEpat was not found. Run apply_epat_prefix_and_exception_fix.py first, "
            "then run this script."
        )

    write(EPAT, s)
    print("[OK] updated EpatRunner.cpp to preserve int pointers and int arrays")
    print("[NEXT] cmake --build build -j")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
