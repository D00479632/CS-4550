#include <vector> 
#include <string>
#pragma once

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IdentifierNode;
class IntegerNode;
class SymbolTableClass; 

class Node {
public:
    virtual ~Node(); // Virtual destructor
};

// Derive StartNode from Node
class StartNode : public Node {
public:
    StartNode(ProgramNode* node); 
    virtual ~StartNode(); 

private:
    ProgramNode* mProgramNode; 
};

// Derive ProgramNode from Node
class ProgramNode : public Node {
public:
    ProgramNode(BlockNode* node);
    virtual ~ProgramNode();

private:
    BlockNode* mBlockNode;
};

// Derive StatementGroupNode from Node
class StatementGroupNode : public Node {
public:
    StatementGroupNode();
    // It loops through each StatementNode pointer, calling delete on each one.
    virtual ~StatementGroupNode();
    // takes as a parameter a StatementNode pointer and adds it to the vector.
    void AddStatement(StatementNode* statement);

private:
    std::vector<StatementNode*> mStatements;
};

// Abstract base class for all statements
class StatementNode : public Node {
public:
    virtual ~StatementNode();
};

// Derive BlockNode from StatementNode
class BlockNode : public StatementNode {
public:
    BlockNode(StatementGroupNode* node);
    virtual ~BlockNode();

private:
    StatementGroupNode* mStatementGroupNode;
};

class DeclarationStatementNode : public StatementNode {
public:
    DeclarationStatementNode(IdentifierNode* identifier);
    virtual ~DeclarationStatementNode();

private:
    IdentifierNode* mIdentifierNode;
};

class AssignmentStatementNode : public StatementNode {
public:
    AssignmentStatementNode(IdentifierNode* identifier, ExpressionNode* expression);
    virtual ~AssignmentStatementNode();

private:
    IdentifierNode* mIdentifierNode;
    ExpressionNode* mExpressionNode;

};

class CoutStatementNode : public StatementNode {
public:
    CoutStatementNode(ExpressionNode* expression);
    virtual ~CoutStatementNode();

private:
    ExpressionNode* mExpressionNode;
};

class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;  // Pure virtual function (= 0)
};

class IntegerNode : public ExpressionNode {
public:
    IntegerNode(int integer);
    virtual int Evaluate() { return mInteger; }

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
};

class MinusNode : public BinaryOperatorNode {
public:
    MinusNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
};

class TimesNode : public BinaryOperatorNode {
public:
    TimesNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
};

class DivideNode : public BinaryOperatorNode {
public:
    DivideNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
};

class LessNode : public BinaryOperatorNode {
public:
    LessNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
};

class LessEqualNode : public BinaryOperatorNode {
public:
    LessEqualNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
};

class GreaterNode : public BinaryOperatorNode {
public:
    GreaterNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
    GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
};

class EqualNode : public BinaryOperatorNode {
public:
    EqualNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
};

class NotEqualNode : public BinaryOperatorNode {
public:
    NotEqualNode(ExpressionNode* left, ExpressionNode* right);
    virtual int Evaluate();
};
