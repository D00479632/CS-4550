#include "Scanner.h"
#include <iostream>
#include <fstream>
#include <string>

ScannerClass::ScannerClass(const std::string& inputFileName) 
    : mLineNumber(1) {
    MSG("Initializing ScannerClass object"); // Debug message
    mFin.open(inputFileName.c_str(), std::ios::binary);
    if (!mFin) {
        std::cerr << "Error opening input file " << inputFileName;
        std::exit(1);
    }
}

ScannerClass::~ScannerClass() {
    mFin.close();
}

TokenClass ScannerClass::GetNextToken(bool isPeeking = false) {
    StateMachineClass stateMachine;
    std::string lexeme;
    MachineState currentState;
    TokenType previousTokenType;

    do {
        char c = mFin.get(); // Read a character from the input file
        lexeme += c; // Append the character to the lexeme

        if (c == '\n') { // Check for newline character
            if (!isPeeking) { // Only print if not peeking
                mLineNumber++; // Increment line number
            }
        }
        currentState = stateMachine.UpdateState(c, previousTokenType); 
        //MSG("Current state: " + std::to_string(currentState) + " Char: " + c);
        if (c == '\n' && currentState != CANNOT_MOVE_STATE) { // Check for newline character
            if (!isPeeking) { // Only print if not peeking
                //MSG("Current line number: " + std::to_string(mLineNumber)); // Debug message for line number
            }
        }
        // If the current state is START_STATE or ENDFILE_STATE, reset the lexeme
        // This is to avoid including whitespace characters in the lexeme
        if (currentState == START_STATE || currentState == ENDFILE_STATE)
            lexeme = ""; 

        // Make sure we don't double count '\n'
        if (currentState == CANNOT_MOVE_STATE && c == '\n'){
           mLineNumber --;}

    } while (currentState != CANNOT_MOVE_STATE); 

    // Check if the previous token type indicates a bad token
    if (previousTokenType == BAD_TOKEN) {
        std::cerr << "Error. BAD_TOKEN from lexeme " << lexeme;
        std::exit(1);
    }

    // The last character read caused the machine to CANTMOVE
    // This character is not part of the current lexeme and 
    // needs to be put back into the stream
    lexeme.pop_back(); 
    mFin.unget(); 

    TokenClass tc(previousTokenType, lexeme); 
    return tc; 
}

int ScannerClass::GetLineNumber() const {
    return mLineNumber; // Accessor method for line number
}

TokenClass ScannerClass::PeekNextToken() {
    std::streampos filePos = mFin.tellg(); // Record the current position
    int currentLine = mLineNumber; // Record the current line number

    TokenClass tc = GetNextToken(true); // Pass true to indicate peeking

    if (!mFin) { // Check if EOF was triggered
        mFin.clear(); // Clear the EOF flag
    }

    mFin.seekg(filePos); // Reset the position back to where we started
    mLineNumber = currentLine; // Reset the line number

    return tc; // Return the token without consuming it
}