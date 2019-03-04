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
Minimal C unittesting framework, inspired by:
http://www.jera.com/techinfo/jtns/jtn002.html
Further inspired by:
https://github.com/siu/minunit

No dependencies on anything and minimal facilities
*/
#ifndef SQMINUNITC_H
#define SQMINUNITC_H

/*  Test setup and teardown function pointers */
static void (*minunit_setup)(void) = NULL;
static void (*minunit_teardown)(void) = NULL;

/* global test run tracking variables */
extern int minunitRun; /* tests run */
extern int minunitFailures; /* tests failed */
extern int minunitAsserts; /* asserts run */
/* test suite status tracking */
static int minunitStatus = 0;

/*  Definitions */
#define MU_TEST(method_name) static void method_name(void)
#define MU_TEST_SUITE(suite_name) static void suite_name(void)

#define MU__SAFE_BLOCK(block) do {\
    block\
} while(0)

/*  Run test suite and unset setup and teardown functions */
#define MU_RUN_SUITE(suite_name) MU__SAFE_BLOCK(\
    suite_name();\
    minunit_setup = NULL;\
    minunit_teardown = NULL;\
)

/*  Configure setup and teardown functions */
#define MU_SUITE_CONFIGURE(setup_fun, teardown_fun) MU__SAFE_BLOCK(\
    minunit_setup = setup_fun;\
    minunit_teardown = teardown_fun;\
)

/*  Test runner */
#define MU_RUN_TEST(test) MU__SAFE_BLOCK(\
    if (minunit_setup) (*minunit_setup)();\
    minunitStatus = 0;\
    test();\
    minunitRun++;\
    if (minunitStatus) minunitFailures++;\
    if (minunit_teardown) (*minunit_teardown)();\
)

/*  Assertions */
#define mu_check(test) MU__SAFE_BLOCK(\
    minunitAsserts++;\
    if (!(test)) {\
        minunitStatus = 1;\
        return;\
    }\
)

#endif