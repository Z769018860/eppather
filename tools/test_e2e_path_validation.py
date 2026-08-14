import importlib.util
import sys
from pathlib import Path

MODULE_PATH = Path(__file__).with_name("e2e_path_validation.py")
SPEC = importlib.util.spec_from_file_location("e2e", MODULE_PATH)
e2e = importlib.util.module_from_spec(SPEC)
sys.modules["e2e"] = e2e
assert SPEC.loader
SPEC.loader.exec_module(e2e)


def test_unsigned_z3_int_is_normalized():
    assert e2e.signed_int32(2147485700) == -2147481596
    assert e2e.signed_int32(4294967295) == -1
    assert e2e.signed_int32(7) == 7


def test_model_parser_completes_unconstrained_parameter():
    assert e2e.parse_model("int x = 4294967295\n", ["x", "y"]) == {"x": -1, "y": 0}


def test_path_decisions_preserve_order():
    assert e2e.expected_outcomes("@(x > 0); x++; @(!(x == 2));") == [1, 0]


def test_signature_parser():
    assert e2e.parse_signature("int solve(int x, int y) { return x+y; }", None) == ("solve", ["x", "y"])


def test_loop_instrumentation_enforces_bound():
    code = e2e.instrument_conditions("int f(int x){while(x){x=x-1;}return x;}", 1)
    assert "EPP_LOOP_TRACE" in code
