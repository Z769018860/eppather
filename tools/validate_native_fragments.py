#!/usr/bin/env python3
"""Measure explicitly instrumented original-source fragments, without implying whole-call MEMS."""
import argparse
import csv
import re
import subprocess
import tempfile
from pathlib import Path


def compile_run(source: str, directory: Path, name: str, includes: list[str]) -> list[str]:
    c = directory / (name + ".c")
    exe = directory / name
    c.write_text(source)
    subprocess.run(["gcc", "-std=c11", "-O0", "-fsanitize=undefined",
                    "-fno-sanitize-recover=undefined", *includes, str(c), "-lm", "-o", str(exe)],
                   check=True)
    return subprocess.check_output([str(exe)], text=True).splitlines()


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    ap.add_argument("--csv", type=Path, required=True)
    args = ap.parse_args()
    root = args.root.resolve()
    cjson = (root / "testcase/cJSON/cJSON.c").read_text()
    start = cjson.index("static parse_buffer *buffer_skip_whitespace(")
    end = cjson.index("/* skip the UTF-8 BOM", start)
    fragment = cjson[start:end]
    assert "buffer->offset++;" in fragment and "buffer->offset--;" in fragment
    counted = fragment.replace("buffer_skip_whitespace(", "counted_buffer_skip_whitespace(", 1)
    counted = re.sub(r"buffer->offset(\+\+|--)", r"MEM_RW(buffer,offset)\1", counted)
    counted = re.sub(r"buffer->(content|offset|length)",
                     r"MEM_FIELD(buffer,\1)", counted)
    # Only direct field expressions written in this helper are counted.
    cjson = ("""static unsigned long fragment_accesses;
#define MEM_FIELD(p,f) (*(++fragment_accesses, &((p)->f)))
#define MEM_RW(p,f) (*(fragment_accesses += 2, &((p)->f)))
""" + cjson[:end] + counted + cjson[end:])
    cjson += r"""
#include <stdio.h>
int main(void) {
    static const unsigned char samples[][5] = { "X", " X", "   X", "    " };
    const size_t lengths[] = { 2, 3, 5, 5 };
    for (int i=0; i<4; ++i) {
        parse_buffer a = {0}, b = {0};
        a.content = b.content = samples[i];
        a.length = b.length = lengths[i];
        buffer_skip_whitespace(&a);
        fragment_accesses = 0;
        counted_buffer_skip_whitespace(&b);
        printf("cJSON,%d,%lu,%d\n", i, fragment_accesses,
               a.offset == b.offset && a.length == b.length);
    }
}
"""
    tiny = (root / "testcase/tinyexpr/tinyexpr.c").read_text()
    start = tiny.index("double te_eval(const te_expr *n) {")
    end = tiny.index("case TE_VARIABLE: return *n->bound;", start)
    chunk = tiny[start:end]
    assert "switch(TYPE_MASK(n->type))" in chunk
    assert "case TE_CONSTANT: return n->value;" in chunk
    chunk = chunk.replace("switch(TYPE_MASK(n->type))",
                          "fragment_accesses++; switch(TYPE_MASK(n->type))", 1)
    chunk = chunk.replace("case TE_CONSTANT: return n->value;",
                          "case TE_CONSTANT: fragment_accesses++; return n->value;", 1)
    tiny = "static unsigned long fragment_accesses;\n" + tiny[:start] + chunk + tiny[end:]
    tiny += r"""
#include <stdio.h>
int main(void) {
    const char *samples[] = { "2", "1+2", "3.5" };
    for (int i=0; i<3; ++i) {
        int error = 0;
        te_expr *tree = te_compile(samples[i], 0, 0, &error);
        if (!tree || error) return 3;
        fragment_accesses = 0;
        double value = te_eval(tree);
        printf("tinyexpr,%d,%lu,%d\n", i, fragment_accesses, value == (i == 0 ? 2.0 : i == 1 ? 3.0 : 3.5));
        te_free(tree);
    }
}
"""
    # Negative controls remove a specific access-bearing source operation.
    ablated_loop = counted.replace(
        "MEM_RW(buffer,offset)++;", "break;")
    assert ablated_loop != counted
    cjson_ablated = cjson.replace(counted, ablated_loop, 1)
    assert cjson_ablated != cjson
    tiny_ablated = tiny.replace(
        "case TE_CONSTANT: fragment_accesses++; return n->value;",
        "case TE_CONSTANT: return 0.0;", 1)
    assert tiny_ablated != tiny
    with tempfile.TemporaryDirectory() as temp:
        d = Path(temp)
        rows = []
        for project, source, headers in [
            ("cJSON", cjson, ["-I" + str(root / "testcase/cJSON")]),
            ("tinyexpr", tiny, ["-I" + str(root / "testcase/tinyexpr")]),
        ]:
            for line in compile_run(source, d, project, headers):
                tag, case, count, equal = line.split(",")
                rows.append(dict(project=tag, case=int(case),
                                 direct_fragment_accesses=int(count), same_source_behavior=int(equal)))
        for project, source, headers in [
            ("cJSON", cjson_ablated, ["-I" + str(root / "testcase/cJSON")]),
            ("tinyexpr", tiny_ablated, ["-I" + str(root / "testcase/tinyexpr")]),
        ]:
            for line in compile_run(source, d, project + "_ablation", headers):
                tag, case, count, equal = line.split(",")
                row = next(r for r in rows if r["project"] == tag and r["case"] == int(case))
                row["ablated_direct_accesses"] = int(count)
                row["ablated_same_behavior"] = int(equal)
    assert len(rows) == 7 and all(r["same_source_behavior"] == 1 for r in rows)
    assert sum(r["ablated_same_behavior"] == 0 for r in rows) == 6
    args.csv.parent.mkdir(parents=True, exist_ok=True)
    with args.csv.open("w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0]))
        w.writeheader()
        w.writerows(rows)
    for row in rows:
        print(row, flush=True)


if __name__ == "__main__":
    main()
