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
    }
    return "UNKNOWN";
}