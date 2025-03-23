#include "Parser.h"

ParserClass::ParserClass(ScannerClass* scanner, SymbolTableClass* symbolTable) 
    : mScanner(scanner), mSymbolTable(symbolTable) {}

StartNode * ParserClass::Start() {
    ProgramNode *pn = Program();
    Match(ENDFILE_TOKEN);
    StartNode * sn = new StartNode(pn);
    return sn;
}

ProgramNode * ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode *blockNode = Block();
    return new ProgramNode(blockNode);
}

BlockNode * ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroupNode *statementGroupNode = StatementGroup();
    Match(RCURLY_TOKEN);
    return new BlockNode(statementGroupNode);
}

StatementGroupNode * ParserClass::StatementGroup() {
    StatementGroupNode *groupNode = new StatementGroupNode();
    while (true) {
        StatementNode *statementNode = Statement();
        if (statementNode == nullptr) break;
        groupNode->AddStatement(statementNode);
    }
    return groupNode;
}

StatementNode * ParserClass::Statement() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == INT_TOKEN) {
        return DeclarationStatement();
    } else if (tt == IDENTIFIER_TOKEN) {
        return AssignmentStatement();
    } else if (tt == COUT_TOKEN) {
        return CoutStatement();
    } else if (tt == LCURLY_TOKEN) {
        return Block();
    } else if (tt == IF_TOKEN) {
        return IfStatement();
    } else if (tt == WHILE_TOKEN) {
        return WhileStatement();
    }
    return nullptr;
}

DeclarationStatementNode * ParserClass::DeclarationStatement() {
    Match(INT_TOKEN);
    IdentifierNode *identifierNode = Identifier();
    Match(SEMICOLON_TOKEN);
    return new DeclarationStatementNode(identifierNode);
}

AssignmentStatementNode * ParserClass::AssignmentStatement() {
    IdentifierNode *identifierNode = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode *expressionNode = Expression();
    Match(SEMICOLON_TOKEN);
    return new AssignmentStatementNode(identifierNode, expressionNode);
}

CoutStatementNode * ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    ExpressionNode *expressionNode = Expression();
    Match(SEMICOLON_TOKEN);
    return new CoutStatementNode(expressionNode);
}

// Expression -> Or -> And -> Relational -> PlusMinus -> TimesDivide -> Exponent -> Factor.

ExpressionNode * ParserClass::Expression() {
    return Or();
}

ExpressionNode * ParserClass::Or() {
    ExpressionNode *current = And();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == OR_TOKEN) {
            Match(tt);
            current = new OrNode(current, And());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::And() {
    ExpressionNode *current = Relational();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == AND_TOKEN) {
            Match(tt);
            current = new AndNode(current, Relational());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::Relational() {
    ExpressionNode *left = PlusMinus();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == LESS_TOKEN || tt == LESSEQUAL_TOKEN || 
        tt == GREATER_TOKEN || tt == GREATEREQUAL_TOKEN || 
        tt == EQUAL_TOKEN || tt == NOTEQUAL_TOKEN) {
        Match(tt);
        ExpressionNode *right = PlusMinus();
        if (tt == LESS_TOKEN) return new LessNode(left, right);
        else if (tt == LESSEQUAL_TOKEN) return new LessEqualNode(left, right);
        else if (tt == GREATER_TOKEN) return new GreaterNode(left, right);
        else if (tt == GREATEREQUAL_TOKEN) return new GreaterEqualNode(left, right);
        else if (tt == EQUAL_TOKEN) return new EqualNode(left, right);
        else if (tt == NOTEQUAL_TOKEN) return new NotEqualNode(left, right);
    }
    return left;
}

ExpressionNode * ParserClass::PlusMinus() {
    ExpressionNode *current = TimesDivide();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == PLUS_TOKEN) {
            Match(tt);
            current = new PlusNode(current, TimesDivide());
        } else if (tt == MINUS_TOKEN) {
            Match(tt);
            current = new MinusNode(current, TimesDivide());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::TimesDivide() {
    ExpressionNode *current = Factor();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == TIMES_TOKEN) {
            Match(tt);
            current = new TimesNode(current, Factor());
        } else if (tt == DIVIDE_TOKEN) {
            Match(tt);
            current = new DivideNode(current, Factor());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::Factor() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == IDENTIFIER_TOKEN) {
        return Identifier();
    } else if (tt == INTEGER_TOKEN) {
        return Integer();
    } else if (tt == LPAREN_TOKEN) {
        Match(tt);
        ExpressionNode *expr = Expression();
        Match(RPAREN_TOKEN);
        return expr;
    }
    Error("Expected identifier, integer, or '(' in Factor");
    return nullptr;
}

IdentifierNode * ParserClass::Identifier() {
    TokenClass token = Match(IDENTIFIER_TOKEN);
    return new IdentifierNode(token.GetLexeme(), mSymbolTable);
}

IntegerNode * ParserClass::Integer() {
    TokenClass token = Match(INTEGER_TOKEN);
    return new IntegerNode(atoi(token.GetLexeme().c_str()));
}

IfStatementNode* ParserClass::IfStatement() {
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode* condition = Expression();
    Match(RPAREN_TOKEN);
    StatementNode* thenStatement = Statement();
    return new IfStatementNode(condition, thenStatement);
}

WhileStatementNode* ParserClass::WhileStatement() {
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode* condition = Expression();
    Match(RPAREN_TOKEN);
    StatementNode* body = Statement();
    return new WhileStatementNode(condition, body);
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
    return currentToken;
}

void ParserClass::Error(const std::string& message) {
    std::cerr << "Error in ParserClass::Error at line " << mScanner->GetLineNumber() << ". Parser Error: " << message << std::endl;
    exit(1);
}