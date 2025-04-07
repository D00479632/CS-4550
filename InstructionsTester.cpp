#include "Instructions.h"

int main()
{
    InstructionsClass code;
    
    code.PushValue(500); // 500 to stack
    code.PopAndStore(1); // to slot 1 of mData
    code.PushVariable(1); // from mData back onto stack
    code.PopAndWrite();
    
    code.Finish();
    code.Execute();
    return 0;
} 