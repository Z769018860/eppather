#!/usr/bin/env python3
"""Fixed-input original-source vs Eppather comparison for list and inih.

Counts include reads and writes of the source function's fields/array elements;
caller initialization is reported separately. No whole-program maximum is implied.
"""
import argparse
import csv
import re
import subprocess
import tempfile
from pathlib import Path


def compile_c(paths, output, includes=()):
    subprocess.run(["gcc", "-std=c11", "-O0", "-fsanitize=undefined",
                    "-fno-sanitize-recover=undefined", *("-I" + str(p) for p in includes),
                    *(str(p) for p in paths), "-o", str(output)], check=True)


def function_bounds(source, name):
    match = re.search(r"\b" + name + r"\s*\([^)]*\)\s*\{", source)
    if not match:
        raise ValueError(name)
    begin = source.index("{", match.start())
    depth = 0
    for pos in range(begin, len(source)):
        depth += (source[pos] == "{") - (source[pos] == "}")
        if not depth:
            return begin, pos + 1
    raise ValueError("unclosed function " + name)


def list_source(root, temp):
    directory = root / "testcase/clib/src"
    source = (directory / "list.c").read_text()
    begin, end = function_bounds(source, "list_rpush")
    body = source[begin:end]
    assert "++self->len" in body and "self->tail->next" in body
    body = body.replace("++self->len", "++MEM_RW(self,len)")
    body = body.replace("self->tail->next", "MEM_FIELD(MEM_FIELD(self,tail),next)")
    body = re.sub(r"\b(self|node)->([A-Za-z_][A-Za-z0-9_]*)", r"MEM_FIELD(\1,\2)", body)
    prefix = """#include <stddef.h>
unsigned long measured_accesses;
#define MEM_FIELD(p,f) (*(++measured_accesses, &((p)->f)))
#define MEM_RW(p,f) (*(measured_accesses += 2, &((p)->f)))
"""
    generated = temp / "list_instrumented.c"
    generated.write_text(prefix + source[:begin] + body + source[end:])
    harness = temp / "list_harness.c"
    harness.write_text('''#include "list.h"
#include <stdio.h>
#include <stdlib.h>
extern unsigned long measured_accesses;
int main(void) {
  list_t list = {0};
  list_node_t prior = {0}, added = {0};
  for (int mode=0; mode<3; ++mode) {
    list.len = mode==2;
    list.head = list.tail = mode==2 ? &prior : NULL;
    prior.next = prior.prev = added.next = added.prev = NULL;
    measured_accesses=0;
    list_node_t *result = list_rpush(&list, mode==0 ? NULL : &added);
    printf("%d,%lu,%d,%u,%d,%d,%d\\n", mode, measured_accesses,
      result==((mode==0)?NULL:&added), list.len,
      list.head==&added, list.tail==&added, prior.next==&added);
  }
}
''')
    exe = temp / "list_measured"
    compile_c([generated, directory / "list_node.c", directory / "list_iterator.c", harness], exe, [directory])
    lines = subprocess.check_output([str(exe)], text=True).splitlines()
    # Assert the original, uninstrumented function has identical outputs/state.
    plain = temp / "list_plain.c"
    plain.write_text(source.replace('#include "list.h"', '#include "list.h"\nunsigned long measured_accesses;'))
    control = temp / "list_control"
    compile_c([plain, directory / "list_node.c", directory / "list_iterator.c", harness], control, [directory])
    controls = subprocess.check_output([str(control)], text=True).splitlines()
    assert [line.split(",")[2:] for line in lines] == [line.split(",")[2:] for line in controls]
    return {int(line.split(",")[0]): int(line.split(",")[1]) for line in lines}


