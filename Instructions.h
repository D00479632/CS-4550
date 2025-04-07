const int MAX_INSTRUCTIONS = 5000;
class InstructionsClass
{
public:
    InstructionsClass();
    void Encode(unsigned char c);
    void Encode(int x);
    void Encode(long long x);
    void Encode(void * p);
    void PushValue(int value);
    void Finish();
    void Execute();
private:
    unsigned char mCode[MAX_INSTRUCTIONS];
    int mCurrent; // where we are in mCode
    int mStartOfMain;
}; 