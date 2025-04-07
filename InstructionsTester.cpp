#include "Instructions.h"

int main()
{
    InstructionsClass code;
    
    // Test for Problem 9 - Division
    code.PushValue(100);
    code.PushValue(8);
    code.PopPopDivPush();
    code.PopAndWrite(); // should print 12
    
    // Test for Problem 10 - Addition
    code.PushValue(25);
    code.PushValue(17);
    code.PopPopAddPush();
    code.PopAndWrite(); // should print 42
    
    // Test for Problem 10 - Subtraction
    code.PushValue(50);
    code.PushValue(8);
    code.PopPopSubPush();
    code.PopAndWrite(); // should print 42
    
    // Test for Problem 10 - Multiplication
    code.PushValue(6);
    code.PushValue(7);
    code.PopPopMulPush();
    code.PopAndWrite(); // should print 42
    
    code.Finish();
    code.Execute();
    return 0;
} 