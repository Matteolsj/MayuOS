#include <assert.h>
#include <string.h>

#include "token.h"

void token_tests_run(void)
{
    assert(strcmp(token_type_name(TOKEN_INTEGER), "INTEGER") == 0);
    assert(strcmp(token_type_name(TOKEN_PLUS), "PLUS") == 0);
    assert(strcmp(token_type_name(TOKEN_EOF), "EOF") == 0);
    assert(strcmp(token_type_name(TOKEN_ERROR), "ERROR") == 0);
}