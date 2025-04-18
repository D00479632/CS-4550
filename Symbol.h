#include <string>
#include <vector>
#include <map>
#include <stack>
#pragma once

class SymbolTableClass {
public:
    // Constructor
    SymbolTableClass();
    
    // returns true if <s> is already in the symbol table.
    bool Exists(const std::string & s); 

    // adds <s> to the symbol table, or quits if it was already there
    void AddEntry(const std::string & s);

    // Returns the current value of variable <s>, when interpreting.
    // Prints a message and quits if variable s does not exist.
    int GetValue(const std::string & s); 

    // Sets variable <s> to the given value when interpreting.
    // Prints a message and quits if variable s does not exist.
    void SetValue(const std::string & s, int v); 

    // Returns a unique index of where variable <s> is.
    // Returns -1 if variable <s> is not there.
    int GetIndex(const std::string & s); 

    // returns the current number of variables in the symbol table.
    size_t GetCount(); 

    // Create a new scope
    void EnterScope();
    
    // Exit current scope and remove all variables declared in this scope
    void ExitScope();

private:
    struct Variable {
        std::string mLabel; // variable name
        int mValue;         // variable value
        int mScopeLevel;    // scope level where this variable was declared

        // Constructor for Variable
        Variable(const std::string & label, int value, int scopeLevel) 
            : mLabel(label), mValue(value), mScopeLevel(scopeLevel) {}
    };

    std::vector<Variable> mVariables; // Vector to store Variable types
    int mCurrentScopeLevel; // Current scope level (0 = global scope)
};