#include "Token.h"

// Implementation of the TokenClass constructor
TokenClass::TokenClass(TokenType type, const std::string &lexeme) : mType(type), mLexeme(lexeme) {
    // Check for reserved words:
    if (mLexeme == "void") {
        mType = VOID_TOKEN;
    } else if (mLexeme == "main") {
        mType = MAIN_TOKEN;
    } else if (mLexeme == "int") {
        mType = INT_TOKEN;
    } else if (mLexeme == "cout") {
        mType = COUT_TOKEN;
    } else if (mLexeme == "if") {
        mType = IF_TOKEN;
    } else if (mLexeme == "while") {
        mType = WHILE_TOKEN;
    } else if (mLexeme == "endl") {
        mType = ENDL_TOKEN;
    }
}

// Implementation of the insertion stream operator for the TokenClass objects
// Idk if this is how we overwrite it
std::ostream & operator<<(std::ostream &out, const TokenClass & tc) {
    out << "Token Type: " << tc.GetTokenType() << ", "
        << "Token Name: " << tc.GetTokenTypeName() << ", "
        << "Token Lexeme: " << tc.GetLexeme();
    return out;
} 