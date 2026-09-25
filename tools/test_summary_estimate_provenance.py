#!/usr/bin/env python3
"""Regression checks for summary preprocessing and estimate provenance."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import run_small_project_summaries as summaries


class SummaryEstimateTests(unittest.TestCase):
    def test_logical_and_survives_preprocessing(self):
        expression = "i < size - 1 && src[i]"
        self.assertEqual(summaries.normalize_expression(expression, set()), expression)

    def test_approximation_is_never_an_original_estimate(self):
        rows = [dict(project="list", entry="list_rpush", mode="summary",
                     summary_ok="true", slice_mode="type_erased",
                     epat_mode="pafi-rs", worst_mems="0")]
        result = summaries.select_final_rows(rows)[0]
        self.assertEqual(result["model_worst_mems"], "0")
        self.assertEqual(result["worst_mems"], "")
        self.assertEqual(result["validated_worst_mems"], "")
        self.assertEqual(result["estimate_scope"], "approximation_or_unavailable")

    def test_native_original_slice_remains_available(self):
        rows = [dict(project="list", entry="list_new", mode="summary",
                     summary_ok="true", slice_mode="closure",
                     epat_mode="pafi-rs", worst_mems="5")]
        result = summaries.select_final_rows(rows)[0]
        self.assertEqual(result["validated_worst_mems"], "5")
        self.assertEqual(result["worst_mems"], "5")


if __name__ == "__main__":
    unittest.main()
