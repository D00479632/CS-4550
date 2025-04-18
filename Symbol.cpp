#include "Symbol.h"
#include <iostream>
#include <cstdlib> // Include for std::exit
#include "Debug.h"

// Constructor to initialize the current scope level to 0 (global scope)
SymbolTableClass::SymbolTableClass() : mCurrentScopeLevel(0) {
}

bool SymbolTableClass::Exists(const std::string & s) {
    // Start searching from the end (most recently added variables) to find in current scope first
    for (int i = mVariables.size() - 1; i >= 0; --i) {
        if (mVariables[i].mLabel == s) {
            return true;
        }
    }
    return false;
}

void SymbolTableClass::AddEntry(const std::string & s) {
    // Check if variable already exists in the current scope
    // Start searching from the end (most recently added variables)
    for (int i = mVariables.size() - 1; i >= 0; --i) {
        if (mVariables[i].mLabel == s && mVariables[i].mScopeLevel == mCurrentScopeLevel) {
            std::cerr << "Error: Variable '" << s << "' already exists in the current scope." << std::endl;
            std::exit(EXIT_FAILURE); // Exit the program
        }
        
        // If we've checked all variables in the current scope for this name, we can stop
        // Variables in the outer scopes with the same name are allowed (shadowing)
        if (mVariables[i].mScopeLevel < mCurrentScopeLevel) {
            break;
        }
    }

    // Add the new variable with the current scope level
    Variable v(s, 0, mCurrentScopeLevel);
    mVariables.push_back(v);
    
    MSG("Added variable '" << s << "' to scope level " << mCurrentScopeLevel);
}

int SymbolTableClass::GetValue(const std::string & s) {
    // Search from newest to oldest to find the most recent variable in scope
    for (int i = mVariables.size() - 1; i >= 0; --i) {
        if (mVariables[i].mLabel == s) {
            return mVariables[i].mValue;
        }
    }
    std::cerr << "Error: Variable '" << s << "' does not exist." << std::endl;
    std::exit(EXIT_FAILURE); // Exit the program
}

void SymbolTableClass::SetValue(const std::string & s, int v) {
    // Search from newest to oldest to set the most recent variable in scope
    for (int i = mVariables.size() - 1; i >= 0; --i) {
        if (mVariables[i].mLabel == s) {
            mVariables[i].mValue = v;
            return;
        }
    }
    std::cerr << "Error: Variable '" << s << "' does not exist." << std::endl;
    std::exit(EXIT_FAILURE); // Exit the program
}

int SymbolTableClass::GetIndex(const std::string & s) {
    // Search from newest to oldest to find the most recent variable in scope
    for (int i = mVariables.size() - 1; i >= 0; --i) {
        if (mVariables[i].mLabel == s) {
            return i;
        }
    }
    return -1; 
}

size_t SymbolTableClass::GetCount() {
    return mVariables.size();
}

void SymbolTableClass::EnterScope() {
    mCurrentScopeLevel++;
    MSG("Entering scope level " << mCurrentScopeLevel);
}

void SymbolTableClass::ExitScope() {
    MSG("Exiting scope level " << mCurrentScopeLevel);
    
    // Remove all variables from the current scope
    while (!mVariables.empty() && mVariables.back().mScopeLevel == mCurrentScopeLevel) {
        MSG("Removing variable '" << mVariables.back().mLabel << "' from scope level " << mCurrentScopeLevel);
        mVariables.pop_back();
    }
    
    // Decrement the scope level
    mCurrentScopeLevel--;
}
