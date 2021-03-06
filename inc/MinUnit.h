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
    int checks; /*!< Total test asserts executed */
    int flagFailed; /*!< did the current test fail */
} minunitState;

/**
 * \brief Macro to register a test
 * 
 * Helper macro to register a test with minunit
 * @param[in]  name   Name of the test
 */
#define MINUNIT_ADD(name)\
    static void minunit_##name(minunitState *testResults);\
    static void __attribute__((constructor)) __construct_minunit_##name(void) {\
        minunitAddTest(minunit_##name);\
    }\
    static void minunit_##name(minunitState *testResults)


extern void (*minunitTestsTable[])(minunitState *testResults); /*!< table of tests to execute */
extern int minunitTestCount; /*!< Counter of available tests */
extern minunitState minunitTestState; /*!< minunit global state */

/**
 * \brief function to add test to the test table
 * 
 * Used internally by the macro MINUNIT_ADD
 * 
 * @param[in]  autoreg_func   Function pointer to the actual test
 */
void minunitAddTest(void (*autoreg_func)(minunitState *testResults));

/**
 * \brief function execute all tests
 * 
 * Executes all tests registered with MINUNIT_ADD
 */
int minunitRun(void);

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