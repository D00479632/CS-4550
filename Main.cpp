#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include <iostream>
#include "Parser.h"

// Problem 13: Code Generator - CodeAndExecute function
void CodeAndExecute(std::string inputFile) {
    // Create scanner, symbol table, and parser objects.
    ScannerClass scanner(inputFile);
    SymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);
    
    // Do the parsing, which results in a parse tree.
    StartNode* root = parser.Start();
    
    // Create the machine code instructions from the parse tree
    InstructionsClass machineCode;
    root->Code(machineCode);
    machineCode.Finish();
    //machineCode.PrintAllMachineCodes();
    
    // Execute the machine code instructions previously created
    machineCode.Execute();
    
    // cleanup recursively
    delete root;
}

void TestParserNoOutput() {
    std::cout << "Running TestParserNoOutput...\n";
    ScannerClass scanner("code1.txt");
    SymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);

    try {
        parser.Start();  // This internally calls Match()
        std::cout << "TestParser passed!\n\n";
    } catch (...) {
        std::cerr << "TestParser failed!\n\n";
    }
}
    
void TestParserOutput() {
    std::cout << "Running TestParserOutput...\n";
    ScannerClass scanner("code1.txt");
    SymbolTableClass st;
    ParserClass p(&scanner, &st);

    try {
        StartNode* s = p.Start();  
        std::cout << "TestParser passed!\n\n";
        delete s;
    } catch (...) {
        std::cerr << "TestParser failed!\n\n";
    }

}

void TestInterpreter() {
    std::cout << "Running Interpreter Test...\n";
    ScannerClass scanner("code11.txt");
    SymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);

    try {
        StartNode* start = parser.Start();
        std::cout << "Parsing completed successfully. Starting interpretation...\n";
        start->Interpret();
        std::cout << "\nInterpretation completed successfully!\n\n";
        delete start;
    } catch (...) {
        std::cerr << "Error during parsing or interpretation!\n\n";
    }
}

int main() {
    //TestParserNoOutput();
    //TestParserOutput();
    std::cout << "\nTesting Interpreter:\n";
    TestInterpreter();
    
    // Problem 14: Incremental testing of code generator
    std::cout << "\nTesting coding:\n";
    CodeAndExecute("code11.txt");
    return 0;
}

/*
int main() {
    // Create symbol table
    // Pref: SymbolTableClass symbolTable;
    SymbolTableClass* symbolTable = new SymbolTableClass();
    // SymbolTableClass symbolTable;
    
    // Create the identifier node for 'sum'
    IdentifierNode* sumId = new IdentifierNode("sum", symbolTable);
    
    // Create the declaration: "int sum;"
    DeclarationStatementNode* declaration = new DeclarationStatementNode(sumId);
    
    // Create the assignment: "sum = 35 + 400;"
    IntegerNode* num35 = new IntegerNode(35);
    IntegerNode* num400 = new IntegerNode(400);
    PlusNode* addition = new PlusNode(num35, num400);
    IdentifierNode* sumId2 = new IdentifierNode("sum", symbolTable);
    AssignmentStatementNode* assignment = new AssignmentStatementNode(sumId2, addition);
    
    // Create the cout statement: "cout << sum;"
    IdentifierNode* sumId3 = new IdentifierNode("sum", symbolTable);
    CoutStatementNode* coutStatement = new CoutStatementNode(sumId3);
    
    // Create statement group and add all statements
    StatementGroupNode* statementGroup = new StatementGroupNode();
    statementGroup->AddStatement(declaration);
    statementGroup->AddStatement(assignment);
    statementGroup->AddStatement(coutStatement);
    
    // Create block node
    BlockNode* block = new BlockNode(statementGroup);
    
    // Create program node
    ProgramNode* program = new ProgramNode(block);
    
    // Create the root (start node)
    StartNode* start = new StartNode(program);
    
    // Clean up everything by deleting the root
    delete start;
    
    // Clean up symbol table
    delete symbolTable;
    
    // I don't know if this would mean that there was no errors.
    std::cout << "Test completed successfully!" << std::endl;
    return 0;
}
*/

/*
int main() {
    ScannerClass scanner("code.txt"); // Create ScannerClass object
    TokenType tt;
    SymbolTableClass symbolTable;

    do {
        TokenClass tc = scanner.GetNextToken(false); // Get the next token
        std::cout << tc << std::endl; // Print the token
        tt = tc.GetTokenType(); // Get the token type
    } while (tt != ENDFILE_TOKEN); // Continue until ENDFILE_TOKEN is reached


    // Test adding a variable
    symbolTable.AddEntry("x"); // Should succeed
    // WORKS
    //symbolTable.AddEntry("x"); // Should trigger error and exit

    // Test getting a variable value
    int value = symbolTable.GetValue("x"); // Should succeed
    std::cout << "value of x: " + std::to_string(value) << std::endl;
    // WORKS
    //value = symbolTable.GetValue("y"); // Should trigger error and exit

    // Test setting a variable value
    symbolTable.SetValue("x", 10); // Should succeed
    int value2 = symbolTable.GetValue("x"); // Should succeed
    std::cout << "value of x: " + std::to_string(value2) << std::endl;

    // WORKS
    //symbolTable.SetValue("y", 10); // Should trigger error and exit

    int getIndexX = symbolTable.GetIndex("x");
    std::cout << "index of x: " + std::to_string(getIndexX) << std::endl;

    //symbolTable.GetIndex("y"); // Should return -1

    return 0;
}
*/