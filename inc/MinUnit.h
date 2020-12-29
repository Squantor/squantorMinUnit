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

/**
 * \brief Datastructure defining test state
 */
typedef struct {
    int executed; /*!< Total tests executed */
    int failures; /*!< Total tests failed */
    int asserts; /*!< Total test asserts executed */
    int failed; /*!< did the current test fail */
} minunitState;

/**
 * \brief TODO
 */
#define MINUNIT_ADD(name)\
    static void minunit_##name(minunitState *testResults);\
    static void __attribute__((constructor)) __construct_minunit_##name(void) {\
        minunitAddTest(#name, minunit_##name);\
    }\
    static void minunit_##name(minunitState *testResults)

#define MINUNIT_RUN()     \
    minunitRun()

extern void (*minunitTestsTable[])(minunitState *testResults);
extern int minunitTestCount;

void minunitAddTest(const char *name, void (*autoreg_func)(minunitState *testResults));
int minunitRun(void);

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
#define minUnitCheck(test) MU__SAFE_BLOCK(\
    testResults->asserts++;\
    if (!(test)) {\
        testResults->failed = 1;\
        return;\
    }\
)

/**
 * \brief automatically fail test
 */
#define minUnitFail() MU__SAFE_BLOCK(\
    testResults->asserts++;\
    testResults->failed = 1;\
    return;\
)

#ifdef __cplusplus
}
#endif

#endif