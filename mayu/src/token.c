#include "token.h"

const char* token_type_name(TokenType type){
    switch (type)
    {
    case TOKEN_EOF:
        return "EOF";
    case TOKEN_ERROR:
        return "ERROR";
    case TOKEN_INTEGER:
        return "INTEGER";
    case TOKEN_PLUS:
        return "PLUS";
    case TOKEN_MINUS:
        return "MINUS";
    case TOKEN_STAR:
        return "STAR";
    case TOKEN_SLASH:
        return "SLASH";
    case TOKEN_LEFT_PAREN:
        return "LEFT_PAREN";
    case TOKEN_RIGHT_PAREN:
        return "RIGHT_PAREN";
    }
    return "UNKNOWN";
}