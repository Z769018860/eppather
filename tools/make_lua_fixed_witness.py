#!/usr/bin/env python3
"""Create a self-contained, fixed-input Eppather witness from the projection."""
import argparse
from pathlib import Path


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--projection", type=Path, required=True)
    ap.add_argument("--available", type=int, required=True)
    ap.add_argument("--requested", type=int, required=True)
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    if not (0 <= args.available <= 3 and 0 <= args.requested <= 3):
        ap.error("the validated domain is 0..3")
    source = args.projection.read_text()
    needle = "int summary_luaZ_read(int *z, int *src, int *dst, int b, int n)"
    if source.count(needle) != 1:
        raise SystemExit("projection signature changed")
    body = source[source.index("{", source.index(needle)) + 1:source.rindex("}")]
    initializers = "\n".join([
        "    int z[2];", "    int src[4];", "    int dst[4];", "    int b;", "    int n;",
        f"    z[0] = {args.available};", "    z[1] = 0;",
        "    src[0] = 11;", "    src[1] = 12;", "    src[2] = 13;", "    src[3] = 14;",
        "    dst[0] = 0;", "    dst[1] = 0;", "    dst[2] = 0;", "    dst[3] = 0;",
        "    b = 0;", f"    n = {args.requested};",
    ])
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(
        "/* 10 caller-owned array initialization writes. Subtract 10 from MEMS. */\n"
        "int main(void)\n{\n" + initializers + "\n" + body + "\n}\n"
    )


if __name__ == "__main__":
    main()
