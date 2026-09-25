#!/usr/bin/env python3
"""Negative controls: remove access-bearing Lua summary operations and find first source mismatch."""
import argparse
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
            cmd = ["python3", str(root / "tools/validate_lua_projection.py"),
                   "--lua-source", str(root / "testcase/lua/lzio.c"),
                   "--projection", str(projection),
                   "--csv", str(Path(tmp) / (name + ".csv"))]
            run = subprocess.run(cmd, text=True, capture_output=True)
            if run.returncode == 0:
                raise AssertionError(name + " unexpectedly matches the original")
            # The validator prints each input before stopping at the first discrepancy.
            mismatches = [line for line in run.stdout.splitlines()
                          if line.startswith(("0,", "1,", "2,", "3,")) and line.endswith(",0")]
            if not mismatches:
                raise AssertionError(name + " failed before producing a source mismatch: " + run.stderr)
            with args.output.open("a") as f:
                f.write(name + "," + mismatches[-1] + "\n")
            print(name, mismatches[-1], flush=True)


if __name__ == "__main__":
    main()
