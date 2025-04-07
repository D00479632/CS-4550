#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
    // Beginning and end of every function:
    unsigned char mCode[] = {0x55, 0x8B, 0xEC,
                            0X5d, 0XC3};
    
    // This allows mCode data to be called as if it were a function:
    int MAX_INSTRUCTIONS = 5;
    mprotect((void *)((uintptr_t)mCode& ~(sysconf(_SC_PAGE_SIZE)-1)),
            MAX_INSTRUCTIONS, PROT_READ|PROT_WRITE|PROT_EXEC);
    
    std::cout << "About to Execute the machine code...\n";
    void * ptr = mCode;
    void (*f)(void);
    f = (void (*)(void)) ptr ;
    f(); // call the array as if it were a function
    std::cout << "There and back again!\n\n";
    
    return 0;
} 