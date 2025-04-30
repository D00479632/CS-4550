#define ShowMessages 0 // Set to 1 to enable debug messages
#if ShowMessages
    #define MSG(X) std::cout << X << std::endl
#else
    #define MSG(X) // No operation
#endif