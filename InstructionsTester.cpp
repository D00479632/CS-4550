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
    
    // Test for Problem 12 - Logical Operators
    
    // AND Operator (&&)
    // Testing true && true = true
    code.PushValue(1);
    code.PushValue(1);
    code.PopPopAndPush();
    code.PopAndWrite(); // should print 1
    
    // Testing true && false = false
    code.PushValue(1);
    code.PushValue(0);
    code.PopPopAndPush();
    code.PopAndWrite(); // should print 0
    
    // Testing false && true = false
    code.PushValue(0);
    code.PushValue(1);
    code.PopPopAndPush();
    code.PopAndWrite(); // should print 0
    
    // Testing false && false = false
    code.PushValue(0);
    code.PushValue(0);
    code.PopPopAndPush();
    code.PopAndWrite(); // should print 0
    
    // OR Operator (||)
    // Testing true || true = true
    code.PushValue(1);
    code.PushValue(1);
    code.PopPopOrPush();
    code.PopAndWrite(); // should print 1
    
    // Testing true || false = true
    code.PushValue(1);
    code.PushValue(0);
    code.PopPopOrPush();
    code.PopAndWrite(); // should print 1
    
    // Testing false || true = true
    code.PushValue(0);
    code.PushValue(1);
    code.PopPopOrPush();
    code.PopAndWrite(); // should print 1
    
    // Testing false || false = false
    code.PushValue(0);
    code.PushValue(0);
    code.PopPopOrPush();
    code.PopAndWrite(); // should print 0
    
    // Test for Problem 13 - Jump Operations
    
    // Test 1: Skip if expression is zero (simulating an if statement)
    code.PushValue(0); // Condition is false
    unsigned char* skipAddress = code.SkipIfZeroStack(); // This will skip the "if body"
    
    // This is the "if body" that should be skipped when condition is false
    code.PushValue(999);
    code.PopAndWrite(); // This should NOT be executed when condition is false
    
    // This is where we want to jump to when condition is false
    unsigned char* afterIf = code.GetAddress();
    // Calculate the offset (distance from skipAddress+4 to afterIf)
    code.SetOffset(skipAddress, (int)(afterIf - (skipAddress + 4)));
    
    // Print a value to confirm we reached this point
    code.PushValue(111);
    code.PopAndWrite(); // Should print 111 (we skipped the 999)
    
    // Test 2: Skip if expression is non-zero (simulating an if statement)
    code.PushValue(1); // Condition is true
    skipAddress = code.SkipIfZeroStack(); // This will NOT skip the "if body"
    
    // This is the "if body" that should be executed when condition is true
    code.PushValue(222);
    code.PopAndWrite(); // This should be executed when condition is true
    
    // This is where we'd jump to if condition was false (but it's true)
    afterIf = code.GetAddress();
    // Calculate the offset (distance from skipAddress+4 to afterIf)
    code.SetOffset(skipAddress, (int)(afterIf - (skipAddress + 4)));
    
    // Test 3: Unconditional jump (used at the end of if or while statements)
    code.PushValue(333);
    code.PopAndWrite(); // Should print 333
    
    unsigned char* jumpAddress = code.Jump(); // This will skip the next section
    
    // This section should be skipped
    code.PushValue(999);
    code.PopAndWrite(); // This should NOT be executed
    
    // This is where we want to jump to
    unsigned char* afterJump = code.GetAddress();
    // Calculate the offset (distance from jumpAddress+4 to afterJump)
    code.SetOffset(jumpAddress, (int)(afterJump - (jumpAddress + 4)));
    
    // Print a value to confirm we reached this point
    code.PushValue(444);
    code.PopAndWrite(); // Should print 444 (we skipped the 999)
    
    code.Finish();
    code.Execute();
    return 0;
} 