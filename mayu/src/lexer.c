#include <stdbool.h>
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

static bool lexer_is_alpha(char c){
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

static bool lexer_is_alphanumeric(char c){
    return lexer_is_alpha(c) || ('0' <= c && c <= '9');
}

static char lexer_peek(const Lexer* lexer){
    return lexer->source[lexer->current];
}

static char lexer_advance(Lexer* lexer){
    if (lexer_is_at_end(lexer)) return '\0';

    char previous_char = '\0';

    if (lexer->current > 0) {
        previous_char = lexer->source[lexer->current - 1];
    }

    char current_char = lexer_peek(lexer);
    lexer->current++;

    if (current_char == '\r') {
        lexer->line++;
        lexer->column = 1;
    } else if (current_char == '\n') {
        if (previous_char != '\r') {
            lexer->line++;
            lexer->column = 1;
        }
    } else {
        lexer->column++;
    }

    return current_char;
}

Token lexer_next_token(Lexer *lexer) {
    while (!lexer_is_at_end(lexer)) {
        char current_char = lexer_peek(lexer);

        if (current_char != ' ' && current_char != '\n' && current_char != '\r' && current_char != '\t' && current_char != '\v' && current_char != '\f') {
            break;
        }

        lexer_advance(lexer);
    }

    Token token;

    if (lexer_is_at_end(lexer)) {
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

        if (lexer_is_alpha(current_char) || current_char == '_') {
            token.type = TOKEN_IDENTIFIER;
            while (!lexer_is_at_end(lexer)) {
                char c = lexer_peek(lexer);

                if (lexer_is_alphanumeric(c) || c == '_') {
                    lexer_advance(lexer);
                } else {
                    break;
                }
            }
        } else if (current_char >= '0' && current_char <= '9') {
            token.type = TOKEN_INTEGER;
            while (!lexer_is_at_end(lexer) && lexer_peek(lexer) >= '0' && lexer_peek(lexer) <= '9') {
                lexer_advance(lexer);
            }
        }
        else { 
            switch (current_char) {
                case '+':
                    token.type = TOKEN_PLUS;
                    lexer_advance(lexer);
                    break;
                case '-':
                    token.type = TOKEN_MINUS;
                    lexer_advance(lexer);
                    break;
                case '/':
                    token.type = TOKEN_SLASH;
                    lexer_advance(lexer);
                    break;
                case '*':
                    token.type = TOKEN_STAR;
                    lexer_advance(lexer);
                    break;
                case '(':
                    token.type = TOKEN_LEFT_PAREN;
                    lexer_advance(lexer);
                    break;
                case ')':
                    token.type = TOKEN_RIGHT_PAREN;
                    lexer_advance(lexer);
                    break;
                default:
                    token.type = TOKEN_ERROR;
                    lexer_advance(lexer);
                    break;
            }
        }

        token.length = lexer->current - token.start;

        if (token.type == TOKEN_IDENTIFIER){
            switch (token.length)
            {
            case 2:
                if (lexer->source[token.start] == 'i' 
                    && lexer->source[token.start + 1] == 'f') {
                        token.type = TOKEN_IF;
                    }
                break;
            case 4:
                if (lexer->source[token.start] == 'e'
                    && lexer->source[token.start + 1] == 'l'
                    && lexer->source[token.start + 2] == 's'
                    && lexer->source[token.start + 3] == 'e') {
                        token.type = TOKEN_ELSE;
                    }
                break;
            case 5:
                if (lexer->source[token.start] == 'w'
                    && lexer->source[token.start + 1] == 'h'
                    && lexer->source[token.start + 2] == 'i'
                    && lexer->source[token.start + 3] == 'l'
                    && lexer->source[token.start + 4] == 'e') {
                        token.type = TOKEN_WHILE;
                    }
                break;
            case 6:
                if (lexer->source[token.start] == 'r'
                    && lexer->source[token.start + 1] == 'e'
                    && lexer->source[token.start + 2] == 't'
                    && lexer->source[token.start + 3] == 'u'
                    && lexer->source[token.start + 4] == 'r'
                    && lexer->source[token.start + 5] == 'n') {
                        token.type = TOKEN_RETURN;
                    }
                break;
            }
        }
    }
    return token;
}