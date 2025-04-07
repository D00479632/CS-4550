#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include "Instructions.h"

// Some assembly like definitions for our machine code:
const unsigned char PUSH_EBP = 0x55;
const unsigned char MOV_EBP_ESP1 = 0x8B;
const unsigned char MOV_EBP_ESP2 = 0xEC;
const unsigned char POP_EBP = 0x5D;
const unsigned char NEAR_RET = 0xC3;

// Put one instruction at a time into mCode:
void InstructionsClass::Encode(unsigned char c)
{
    if(mCurrent + sizeof(unsigned char) < MAX_INSTRUCTIONS)
    {
        mCode[mCurrent] = c;
        mCurrent += sizeof(unsigned char);
    }
    else
    {
        std::cerr << "Error. Used up all " << MAX_INSTRUCTIONS
                  << " instructions." << std::endl;
        exit(1);
    }
}

// 2.a - Encode an integer (4 bytes)
void InstructionsClass::Encode(int x)
{
    if(mCurrent + sizeof(int) < MAX_INSTRUCTIONS)
    {
        *((int*)(&(mCode[mCurrent]))) = x;
        mCurrent += sizeof(int);
    }
    else
    {
        std::cerr << "Error. Used up all " << MAX_INSTRUCTIONS
                  << " instructions." << std::endl;
        exit(1);
    }
}

// 2.b - Encode a long long (8 bytes)
void InstructionsClass::Encode(long long x)
{
    if(mCurrent + sizeof(long long) < MAX_INSTRUCTIONS)
    {
        *((long long*)(&(mCode[mCurrent]))) = x;
        mCurrent += sizeof(long long);
    }
    else
    {
        std::cerr << "Error. Used up all " << MAX_INSTRUCTIONS
                  << " instructions." << std::endl;
        exit(1);
    }
}

// 2.c - Encode a pointer (4 or 8 bytes)
void InstructionsClass::Encode(void * p)
{
    int pointerSize = sizeof(p);
    if (pointerSize == 4)
    {
        Encode((int)(long long)p);
    }
    else if(pointerSize == 8)
    {
        Encode((long long)p);
    }
}

InstructionsClass::InstructionsClass()
{
    mprotect((void *)((uintptr_t)mCode& ~(sysconf(_SC_PAGE_SIZE)-1)),
            MAX_INSTRUCTIONS, PROT_READ|PROT_WRITE|PROT_EXEC);
    mCurrent = 0;
    mStartOfMain = 0;
    // All functions start this way. So does our main function.
    Encode(PUSH_EBP);
    Encode(MOV_EBP_ESP1);
    Encode(MOV_EBP_ESP2);
}

void InstructionsClass::Finish()
{
    // All functions end this way:
    Encode(POP_EBP);
    Encode(NEAR_RET);
    std::cout << "Finished creating " << mCurrent <<
              " bytes of machine code" << std::endl;
}

void InstructionsClass::Execute()
{
    // Jump into the main function of what we just coded,
    // found at mCode[mStartOfMain]
    std::cout << "About to Execute the machine code..." << std::endl;
    void * ptr = &(mCode[mStartOfMain]);
    void (*f)(void);
    f = (void (*)(void)) ptr ;
    f();
    // Did everything work?
    std::cout << "\nThere and back again!" << std::endl;
} 