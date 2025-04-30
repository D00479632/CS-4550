#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

const int MAX_INSTRUCTIONS = 5000;
const int MAX_DATA = 5000;

class InstructionsClass
{
public:
    // Constructor
    InstructionsClass();
    
    // Core execution methods
    void Finish();
    void Execute();
    
    // Problem 4 - Methods for pushing values to the stack
    void PushValue(int value);
    
    // Problem 5 - Methods for printing
    void PopAndWrite();
    void WriteEndlLinux64();
    
    // Problem 6-7 - Methods for variables
    void PushVariable(int index);
    void PopAndStore(int index);
    
    // Problem 9-10 - Arithmetic operators
    void PopPopDivPush();
    void PopPopModPush();
    void PopPopAddPush();
    void PopPopSubPush();
    void PopPopMulPush();
    
    // Problem 11 - Relational operators
    void PopPopLessPush();
    void PopPopLessEqualPush();
    void PopPopGreaterPush();
    void PopPopGreaterEqualPush();
    void PopPopEqualPush();
    void PopPopNotEqualPush();
    
    // Problem 12 - Logical operators
    void PopPopAndPush();
    void PopPopOrPush();
    
    // Problem 13 - Jump operations
    unsigned char * GetAddress();
    unsigned char * SkipIfZeroStack();
    unsigned char * Jump();
    void SetOffset(unsigned char * codeAddress, int offset);
    
    // Problem 14 - Debug method
    void PrintAllMachineCodes();
    
    virtual void Code([[maybe_unused]] InstructionsClass &machineCode) { }
    
private:
    // Private data members
    unsigned char mCode[MAX_INSTRUCTIONS];
    int mData[MAX_DATA];
    int mCurrent; // where we are in mCode
    int mPrintInteger; // Location to store an integer about to be printed.
    int mTempInteger; // Location to store one char of integer to be printed.
    int mStartOfPrint; // The value of mCurrent where PrintIntegerLinux64 starts.
                       // Jump to this offset of mCode to print.
    int mStartOfMain; // the value of mCurrent after coding the Print functions.
                      // Jump to this offset of mCode to start program execution.
    char mMinusString; // Holds '-'
    char mSpaceString; // Holds ' '
    char mNewlineString; // Holds '\n'
    
    // Problem 2 - Encoding methods
    void Encode(unsigned char c);
    void Encode(int x);
    void Encode(long long x);
    void Encode(void * p);
    
    // Problem 5 - Helper methods for printing
    void PrintIntegerLinux64();
    void WriteMinusLinux64();
    void WriteSpaceLinux64();
    void Call(void * function_address);
    
    // Problem 6 - Memory access
    int * GetMem(int index);
    
    // Problem 11 - Relational operator helper
    void PopPopComparePush(unsigned char relational_operator);
};

#endif 