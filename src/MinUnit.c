#include <MinUnit.h>

#ifndef MINUNIT_MAX_TESTS
#warning No maximum number of tests defined, defaulting to 100
#define MINUNIT_MAX_TESTS 100
#endif


void (*minunitTestsTable[MINUNIT_MAX_TESTS])(minunitState *testResults);
int minunitTestCount = 0;

minunitState minunitTestState;

void minunitAddTest(const char *name, void (*autoreg_func)(minunitState *testResults))
{
    if(minunitTestCount < MINUNIT_MAX_TESTS-1)
    {
        minunitTestsTable[minunitTestCount] = autoreg_func;
        minunitTestCount++;
    }
}

int minunitRun(void)
{
    minunitTestState.executed = 0;
    minunitTestState.failures = 0;
    minunitTestState.checks = 0;
    for(int i = 0; i < minunitTestCount; i++)
    {
        minunitTestState.failed = 0;
        minunitTestsTable[i](&minunitTestState);
        if(minunitTestState.failed != 0)
        {
            minunitTestState.failures++;
        }
        minunitTestState.executed++;
    }
    return 0;
}