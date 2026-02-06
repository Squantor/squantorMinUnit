/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2020-2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file minunit.c
 * @brief Minimal C/C++ unittesting framework
 * @version 20260206
 *
 * Minimal C++ unittesting framework, based on:
 * https://github.com/siu/minunit
 * Further inspiration drawn from:
 * https://github.com/ollelogdahl/ihct
 */
#include <minunit.h>

Minunit_tests_table default_test_table = {0};

Minunit_state minunit_test_state;

void minunit_add_test(Minunit_tests_table *table, void (*body)(Minunit_state *test_results),
                      void (*setup)(Minunit_state *test_results), void (*teardown)(Minunit_state *test_results)) {
  if (table->testcount < MINUNIT_MAX_TESTS - 1) {
    table->tests[table->testcount].body = body;
    table->tests[table->testcount].setup = setup;
    table->tests[table->testcount].teardown = teardown;
    table->testcount++;
  }
}

int minunit_run(void) {
  return minunit_run_table_callback(&default_test_table, NULL);
}

int minunit_run_callback(Intra_test_callback callback) {
  return minunit_run_table_callback(&default_test_table, callback);
}

int minunit_run_table_callback(Minunit_tests_table *table, Intra_test_callback callback) {
  minunit_test_state.executed = 0;
  minunit_test_state.failures = 0;
  minunit_test_state.checks = 0;
  for (int i = 0; i < table->testcount; i++) {
    if (table->tests[i].setup != NULL)
      table->tests[i].setup(&minunit_test_state);
    if (minunit_test_state.flag_fail == 0) {
      table->tests[i].body(&minunit_test_state);
      if (table->tests[i].teardown != NULL)
        table->tests[i].teardown(&minunit_test_state);
    }
    if (minunit_test_state.flag_fail != 0) {
      minunit_test_state.flag_fail = 0;
      minunit_test_state.failures++;
    }
    minunit_test_state.executed++;
    if (callback != NULL)
      callback();
#ifndef MINUNIT_REPORT_DISABLE
    minunit_report("\n");
#endif
  }
  return 0;
}

__attribute__((weak)) void minunit_report(const char *) {
  // empty body, as this is a weak function, no action should be taken
}

__attribute__((weak)) void minunit_fail_callback() {}
