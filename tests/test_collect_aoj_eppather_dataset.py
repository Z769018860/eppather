import importlib.util
import pathlib
import sys
import unittest

PATH = pathlib.Path(__file__).parents[1] / "tools" / "collect_aoj_eppather_dataset.py"
SPEC = importlib.util.spec_from_file_location("collector", PATH)
collector = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = collector
SPEC.loader.exec_module(collector)


class CollectorTest(unittest.TestCase):
    def test_compatible_array_pointer_program(self):
        src = "#include <stdio.h>\nint main(void){int n=1; int a[10]; int *p=a; scanf(\"%d\",p); printf(\"%d\\n\",a[n-1]); return 0;}"
        result = collector.compatibility(src)
        self.assertTrue(result.accepted, result.reasons)
        self.assertIn("array", result.features)
        self.assertIn("pointer", result.features)

    def test_rejects_known_unsupported_constructs(self):
        for src in ("int main(){struct X{x;} v;}", "int main(){int n; int a[n];}",
                    "int main(){int *p=malloc(4);}", "int main(){switch(1){case 1:break;}}"):
            self.assertFalse(collector.compatibility(src).accepted, src)

    def test_api_shape_helpers(self):
        self.assertEqual(collector.records({"content": [{"judgeId": 7}]}), [{"judgeId": 7}])
        self.assertEqual(collector.source_from_review({"data": {"sourceCode": "int x;"}}), "int x;")
        self.assertEqual(collector.test_count({"headers": [{}, {}]}), 2)
        self.assertEqual(collector.test_io({"data": {"input": "1\n", "output": "2\n"}}), ("1\n", "2\n"))


if __name__ == "__main__":
    unittest.main()
