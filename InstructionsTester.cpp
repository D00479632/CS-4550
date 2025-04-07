#include "Instructions.h"
#include <iostream>

// Test function headers
void testArithmeticOperations(InstructionsClass &code);
void testRelationalOperators(InstructionsClass &code);
void testLogicalOperators(InstructionsClass &code);
void testVariables(InstructionsClass &code);
void testJumpOperations(InstructionsClass &code);

int main()
{
    InstructionsClass code;
    
    std::cout << "Starting InstructionsClass tests...\n";
    
    // Test variables and memory operations
    testVariables(code);
    
    // Test arithmetic operations
    testArithmeticOperations(code);
    
    // Test relational operators
    testRelationalOperators(code);
    
    // Test logical operators
    testLogicalOperators(code);
    
    // Test jump operations
    testJumpOperations(code);
    
    // Uncomment to see the machine code details
    // code.PrintAllMachineCodes();
    
    // Finish and execute the machine code
    code.Finish();
    code.Execute();
    
    std::cout << "\nAll tests completed.\n";
    return 0;
}

// Test variable storage and retrieval
void testVariables(InstructionsClass &code)
{
    std::cout << "\n=== Testing Variables ===\n";
    
    // Store values in memory locations
    code.PushValue(100);
    code.PopAndStore(0);  // Store 100 in memory location 0
    
    code.PushValue(200);
    code.PopAndStore(1);  // Store 200 in memory location 1
    
    code.PushValue(300);
    code.PopAndStore(2);  // Store 300 in memory location 2
    
    // Retrieve and print values
    code.PushVariable(0);
    code.PopAndWrite();  // Should print 100
    
    code.PushVariable(1);
    code.PopAndWrite();  // Should print 200
    
    code.PushVariable(2);
    code.PopAndWrite();  // Should print 300
    
    // Test updating variables
    code.PushVariable(0);  // Push 100
    code.PushValue(50);    // Push 50
    code.PopPopAddPush();  // Add: 100 + 50 = 150
    code.PopAndStore(0);   // Store result in location 0
    
    code.PushVariable(0);
    code.PopAndWrite();    // Should print 150
}

// Test all arithmetic operations
void testArithmeticOperations(InstructionsClass &code)
{
    std::cout << "\n=== Testing Arithmetic Operations ===\n";
    
    // Test addition
    code.PushValue(25);
    code.PushValue(17);
    code.PopPopAddPush();
    code.PopAndWrite();  // Should print 42
    
    // Test subtraction
    code.PushValue(50);
    code.PushValue(8);
    code.PopPopSubPush();
    code.PopAndWrite();  // Should print 42
    
    // Test multiplication
    code.PushValue(6);
    code.PushValue(7);
    code.PopPopMulPush();
    code.PopAndWrite();  // Should print 42
    
    // Test division
    code.PushValue(84);
    code.PushValue(2);
    code.PopPopDivPush();
    code.PopAndWrite();  // Should print 42
    
    // Test complex expression: (10 + 5) * 3 / 2 - 1
    code.PushValue(10);  // Push 10
    code.PushValue(5);   // Push 5
    code.PopPopAddPush();  // Add: 10 + 5 = 15
    code.PushValue(3);   // Push 3
    code.PopPopMulPush();  // Multiply: 15 * 3 = 45
    code.PushValue(2);   // Push 2
    code.PopPopDivPush();  // Divide: 45 / 2 = 22
    code.PushValue(1);   // Push 1
    code.PopPopSubPush();  // Subtract: 22 - 1 = 21
    code.PopAndWrite();    // Should print 21
}

