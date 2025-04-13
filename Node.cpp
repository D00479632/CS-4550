#include <iostream>
#include "Node.h"
#include "Symbol.h"
#include "Debug.h"

Node::~Node(){
}

StartNode::StartNode(ProgramNode* node) 
    : mProgramNode(node) {
}

StartNode::~StartNode() {
    MSG("Deleting startNode");
    delete mProgramNode; // Clean up the ProgramNode pointer
}

ProgramNode::ProgramNode(BlockNode* node) 
    : mBlockNode(node) {
}

ProgramNode::~ProgramNode() {
    MSG("Deleting programNode");
    delete mBlockNode;
}

BlockNode::BlockNode(StatementGroupNode* node) 
    : mStatementGroupNode(node) {

}

BlockNode::~BlockNode() {
    MSG("Deleting blockNode");
    delete mStatementGroupNode;
}

StatementGroupNode::StatementGroupNode() {
    // Vector is automatically initialized
}

StatementGroupNode::~StatementGroupNode() {
    // Delete all statements in the vector
    for (StatementNode* statement : mStatements) {
        MSG("Deleting statementNode");
        delete statement;
    }
}

void StatementGroupNode::AddStatement(StatementNode* statement) {
    mStatements.push_back(statement);
}

// StatementNode implementation
StatementNode::~StatementNode() {
}

// DeclarationStatementNode implementation
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* identifier, ExpressionNode* initExpression) 
    : mIdentifierNode(identifier), mInitializationExpression(initExpression) {
}

DeclarationStatementNode::~DeclarationStatementNode() {
    MSG("Deleting DeclarationStatementNode");
    delete mIdentifierNode;
    if (mInitializationExpression) {
        delete mInitializationExpression;
    }
}

void DeclarationStatementNode::Interpret() {
    mIdentifierNode->DeclareVariable();
    if (mInitializationExpression) {
        int value = mInitializationExpression->Evaluate();
        mIdentifierNode->SetValue(value);
    }
}

// Problem 4: Code Generator - DeclarationStatementNode implementation
void DeclarationStatementNode::Code(InstructionsClass &machineCode) {
    mIdentifierNode->DeclareVariable();
    // Note: Variable storage will be handled by InstructionsClass's mData array
    // No need to set initial value as in Interpret
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* identifier, ExpressionNode* expression)
    : mIdentifierNode(identifier), mExpressionNode(expression) {
}

AssignmentStatementNode::~AssignmentStatementNode() {
    MSG("Deleting AssignmentStatementNode");
    delete mIdentifierNode;
    delete mExpressionNode;
}

void AssignmentStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(value);
}

// Problem 5: Code Generator - AssignmentStatementNode implementation
void AssignmentStatementNode::Code(InstructionsClass &machineCode) {
    // Generate code to evaluate the expression and leave its value on the stack
    mExpressionNode->CodeEvaluate(machineCode);
    
    // Get the index where this variable is stored in mData
    int index = mIdentifierNode->GetIndex();
    
    // Generate code to pop the value from the stack and store it in mData[index]
    machineCode.PopAndStore(index);
}

CoutStatementNode::CoutStatementNode(ExpressionNode* expression) 
    : mExpressionNode(expression) {
}

CoutStatementNode::~CoutStatementNode() {
    MSG("Deleting CoutStatementNode");
    delete mExpressionNode;
}

ExpressionNode::~ExpressionNode() {
    // empty implementation
}

// IntegerNode implementation
IntegerNode::IntegerNode(int integer) : mInteger(integer) {
}

// Problem 10: Code Generator - IntegerNode implementation
void IntegerNode::CodeEvaluate(InstructionsClass &machineCode) {
    // Push the integer constant onto the stack
    machineCode.PushValue(mInteger);
}

// IdentifierNode implementation
IdentifierNode::IdentifierNode(const std::string& label, SymbolTableClass* symbolTable)
    : mLabel(label), mSymbolTable(symbolTable) {
}

void IdentifierNode::DeclareVariable() {
    mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v) {
    mSymbolTable->SetValue(mLabel, v);
}

int IdentifierNode::GetIndex() const {
    return mSymbolTable->GetIndex(mLabel);
}

int IdentifierNode::Evaluate() {
    return mSymbolTable->GetValue(mLabel);
}

// Problem 9: Code Generator - IdentifierNode implementation
void IdentifierNode::CodeEvaluate(InstructionsClass &machineCode) {
    // Push the variable's value onto the stack using its index in mData
    machineCode.PushVariable(this->GetIndex());
}

// BinaryOperatorNode implementation
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right)
    : mLeft(left), mRight(right) {
}

BinaryOperatorNode::~BinaryOperatorNode() {
    MSG("Deleting BinaryOperatorNode");
    delete mLeft;
    delete mRight;
}

