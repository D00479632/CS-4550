#include "Parser.h"

ParserClass::ParserClass(ScannerClass* scanner, SymbolTableClass* symbolTable) 
    : mScanner(scanner), mSymbolTable(symbolTable) {}

void ParserClass::Start() {
    Program();
    Match(ENDFILE_TOKEN);
}

void ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    Block();
}

void ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroup();
    Match(RCURLY_TOKEN);
}

void ParserClass::StatementGroup() {
    // Handle zero or more statements
    while (Statement()) {
        // Continue processing statements
    }
}

bool ParserClass::Statement() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == INT_TOKEN) {
        DeclarationStatement();
        return true;
    } else if (tt == IDENTIFIER_TOKEN) {
        AssignmentStatement();
        return true;
    } else if (tt == COUT_TOKEN) {
        CoutStatement();
        return true;
    } else if (tt == LCURLY_TOKEN) {
        Block();
        return true;
    }
    return false; // No valid statement found
}

void ParserClass::DeclarationStatement() {
    Match(INT_TOKEN);
    Identifier();
    Match(SEMICOLON_TOKEN);
}

void ParserClass::AssignmentStatement() {
    Identifier();
    Match(ASSIGNMENT_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
}

void ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
}

void ParserClass::Expression() {
    Relational(); // Start parsing with relational expressions
}

void ParserClass::Relational() {
    PlusMinus();
    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == LESS_TOKEN || tt == LESSEQUAL_TOKEN || 
        tt == GREATER_TOKEN || tt == GREATEREQUAL_TOKEN || 
        tt == EQUAL_TOKEN || tt == NOTEQUAL_TOKEN) {
        Match(tt);
        PlusMinus();
    }
}

void ParserClass::PlusMinus() {
    TimesDivide();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == PLUS_TOKEN) {
            Match(tt);
            TimesDivide();
        } else if (tt == MINUS_TOKEN) {
            Match(tt);
            TimesDivide();
        } else {
            return;
        }
    }
}

void ParserClass::TimesDivide() {
    Factor();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == TIMES_TOKEN) {
            Match(tt);
            Factor();
        } else if (tt == DIVIDE_TOKEN) {
            Match(tt);
            Factor();
        } else {
            return;
        }
    }
}

void ParserClass::Factor() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == IDENTIFIER_TOKEN) {
        Match(tt); // Match identifier
    } else if (tt == INTEGER_TOKEN) {
        Match(tt); // Match integer
    } else if (tt == LPAREN_TOKEN) {
        Match(tt); // Match left parenthesis
        Relational(); // Parse the expression inside parentheses
        Match(RPAREN_TOKEN); // Match right parenthesis
    } else {
        std::cerr << "Error in ParserClass::Factor at line " << mScanner->GetLineNumber() << ". Unexpected token: " <<
            mScanner->PeekNextToken().GetTokenTypeName() << std::endl;
        exit(1);
    }
}

void ParserClass::Identifier() {
    Match(IDENTIFIER_TOKEN); // Match an identifier token
}

void ParserClass::Integer() {
    Match(INTEGER_TOKEN); // Match an integer token
}

TokenClass ParserClass::Match(TokenType expectedType) {
    TokenClass currentToken = mScanner->GetNextToken(false);
    if (currentToken.GetTokenType() != expectedType) {
        std::cerr << "Error in ParserClass::Match at line " << mScanner->GetLineNumber() << ". " << std::endl;
        std::cerr << "Expected token type " <<
            TokenClass::GetTokenTypeName(expectedType) <<
            ", but got type " << currentToken.GetTokenTypeName() <<
            std::endl;
        exit(1);
    }
    MSG("\tSuccessfully matched Token Type: " <<
        currentToken.GetTokenTypeName() << ". Lexeme: \"" <<
        currentToken.GetLexeme() << "\"");
    return currentToken; // the one we just processed
}

void ParserClass::Error(const std::string& message) {
    std::cerr << "Error in ParserClass::Error at line " << mScanner->GetLineNumber() << ". Parser Error: " << message << std::endl;
    exit(1); // Exit the program on error
}