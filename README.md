# Minimal Unittest framework for C
Yet another minimal unittest framework for C, but this one does not depend on anything. The reason for this is to allow unittests to be run on an embedded target or other niche usecases. Copied and modified from [Minunit](https://github.com/siu/minunit) and uses minimal C runtime environment from [rt0](https://github.com/lpsantil/rt0.git).
## Usage
As this framework is is based on [Minunit](https://github.com/siu/minunit) its usage is identical but some functions/macros have been removed. Below is a minimal example:
```
#include "sqMinUnitC.h"

int minunitRun; /* tests run */
int minunitFailures; /* tests failed */
int minunitAsserts; /* asserts run */

MU_TEST(test_check) {
    mu_check(5 == 7);
}
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_check);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    // print statistics
    printf("Tests run %d\n", minunitRun);
    printf("Asserts checked %d\n",minunitAsserts);
    printf("Asserts failed %d\n",minunitFailures);
    return minunit_status;
}
```
## Setup and teardown functions
One can define setup and teardown functions and configure the test suite to run them by using the macro MU_SUITE_CONFIGURE with within a MU_TEST_SUITE declaration.
## Assertion types
mu_check(condition): will pass if the condition is evaluated to true, otherwise it will show the condition as the error message

mu_fail(): will fail instantly.
## Global test counters
You need to define a few global variables that gather the test results.
```
int minunitRun; /* tests run */
int minunitFailures; /* tests failed */
int minunitAsserts; /* asserts run */
```
This makes it possible to spread out your test suites over multiple files.
## Building example
Building happens with make. Just invoking make will compile the PC target in release mode. Using the ```PLATFORM=``` on the commandline you can specify what platform to compile for, valid options are:
* ```PC```, just any PC with gcc and libc
* ```bare_PC```, just has gcc and works only in linux (tested on ubuntu 18.04) and uses syscalls to print something

The reason for the bare_PC target is I wanted something barebones on my development machine that resembles an embedded target library wise. 

Example debug build command for PC target:

```make PLATFORM=PC debug```

Binaries are placed in the bin directory.
## limitations
None found, yet. Please report if you encounter issues.