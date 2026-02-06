/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2020-2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file minunit.h
 * @brief Minimal C/C++ unittesting framework
 * @version 20260206
 *
 * Minimal C++ unittesting framework, based on:
 * https://github.com/siu/minunit
 * Further inspiration drawn from:
 * https://github.com/ollelogdahl/ihct
 */
#ifndef MINUNIT_H
#define MINUNIT_H

#ifndef NULL
#ifndef __cplusplus
#include <stddef.h>
#else
#include <cstddef>
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MINUNIT_MAX_TESTS
#warning No maximum number of tests defined, defaulting to 100
#define MINUNIT_MAX_TESTS 100
#endif

/**
 * @brief Datastructure defining test state
 */
typedef struct {
  int executed;  /*!< Total tests executed */
  int failures;  /*!< Total tests failed */
  int checks;    /*!< Total test asserts executed */
  int flag_fail; /*!< did the current test fail */
} Minunit_state;

/**
 * @brief Test instance entry
 */
typedef struct {
  void (*body)(Minunit_state *test_results);     /*!< code to test */
  void (*setup)(Minunit_state *test_results);    /*!< setup to run before the test */
  void (*teardown)(Minunit_state *test_results); /*!< teardown to run after the test */
} Minunit_test_entry;

/**
 * @brief Table of tests
 */
typedef struct {
  int testcount;                               /*!< amount of tests in the table */
  Minunit_test_entry tests[MINUNIT_MAX_TESTS]; /*!< table of tests */
} Minunit_tests_table;

/**
 * @brief Test instance entry
 */
typedef void (*Intra_test_callback)(void);

/**
 * @brief Macro to define a test setup function
 * Helper macro to create a function definition of a test setup
 * @param[in]  name         Name of the test setup function
 */
#define MINUNIT_SETUP(name) void name(Minunit_state *test_results)

/**
 * @brief Macro to define a test teardown function
 * Helper macro to create a function definition of a test teardown
 * @param[in]  name         Name of the test teardown function
 */
#define MINUNIT_TEARDOWN(name) void name(Minunit_state *test_results)

extern Minunit_state minunit_test_state;       /*!< minunit global state */
extern Minunit_tests_table default_test_table; /*!< default table of tests */

/**
 * @brief Macro to register a test
 * Helper macro to register a test with minunit
 * @param[in]  name         Name of the test
 * @param[in]  setupFunc    test setup function, NULL for no setup
 * @param[in]  teardownFunc test setup function, NULL for no setup
 */
#define MINUNIT_ADD(name, setupFunc, teardownFunc)                                  \
  static void minunit_##name(Minunit_state *test_results);                          \
  static void __attribute__((constructor)) __construct_minunit_##name(void) {       \
    minunit_add_test(&default_test_table, minunit_##name, setupFunc, teardownFunc); \
  }                                                                                 \
  static void minunit_##name(Minunit_state *test_results)

/**
 * @brief function to add test to the test table
 * Used internally by the macro MINUNIT_ADD
 * @param[in]  table        Pointer to a table of tests
 * @param[in]  body     Function pointer to the actual test
 * @param[in]  setup    Function pointer to the test setup
 * @param[in]  teardown Function pointer to the test teardown
 */
void minunit_add_test(Minunit_tests_table *table, void (*body)(Minunit_state *test_results),
                      void (*setup)(Minunit_state *test_results), void (*teardown)(Minunit_state *test_results));

/**
 * @brief function execute all tests
 * Executes all tests registered with MINUNIT_ADD
 */
int minunit_run(void);

/**
 * @brief function execute all tests with a callback inbetween
 * Executes all tests registered with MINUNIT_ADD and calls between each test
 * a callback given by the callback argument.
 * @param[in]   callback    Function pointer to call in between tests
 */
int minunit_run_callback(Intra_test_callback callback);

