/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2020-2020 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file MinUnit.hpp
 * 
 * Minimal C++ unittesting framework
 * 
 * Minimal C++ unittesting framework, based on:
 * https://github.com/siu/minunit
 * Further inspiration drawn from:
 * https://github.com/ollelogdahl/ihct
 */ 
#ifndef MINUNIT_H
#define MINUNIT_H

#ifndef NULL
# ifndef __cplusplus
#  define NULL ((void *)0)
# else
# define NULL 0
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MINUNIT_MAX_TESTS
#warning No maximum number of tests defined, defaulting to 100
#define MINUNIT_MAX_TESTS 100
#endif

/**
 * \brief Datastructure defining test state
 */
typedef struct {
    int executed; /*!< Total tests executed */
    int failures; /*!< Total tests failed */
    int checks; /*!< Total test asserts executed */
    int flagFailed; /*!< did the current test fail */
} minunitState;

/**
 * \brief Test instance entry
 */
typedef struct {
    void (*testBody)(minunitState *testResults); /*!< code to test */
    void (*testSetup)(minunitState *testResults); /*!< setup to run before the test */
    void (*testTeardown)(minunitState *testResults); /*!< teardown to run after the test */
} minunitTestEntry;

/**
 * \brief Table of tests
 */
typedef struct {
    int testcount;  /*!< amount of tests in the table */
    minunitTestEntry tests[MINUNIT_MAX_TESTS]; /*!< table of tests */
} minunitTestsTable;

/**
 * \brief Test instance entry
 */
typedef void (*intraTestCallback)(void);

/**
 * \brief Macro to define a test setup function
 * 
 * Helper macro to create a function definition of a test setup
 * @param[in]  name         Name of the test setup function
 */
#define MINUNIT_SETUP(name)\
    void name(minunitState *testResults)

/**
 * \brief Macro to define a test teardown function
 * 
 * Helper macro to create a function definition of a test teardown
 * @param[in]  name         Name of the test teardown function
 */
#define MINUNIT_TEARDOWN(name)\
    void name(minunitState *testResults)


extern minunitState minunitTestState; /*!< minunit global state */
extern minunitTestsTable defaultTestTable; /*!< default table of tests */

/**
 * \brief Macro to register a test
 * 
 * Helper macro to register a test with minunit
 * @param[in]  name         Name of the test
 * @param[in]  setupFunc    test setup function, NULL for no setup
 * @param[in]  teardownFunc test setup function, NULL for no setup
 */
#define MINUNIT_ADD(name, setupFunc, teardownFunc)\
    static void minunit_##name(minunitState *testResults);\
    static void __attribute__((constructor)) __construct_minunit_##name(void) {\
        minunitAddTest(&defaultTestTable, minunit_##name, setupFunc, teardownFunc);\
    }\
    static void minunit_##name(minunitState *testResults)

/**
 * \brief function to add test to the test table
 * 
 * Used internally by the macro MINUNIT_ADD
 * 
 * @param[in]  table        Pointer to a table of tests
 * @param[in]  testBody     Function pointer to the actual test
 * @param[in]  testSetup    Function pointer to the test setup 
 * @param[in]  testTeardown Function pointer to the test teardown
 */
void minunitAddTest(
    minunitTestsTable *table,
    void (*testBody)(minunitState *testResults),
    void (*testSetup)(minunitState *testResults),
    void (*testTeardown)(minunitState *testResults));

/**
 * \brief function execute all tests
 * 
 * Executes all tests registered with MINUNIT_ADD
 */
int minunitRun(void);

/**
 * \brief function execute all tests with a callback inbetween
 * 
 * Executes all tests registered with MINUNIT_ADD and calls between each test
 * a callback given by the callback argument.
 * 
 * @param[in]   callback    Function pointer to call in between tests
 */
int minunitRunCallback(intraTestCallback callback);

/**
 * \brief function execute all tests with a in between test callback from a given table
 * 
 * Executes all tests passed along in the tests table and calls between each test
 * a callback given by the callback argument.
 * 
 * @param[in]   table       Table of tests to execute
 * @param[in]   callback    Function pointer to call in between tests
 */
int minunitRunTableCallback(minunitTestsTable *table, intraTestCallback callback);

/**
 * \brief function to report messages
 * 
 * Used by minunit to report failing tests or just print progress
 * 
 * @param[in]  message   Message to print
 */
void minunitReport(const char * message);

/**
 * \brief Macro to wrap a safe define block
 * 
 * Helper macro to create a safe block to be used in other C style macros
 * @param[in]  block   Block of statements that will be wrapped in a ```do{ }while(0)``` block.
 */
#define MU__SAFE_BLOCK(block) do {\
    block\
} while(0)

/**
 * \brief Convert a macro literal to string
 * 
 * Helper macro to convert a macro literal to a string, useful for __LINE__
 * 
 * @param[in]  x   Macro definition to convert to a string
 */
#define STRINGIFY(x) #x

/**
 * \brief Convert a macro literal to string
 * 
 * Final helper macro to convert a macro literal to a string, useful for __LINE__
 * 
 * @param[in]  x   Macro definition to convert to a string
 */
#define TOSTRING(x) STRINGIFY(x)

/**
 * \brief Executes a check
 * 
 * Executes a check, the argument needs to be true for the check to pass.
 * ```
 * MU_TEST(myTest)
 * {
 *     mu_check(true == true);
 * }
 * ```
 * @param[in] test Check to perform
 */

#ifndef MINUNIT_REPORT_DISABLE
#define minUnitCheck(test) MU__SAFE_BLOCK(\
    testResults->checks++;\
    if (!(test)) {\
        testResults->flagFailed = 1;\
        minunitReport("\n" __FILE__ ":" TOSTRING(__LINE__) " failed: " TOSTRING(test) "\n");\
        return;\
    }\
    else\
    {\
        minunitReport(".");\
    }\
)
#else
#define minUnitCheck(test) MU__SAFE_BLOCK(\
    testResults->checks++;\
    if (!(test)) {\
        testResults->flagFailed = 1;\
        return;\
    }\
)
#endif

/**
 * \brief automatically pass test
 * 
 * Automatically passing test, useful for the teardown and setup functions
 */
#define minUnitPass() MU__SAFE_BLOCK(\
    testResults->checks++;\
)

/**
 * \brief automatically fail test
 */
#define minUnitFail() MU__SAFE_BLOCK(\
    testResults->checks++;\
    testResults->flagFailed = 1;\
    return;\
)

#ifdef __cplusplus
}
#endif

#endif