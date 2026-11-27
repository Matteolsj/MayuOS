#ifndef MAYU_LEXER_H
#define MAYU_LEXER_H

#include <stddef.h>
#include "token.h"

typedef struct {
    const char* source;
    size_t source_length;

    size_t current;

    size_t line;
    size_t column;
} Lexer;


/*
Initializes a lexer.
The source must remain valid while the lexer is in use!
*/
void lexer_init(Lexer *lexer, const char *source, size_t source_length);

Token lexer_next_token(Lexer *lexer);

#endif