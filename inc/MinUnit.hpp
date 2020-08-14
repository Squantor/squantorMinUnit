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
 */ 
#ifndef MINUNIT_HPP
#define MINUNIT_HPP

#ifndef NULL
# ifndef __cplusplus
#  define NULL ((void *)0)
# else
# define NULL 0
# endif
#endif

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
 * \brief Macro to generate the global state for all the tests
 * 
 * Generates the global state for all tests, these are all the counters like tests run, 
 * tests failed and amount of test assertions executed.
 */
#define MU_TEST_GLOBAL_STATE \
    int minunitRun; /*!< Total tests run, needs to be gobally defined */\
    int minunitFailures; /*!< Total tests failed, needs to be globally defined */\
    int minunitAsserts; /*!< Total test asserts executed, needs to be globally defined */\

/**
 * \brief Macro to generate the state for the current test suite
 * 
 * Generates the local state for the test suite, these are setup and teardown functions and
 * the running test state.
 */
#define MU_TEST_TEST_STATE \
    static int minunitStatus = 0; /*!< Test suite local status variable */\
    static void (*minunitSetup)(void) = NULL; /*!< Test suite local function pointer to test setup */\
    static void (*minunitTeardown)(void) = NULL; /*!< Test suite local function pointer to test teardown */\


extern int minunitRun; /*!< Total tests run, needs to be defined with MU_TEST_GLOBAL_STATE */
extern int minunitFailures; /*!< Total tests failed, needs to be defined with MU_TEST_GLOBAL_STATE */
extern int minunitAsserts; /*!< Total test asserts executed, needs to be defined with MU_TEST_GLOBAL_STATE */

/**
 * \brief Creates a test suite entry
 * 
 * Used to create a test suite for a bunch of tests, example:
 * ```
 * MU_TEST_SUITE(mysuite)
 * {
 *     MU_SUITE_CONFIGURE(&myTestSetup, &myTestTeardown);
 *     MU_RUN_TEST(mytest);
 * }
 * ```
 */
#define MU_TEST_SUITE(suiteName) static void suiteName(void)

/**
 * \brief Configures the test suite
 * 
 * Configures the tests suite with the setup and teardown functions.
 * Needs to be configured before each test.
 * ```
 * MU_TEST_SUITE(mysuite)
 * {
 *     MU_SUITE_CONFIGURE(&myTestSetup, &myTestTeardown);
 *     MU_RUN_TEST(mytest);
 * }
 * ```
 * @param[in] setupFun Function pointer to the test setup function
 * @param[in] teardownFun Function pointer to the test teardown function
 */
#define MU_SUITE_CONFIGURE(setupFun, teardownFun) MU__SAFE_BLOCK(\
    minunitSetup = setupFun;\
    minunitTeardown = teardownFun;\
)

/**
 * \brief Executes a test suite
 * 
 * Executes a defined test suite, clears the setup and teardown afterwards.
 * ```
 * MU_TEST_SUITE(mysuite)
 * {
 *     MU_SUITE_CONFIGURE(&myTestSetup, &myTestTeardown);
 *     MU_RUN_TEST(mytest);
 * }
 * ```
 */
#define MU_RUN_SUITE(suiteName) MU__SAFE_BLOCK(\
    suiteName();\
    minunitSetup = NULL;\
    minunitTeardown = NULL;\
)

/**
 * \brief executes a test
 * 
 * Runs the test, the test setup (if configured) will be run before and
 * test teardown (if configured) will be executed afterwards.
 * ```
 * MU_TEST_SUITE(mysuite)
 * {
 *     MU_SUITE_CONFIGURE(&myTestSetup, &myTestTeardown);
 *     MU_RUN_TEST(mytest); // clears the setup and teardown
 *     MU_SUITE_CONFIGURE(&myTestSetup, &myTestTeardown);
 *     MU_RUN_TEST(mytest2);
 * }
 * ```
 * @param[in] test Test name to execute
 */
#define MU_RUN_TEST(test) MU__SAFE_BLOCK(\
    if (minunitSetup) (*minunitSetup)();\
    minunitStatus = 0;\
    test();\
    minunitRun++;\
    if (minunitStatus) minunitFailures++;\
    if (minunitTeardown) (*minunitTeardown)();\
)

/**
 * \brief Creates a test
 * 
 * Creates a test.
 * ```
 * MU_TEST(myTest)
 * {
 *     mu_check(true == true);
 * }
 * ```
 * @param[in] methodName Test name
 */
#define MU_TEST(methodName) static void methodName(void)

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
#define mu_check(test) MU__SAFE_BLOCK(\
    minunitAsserts++;\
    if (!(test)) {\
        minunitStatus = 1;\
        return;\
    }\
)

#define mu_fail() MU__SAFE_BLOCK(\
    minunitAsserts++;\
    minunitStatus = 1;\
    return;\
)

#endif