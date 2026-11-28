#include <assert.h>
#include <string.h>

#include "token.h"

void token_tests_run(void)
{
    assert(strcmp(token_type_name(TOKEN_INTEGER), "INTEGER") == 0);
    assert(strcmp(token_type_name(TOKEN_PLUS), "PLUS") == 0);
    assert(strcmp(token_type_name(TOKEN_MINUS), "MINUS") == 0);
    assert(strcmp(token_type_name(TOKEN_STAR), "STAR") == 0);
    assert(strcmp(token_type_name(TOKEN_SLASH), "SLASH") == 0);
    assert(strcmp(token_type_name(TOKEN_LEFT_PAREN), "LEFT_PAREN") == 0);
    assert(strcmp(token_type_name(TOKEN_RIGHT_PAREN), "RIGHT_PAREN") == 0);
    assert(strcmp(token_type_name(TOKEN_IDENTIFIER), "IDENTIFIER") == 0);
    assert(strcmp(token_type_name(TOKEN_EOF), "EOF") == 0);
    assert(strcmp(token_type_name(TOKEN_ERROR), "ERROR") == 0);
    assert(strcmp(token_type_name(TOKEN_IF), "IF") == 0);
    assert(strcmp(token_type_name(TOKEN_ELSE), "ELSE") == 0);
    assert(strcmp(token_type_name(TOKEN_WHILE), "WHILE") == 0);
    assert(strcmp(token_type_name(TOKEN_RETURN), "RETURN") == 0);
}