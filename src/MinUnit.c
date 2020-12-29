#include <MinUnit.h>

void (*minunitTestsTable[1000])(void);
int minunitTestCount = 0;


void minunitAddTest(const char *name, void (*autoreg_func)(void))
{
    minunitTestsTable[minunitTestCount] = autoreg_func;
    minunitTestCount++;
}

int minunitRun(void)
{
    for(int i = 0; i < minunitTestCount; i++)
    {
        minunitTestsTable[i]();
    }
    return 0;
}