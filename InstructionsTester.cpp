#include "Instructions.h"

int main()
{
    InstructionsClass code;
    
    // Test for Problem 14 - Debug printing
    // Create a simple program with just a few instructions
    code.PushValue(42);
    code.PopAndWrite();
    
    code.Finish();
    
    // Print all machine codes for debugging
    code.PrintAllMachineCodes();
    
    code.Execute();
    return 0;
} 