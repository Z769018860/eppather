#!/usr/bin/env python3
"""Compare the original Lua function and its bounded access projection."""
import argparse
import csv
import re
import subprocess
import tempfile
from pathlib import Path


def function(source: str, name: str) -> str:
    match = re.search(r"\b(?:static\s+int|size_t)\s+" + name + r"\s*\([^)]*\)\s*\{", source)
    if not match:
        raise ValueError("missing original function: " + name)
    depth = 0
    for i in range(source.index("{", match.start()), len(source)):
        depth += (source[i] == "{") - (source[i] == "}")
        if not depth:
            return source[match.start():i + 1]
    raise ValueError("unclosed function: " + name)


def instrument_lua(code: str) -> str:
    code = re.sub(r"\bcheckbuffer\s*\(", "inst_checkbuffer(", code)
    code = code.replace("luaZ_read (", "inst_read (")
    code = code.replace("memcpy(", "counted_copy(")
    code = re.sub(r"z->(n|p)\s*(\-=|\+=)\s*m", r"MEM_RW(z,\1) \2 m", code)
    code = code.replace("z->n++", "MEM_RW(z,n)++").replace("z->p--", "MEM_RW(z,p)--")
    return re.sub(r"z->(n|p)", r"MEM_FIELD(z,\1)", code)


def instrument_projection(code: str) -> str:
    code = code.replace("summary_luaZ_read(", "projection(")
    return re.sub(r"\b(z|src|dst)\s*\[\s*([^\[\]]+)\s*\]", r"MEM_ELEM(\1,\2)", code)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--lua-source", type=Path, required=True)
    ap.add_argument("--projection", type=Path, required=True)
    ap.add_argument("--csv", type=Path, required=True)
    args = ap.parse_args()
    source = args.lua_source.read_text()
    original = function(source, "checkbuffer") + "\n" + function(source, "luaZ_read")
    original = re.sub(r"\bcheckbuffer\s*\(", "original_checkbuffer(", original)
    original = original.replace("luaZ_read (", "original_read (")
    instrumented = instrument_lua(function(source, "checkbuffer") + "\n" + function(source, "luaZ_read"))
    projection = instrument_projection(args.projection.read_text())
    # These assertions stop the experiment if the original function changes.
    assert "if (!checkbuffer(z))" in function(source, "luaZ_read")
    assert "memcpy(b, z->p, m);" in function(source, "luaZ_read")
    assert "z->n -= m;" in function(source, "luaZ_read")
    header = r'''
#include <stddef.h>
#include <stdio.h>
#include <string.h>
typedef struct { size_t n; const unsigned char *p; } ZIO;
#define EOZ (-1)
static int luaZ_fill(ZIO *z) { (void)z; return EOZ; }
static unsigned long accesses;
#define MEM_FIELD(z,f) (*(++accesses, &((z)->f)))
#define MEM_RW(z,f) (*(accesses += 2, &((z)->f)))
#define MEM_ELEM(a,i) (*(++accesses, &((a)[i])))
static void *counted_copy(void *d, const void *s, size_t n) {
  accesses += 2 * n;
  return memcpy(d,s,n);
}
'''
    harness = r'''
int main(void) {
  unsigned char src[4] = {11,12,13,14};
  for (int available=0; available<=3; available++) {
    for (int requested=0; requested<=3; requested++) {
      unsigned char original_dst[4]={0}, instrumented_dst[4]={0};
      int projected_src[4]={11,12,13,14}, projected_dst[4]={0};
      int projected_z[2]={available,0};
      ZIO original_z={(size_t)available,src}, instrumented_z={(size_t)available,src};
      size_t actual=original_read(&original_z,original_dst,(size_t)requested);
      accesses=0;
      size_t same=inst_read(&instrumented_z,instrumented_dst,(size_t)requested);
      unsigned long observed=accesses;
      accesses=0;
      int predicted=projection(projected_z,projected_src,projected_dst,0,requested);
      unsigned long projected=accesses;
      int values_equal=actual==same && actual==(size_t)predicted &&
        original_z.n==instrumented_z.n && original_z.n==(size_t)projected_z[0] &&
        original_z.p==instrumented_z.p && original_z.p==src+projected_z[1];
      for (int i=0;i<4;i++) {
        values_equal=values_equal && original_dst[i]==instrumented_dst[i] &&
          original_dst[i]==projected_dst[i];
      }
      printf("%d,%d,%lu,%lu,%d\n",available,requested,observed,projected,values_equal);
      if (!values_equal || observed!=projected) return 1;
    }
  }
  return 0;
}
'''
    with tempfile.TemporaryDirectory() as d:
        src = Path(d) / "compare.c"
        exe = Path(d) / "compare"
        src.write_text(header + "\n" + original + "\n" + instrumented + "\n" + projection + "\n" + harness)
        subprocess.run(["gcc", "-std=c11", "-O0", "-fsanitize=undefined",
                        "-fno-sanitize-recover=undefined", str(src), "-o", str(exe)], check=True)
        run = subprocess.run([str(exe)], check=True, text=True, capture_output=True)
    args.csv.parent.mkdir(parents=True, exist_ok=True)
    rows = list(csv.DictReader(run.stdout.splitlines(), fieldnames=[
        "available", "requested", "original_source_accesses", "projection_accesses", "same_output_and_state"]))
    with args.csv.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=rows[0].keys())
        writer.writeheader()
        writer.writerows(rows)
    print(f"Compared {len(rows)} defined input cases; all outputs, states, and access counts matched.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
