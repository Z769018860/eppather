#!/usr/bin/env bash
set -euo pipefail
repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
tmp_bin="$(mktemp "${TMPDIR:-/tmp}/eppather-loop-bound.XXXXXX")"
trap 'rm -f "$tmp_bin"' EXIT
"${CXX:-c++}" -std=c++14 -Wall -Wextra -pedantic \
  "$repo_root/tests/loop_bound_predictor_test.cpp" -o "$tmp_bin"
"$tmp_bin"
echo "loop-bound predictor tests passed"
