#include "../includes/tests_includes.h"

void    set_list(int amount, ...)
{
    int     i;
    t_token *token;
    va_list ap;

    i = 1;
    token = NULL;
    va_start(ap, amount);
    token = va_arg(ap, t_token *);
    while (i < amount)
    {
        if (!token)
            break ;
        token->next = va_arg(ap, t_token *);
        token = token->next;
        i++;
    }
    va_end(ap);
}

void    mu_assert_token_test(t_token *expected, t_token *result)
{
    char    str[100];
    ft_bzero(&str, 0);

    while (expected)
    {
        mu_assert_string_eq(expected->token[0], result->token[0]);
        //mu_assert_int_eq(expected->type, result->type);
        expected = expected->next;
        result = result->next;
    }
    sprintf(str, "expected: %p, but has result: %p\n", expected, result);
    mu_assert(expected == result, str);
}

t_sys_config ms                 = (t_sys_config) {.env = NULL, .tokens = NULL,
    .exec = NULL, .prompt = NULL, .new_parser = NULL, .path = NULL};

MU_TEST(test) {
    int NUMBER_OF_TOKENS            = 2;
    t_token *token                  =   CMD_M("echo\atestando", '\a', OP_ECHO);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M(">\aola", '\a', OP_OUTPUT));
    t_token *expected               = CMD_M(">\aola", '\a', OP_OUTPUT);
                                    set_list(NUMBER_OF_TOKENS,
                                    expected,
                                    CMD_M("echo\atestando", '\a', OP_ECHO));
    ms.tokens                       = token;


    ms.tokens = ft_handle_operators(ms.tokens);

    mu_assert_token_test(expected, ms.tokens);
    ft_token_free(&ms.tokens);
    ft_token_free(&expected);
}

MU_TEST(test1) {
    int NUMBER_OF_TOKENS            = 4;
    t_token *token                  =   CMD_M("echo\atestando", '\a', OP_ECHO);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M(">\aola", '\a', OP_OUTPUT),
                                    CMD_M("cat\aMakefile", '\a', OP_OUTPUT),
                                    CMD_M(">>\aola", '\a', OP_OUTPUT));
    t_token *expected               = CMD_M(">\aola", '\a', OP_OUTPUT);
                                    set_list(NUMBER_OF_TOKENS,
                                    expected,
                                    CMD_M("echo\atestando", '\a', OP_ECHO),
                                    CMD_M(">>\aola", '\a', OP_OUTPUT),
                                    CMD_M("cat\aMakefile", '\a', OP_OUTPUT));
    ms.tokens                       = token;


    ms.tokens = ft_handle_operators(ms.tokens);

    mu_assert_token_test(expected, ms.tokens);
    ft_token_free(&ms.tokens);
    ft_token_free(&expected);
}

MU_TEST(test2) {
    int NUMBER_OF_TOKENS            = 4;
    t_token *token                  =   CMD_M("echo\atestando", '\a', OP_ECHO);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M(">\aola", '\a', OP_OUTPUT),
                                    CMD_M(">>\aola", '\a', OP_OUTPUT));
    t_token *expected               = CMD_M(">\aola", '\a', OP_OUTPUT);
                                    set_list(NUMBER_OF_TOKENS,
                                    expected,
                                    CMD_M(">>\aola", '\a', OP_OUTPUT),
                                    CMD_M("echo\atestando", '\a', OP_ECHO));
    ms.tokens                       = token;


    ms.tokens = ft_handle_operators(ms.tokens);

    mu_assert_token_test(expected, ms.tokens);
    ft_token_free(&ms.tokens);
    ft_token_free(&expected);
}

MU_TEST_SUITE(test_suite) {
    //MU_RUN_TEST(test);
    MU_RUN_TEST(test1);
    //MU_RUN_TEST(test2);
}

int main() {
    MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
