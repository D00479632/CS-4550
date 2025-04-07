const int MAX_INSTRUCTIONS = 5000;
const int MAX_DATA = 5000;

class InstructionsClass
{
public:
    InstructionsClass();
    void Encode(unsigned char c);
    void Encode(int x);
    void Encode(long long x);
    void Encode(void * p);
    void PushValue(int value);
    void PushVariable(int index);
    void PopAndWrite();
    void PopAndStore(int index);
    void PopPopDivPush();
    void PopPopAddPush();
    void PopPopSubPush();
    void PopPopMulPush();
    
    // Problem 11 - Relational operators
    void PopPopComparePush(unsigned char relational_operator);
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
    unsigned char * SkipIfZeroStack();
    unsigned char * Jump();
    void SetOffset(unsigned char * codeAddress, int offset);
    
    void PrintIntegerLinux64();
    void WriteMinusLinux64();
    void WriteSpaceLinux64();
    void Call(void * function_address);
    unsigned char * GetAddress();
    int * GetMem(int index);
    void Finish();
    void Execute();
private:
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
}; 