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
    // Declare the variable to get its index in mData
    mIdentifierNode->DeclareVariable();
    
    // If there's an initialization expression, evaluate it and store the result
    if (mInitializationExpression) {
        mInitializationExpression->CodeEvaluate(machineCode);
        machineCode.PopAndStore(mIdentifierNode->GetIndex());
    }
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

// PlusEqualsStatementNode implementation
PlusEqualsStatementNode::PlusEqualsStatementNode(IdentifierNode* identifier, ExpressionNode* expression)
    : mIdentifierNode(identifier), mExpressionNode(expression) {
}

PlusEqualsStatementNode::~PlusEqualsStatementNode() {
    MSG("Deleting PlusEqualsStatementNode");
    delete mIdentifierNode;
    delete mExpressionNode;
}

void PlusEqualsStatementNode::Interpret() {
    int currentValue = mIdentifierNode->Evaluate();
    int expressionValue = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(currentValue + expressionValue);
}

void PlusEqualsStatementNode::Code(InstructionsClass &machineCode) {
    // Get the index where this variable is stored in mData
    int index = mIdentifierNode->GetIndex();
    
    // Push the current value of the variable
    machineCode.PushVariable(index);
    
    // Push the expression value
    mExpressionNode->CodeEvaluate(machineCode);
    
    // Add them together
    machineCode.PopPopAddPush();
    
    // Store the result back in the variable
    machineCode.PopAndStore(index);
}

// MinusEqualsStatementNode implementation
MinusEqualsStatementNode::MinusEqualsStatementNode(IdentifierNode* identifier, ExpressionNode* expression)
    : mIdentifierNode(identifier), mExpressionNode(expression) {
}

MinusEqualsStatementNode::~MinusEqualsStatementNode() {
    MSG("Deleting MinusEqualsStatementNode");
    delete mIdentifierNode;
    delete mExpressionNode;
}

void MinusEqualsStatementNode::Interpret() {
    int currentValue = mIdentifierNode->Evaluate();
    int expressionValue = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(currentValue - expressionValue);
}

void MinusEqualsStatementNode::Code(InstructionsClass &machineCode) {
    // Get the index where this variable is stored in mData
    int index = mIdentifierNode->GetIndex();
    
    // Push the current value of the variable
    machineCode.PushVariable(index);
    
    // Push the expression value
    mExpressionNode->CodeEvaluate(machineCode);
    
    // Subtract the expression from the variable
    machineCode.PopPopSubPush();
    
    // Store the result back in the variable
    machineCode.PopAndStore(index);
}

CoutStatementNode::CoutStatementNode() {
}

CoutStatementNode::~CoutStatementNode() {
    MSG("Deleting CoutStatementNode");
    for (ExpressionNode* expr : mExpressions) {
        if (expr) delete expr;
    }
}

void CoutStatementNode::AddExpression(ExpressionNode* expression) {
    mExpressions.push_back(expression);
}

void CoutStatementNode::AddEndl() {
    mExpressions.push_back(NULL);
}

void CoutStatementNode::Interpret() {
    for (size_t i = 0; i < mExpressions.size(); i++) {
        if (mExpressions[i] == NULL) {
            std::cout << std::endl;
        } else {
            int value = mExpressions[i]->Evaluate();
            std::cout << value;
        }
    }
}

// Problem 6: Code Generator - CoutStatementNode implementation
void CoutStatementNode::Code(InstructionsClass &machineCode) {
    for (size_t i = 0; i < mExpressions.size(); i++) {
        if (mExpressions[i] == NULL) {
            machineCode.WriteEndlLinux64();
        } else {
            // Generate code to evaluate the expression and leave its value on the stack
            mExpressions[i]->CodeEvaluate(machineCode);
            // Generate code to pop the value from the stack and write it
            machineCode.PopAndWrite();
        }
    }
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

// Problem 11: Code Generator - PlusNode implementation
void PlusNode::CodeEvaluate(InstructionsClass &machineCode) {
    // Generate code to evaluate left operand and leave result on stack
    mLeft->CodeEvaluate(machineCode);
    
    // Generate code to evaluate right operand and leave result on stack
    mRight->CodeEvaluate(machineCode);
    
    // Generate code to pop both values, add them, and push result
    machineCode.PopPopAddPush();
}

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int MinusNode::Evaluate() {
    return mLeft->Evaluate() - mRight->Evaluate();
}

// Problem 12: Code Generator - MinusNode implementation
void MinusNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int TimesNode::Evaluate() {
    return mLeft->Evaluate() * mRight->Evaluate();
}

// Problem 12: Code Generator - TimesNode implementation
void TimesNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int DivideNode::Evaluate() {
    return mLeft->Evaluate() / mRight->Evaluate();
}

// Problem 12: Code Generator - DivideNode implementation
void DivideNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopDivPush();
}

