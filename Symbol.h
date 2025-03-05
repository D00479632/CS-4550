#include <string>
#include <vector>
#pragma once

class SymbolTableClass {
public:
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

private:
    struct Variable {
        std::string mLabel; // variable name
        int mValue;         // variable value

        // Constructor for Variable
        Variable(const std::string & label, int value) : mLabel(label), mValue(value) {}
    };

    std::vector<Variable> mVariables; // Vector to store Variable types
};