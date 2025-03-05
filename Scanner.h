#include <iostream>
#include <fstream>
#include "StateMachineClass.h"
#pragma once

class ScannerClass {
public:
    ScannerClass(const std::string& inputFileName);
    ~ScannerClass();
    TokenClass GetNextToken(bool isPeeking);
    int GetLineNumber() const;
    // New method to peek at the next token without consuming it
    TokenClass PeekNextToken();

private:
    std::ifstream mFin;
    int mLineNumber;
};


