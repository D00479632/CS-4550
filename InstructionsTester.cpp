#include "Instructions.h"

int main()
{
    InstructionsClass code;
    
    // Test for Problem 9 - Division
    code.PushValue(100);
    code.PushValue(8);
    code.PopPopDivPush();
    code.PopAndWrite(); // should print 12
    
    code.Finish();
    code.Execute();
    return 0;
} 