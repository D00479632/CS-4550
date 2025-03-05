#include "Token.h"
#pragma once

// Note that as your compiler evolves, this enumeration must be kept in sync with 
// your finite automata picture of problem one.

// Programming trick: LAST_STATE and LAST_CHAR is to keep the total count
enum MachineState {
    START_STATE, // 0
    CANNOT_MOVE_STATE, // 1
    ENDFILE_STATE, // 2
    INTEGER_STATE, // 3
    IDENTIFIER_STATE, // 4
    LESS_THAN_STATE, // 5
    INSERTION_STATE, // 6
    LESS_EQUAL_STATE, // 7
    ASSIGNMENT_STATE, // 8
    EQUAL_STATE, // 9
    PLUS_STATE, // 10
    EXCLAMATION_STATE, // 11
    NOT_EQUAL_STATE, // 12
    DIVIDE_STATE, // 13
    SHORT_COMMENT_STATE, // 14
    LONG_COMMENT_STATE, // 15
    LONG_COMMENT_END_STATE, // 16
    SEMICOLON_STATE, // 17
    GREADER_THAN_STATE, // 18
    GREADER_EQUAL_STATE, // 19
    RIGHT_PARENTHESIS_STATE, // 20
    LEFT_PARENTHESIS_STATE, // 21
    RIGHT_CURLY_STATE, // 22
    LEFT_CURLY_STATE, // 23
    TIMES_STATE, // 24
    MINUS_STATE, // 25
    
    LAST_STATE // Ensure this is the last state
};

enum CharacterType {
    BAD_CHAR,
    WHITESPACE_CHAR,
    TAB_CHAR,
    RETURN_CHAR,
    EOF_CHAR,
    DIGIT_CHAR,
    LETTER_CHAR,
    LESS_THAN_CHAR,
    EQUAL_CHAR,
    PLUS_CHAR,
    EXCLAMATION_CHAR,
    DIVIDE_CHAR,
    STAR_CHAR,
    SEMICOLON_CHAR,
    GREADER_THAN_CHAR,
    LEFT_PARENTHESIS_CHAR,
    RIGHT_PARENTHESIS_CHAR,
    LEFT_CURLY_CHAR,
    RIGHT_CURLY_CHAR,
    MINUS_CHAR,

    LAST_CHAR // Ensure this is the last character type
};

class StateMachineClass {
    public:
        StateMachineClass();
        MachineState UpdateState(char currentCharacter, TokenType & previousTokenType);

    private:
        MachineState mCurrentState;

        // The matix of legal moves:
        MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

        // Which end-machine-states correspond to which toke types.
        // (non end states correspond to the BAD_TOKEN token type)
        TokenType mCorrespondingTokenTypes[LAST_STATE];
};