def inih_source(root, temp):
    source = (root / "testcase/inih/ini.c").read_text()
    begin, end = function_bounds(source, "ini_strncpy0")
    body = source[begin:end]
    body = re.sub(r"\b(src|dest)\[i\]", r"MEM_ELEM(\1,i)", body)
    assert body.count("MEM_ELEM(") == 4
    prefix = """unsigned long measured_accesses;
#define MEM_ELEM(p,i) (*(++measured_accesses, &((p)[i])))
"""
    wrapper = '''
#include <stdio.h>
int main(void) {
  for (int size=1;size<=3;size++) for(int len=0;len<=2;len++) {
    char src[4]={'x','x',0,0}, dst[4]={0};
    src[len]=0;
    measured_accesses=0;
    char *ret=ini_strncpy0(dst,src,(size_t)size);
    printf("%d,%d,%lu,%d,%d,%d,%d\\n",size,len,measured_accesses,ret==dst,
      dst[0],dst[1],dst[2]);
  }
}
'''
    instrumented = temp / "inih_instrumented.c"
    instrumented.write_text(prefix + source[:begin] + body + source[end:] + wrapper)
    plain = temp / "inih_plain.c"
    plain.write_text("unsigned long measured_accesses;\n" + source + wrapper)
    outputs = []
    for path in (instrumented, plain):
        exe = temp / path.stem
        compile_c([path], exe, [root / "testcase/inih"])
        outputs.append(subprocess.check_output([str(exe)], text=True).splitlines())
    assert [x.split(",")[3:] for x in outputs[0]] == [x.split(",")[3:] for x in outputs[1]]
    return {(int(parts[0]),int(parts[1])):int(parts[2])
            for line in outputs[0] for parts in [line.split(",")]}


def sds_source(root, temp):
    directory = root / "testcase/sds"
    header = (directory / "sds.h").read_text()
    source = (directory / "sds.c").read_text()
    begin, end = function_bounds(header, "sdssetlen")
    body = header[begin:end]
    assert "unsigned char flags = s[-1];" in body
    body = body.replace("unsigned char flags = s[-1];",
                        "unsigned char flags = MEM_ELEM(s,-1);")
    body = body.replace("*fp = SDS_TYPE_5", "MEM_DEREF(fp) = SDS_TYPE_5")
    for typ in (8, 16, 32, 64):
        body = body.replace(f"SDS_HDR({typ},s)->len = newlen;",
                            f"MEM_HDR(SDS_HDR({typ},s),len) = newlen;")
    assert body.count("MEM_HDR(") == 4
    modified_header = header[:begin] + body + header[end:]
    begin, end = function_bounds(source, "sdsclear")
    body = source[begin:end]
    assert "s[0] = '\\0';" in body
    body = body.replace("s[0] = '\\0';", "MEM_ELEM(s,0) = '\\0';")
    modified_source = source[:begin] + body + source[end:]
    prelude = '''unsigned long measured_accesses;
#define MEM_ELEM(p,i) (*(++measured_accesses, &((p)[i])))
#define MEM_DEREF(p) (*(++measured_accesses, &(p)[0]))
#define MEM_HDR(p,f) (*(++measured_accesses, &((p)->f)))
'''
    header_dir = temp / "sds_header"
    header_dir.mkdir()
    (header_dir / "sds.h").write_text(modified_header)
    (header_dir / "sdsalloc.h").write_text((directory / "sdsalloc.h").read_text())
    measured_source = temp / "sds_instrumented.c"
    measured_source.write_text(prelude + modified_source)
    plain_source = temp / "sds_plain.c"
    plain_source.write_text("unsigned long measured_accesses;\n" + source)
    harness = temp / "sds_harness.c"
    harness.write_text('''#include "sds.h"
#include <stdio.h>
extern unsigned long measured_accesses;
int main(void) {
  for (int typ=0;typ<2;typ++) {
    sds s=typ ? sdsnewlen(NULL,40) : sdsnew("abc");
    if (!s) return 2;
    s[0]='a';
    measured_accesses=0;
    sdsclear(s);
    unsigned long count=measured_accesses;
    printf("%d,%lu,%d,%d\\n",typ,count,sdslen(s)==0,s[0]==0);
    sdsfree(s);
  }
}
''')
    outputs=[]
    for name, impl, include in (("sds_measured",measured_source,header_dir),
                                ("sds_control",plain_source,directory)):
        exe=temp/name
        compile_c([impl,harness],exe,[include])
        outputs.append(subprocess.check_output([str(exe)],text=True).splitlines())
    assert [line.split(",")[2:] for line in outputs[0]] == [line.split(",")[2:] for line in outputs[1]]
    return {int(line.split(",")[0]):int(line.split(",")[1]) for line in outputs[0]}


