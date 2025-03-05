#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#pragma once

class ParserClass {
public:
    ParserClass(ScannerClass* scanner, SymbolTableClass* symbolTable);
    StartNode* Start();

private:
    ScannerClass* mScanner;
    SymbolTableClass* mSymbolTable;

    // Grammar Methods
    ProgramNode* Program();
    BlockNode* Block();
    StatementGroupNode* StatementGroup();
    StatementNode* Statement();
    DeclarationStatementNode* DeclarationStatement();
    AssignmentStatementNode* AssignmentStatement();
    CoutStatementNode* CoutStatement();

    // Expression Parsing Methods
    ExpressionNode* Expression();
    ExpressionNode* Relational();
    ExpressionNode* PlusMinus();
    ExpressionNode* TimesDivide();
    ExpressionNode* Factor();
    
    // Helper Methods
    IdentifierNode* Identifier();
    IntegerNode* Integer();
    
    void Error(const std::string& message);
    TokenClass Match(TokenType expectedType);
};

