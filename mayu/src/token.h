#ifndef MAYU_TOKEN_H
#define MAYU_TOKEN_H

#include <stddef.h>

typedef enum {
    TOKEN_INTEGER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;

    size_t start;
    size_t length;

    size_t line;
    size_t column;
} Token;

const char* token_type_name(TokenType type);

#endif