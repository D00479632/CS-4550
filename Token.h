#pragma once // This is used to ensure the header file is included only once in a single compilation
#include "Debug.h"
#include <iostream>
#include <string>

// This assigns integers to the variables in the list ex. VOID_TOKEN = 0
enum TokenType {
    // Should I add more tokens?

    // Reserved Words: 
    VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN,
    // Relational Operators:
    LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN, EQUAL_TOKEN, NOTEQUAL_TOKEN,
    // Other Operators:
    INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN,
    PLUSEQUAL_TOKEN, MINUSEQUAL_TOKEN,
    // Other Characters:
    SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN, RCURLY_TOKEN,
    // Other Token Types:
    IDENTIFIER_TOKEN, INTEGER_TOKEN, BAD_TOKEN, ENDFILE_TOKEN, ENDL_TOKEN, 
    // Add new tokens
    IF_TOKEN, ELSE_TOKEN, WHILE_TOKEN, DO_TOKEN,
    AND_TOKEN, OR_TOKEN,  // For '&&' and '||' operators
};

// IMPORTANT: The list above and the list below MUST be kept in sync.
const std::string gTokenTypeNames[] = {
"VOID", "MAIN", "INT", "COUT",
"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL",
"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE",
"PLUSEQUAL", "MINUSEQUAL",
"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
"IDENTIFIER", "INTEGER", "BAD", "ENDFILE", "ENDL",
"IF", "ELSE", "WHILE", "DO",
"AND", "OR"
};

// Now you can access the name given the enum using: gTokenTypeNames[mType] because mType is an integer

class TokenClass {
    // Note that all the classes of the compiler project should use private, protected, and public appropiately.
    private:
        TokenType mType;
        std::string mLexeme;
    public:
        // In c++ there is pass by value, pass by reference, and pass by const reference
        // pass by value and const reference is so that we dont have to copy the value in memory like value does.
        // If we pass by const reference we protect the variable so that we cannot change it but its faster
        TokenClass(TokenType type, const std::string& lexeme);
        TokenType GetTokenType() const { return mType; }
        // The const before the return is so that it doesn't change the data of the class
        const std::string& GetTokenTypeName() const {
            return gTokenTypeNames[mType];
        }
        std::string GetLexeme() const { return mLexeme; }
        // There are 3 types of static: static variabe in a file, static variable in a function and static method
        // In this case the method is static, which means that it is not called from an object but from the class
        // Ex. the function below would be called TokenClass.GetTokenTypeName(whatever) 
        // If it didnt have the static it would be called like T.GetTokenType() where T is a token object
        static const std::string& GetTokenTypeName(TokenType type) {
            return gTokenTypeNames[type];
        }
};

// Override the insertion stream operator for the TokenClass objets so it outputs the token type, token name, 
// and token lexeme.
std::ostream & operator<<(std::ostream &out, const TokenClass & tc);