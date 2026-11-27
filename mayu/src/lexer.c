#include <stdbool.h>
#include <stdlib.h>
#include "lexer.h"

void lexer_init(Lexer *lexer, const char *source, size_t source_length){
    lexer->source = source;
    lexer->source_length = source_length;
    lexer->current = 0;
    lexer->line = 1;
    lexer->column = 1;
}

static bool lexer_is_at_end(const Lexer* lexer){
    return lexer->current >= lexer->source_length;
}

static char lexer_peek(const Lexer* lexer){
    return lexer->source[lexer->current];
}

static char lexer_advance(Lexer* lexer){
    if (lexer_is_at_end(lexer)) return '\0';

    char current_char = lexer_peek(lexer);
    lexer->current++;

    if (current_char == '\n'){
        lexer->line++;
        lexer->column = 1;
    } else {
        lexer->column++;
    }

    return current_char;
}

Token lexer_next_token(Lexer *lexer){
    while (!lexer_is_at_end(lexer)) {
        char current_char = lexer_peek(lexer);

        if (current_char != ' ' && current_char != '\n' && current_char != '\r' && current_char != '\t' && current_char != '\v' && current_char != '\f') {
            break;
        }

        lexer_advance(lexer);
    }

    Token token;

    if (lexer_is_at_end(lexer)){
        token.type = TOKEN_EOF;
        token.length = 0;
        token.column = lexer->column;
        token.line = lexer->line;
        token.start = lexer->current;
    } else {
        token.start = lexer->current;
        token.line = lexer->line;
        token.column = lexer->column;

        char current_char = lexer_peek(lexer);

        if (current_char >= '0' && current_char <= '9') {
            token.type = TOKEN_INTEGER;
            while (!lexer_is_at_end(lexer) && lexer_peek(lexer) >= '0' && lexer_peek(lexer) <= '9') {
                lexer_advance(lexer);
            }
        }
        else if (current_char == '+') {
            token.type = TOKEN_PLUS;
            lexer_advance(lexer);
        }
        else {
            token.type = TOKEN_ERROR;
            lexer_advance(lexer);
        }

        token.length = lexer->current - token.start;
    }
    return token;
}