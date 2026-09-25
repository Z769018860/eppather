#!/usr/bin/env python3
"""Negative controls: remove access-bearing Lua summary operations and find first source mismatch."""
import argparse
import csv
import subprocess
import tempfile
from pathlib import Path


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    root = args.root.resolve()
    original = (root / "testcase/llm_calibrated/lua_zread_summary.c").read_text()
    variants = {
        "no_byte_copy": original.replace("dst[b + i] = src[p + i];", "/* ablated byte copy */"),
        "no_zio_state_update": original.replace("z[0] = z[0] - m;", "/* ablated remaining-byte update */")
                            .replace("z[1] = z[1] + m;", "/* ablated pointer advance */"),
    }
    assert all(body != original for body in variants.values())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory() as tmp:
        for name, source in variants.items():
            projection = Path(tmp) / (name + ".c")
            projection.write_text(source)
            out = Path(tmp) / (name + ".csv")
            cmd = ["python3", str(root / "tools/validate_lua_projection.py"),
                   "--lua-source", str(root / "testcase/lua/lzio.c"),
                   "--projection", str(projection), "--allow-mismatch",
                   "--csv", str(out)]
            subprocess.run(cmd, check=True)
            with out.open(newline="") as f:
                rows = list(csv.DictReader(f))
            mismatch = [r for r in rows if r["original_source_accesses"] != r["projection_accesses"]
                        or r["same_output_and_state"] != "1"]
            if not mismatch:
                raise AssertionError(name + " unexpectedly matches the original")
            first = mismatch[0]
            with args.output.open("a") as f:
                f.write(",".join([name, str(len(mismatch)), first["available"],
                                  first["requested"], first["original_source_accesses"],
                                  first["projection_accesses"], first["same_output_and_state"]]) + "\\n")
            print(name, len(mismatch), "mismatches; first", first, flush=True)



if __name__ == "__main__":
    main()
