#include "Instructions.h"

int main()
{
    InstructionsClass code;
    
    // Store values in memory
    *(code.GetMem(0)) = 42;
    *(code.GetMem(1)) = -123;
    
    // Push and print immediate values
    code.PushValue(-500);
    code.PopAndWrite();
    code.PushValue(1000);
    code.PopAndWrite();
    
    // Push and print variables from memory
    code.PushVariable(0);  // Push the value 42 from memory location 0
    code.PopAndWrite();
    code.PushVariable(1);  // Push the value -123 from memory location 1
    code.PopAndWrite();
    
    code.Finish();
    code.Execute();
    return 0;
} 