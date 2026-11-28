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

static void test_LF_expression(void)
{
    const char source[] = "12\n+34";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_INTEGER, 0, 2, 1, 1);
    expect_token(&lexer, TOKEN_PLUS, 3, 1, 2, 1);
    expect_token(&lexer, TOKEN_INTEGER, 4, 2, 2, 2);
    expect_token(&lexer, TOKEN_EOF, 6, 0, 2, 4);
}

static void test_CR_expression(void)
{
    const char source[] = "12\r+34";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_INTEGER, 0, 2, 1, 1);
    expect_token(&lexer, TOKEN_PLUS, 3, 1, 2, 1);
    expect_token(&lexer, TOKEN_INTEGER, 4, 2, 2, 2);
    expect_token(&lexer, TOKEN_EOF, 6, 0, 2, 4);
}

static void test_CRLF_expression(void)
{
    const char source[] = "12\r\n+34";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_INTEGER, 0, 2, 1, 1);
    expect_token(&lexer, TOKEN_PLUS, 4, 1, 2, 1);
    expect_token(&lexer, TOKEN_INTEGER, 5, 2, 2, 2);
    expect_token(&lexer, TOKEN_EOF, 7, 0, 2, 4);
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

static void test_repeated_eof(void)
{
    const char source[] = "1";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_INTEGER, 0, 1, 1, 1);
    expect_token(&lexer, TOKEN_EOF, 1, 0, 1, 2);
    expect_token(&lexer, TOKEN_EOF, 1, 0, 1, 2);
}

static void test_all_operators(void)
{
    const char source[] = "(12 + 34) * 5 - 8 / 2";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_LEFT_PAREN, 0, 1, 1, 1);
    expect_token(&lexer, TOKEN_INTEGER, 1, 2, 1, 2);
    expect_token(&lexer, TOKEN_PLUS, 4, 1, 1, 5);
    expect_token(&lexer, TOKEN_INTEGER, 6, 2, 1, 7);
    expect_token(&lexer, TOKEN_RIGHT_PAREN, 8, 1, 1, 9);
    expect_token(&lexer, TOKEN_STAR, 10, 1, 1, 11);
    expect_token(&lexer, TOKEN_INTEGER, 12, 1, 1, 13);
    expect_token(&lexer, TOKEN_MINUS, 14, 1, 1, 15);
    expect_token(&lexer, TOKEN_INTEGER, 16, 1, 1, 17);
    expect_token(&lexer, TOKEN_SLASH, 18, 1, 1, 19);
    expect_token(&lexer, TOKEN_INTEGER, 20, 1, 1, 21);
    expect_token(&lexer, TOKEN_EOF, 21, 0, 1, 22);
}

static void test_simple_identifier(void)
{
    const char source[] = "counter";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_IDENTIFIER, 0, 7, 1, 1);
    expect_token(&lexer, TOKEN_EOF, 7, 0, 1, 8);
}

static void test_underscore_identifier(void)
{
    const char source[] = "_temp";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_IDENTIFIER, 0, 5, 1, 1);
    expect_token(&lexer, TOKEN_EOF, 5, 0, 1, 6);
}

static void test_alphanumeric_identifier(void)
{
    const char source[] = "value42";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_IDENTIFIER, 0, 7, 1, 1);
    expect_token(&lexer, TOKEN_EOF, 7, 0, 1, 8);
}

static void test_identifier_with_underscore(void)
{
    const char source[] = "abc_def";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_IDENTIFIER, 0, 7, 1, 1);
    expect_token(&lexer, TOKEN_EOF, 7, 0, 1, 8);
}

static void test_identifier_with_operator(void)
{
    const char source[] = "counter+10";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_IDENTIFIER, 0, 7, 1, 1);
    expect_token(&lexer, TOKEN_PLUS, 7, 1, 1, 8);
    expect_token(&lexer, TOKEN_INTEGER, 8, 2, 1, 9);
    expect_token(&lexer, TOKEN_EOF, 10, 0, 1, 11);
}

static void test_integer_followed_by_identifier(void)
{
    const char source[] = "42value";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_INTEGER, 0, 2, 1, 1);
    expect_token(&lexer, TOKEN_IDENTIFIER, 2, 5, 1, 3);
    expect_token(&lexer, TOKEN_EOF, 7, 0, 1, 8);
}

static void test_keyword_recognition(void)
{
    const char source[] = "if else while return";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_IF, 0, 2, 1, 1);
    expect_token(&lexer, TOKEN_ELSE, 3, 4, 1, 4);
    expect_token(&lexer, TOKEN_WHILE, 8, 5, 1, 9);
    expect_token(&lexer, TOKEN_RETURN, 14, 6, 1, 15);
    expect_token(&lexer, TOKEN_EOF, 20, 0, 1, 21);
}

static void test_keyword_prefixes_and_case(void)
{
    const char source[] = "ifCounter if2 returnValue IF";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_IDENTIFIER, 0, 9, 1, 1);
    expect_token(&lexer, TOKEN_IDENTIFIER, 10, 3, 1, 11);
    expect_token(&lexer, TOKEN_IDENTIFIER, 14, 11, 1, 15);
    expect_token(&lexer, TOKEN_IDENTIFIER, 26, 2, 1, 27);
    expect_token(&lexer, TOKEN_EOF, 28, 0, 1, 29);
}

static void test_keyword_without_whitespace(void)
{
    const char source[] = "if+while";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_IF, 0, 2, 1, 1);
    expect_token(&lexer, TOKEN_PLUS, 2, 1, 1, 3);
    expect_token(&lexer, TOKEN_WHILE, 3, 5, 1, 4);
    expect_token(&lexer, TOKEN_EOF, 8, 0, 1, 9);
}

static void test_underscore_edge_cases(void)
{
    const char source[] = "_ __ foo_ _42 a__b if_";

    Lexer lexer;
    lexer_init(&lexer, source, sizeof(source) - 1);

    expect_token(&lexer, TOKEN_IDENTIFIER, 0, 1, 1, 1);
    expect_token(&lexer, TOKEN_IDENTIFIER, 2, 2, 1, 3);
    expect_token(&lexer, TOKEN_IDENTIFIER, 5, 4, 1, 6);
    expect_token(&lexer, TOKEN_IDENTIFIER, 10, 3, 1, 11);
    expect_token(&lexer, TOKEN_IDENTIFIER, 14, 4, 1, 15);
    expect_token(&lexer, TOKEN_IDENTIFIER, 19, 3, 1, 20);
    expect_token(&lexer, TOKEN_EOF, 22, 0, 1, 23);
}

void lexer_tests_run(void)
{
    test_arithmetic_expression();
    test_LF_expression();
    test_CR_expression();
    test_CRLF_expression();
    test_invalid_character_recovery();
    test_empty_source();
    test_whitespace_only_source();
    test_repeated_eof();
    test_all_operators();
    test_simple_identifier();
    test_underscore_identifier();
    test_alphanumeric_identifier();
    test_identifier_with_underscore();
    test_identifier_with_operator();
    test_integer_followed_by_identifier();
    test_keyword_recognition();
    test_keyword_prefixes_and_case();
    test_keyword_without_whitespace();
    test_underscore_edge_cases();
}