// Comparison Nodes implementations
LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int LessNode::Evaluate() {
    return mLeft->Evaluate() < mRight->Evaluate() ? 1 : 0;
}

// Problem 12: Code Generator - LessNode implementation
void LessNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int LessEqualNode::Evaluate() {
    return mLeft->Evaluate() <= mRight->Evaluate() ? 1 : 0;
}

// Problem 12: Code Generator - LessEqualNode implementation
void LessEqualNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopLessEqualPush();
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int GreaterNode::Evaluate() {
    return mLeft->Evaluate() > mRight->Evaluate() ? 1 : 0;
}

// Problem 12: Code Generator - GreaterNode implementation
void GreaterNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int GreaterEqualNode::Evaluate() {
    return mLeft->Evaluate() >= mRight->Evaluate() ? 1 : 0;
}

// Problem 12: Code Generator - GreaterEqualNode implementation
void GreaterEqualNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterEqualPush();
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int EqualNode::Evaluate() {
    return mLeft->Evaluate() == mRight->Evaluate() ? 1 : 0;
}

// Problem 12: Code Generator - EqualNode implementation
void EqualNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopEqualPush();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int NotEqualNode::Evaluate() {
    return mLeft->Evaluate() != mRight->Evaluate() ? 1 : 0;
}

// Problem 12: Code Generator - NotEqualNode implementation
void NotEqualNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopNotEqualPush();
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
    // Enter a new scope before interpreting the block
    SymbolTableClass* symbolTable = nullptr;
    
    // Find the symbol table to use for scope management
    // We need to find an IdentifierNode within the statements to get access to the symbol table
    for (size_t i = 0; i < mStatementGroupNode->GetStatementCount(); i++) {
        DeclarationStatementNode* declStatement = 
            dynamic_cast<DeclarationStatementNode*>(mStatementGroupNode->GetStatement(i));
        if (declStatement) {
            IdentifierNode* identNode = declStatement->GetIdentifierNode();
            if (identNode) {
                symbolTable = identNode->GetSymbolTable();
                break;
            }
        }
        
        AssignmentStatementNode* assignStatement = 
            dynamic_cast<AssignmentStatementNode*>(mStatementGroupNode->GetStatement(i));
        if (assignStatement) {
            IdentifierNode* identNode = assignStatement->GetIdentifierNode();
            if (identNode) {
                symbolTable = identNode->GetSymbolTable();
                break;
            }
        }
    }
    
    if (symbolTable) {
        symbolTable->EnterScope();
    }
    
    // Interpret the statement group
    mStatementGroupNode->Interpret();
    
    // Exit the scope after interpreting the block
    if (symbolTable) {
        symbolTable->ExitScope();
    }
}

