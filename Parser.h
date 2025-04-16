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
    StatementNode* AssignmentStatement();
    PlusEqualsStatementNode* PlusEqualsStatement(IdentifierNode* identifierNode);
    MinusEqualsStatementNode* MinusEqualsStatement(IdentifierNode* identifierNode);
    CoutStatementNode* CoutStatement();


    // Expression Parsing Methods
    ExpressionNode* Expression();
    // New expression parsing methods for AND/OR operators
    ExpressionNode* Or();
    ExpressionNode* And();
    ExpressionNode* Relational();
    ExpressionNode* PlusMinus();
    ExpressionNode* TimesDivide();
    // Exponent will go here
    ExpressionNode* Factor();
    
    // Helper Methods
    IdentifierNode* Identifier();
    IntegerNode* Integer();
    
    // New statement parsing If and While
    IfStatementNode* IfStatement();
    WhileStatementNode* WhileStatement();

    TokenClass Match(TokenType expectedType);
    void Error(const std::string& message);

};

