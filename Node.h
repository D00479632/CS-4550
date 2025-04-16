#include <vector> 
#include <string>
#include "Instructions.h"
#pragma once

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class PlusEqualsStatementNode;
class MinusEqualsStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IdentifierNode;
class IntegerNode;
class SymbolTableClass; 

class Node {
public:
    virtual ~Node(); // Virtual destructor
    virtual void Interpret() = 0; // Pure virtual method
    // Problem 2: Code Generator - Pure virtual method for code generation
    virtual void Code(InstructionsClass &machineCode) = 0;
};

// Derive StartNode from Node
class StartNode : public Node {
public:
    StartNode(ProgramNode* node); 
    virtual ~StartNode(); 
    virtual void Interpret(); // New method
    virtual void Code(InstructionsClass &machineCode); // Problem 3: Code Generator

private:
    ProgramNode* mProgramNode; 
};

// Derive ProgramNode from Node
class ProgramNode : public Node {
public:
    ProgramNode(BlockNode* node);
    virtual ~ProgramNode();
    virtual void Interpret(); // New method
    virtual void Code(InstructionsClass &machineCode); // Problem 3: Code Generator

private:
    BlockNode* mBlockNode;
};

// Derive StatementGroupNode from Node
class StatementGroupNode : public Node {
public:
    StatementGroupNode();
    // It loops through each StatementNode pointer, calling delete on each one.
    virtual ~StatementGroupNode();
    virtual void Interpret(); // New method
    virtual void Code(InstructionsClass &machineCode); // Problem 3: Code Generator
    // takes as a parameter a StatementNode pointer and adds it to the vector.
    void AddStatement(StatementNode* statement);

private:
    std::vector<StatementNode*> mStatements;
};

// Abstract base class for all statements
class StatementNode : public Node {
public:
    virtual ~StatementNode();
    // Pure virtual because a "generic" statement has no meaning;
    // every statement must be a specific type (declaration, assignment, if, while, etc.)
    // and must provide its own interpretation logic
    virtual void Interpret() = 0;
    virtual void Code(InstructionsClass &machineCode) = 0; // Problem 3: Code Generator
};

// Derive BlockNode from StatementNode
class BlockNode : public StatementNode {
public:
    BlockNode(StatementGroupNode* node);
    virtual ~BlockNode();
    virtual void Interpret(); 
    virtual void Code(InstructionsClass &machineCode); // Problem 3: Code Generator

private:
    StatementGroupNode* mStatementGroupNode;
};

class DeclarationStatementNode : public StatementNode {
public:
    DeclarationStatementNode(IdentifierNode* identifier, ExpressionNode* initExpression = nullptr);
    virtual ~DeclarationStatementNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &machineCode); // Problem 4: Code Generator

private:
    IdentifierNode* mIdentifierNode;
    ExpressionNode* mInitializationExpression;
};

class AssignmentStatementNode : public StatementNode {
public:
    AssignmentStatementNode(IdentifierNode* identifier, ExpressionNode* expression);
    virtual ~AssignmentStatementNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &machineCode); // Problem 5: Code Generator

private:
    IdentifierNode* mIdentifierNode;
    ExpressionNode* mExpressionNode;
};

class PlusEqualsStatementNode : public StatementNode {
public:
    PlusEqualsStatementNode(IdentifierNode* identifier, ExpressionNode* expression);
    virtual ~PlusEqualsStatementNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &machineCode);

private:
    IdentifierNode* mIdentifierNode;
    ExpressionNode* mExpressionNode;
};

class MinusEqualsStatementNode : public StatementNode {
public:
    MinusEqualsStatementNode(IdentifierNode* identifier, ExpressionNode* expression);
    virtual ~MinusEqualsStatementNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &machineCode);

private:
    IdentifierNode* mIdentifierNode;
    ExpressionNode* mExpressionNode;
};

class CoutStatementNode : public StatementNode {
public:
    CoutStatementNode();
    virtual ~CoutStatementNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &machineCode); // Problem 3: Code Generator
    void AddExpression(ExpressionNode* expression);
    void AddEndl();

private:
    std::vector<ExpressionNode*> mExpressions;
    // Just use None for is end of line
    //std::vector<bool> mIsEndl;
};

class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;  // Pure virtual function
    // Problem 2: Code Generator - Pure virtual method for code generation
    virtual void CodeEvaluate(InstructionsClass &machineCode) = 0;
};

class IntegerNode : public ExpressionNode {
public:
    IntegerNode(int integer);
    virtual int Evaluate() { return mInteger; }
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator

private:
    int mInteger;
};

class IdentifierNode : public ExpressionNode {
// Note that IdentifierNode does not need a destructor because it does not 
// own the symbol table it points to.
public:
    IdentifierNode(const std::string& label, SymbolTableClass* symbolTable);
    
    void DeclareVariable();
    void SetValue(int v);
    int GetIndex() const;
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator

private:
    std::string mLabel;
    SymbolTableClass* mSymbolTable;
};

class BinaryOperatorNode : public ExpressionNode {
public:
    BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right);
    virtual ~BinaryOperatorNode();

protected:
    ExpressionNode* mLeft;
    ExpressionNode* mRight;
};

class PlusNode : public BinaryOperatorNode {
public:
    PlusNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class MinusNode : public BinaryOperatorNode {
public:
    MinusNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class TimesNode : public BinaryOperatorNode {
public:
    TimesNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class DivideNode : public BinaryOperatorNode {
public:
    DivideNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class LessNode : public BinaryOperatorNode {
public:
    LessNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class LessEqualNode : public BinaryOperatorNode {
public:
    LessEqualNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class GreaterNode : public BinaryOperatorNode {
public:
    GreaterNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
    GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class EqualNode : public BinaryOperatorNode {
public:
    EqualNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class NotEqualNode : public BinaryOperatorNode {
public:
    NotEqualNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class IfStatementNode : public StatementNode {
public:
    IfStatementNode(ExpressionNode* condition, StatementNode* thenStatement);
    virtual ~IfStatementNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &machineCode); // Problem 3: Code Generator

private:
    ExpressionNode* mCondition;
    StatementNode* mThenStatement;
};

class WhileStatementNode : public StatementNode {
public:
    WhileStatementNode(ExpressionNode* condition, StatementNode* body);
    virtual ~WhileStatementNode();
    virtual void Interpret();
    virtual void Code(InstructionsClass &machineCode); // Problem 3: Code Generator

private:
    ExpressionNode* mCondition;
    StatementNode* mBody;
};

class AndNode : public BinaryOperatorNode {
public:
    AndNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

class OrNode : public BinaryOperatorNode {
public:
    OrNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
    virtual void CodeEvaluate(InstructionsClass &machineCode); // Problem 3: Code Generator
};

// Problem 2 midterm2: Added NullStatementNode to support empty statements
class NullStatementNode : public StatementNode {
public:
    virtual void Interpret() { } // Does nothing when interpreted
    virtual void Code([[maybe_unused]] InstructionsClass &machineCode) { } // Problem 3: Code Generator - Does nothing when coded
};
