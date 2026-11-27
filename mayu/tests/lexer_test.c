#include <assert.h>
#include <stdio.h>

#include "lexer.h"

static void expect_token(
    Lexer *lexer,
    TokenType expected_type,
    size_t expected_start,
    size_t expected_length,
    size_t expected_line,
    size_t expected_column
)
{
    Token token = lexer_next_token(lexer);

    assert(token.type == expected_type);
    assert(token.start == expected_start);
    assert(token.length == expected_length);
    assert(token.line == expected_line);
    assert(token.column == expected_column);
}

static void test_arithmetic_expression(void)
{
    const char source[] = "123 + 45";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_INTEGER, 0, 3, 1, 1);
    expect_token(&lexer, TOKEN_PLUS, 4, 1, 1, 5);
    expect_token(&lexer, TOKEN_INTEGER, 6, 2, 1, 7);
    expect_token(&lexer, TOKEN_EOF, 8, 0, 1, 9);
}

static void test_multiline_expression(void)
{
    const char source[] = "12\n+34";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_INTEGER, 0, 2, 1, 1);
    expect_token(&lexer, TOKEN_PLUS, 3, 1, 2, 1);
    expect_token(&lexer, TOKEN_INTEGER, 4, 2, 2, 2);
    expect_token(&lexer, TOKEN_EOF, 6, 0, 2, 4);
}

static void test_invalid_character_recovery(void)
{
    const char source[] = "12@34";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_INTEGER, 0, 2, 1, 1);
    expect_token(&lexer, TOKEN_ERROR, 2, 1, 1, 3);
    expect_token(&lexer, TOKEN_INTEGER, 3, 2, 1, 4);
    expect_token(&lexer, TOKEN_EOF, 5, 0, 1, 6);
}

static void test_empty_source(void)
{
    const char source[] = "";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_EOF, 0, 0, 1, 1);
}

static void test_whitespace_only_source(void)
{
    const char source[] = "   \t\n";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_EOF, 5, 0, 2, 1);
}

int main(void)
{
    test_arithmetic_expression();
    test_multiline_expression();
    test_invalid_character_recovery();
    test_empty_source();
    test_whitespace_only_source();

    printf("All lexer tests passed!\n");

    return 0;
}