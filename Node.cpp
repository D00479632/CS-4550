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
    delete mProgramNode; // Clean up the ProgramNode pointer
}

ProgramNode::ProgramNode(BlockNode* node) 
    : mBlockNode(node) {
}

ProgramNode::~ProgramNode() {
    MSG("ProgramNode is deleting BlockNode");
    delete mBlockNode;
}

BlockNode::BlockNode(StatementGroupNode* node) 
    : mStatementGroupNode(node) {

}

BlockNode::~BlockNode() {
    MSG("BlockNode is deleting StatementGroupNode");
    delete mStatementGroupNode;
}

StatementGroupNode::StatementGroupNode() {
    // Vector is automatically initialized
}

StatementGroupNode::~StatementGroupNode() {
    // Delete all statements in the vector
    for (StatementNode* statement : mStatements) {
        MSG("Deleting statement in Statements.");
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
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* identifier) 
    : mIdentifierNode(identifier) {
}

DeclarationStatementNode::~DeclarationStatementNode() {
    MSG("DeclarationStatementNode is deleting IdentifierNode");
    delete mIdentifierNode;
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* identifier, ExpressionNode* expression)
    : mIdentifierNode(identifier), mExpressionNode(expression) {
}

AssignmentStatementNode::~AssignmentStatementNode() {
    MSG("AssignmentStatementNode is deleting IdentifierNode and ExpressionNode");
    delete mIdentifierNode;
    delete mExpressionNode;
}

CoutStatementNode::CoutStatementNode(ExpressionNode* expression) 
    : mExpressionNode(expression) {
}

CoutStatementNode::~CoutStatementNode() {
    MSG("CoutStatementNode is deleting ExpressionNode");
    delete mExpressionNode;
}

ExpressionNode::~ExpressionNode() {
    // empty implementation
}

// IntegerNode implementation
IntegerNode::IntegerNode(int integer) : mInteger(integer) {
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

// BinaryOperatorNode implementation
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right)
    : mLeft(left), mRight(right) {
}

BinaryOperatorNode::~BinaryOperatorNode() {
    MSG("BinaryOperatorNode is deleting Left and Right");
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