// Test all relational operators
void testRelationalOperators(InstructionsClass &code)
{
    std::cout << "\n=== Testing Relational Operators ===\n";
    
    // Test less than (<)
    code.PushValue(5);
    code.PushValue(10);
    code.PopPopLessPush();
    code.PopAndWrite();  // Should print 1 (5 < 10 is true)
    
    code.PushValue(10);
    code.PushValue(5);
    code.PopPopLessPush();
    code.PopAndWrite();  // Should print 0 (10 < 5 is false)
    
    // Test less than or equal (<=)
    code.PushValue(5);
    code.PushValue(5);
    code.PopPopLessEqualPush();
    code.PopAndWrite();  // Should print 1 (5 <= 5 is true)
    
    // Test greater than (>)
    code.PushValue(10);
    code.PushValue(5);
    code.PopPopGreaterPush();
    code.PopAndWrite();  // Should print 1 (10 > 5 is true)
    
    // Test greater than or equal (>=)
    code.PushValue(5);
    code.PushValue(5);
    code.PopPopGreaterEqualPush();
    code.PopAndWrite();  // Should print 1 (5 >= 5 is true)
    
    // Test equal (==)
    code.PushValue(5);
    code.PushValue(5);
    code.PopPopEqualPush();
    code.PopAndWrite();  // Should print 1 (5 == 5 is true)
    
    // Test not equal (!=)
    code.PushValue(5);
    code.PushValue(10);
    code.PopPopNotEqualPush();
    code.PopAndWrite();  // Should print 1 (5 != 10 is true)
}

// Test all logical operators
void testLogicalOperators(InstructionsClass &code)
{
    std::cout << "\n=== Testing Logical Operators ===\n";
    
    // Test AND
    code.PushValue(1);
    code.PushValue(1);
    code.PopPopAndPush();
    code.PopAndWrite();  // Should print 1 (true AND true = true)
    
    code.PushValue(1);
    code.PushValue(0);
    code.PopPopAndPush();
    code.PopAndWrite();  // Should print 0 (true AND false = false)
    
    // Test OR
    code.PushValue(0);
    code.PushValue(1);
    code.PopPopOrPush();
    code.PopAndWrite();  // Should print 1 (false OR true = true)
    
    code.PushValue(0);
    code.PushValue(0);
    code.PopPopOrPush();
    code.PopAndWrite();  // Should print 0 (false OR false = false)
    
    // Test complex logical expressions: (1 AND 1) OR (0 AND 1)
    code.PushValue(1);
    code.PushValue(1);
    code.PopPopAndPush();  // 1 AND 1 = 1
    
    code.PushValue(0);
    code.PushValue(1);
    code.PopPopAndPush();  // 0 AND 1 = 0
    
    code.PopPopOrPush();   // 1 OR 0 = 1
    code.PopAndWrite();    // Should print 1
}

// Test all jump operations
void testJumpOperations(InstructionsClass &code)
{
    std::cout << "\n=== Testing Jump Operations ===\n";
    
    // Test 1: Skip if expression is zero (false condition)
    code.PushValue(0);  // Push false condition
    unsigned char* skipAddress = code.SkipIfZeroStack();
    
    // Code that should be skipped
    code.PushValue(999);
    code.PopAndWrite();
    
    // Calculate where to jump to
    unsigned char* endOfSkip = code.GetAddress();
    code.SetOffset(skipAddress, (int)(endOfSkip - (skipAddress + 4)));
    
    // This should execute after the skip
    code.PushValue(101);
    code.PopAndWrite();  // Should print 101
    
    // Test 2: Skip if expression is zero (true condition)
    code.PushValue(1);  // Push true condition
    skipAddress = code.SkipIfZeroStack();
    
    // Code that should NOT be skipped
    code.PushValue(102);
    code.PopAndWrite();  // Should print 102
    
    // Calculate where to jump to
    endOfSkip = code.GetAddress();
    code.SetOffset(skipAddress, (int)(endOfSkip - (skipAddress + 4)));
    
    // Test 3: Unconditional jump
    code.PushValue(103);
    code.PopAndWrite();  // Should print 103
    
    unsigned char* jumpAddress = code.Jump();
    
    // Code that should be skipped
    code.PushValue(999);
    code.PopAndWrite();
    
    // Calculate where to jump to
    unsigned char* jumpTarget = code.GetAddress();
    code.SetOffset(jumpAddress, (int)(jumpTarget - (jumpAddress + 4)));
    
    // This should execute after the jump
    code.PushValue(104);
    code.PopAndWrite();  // Should print 104
} 