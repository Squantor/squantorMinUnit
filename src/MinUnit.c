#include <MinUnit.h>

minunitTestsTable defaultTestTable = {0};

minunitState minunitTestState;

void minunitAddTest( minunitTestsTable *table,
    void (*testBody)(minunitState *testResults),
    void (*testSetup)(minunitState *testResults),
    void (*testTeardown)(minunitState *testResults))
{
    if(table->testcount < MINUNIT_MAX_TESTS-1)
    {
        table->tests[table->testcount].testBody = testBody;
        table->tests[table->testcount].testSetup = testSetup;
        table->tests[table->testcount].testTeardown = testTeardown;
        table->testcount++;
    }
}

int minunitRun(void) 
{
    return minunitRunTableCallback(&defaultTestTable, NULL);
}

int minunitRunCallback(intraTestCallback callback)
{
    return minunitRunTableCallback(&defaultTestTable, callback);
}

int minunitRunTableCallback(minunitTestsTable *table, intraTestCallback callback)
{
    minunitTestState.executed = 0;
    minunitTestState.failures = 0;
    minunitTestState.checks = 0;
    for(int i = 0; i < table->testcount; i++)
    {
        if(table->tests[i].testSetup != NULL)
            table->tests[i].testSetup(&minunitTestState);
        if(minunitTestState.flagFailed == 0)
        {
            table->tests[i].testBody(&minunitTestState);
            if(table->tests[i].testTeardown != NULL)
                table->tests[i].testTeardown(&minunitTestState);  
        }
        if(minunitTestState.flagFailed != 0)
        {
            minunitTestState.flagFailed = 0;
            minunitTestState.failures++;
        }
        minunitTestState.executed++;
        if(callback != NULL)
            callback();
        #ifndef MINUNIT_REPORT_DISABLE
        minunitReport("\n");
        #endif
    }
    return 0;
}


#pragma GCC diagnostic ignored "-Wunused-parameter"

__attribute__((weak)) void minunitReport(const char * message)
{
    // empty body, as this is a weak function, no action should be taken
}