// Problem 3: Code Generator - BlockNode implementation
void BlockNode::Code(InstructionsClass &machineCode) {
    // Enter a new scope before generating code for the block
    SymbolTableClass* symbolTable = nullptr;
    
    // Find the symbol table to use for scope management
    // We need to find an IdentifierNode within the statements to get access to the symbol table
    for (size_t i = 0; i < mStatementGroupNode->GetStatementCount(); i++) {
        DeclarationStatementNode* declStatement = 
            dynamic_cast<DeclarationStatementNode*>(mStatementGroupNode->GetStatement(i));
        if (declStatement) {
            IdentifierNode* identNode = declStatement->GetIdentifierNode();
            if (identNode) {
                symbolTable = identNode->GetSymbolTable();
                break;
            }
        }
        
        AssignmentStatementNode* assignStatement = 
            dynamic_cast<AssignmentStatementNode*>(mStatementGroupNode->GetStatement(i));
        if (assignStatement) {
            IdentifierNode* identNode = assignStatement->GetIdentifierNode();
            if (identNode) {
                symbolTable = identNode->GetSymbolTable();
                break;
            }
        }
    }
    
    if (symbolTable) {
        symbolTable->EnterScope();
    }
    
    // Generate code for the statement group
    mStatementGroupNode->Code(machineCode);
    
    // Exit the scope after generating code for the block
    if (symbolTable) {
        symbolTable->ExitScope();
    }
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

IfStatementNode::IfStatementNode(ExpressionNode* condition, StatementNode* thenStatement, StatementNode* elseStatement)
    : mCondition(condition), mThenStatement(thenStatement), mElseStatement(elseStatement) {
}

IfStatementNode::~IfStatementNode() {
    delete mCondition;
    delete mThenStatement;
    if (mElseStatement) {
        delete mElseStatement;
    }
}

void IfStatementNode::Interpret() {
    if (mCondition->Evaluate() != 0) {
        mThenStatement->Interpret();
    } else if (mElseStatement) {
        mElseStatement->Interpret();
    }
}

// Problem 7: Code Generator - IfStatementNode implementation
void IfStatementNode::Code(InstructionsClass &machineCode) {
    // Generate code to evaluate the condition and leave its value on the stack
    mCondition->CodeEvaluate(machineCode);
    
    // Generate a conditional jump instruction (initially with 0 offset)
    // and save the address where we need to fill in the offset later
    unsigned char* skipThenAddress = machineCode.SkipIfZeroStack();
    
    // Save the current address (start of the then statement body)
    unsigned char* thenAddress = machineCode.GetAddress();
    
    // Generate code for the then statement body
    mThenStatement->Code(machineCode);
    
    if (mElseStatement) {
        // If there's an else clause, we need to jump over it after executing the then clause
        unsigned char* skipElseAddress = machineCode.Jump();
        
        // Save the address after the jump (start of the else statement)
        unsigned char* elseAddress = machineCode.GetAddress();
        
        // Set the offset for the conditional jump to skip the then clause
        // This jumps to the else clause if the condition is false
        machineCode.SetOffset(skipThenAddress, (int)(elseAddress - thenAddress));
        
        // Generate code for the else statement body
        mElseStatement->Code(machineCode);
        
        // Save the address after the else statement
        unsigned char* endAddress = machineCode.GetAddress();
        
        // Set the offset for the unconditional jump after the then clause
        // This jumps over the else clause after executing the then clause
        machineCode.SetOffset(skipElseAddress, (int)(endAddress - elseAddress));
    } else {
        // If there's no else clause, just set the offset to skip the then clause
        unsigned char* endAddress = machineCode.GetAddress();
        machineCode.SetOffset(skipThenAddress, (int)(endAddress - thenAddress));
    }
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

// Problem 12: Code Generator - AndNode implementation
void AndNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {
}

int OrNode::Evaluate() {
    return (mLeft->Evaluate() || mRight->Evaluate()) ? 1 : 0;
}

// Problem 12: Code Generator - OrNode implementation
void OrNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopOrPush();
}

DoWhileStatementNode::DoWhileStatementNode(StatementNode* body, ExpressionNode* condition)
    : mBody(body), mCondition(condition) {
}

DoWhileStatementNode::~DoWhileStatementNode() {
    delete mBody;
    delete mCondition;
}

void DoWhileStatementNode::Interpret() {
    do {
        mBody->Interpret();
    } while (mCondition->Evaluate() != 0);
}

void DoWhileStatementNode::Code(InstructionsClass &machineCode) {
    // Save the address of the start of the loop body
    unsigned char* bodyAddress = machineCode.GetAddress();
    
    // Generate code for the loop body
    mBody->Code(machineCode);
    
    // Generate code to evaluate the condition
    mCondition->CodeEvaluate(machineCode);
    
    // We want to jump back to the start if condition is non-zero
    // So we'll jump to the end if condition is zero
    unsigned char* jumpAddress = machineCode.SkipIfZeroStack();
    
    // Generate an unconditional jump back to the start
    unsigned char* jumpBackAddress = machineCode.Jump();
    
    // Save the address after both jumps
    unsigned char* endAddress = machineCode.GetAddress();
    
    // Set the offset for the conditional jump to the end if condition is zero
    machineCode.SetOffset(jumpAddress, (int)(endAddress - jumpBackAddress));
    
    // Set the offset for the unconditional jump back to the start
    machineCode.SetOffset(jumpBackAddress, (int)(bodyAddress - endAddress));
}