def fixed_list(mode):
    # list[0]=len, [1]=head, [2]=tail; node[0]=next, [1]=prev.
    # old[0] is the old tail's next, and list[2]=0 denotes old.
    return f'''int main(void) {{
  int list[3]; int node[2]; int old[2]; int valid;
  list[0]={int(mode==2)}; list[1]=0; list[2]=0;
  node[0]=0; node[1]=0; old[0]=0; old[1]=0;
  valid={int(mode!=0)};
  if (!valid) {{return 0;}}
  if (list[0]) {{
    node[1]=list[2]; node[0]=0; old[list[2]]=1; list[2]=1;
  }} else {{
    list[2]=1; list[1]=1; node[0]=0; node[1]=0;
  }}
  list[0]=list[0]+1;
  return 1;
}}
'''


def fixed_inih(size, length):
    return f'''int main(void) {{
  int src[4]; int dst[4]; int i; int size;
  src[0]={int(length>0)}; src[1]={int(length>1)}; src[2]=0; src[3]=0;
  dst[0]=0; dst[1]=0; dst[2]=0; dst[3]=0;
  size={size}; i=0;
  while (i<size-1 && src[i]) {{dst[i]=src[i]; i=i+1;}}
  dst[i]=0;
  return 0;
}}
'''


def fixed_sds(typ):
    return f'''int main(void) {{
  int s[3]; int flags;
  s[0]={1 if typ else 24}; s[1]={40 if typ else 3}; s[2]=97;
  flags=s[0];
  if (flags == 24) {{s[0]=0;}} else {{s[1]=0;}}
  s[2]=0;
  return 0;
}}
'''


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    p.add_argument("--cnip", type=Path, required=True)
    p.add_argument("--output-dir", type=Path, required=True)
    args = p.parse_args()
    root=args.root.resolve(); out=args.output_dir.resolve(); out.mkdir(parents=True,exist_ok=True)
    rows=[]
    with tempfile.TemporaryDirectory() as scratch:
        temp=Path(scratch)
        cases=[]
        for mode, expected in list_source(root,temp).items():
            cases.append(("list","list_rpush",str(mode),expected,7,fixed_list(mode)))
        for (size,length), expected in inih_source(root,temp).items():
            cases.append(("inih","ini_strncpy0",f"{size}-{length}",expected,8,fixed_inih(size,length)))
        for typ, expected in sds_source(root,temp).items():
            cases.append(("SDSLib","sdsclear",str(typ),expected,3,fixed_sds(typ)))
        for project,function,case,expected,caller,source in cases:
            fixture=out/(project+"_"+case+".c");fixture.write_text(source)
            run=subprocess.run([str(args.cnip.resolve()),"-q","--maxloop","4","--maxpaths","20",str(fixture)],
                               capture_output=True,text=True,timeout=60)
            (out/(fixture.stem+".log")).write_text(run.stdout+run.stderr)
            m=re.search(r"^\[DFS MAX MEMS\]:\s*(\d+)\s*$",run.stdout,re.M)
            total=int(m.group(1)) if m else None
            row=dict(project=project,function=function,case=case,source_accesses=expected,
                     eppather_total=total,caller_initialization=caller,
                     eppather_function=total-caller if total is not None else None,
                     matched=(total-caller==expected and run.returncode==0) if total is not None else False)
            rows.append(row);print(row,flush=True)
    with (out/"small_project_fixed_comparison.csv").open("w",newline="") as f:
        writer=csv.DictWriter(f,fieldnames=list(rows[0]));writer.writeheader();writer.writerows(rows)
    return 0 if all(row["matched"] for row in rows) else 1


if __name__ == "__main__":
    raise SystemExit(main())
