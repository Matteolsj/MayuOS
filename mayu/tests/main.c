#include <stdio.h>

void token_tests_run(void);
void lexer_tests_run(void);

int main(void)
{
    printf("Running token tests...\n");
    token_tests_run();

    printf("Running lexer tests...\n");
    lexer_tests_run();

    printf("\nAll Mayu tests passed!\n");

    return 0;
}