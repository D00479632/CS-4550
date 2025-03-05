#include "Scanner.h"
#include "Symbol.h"
#pragma once

class ParserClass {
public:
    ParserClass(ScannerClass* scanner, SymbolTableClass* symbolTable);
    void Start();

private:
    ScannerClass* mScanner;
    SymbolTableClass* mSymbolTable;

    // Grammar Methods
    void Program();
    void Block();
    void StatementGroup();
    bool Statement();
    void DeclarationStatement();
    void AssignmentStatement();
    void CoutStatement();

    // Expression Parsing Methods
    void Expression();
    void Relational();
    void PlusMinus();
    void TimesDivide();
    void Factor();
    
    // Helper Methods
    void Identifier();
    void Integer();
    
    void Error(const std::string& message);
    TokenClass Match(TokenType expectedType);
};

