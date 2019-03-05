/*
MIT License

Copyright (c) 2019 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
Minimal C unittesting framework, based on:
https://github.com/siu/minunit

No dependencies on anything and minimal facilities
*/
#ifndef SQMINUNITC_H
#define SQMINUNITC_H

#ifndef NULL
# ifndef __cplusplus
#  define NULL ((void *)0)
# else
# define NULL 0
# endif
#endif

/*  Test setup and teardown function pointers */
static void (*minunitSetup)(void) = NULL;
static void (*minunitTeardown)(void) = NULL;

/* test run tracking variables, need to be globally defined */
extern int minunitRun; /* tests run */
extern int minunitFailures; /* tests failed */
extern int minunitAsserts; /* asserts run */
/* test suite status tracking */
static int minunitStatus = 0;

/*  Definitions */
#define MU_TEST(methodName) static void methodName(void)
#define MU_TEST_SUITE(suiteName) static void suiteName(void)

#define MU__SAFE_BLOCK(block) do {\
    block\
} while(0)

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