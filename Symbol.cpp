#include "Symbol.h"
#include <iostream>
#include <cstdlib> // Include for std::exit

bool SymbolTableClass::Exists(const std::string & s) {
    for (const auto & var : mVariables) {
        if (var.mLabel == s) {
            return true;
        }
    }
    return false;
}

void SymbolTableClass::AddEntry(const std::string & s) {
    // Avoid adding twice
    if (Exists(s)) {
        std::cerr << "Error: Variable '" << s << "' already exists." << std::endl;
        std::exit(EXIT_FAILURE); // Exit the program
    }

    Variable v (s, 0);
    mVariables.push_back(v); 
}

int SymbolTableClass::GetValue(const std::string & s) {
    for (const auto & var : mVariables) {
        if (var.mLabel == s) {
            return var.mValue;
        }
    }
    std::cerr << "Error: Variable '" << s << "' does not exist." << std::endl;
    std::exit(EXIT_FAILURE); // Exit the program
}

void SymbolTableClass::SetValue(const std::string & s, int v) {
    for (auto & var : mVariables) {
        if (var.mLabel == s) {
            var.mValue = v;
            return;
        }
    }
    std::cerr << "Error: Variable '" << s << "' does not exist." << std::endl;
    std::exit(EXIT_FAILURE); // Exit the program
}

int SymbolTableClass::GetIndex(const std::string & s) {
    // size_t: unsigned integer type for sizes
    for (size_t i = 0; i < mVariables.size(); ++i) {
        if (mVariables[i].mLabel == s) {
            // Since size_t is not an int we need to cast it
            return static_cast<int>(i);
        }
    }
    return -1; 
}

size_t SymbolTableClass::GetCount() {
    return mVariables.size();
}
