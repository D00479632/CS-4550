#include "Token.h"

// Implementation of the TokenClass constructor
TokenClass::TokenClass(TokenType type, const std::string &lexeme) : mType(type), mLexeme(lexeme) {
    MSG("Creating token with type " << type << " (" << gTokenTypeNames[type] << ") and lexeme: '" << lexeme << "'");
    
    // Check for reserved words:
    if (mLexeme == "void") {
        mType = VOID_TOKEN;
        MSG("  -> Changed to VOID_TOKEN");
    } else if (mLexeme == "main") {
        mType = MAIN_TOKEN;
        MSG("  -> Changed to MAIN_TOKEN");
    } else if (mLexeme == "int") {
        mType = INT_TOKEN;
        MSG("  -> Changed to INT_TOKEN");
    } else if (mLexeme == "cout") {
        mType = COUT_TOKEN;
        MSG("  -> Changed to COUT_TOKEN");
    } else if (mLexeme == "if") {
        mType = IF_TOKEN;
        MSG("  -> Changed to IF_TOKEN");
    } else if (mLexeme == "while") {
        mType = WHILE_TOKEN;
        MSG("  -> Changed to WHILE_TOKEN");
    } else if (mLexeme == "endl") {
        mType = ENDL_TOKEN;
        MSG("  -> Changed to ENDL_TOKEN");
    } else if (mLexeme == "(") {
        // Special debugging - parentheses confusion fix
        MSG("  -> CRITICAL: '(' should be LPAREN_TOKEN (19)");
        mType = LPAREN_TOKEN;
    } else if (mLexeme == ")") {
        // Special debugging - parentheses confusion fix
        MSG("  -> CRITICAL: ')' should be RPAREN_TOKEN (20)"); 
        mType = RPAREN_TOKEN;
    } else if (mLexeme == "{") {
        // Special debugging - braces confusion fix
        MSG("  -> CRITICAL: '{' should be LCURLY_TOKEN (21)");
        mType = LCURLY_TOKEN;
    } else if (mLexeme == "}") {
        // Special debugging - braces confusion fix
        MSG("  -> CRITICAL: '}' should be RCURLY_TOKEN (22)");
        mType = RCURLY_TOKEN;
    }
    
    MSG("  => Final token type: " << mType << " (" << gTokenTypeNames[mType] << ")");
}

// Implementation of the insertion stream operator for the TokenClass objects
// Idk if this is how we overwrite it
std::ostream & operator<<(std::ostream &out, const TokenClass & tc) {
    out << "Token Type: " << tc.GetTokenType() << ", "
        << "Token Name: " << tc.GetTokenTypeName() << ", "
        << "Token Lexeme: " << tc.GetLexeme();
    return out;
} 