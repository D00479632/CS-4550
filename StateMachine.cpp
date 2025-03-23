#include "StateMachineClass.h"
#include <cctype>

StateMachineClass::StateMachineClass() {
    // Initialize mCurrentState to START_STATE
    mCurrentState = START_STATE;

    // Initializing mLegalMoves
    // First, initialize all the mLegalMoves to CANNOT_MOVE_STATE
    for(int i = 0; i < LAST_STATE; i++) {
        for(int j = 0; j < LAST_CHAR; j++) {
            mLegalMoves[i][j] = CANNOT_MOVE_STATE;
        }
    }

    // Then, reset the mLegalMoves that are legitimate

    // Starting at the START STATE
    mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
    mLegalMoves[START_STATE][TAB_CHAR] = START_STATE;
    mLegalMoves[START_STATE][RETURN_CHAR] = START_STATE;

    mLegalMoves[START_STATE][EOF_CHAR] = ENDFILE_STATE;
    mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[START_STATE][LESS_THAN_CHAR] = LESS_THAN_STATE; 
    mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
    mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
    mLegalMoves[START_STATE][EXCLAMATION_CHAR] = EXCLAMATION_STATE; // Intermediate state for not equal
    mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE; 
    mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE; 
    mLegalMoves[START_STATE][GREADER_THAN_CHAR] = GREADER_THAN_STATE; 
    mLegalMoves[START_STATE][RIGHT_PARENTHESIS_CHAR] = RIGHT_PARENTHESIS_STATE;
    mLegalMoves[START_STATE][LEFT_PARENTHESIS_CHAR] = LEFT_PARENTHESIS_STATE;
    mLegalMoves[START_STATE][RIGHT_CURLY_CHAR] = RIGHT_CURLY_STATE;
    mLegalMoves[START_STATE][LEFT_CURLY_CHAR] = LEFT_CURLY_STATE;
    mLegalMoves[START_STATE][STAR_CHAR] = TIMES_STATE;
    mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;

    // Now deeper level nodes
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[LESS_THAN_STATE][LESS_THAN_CHAR] = INSERTION_STATE;
    mLegalMoves[LESS_THAN_STATE][EQUAL_CHAR] = LESS_EQUAL_STATE;
    mLegalMoves[EXCLAMATION_STATE][EQUAL_CHAR] = NOT_EQUAL_STATE;
    mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR] = EQUAL_STATE;

    // TODO: something is not working with my short comments it comments
    // everything after the // no matter if there is a return or not
    mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = SHORT_COMMENT_STATE;
    // Lets overwrite every character to go back to itself since we should ignore
    // every character unless its a return or eof then we go to start state. 
    for(int s = 0; s < LAST_CHAR; s++)
        mLegalMoves[SHORT_COMMENT_STATE][s] = SHORT_COMMENT_STATE;
    mLegalMoves[SHORT_COMMENT_STATE][RETURN_CHAR] = START_STATE;
    mLegalMoves[SHORT_COMMENT_STATE][EOF_CHAR] = START_STATE;

    mLegalMoves[DIVIDE_STATE][STAR_CHAR] = LONG_COMMENT_STATE;
    // Lets overwrite every character to go back to itself since we should ignore
    // every character unless its a star then we go to end of comment state. 
    for(int s = 0; s < LAST_CHAR; s++)
        mLegalMoves[LONG_COMMENT_STATE][s] = LONG_COMMENT_STATE;
    mLegalMoves[LONG_COMMENT_STATE][STAR_CHAR] = LONG_COMMENT_END_STATE;

    for(int s = 0; s < LAST_CHAR; s++)
        mLegalMoves[LONG_COMMENT_END_STATE][s] = LONG_COMMENT_STATE;
    mLegalMoves[LONG_COMMENT_END_STATE][STAR_CHAR] = LONG_COMMENT_END_STATE;
    mLegalMoves[LONG_COMMENT_END_STATE][DIVIDE_CHAR] = START_STATE;
    
    mLegalMoves[GREADER_THAN_STATE][EQUAL_CHAR] = GREADER_EQUAL_STATE;

    // Add new legal moves from START_STATE
    mLegalMoves[START_STATE][AND_CHAR] = AND_STATE;
    mLegalMoves[START_STATE][OR_CHAR] = OR_STATE;

    // Add transitions for double characters
    mLegalMoves[AND_STATE][AND_CHAR] = DOUBLE_AND_STATE;
    mLegalMoves[OR_STATE][OR_CHAR] = DOUBLE_OR_STATE;

    // Initializing mCorrespondingTokenTypes
    // First, initialize all states to correspond to BAD_TOKEN.
    for(int i = 0; i < LAST_STATE; i++) {
        mCorrespondingTokenTypes[i] = BAD_TOKEN;
    }

    // Then, reset end states to correspond to correct token types.
    mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[LESS_THAN_STATE] = LESS_TOKEN;
    mCorrespondingTokenTypes[LESS_EQUAL_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenTypes[NOT_EQUAL_STATE] = NOTEQUAL_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[GREADER_THAN_STATE] = GREATER_TOKEN;
    mCorrespondingTokenTypes[GREADER_EQUAL_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenTypes[RIGHT_PARENTHESIS_STATE] = RPAREN_TOKEN;
    mCorrespondingTokenTypes[LEFT_PARENTHESIS_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenTypes[RIGHT_CURLY_STATE] = RCURLY_TOKEN;
    mCorrespondingTokenTypes[LEFT_CURLY_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenTypes[DOUBLE_AND_STATE] = AND_TOKEN;
    mCorrespondingTokenTypes[DOUBLE_OR_STATE] = OR_TOKEN;
}

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType & previousTokenType) {
    // Convert the input character into an input character type
    CharacterType charType = BAD_CHAR;

    //MSG("CurrentChar: " + std::string(1, currentCharacter) + " ASCII Value: " + std::to_string(static_cast<int>(currentCharacter))); // Debug current char

    if (currentCharacter == EOF)
        charType = EOF_CHAR;
    else if (currentCharacter == '\n')
        // Because I had white space before new line and new line is considered
        // white space it was never reaching the new line if statement.
        //MSG("NEW LINE DETECTED"); // For some reason '\n' not detected
        charType = RETURN_CHAR;
    else if (isspace(currentCharacter)) 
        //MSG("WHITESPACE DETECTED");
        charType = WHITESPACE_CHAR;
    else if (currentCharacter == '\t')
        charType = TAB_CHAR;
    else if (isdigit(currentCharacter))
        charType = DIGIT_CHAR;
    else if (isalpha(currentCharacter))
        charType = LETTER_CHAR;
    else if (currentCharacter == '<')
        charType = LESS_THAN_CHAR;
    else if (currentCharacter == '=')
        charType = EQUAL_CHAR;
    else if (currentCharacter == '+')
        charType = PLUS_CHAR;
    else if (currentCharacter == '!')
        charType = EXCLAMATION_CHAR;
    else if (currentCharacter == '/')
        charType = DIVIDE_CHAR;
    else if (currentCharacter == '*')
        charType = STAR_CHAR;
    else if (currentCharacter == ';')
        charType = SEMICOLON_CHAR;
    else if (currentCharacter == '>')
        charType = GREADER_THAN_CHAR;
    else if (currentCharacter == '(')
        charType = LEFT_PARENTHESIS_CHAR;
    else if (currentCharacter == ')')
        charType = RIGHT_PARENTHESIS_CHAR;
    else if (currentCharacter == '{')
        charType = LEFT_CURLY_CHAR;
    else if (currentCharacter == '}')
        charType = RIGHT_CURLY_CHAR;
    else if (currentCharacter == '-')
        charType = MINUS_CHAR;
    else if (currentCharacter == '&')
        charType = AND_CHAR;
    else if (currentCharacter == '|')
        charType = OR_CHAR;
    else 
        charType = BAD_CHAR;

    // Bookkeeping: set previousTokenType before updating mCurrentState
    previousTokenType = mCorrespondingTokenTypes[mCurrentState];

    // Update mCurrentState based on the legal moves
    mCurrentState = mLegalMoves[mCurrentState][charType];

    // Return the current state
    return mCurrentState;
}

