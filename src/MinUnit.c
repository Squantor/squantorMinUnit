#include <MinUnit.h>

#ifndef MINUNIT_MAX_TESTS
#warning No maximum number of tests defined, defaulting to 100
#define MINUNIT_MAX_TESTS 100
#endif

void (*minunitTestsTable[MINUNIT_MAX_TESTS])(void);
int minunitTestCount = 0;


void minunitAddTest(const char *name, void (*autoreg_func)(void))
{
    if(minunitTestCount < MINUNIT_MAX_TESTS-1)
    {
        minunitTestsTable[minunitTestCount] = autoreg_func;
        minunitTestCount++;
    }
}

int minunitRun(void)
{
    for(int i = 0; i < minunitTestCount; i++)
    {
        minunitTestsTable[i]();
    }
    return 0;
}