/**
 * @brief function execute all tests with a in between test callback from a
 * given table
 * Executes all tests passed along in the tests table and calls between each
 * test a callback given by the callback argument.
 * @param[in]   table       Table of tests to execute
 * @param[in]   callback    Function pointer to call in between tests
 */
int minunit_run_table_callback(Minunit_tests_table *table, Intra_test_callback callback);

/**
 * @brief weak overridable callback function to report messages
 * Used by minunit to report failing tests or just print progress. This is a
 * weak function to be overridden by the user if he wants a different report
 * message
 * @param[in]  message   Message to print
 */
void minunit_report(const char *message);

/**
 * @brief weak overridable callback function called when a test fails
 * When a minunit check fails, this function is called. Useful for examining the
 * callstack in embedded targets to see where it fails.
 */
void minunit_fail_callback();

/**
 * @brief Macro to wrap a safe define block
 * Helper macro to create a safe block to be used in other C style macros
 * @param[in]  block   Block of statements that will be wrapped in a ```do{
 * }while(0)``` block.
 */
#define MU__SAFE_BLOCK(block) \
  do {                        \
    block                     \
  } while (0)

/**
 * @brief Convert a macro literal to string
 * Helper macro to convert a macro literal to a string, useful for __LINE__
 * @param[in]  x   Macro definition to convert to a string
 */
#define STRINGIFY(x) #x

/**
 * @brief Convert a macro literal to string
 * Final helper macro to convert a macro literal to a string, useful for
 * __LINE__
 * @param[in]  x   Macro definition to convert to a string
 */
#define TOSTRING(x) STRINGIFY(x)

/**
 * @brief Executes a assertion
 * Executes a check, the argument needs to be true for passing.
 * ```
 * MU_TEST(myTest)
 * {
 *     mu_check(true == true);
 * }
 * ```
 * @param[in] test Check to perform
 */
#ifndef MINUNIT_REPORT_DISABLE
#define MINUNIT_ASSERT(test)                                                                \
  MU__SAFE_BLOCK(                                                                           \
    test_results->checks++; if (!(test)) {                                                  \
      minunit_fail_callback();                                                              \
      test_results->flag_fail = 1;                                                          \
      minunit_report("\n" __FILE__ ":" TOSTRING(__LINE__) " failed: " TOSTRING(test) "\n"); \
      return;                                                                               \
    } else { minunit_report("."); })
#else
#define MINUNIT_ASSERT(test)                            \
  MU__SAFE_BLOCK(test_results->checks++; if (!(test)) { \
    minunit_fail_callback();                            \
    test_results->flag_fail = 1;                        \
    return;                                             \
  })
#endif

/**
 * @brief Executes a check
 * Executes a check, the argument does not need to be true for passing.
 * ```
 * MU_TEST(myTest)
 * {
 *     mu_check(true == true);
 * }
 * ```
 * @param[in] test Check to perform
 */
#ifndef MINUNIT_REPORT_DISABLE
#define MINUNIT_CHECK(test)                                                                 \
  MU__SAFE_BLOCK(                                                                           \
    test_results->checks++; if (!(test)) {                                                  \
      minunit_fail_callback();                                                              \
      test_results->flag_fail = 1;                                                          \
      minunit_report("\n" __FILE__ ":" TOSTRING(__LINE__) " failed: " TOSTRING(test) "\n"); \
    } else { minunit_report("."); })
#else
#define MINUNIT_CHECK(test)                             \
  MU__SAFE_BLOCK(test_results->checks++; if (!(test)) { \
    minunit_fail_callback();                            \
    test_results->flag_fail = 1;                        \
  })
#endif

/**
 * @brief automatically pass test
 * Automatically passing test, useful for the teardown and setup functions
 */
#define MINUNIT_PASS() MU__SAFE_BLOCK(test_results->checks++;)

/**
 * @brief automatically fail test
 */
#define MINUNIT_FAIL() MU__SAFE_BLOCK(test_results->checks++; minunit_fail_callback(); test_results->flag_fail = 1; return;)

#ifdef __cplusplus
}
#endif

#endif
