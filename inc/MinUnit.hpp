/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2020-2020 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
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
 *  Macro to wrap a safe define block
 *  
 *  Helper macro to create a safe block to be used in other C style macros
 *  @param[in]  block   Block of statements that will be wrapped in a ```do{ }while(0)``` block.
 */
#define MU__SAFE_BLOCK(block) do {\
    block\
} while(0)

#define MU_TEST_GLOBAL_STATE \
    int minunitRun; /*!< Total tests run, needs to be gobally defined */\
    int minunitFailures; /*!< Total tests failed, needs to be globally defined */\
    int minunitAsserts; /*!< Total test asserts executed, needs to be globally defined */\

#define MU_TEST_TEST_STATE \
    static int minunitStatus = 0; /*!< Test suite local status variable */\
    static void (*minunitSetup)(void) = NULL; /*!< Test suite local function pointer to test setup */\
    static void (*minunitTeardown)(void) = NULL; /*!< Test suite local function pointer to test teardown */\

extern int minunitRun; /*!< Total tests run, needs to be gobally defined */
extern int minunitFailures; /*!< Total tests failed, needs to be globally defined */
extern int minunitAsserts; /*!< Total test asserts executed, needs to be globally defined */

/**
 * Creates a test suite entry
 * 
 * Used to create a test suite for a bunch of tests, example definition:
 * ```
 * MU_TEST_SUITE(mysuite)
 * {
 * }
 * ```
 */
#define MU_TEST_SUITE(suiteName) static void suiteName(void)

/**
 *  
 */
#define MU_TEST(methodName) static void methodName(void)

/*  Run test suite and unset setup and teardown functions */
#define MU_RUN_SUITE(suiteName) MU__SAFE_BLOCK(\
    suiteName();\
    minunitSetup = NULL;\
    minunitTeardown = NULL;\
)

/*  Configure setup and teardown functions */
#define MU_SUITE_CONFIGURE(setupFun, teardownFun) MU__SAFE_BLOCK(\
    minunitSetup = setupFun;\
    minunitTeardown = teardownFun;\
)

/*  Test runner */
#define MU_RUN_TEST(test) MU__SAFE_BLOCK(\
    if (minunitSetup) (*minunitSetup)();\
    minunitStatus = 0;\
    test();\
    minunitRun++;\
    if (minunitStatus) minunitFailures++;\
    if (minunitTeardown) (*minunitTeardown)();\
)

/*  Assertions */
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