// PlusNode implementation
PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int PlusNode::Evaluate() {
    return mLeft->Evaluate() + mRight->Evaluate();
}

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int MinusNode::Evaluate() {
    return mLeft->Evaluate() - mRight->Evaluate();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int TimesNode::Evaluate() {
    return mLeft->Evaluate() * mRight->Evaluate();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int DivideNode::Evaluate() {
    return mLeft->Evaluate() / mRight->Evaluate();
}

// Comparison Nodes implementations
LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int LessNode::Evaluate() {
    return mLeft->Evaluate() < mRight->Evaluate() ? 1 : 0;
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int LessEqualNode::Evaluate() {
    return mLeft->Evaluate() <= mRight->Evaluate() ? 1 : 0;
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int GreaterNode::Evaluate() {
    return mLeft->Evaluate() > mRight->Evaluate() ? 1 : 0;
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int GreaterEqualNode::Evaluate() {
    return mLeft->Evaluate() >= mRight->Evaluate() ? 1 : 0;
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int EqualNode::Evaluate() {
    return mLeft->Evaluate() == mRight->Evaluate() ? 1 : 0;
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int NotEqualNode::Evaluate() {
    return mLeft->Evaluate() != mRight->Evaluate() ? 1 : 0;
}

void StartNode::Interpret() {
    mProgramNode->Interpret();
}

// Problem 3: Code Generator - StartNode implementation
void StartNode::Code(InstructionsClass &machineCode) {
    mProgramNode->Code(machineCode);
}

void ProgramNode::Interpret() {
    mBlockNode->Interpret();
}

// Problem 3: Code Generator - ProgramNode implementation
void ProgramNode::Code(InstructionsClass &machineCode) {
    mBlockNode->Code(machineCode);
}

void BlockNode::Interpret() {
    mStatementGroupNode->Interpret();
}

// Problem 3: Code Generator - BlockNode implementation
void BlockNode::Code(InstructionsClass &machineCode) {
    mStatementGroupNode->Code(machineCode);
}

void StatementGroupNode::Interpret() {
    for (StatementNode* statement : mStatements) {
        statement->Interpret();
    }
}

// Problem 3: Code Generator - StatementGroupNode implementation
void StatementGroupNode::Code(InstructionsClass &machineCode) {
    for (StatementNode* statement : mStatements) {
        statement->Code(machineCode);
    }
}

void CoutStatementNode::Interpret() {
    int value = mExpressionNode->Evaluate();
    std::cout << value << " ";
}

// Problem 6: Code Generator - CoutStatementNode implementation
void CoutStatementNode::Code(InstructionsClass &machineCode) {
    // Generate code to evaluate the expression and leave its value on the stack
    mExpressionNode->CodeEvaluate(machineCode);
    
    // Generate code to pop the value from the stack and write it
    machineCode.PopAndWrite();
}

IfStatementNode::IfStatementNode(ExpressionNode* condition, StatementNode* thenStatement)
    : mCondition(condition), mThenStatement(thenStatement) {
}

IfStatementNode::~IfStatementNode() {
    delete mCondition;
    delete mThenStatement;
}

void IfStatementNode::Interpret() {
    if (mCondition->Evaluate() != 0) {
        mThenStatement->Interpret();
    }
}

// Problem 7: Code Generator - IfStatementNode implementation
void IfStatementNode::Code(InstructionsClass &machineCode) {
    // Generate code to evaluate the condition and leave its value on the stack
    mCondition->CodeEvaluate(machineCode);
    
    // Generate a conditional jump instruction (initially with 0 offset)
    // and save the address where we need to fill in the offset later
    unsigned char* insertAddress = machineCode.SkipIfZeroStack();
    
    // Save the current address (start of the statement body)
    unsigned char* address1 = machineCode.GetAddress();
    
    // Generate code for the statement body
    mThenStatement->Code(machineCode);
    
    // Save the address after the statement body
    unsigned char* address2 = machineCode.GetAddress();
    
    // Calculate and set the correct jump offset
    // This is how many bytes to skip if the condition is false
    machineCode.SetOffset(insertAddress, (int)(address2 - address1));
}

WhileStatementNode::WhileStatementNode(ExpressionNode* condition, StatementNode* body)
    : mCondition(condition), mBody(body) {
}

WhileStatementNode::~WhileStatementNode() {
    delete mCondition;
    delete mBody;
}

void WhileStatementNode::Interpret() {
    while (mCondition->Evaluate() != 0) {
        mBody->Interpret();
    }
}

// Problem 8: Code Generator - WhileStatementNode implementation
void WhileStatementNode::Code(InstructionsClass &machineCode) {
    // GetAddress 1 - Save the address of the start of the loop (where we test the condition)
    unsigned char* address1 = machineCode.GetAddress();
    
    // Code the While's test expression
    mCondition->CodeEvaluate(machineCode);
    
    // Code SkipIfZeroStack and save the address where we'll need to put the skip offset
    unsigned char* insertAddressToSkip = machineCode.SkipIfZeroStack();
    
    // GetAddress 2 - Save the address of the start of the loop body
    unsigned char* address2 = machineCode.GetAddress();
    
    // Code the While's statement (loop body)
    mBody->Code(machineCode);
    
    // Add unconditional jump back to start of loop and save its address
    unsigned char* insertAddressToJump = machineCode.Jump();
    
    // Get Address 3 - Save the address of the end of the loop
    unsigned char* address3 = machineCode.GetAddress();
    
    // Set the skip offset (how far to jump if condition is false)
    // This jumps from the SkipIfZeroStack to the end of the loop
    machineCode.SetOffset(insertAddressToSkip, (int)(address3 - address2));
    
    // Set the jump offset (how far to jump back to the start)
    // This jumps from the end back to the start of the loop
    machineCode.SetOffset(insertAddressToJump, (int)(address1 - address3));
}

AndNode::AndNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int AndNode::Evaluate() {
    return (mLeft->Evaluate() && mRight->Evaluate()) ? 1 : 0;
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int OrNode::Evaluate() {
    return (mLeft->Evaluate() || mRight->Evaluate()) ? 1 : 0;
}