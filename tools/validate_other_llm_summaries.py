#!/usr/bin/env python3
"""Source behavior witnesses for legacy LLM summaries; no MEMS equivalence implied."""
import argparse
import csv
import subprocess
import tempfile
from pathlib import Path


def build(source: Path, exe: Path, args: list[str]) -> None:
    subprocess.run(["gcc", "-std=c11", "-O0", "-fsanitize=undefined",
                    "-fno-sanitize-recover=undefined", str(source), *args,
                    "-o", str(exe)], check=True)


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    ap.add_argument("--csv", type=Path, required=True)
    args = ap.parse_args()
    root = args.root.resolve()
    cases = [
        ("cJSON", "null", 1),
        ("cJSON", "xxxx", 1),
        ("cJSON", " 0", 1),
        ("tinyexpr", "1+2", 1),
        ("tinyexpr", "2", 1),
    ]
    with tempfile.TemporaryDirectory() as tmp:
        d = Path(tmp)
        native_c = d / "native.c"
        native_c.write_text(r"""
#include <stdio.h>
#include <string.h>
#include "cJSON.h"
#include "tinyexpr.h"
int main(int argc, char **argv) {
    if (argc != 3) return 2;
    if (strcmp(argv[1], "cJSON") == 0) {
        cJSON *v = cJSON_ParseWithLengthOpts(argv[2], strlen(argv[2]) + 1, NULL, 0);
        printf("%d\n", v != NULL);
        cJSON_Delete(v);
    } else {
        int error = 0;
        double v = te_interp(argv[2], &error);
        printf("%.17g\n", v);
    }
    return 0;
}
""")
        build(native_c, d / "native", [
            "-I" + str(root / "testcase/cJSON"),
            "-I" + str(root / "testcase/tinyexpr"),
            str(root / "testcase/cJSON/cJSON.c"),
            str(root / "testcase/tinyexpr/tinyexpr.c"), "-lm"])
        c_h = d / "c_summary.c"
        c_h.write_text((root / "testcase/llm_summaries/cjson_parse_summary.c").read_text() + r"""
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
    int c[4] = {0};
    size_t n = strlen(argv[1]) + 1;
    for (int i = 0; i < 4 && i < (int)n; ++i) c[i] = (unsigned char)argv[1][i];
    printf("%d\n", summary_cJSON_ParseWithLengthOpts((int)n, 0, 0, 0, 1, atoi(argv[2]),
           c[0], c[1], c[2], c[3]));
    return 0;
}
""")
        build(c_h, d / "c_summary", [])
        t_h = d / "t_summary.c"
        t_h.write_text((root / "testcase/llm_summaries/tinyexpr_interp_summary.c").read_text() + r"""
#include <stdio.h>
int main(int argc, char **argv) {
    int c[8] = {0};
    for (int i = 0; i < 8 && argv[1][i]; ++i) c[i] = (unsigned char)argv[1][i];
    printf("%d\n", summary_te_interp(c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7]));
    return 0;
}
""")
        build(t_h, d / "t_summary", [])
        rows = []
        for project, expression, assumed_parse_success in cases:
            native = subprocess.check_output([str(d / "native"), project, expression], text=True).strip()
            summary_cmd = ([str(d / "c_summary"), expression, str(assumed_parse_success)]
                           if project == "cJSON" else [str(d / "t_summary"), expression])
            model = subprocess.check_output(summary_cmd, text=True).strip()
            equal = float(native) == float(model)
            rows.append(dict(project=project, input=expression, source_result=native,
                             legacy_summary_result=model, same_result=equal,
                             note="assumed parse_success=1" if project == "cJSON" else "ASCII return"))
    args.csv.parent.mkdir(parents=True, exist_ok=True)
    with args.csv.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    for row in rows:
        print(row, flush=True)
    if not any(r["project"] == "cJSON" and not r["same_result"] for r in rows):
        raise AssertionError("expected cJSON discrepancy not reproduced")
    if not any(r["project"] == "tinyexpr" and not r["same_result"] for r in rows):
        raise AssertionError("expected tinyexpr discrepancy not reproduced")


if __name__ == "__main__":
    main()
