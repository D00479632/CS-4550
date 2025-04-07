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
    
    // Test for Problem 11 - Relational Operators
    
    // Less than (<)
    code.PushValue(3);
    code.PushValue(4);
    code.PopPopLessPush();
    code.PopAndWrite(); // should print 1 (3 < 4 is true)
    
    code.PushValue(4);
    code.PushValue(4);
    code.PopPopLessPush();
    code.PopAndWrite(); // should print 0 (4 < 4 is false)
    
    code.PushValue(5);
    code.PushValue(4);
    code.PopPopLessPush();
    code.PopAndWrite(); // should print 0 (5 < 4 is false)
    
    // Less than or equal (<=)
    code.PushValue(3);
    code.PushValue(4);
    code.PopPopLessEqualPush();
    code.PopAndWrite(); // should print 1 (3 <= 4 is true)
    
    code.PushValue(4);
    code.PushValue(4);
    code.PopPopLessEqualPush();
    code.PopAndWrite(); // should print 1 (4 <= 4 is true)
    
    code.PushValue(5);
    code.PushValue(4);
    code.PopPopLessEqualPush();
    code.PopAndWrite(); // should print 0 (5 <= 4 is false)
    
    // Greater than (>)
    code.PushValue(3);
    code.PushValue(4);
    code.PopPopGreaterPush();
    code.PopAndWrite(); // should print 0 (3 > 4 is false)
    
    code.PushValue(4);
    code.PushValue(4);
    code.PopPopGreaterPush();
    code.PopAndWrite(); // should print 0 (4 > 4 is false)
    
    code.PushValue(5);
    code.PushValue(4);
    code.PopPopGreaterPush();
    code.PopAndWrite(); // should print 1 (5 > 4 is true)
    
    // Greater than or equal (>=)
    code.PushValue(3);
    code.PushValue(4);
    code.PopPopGreaterEqualPush();
    code.PopAndWrite(); // should print 0 (3 >= 4 is false)
    
    code.PushValue(4);
    code.PushValue(4);
    code.PopPopGreaterEqualPush();
    code.PopAndWrite(); // should print 1 (4 >= 4 is true)
    
    code.PushValue(5);
    code.PushValue(4);
    code.PopPopGreaterEqualPush();
    code.PopAndWrite(); // should print 1 (5 >= 4 is true)
    
    // Equal (==)
    code.PushValue(3);
    code.PushValue(4);
    code.PopPopEqualPush();
    code.PopAndWrite(); // should print 0 (3 == 4 is false)
    
    code.PushValue(4);
    code.PushValue(4);
    code.PopPopEqualPush();
    code.PopAndWrite(); // should print 1 (4 == 4 is true)
    
    code.PushValue(5);
    code.PushValue(4);
    code.PopPopEqualPush();
    code.PopAndWrite(); // should print 0 (5 == 4 is false)
    
    // Not equal (!=)
    code.PushValue(3);
    code.PushValue(4);
    code.PopPopNotEqualPush();
    code.PopAndWrite(); // should print 1 (3 != 4 is true)
    
    code.PushValue(4);
    code.PushValue(4);
    code.PopPopNotEqualPush();
    code.PopAndWrite(); // should print 0 (4 != 4 is false)
    
    code.PushValue(5);
    code.PushValue(4);
    code.PopPopNotEqualPush();
    code.PopAndWrite(); // should print 1 (5 != 4 is true)
    
    code.Finish();
    code.Execute();
    return 0;
} 