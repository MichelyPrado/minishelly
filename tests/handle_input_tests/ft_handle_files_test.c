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

t_sys_config ms = (t_sys_config) {.env = NULL, .tokens = NULL,
    .exec = NULL, .prompt = NULL, .new_parser = NULL, .path = NULL};


void    mu_assert_token_test(t_token *expected, t_token *result)
{
    char    str[100];
    ft_bzero(&str, 0);

    while (expected)
    {
        mu_assert_string_eq(expected->token[0], result->token[0]);
        mu_assert_int_eq(expected->type, result->type);
        expected = expected->next;
        result = result->next;
    }
    sprintf(str, "expected: %p, but has result: %p\n", expected, result);
    mu_assert(expected == result, str);
}

MU_TEST(test_passing_a_output_command) {
    int NUMBER_OF_TOKENS            = 2;
    t_token *token                  =   CMD_M(">", '\a', OP_OUTPUT);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M("ola", '\a', OP_CMD));
    t_token *expected               = CMD_M(">\aola", '\a', OP_OUTPUT);
    ms.tokens = token;

    prepare_commands(&ms);

    mu_assert_token_test(expected, token);
    ft_token_free(&token);
    ft_token_free(&expected);
}

MU_TEST(test_passing_a_input_command) {
    int NUMBER_OF_TOKENS            = 2;
    t_token *token                  =   CMD_M("<", '\a', OP_OUTPUT);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M("ola", '\a', OP_CMD));
    t_token *expected               = CMD_M("<\aola", '\a', OP_OUTPUT);
    ms.tokens = token;

    prepare_commands(&ms);

    mu_assert_token_test(expected, token);
    ft_token_free(&token);
    ft_token_free(&expected);
}

MU_TEST(test_passing_a_append_command) {
    int NUMBER_OF_TOKENS            = 2;
    t_token *token                  =   CMD_M(">>", '\a', OP_OUTPUT);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M("ola", '\a', OP_CMD));
    t_token *expected               = CMD_M(">>\aola", '\a', OP_OUTPUT);
    ms.tokens = token;

    prepare_commands(&ms);

    mu_assert_token_test(expected, token);
    ft_token_free(&token);
    ft_token_free(&expected);
}

MU_TEST(test_passing_a_until_command) {
    int NUMBER_OF_TOKENS            = 2;
    t_token *token                  =   CMD_M("<<", '\a', OP_OUTPUT);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M("ola", '\a', OP_CMD));
    t_token *expected               = CMD_M("<<\aola", '\a', OP_OUTPUT);
    ms.tokens = token;

    prepare_commands(&ms);

    mu_assert_token_test(expected, token);
    ft_token_free(&token);
    ft_token_free(&expected);
}

MU_TEST(test_passing_only_a_append_command) {
    t_token *token                  =   CMD_M("<<", '\a', OP_OUTPUT);
    t_token *expected               = CMD_M("<<", '\a', OP_OUTPUT);
    ms.tokens = token;

    prepare_commands(&ms);

    mu_assert_token_test(expected, token);
    ft_token_free(&token);
    ft_token_free(&expected);
}

MU_TEST(test1) {
    int NUMBER_OF_TOKENS            = 8;
    t_token *token                  =   CMD_M("<<", '\a', OP_UNTIL);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M("ola", '\a', OP_CMD),
                                    CMD_M(">>", '\a', OP_APPEND),
                                    CMD_M("hello", '\a', OP_CMD),
                                    CMD_M("<", '\a', OP_INPUT),
                                    CMD_M("view", '\a', OP_CMD),
                                    CMD_M(">", '\a', OP_OUTPUT),
                                    CMD_M("show", '\a', OP_CMD));
    t_token *expected               = CMD_M("<<\aola", '\a', OP_UNTIL);
                                    set_list(NUMBER_OF_TOKENS / 2,
                                    expected,
                                    CMD_M(">>\ahello", '\a', OP_APPEND),
                                    CMD_M("<\aview", '\a', OP_INPUT),
                                    CMD_M(">\ashow", '\a', OP_OUTPUT));
    ms.tokens = token;

    prepare_commands(&ms);

    mu_assert_token_test(expected, token);
    ft_token_free(&token);
    ft_token_free(&expected);
}

MU_TEST_SUITE(test_suite_files_handle) {
	MU_RUN_TEST(test_passing_a_output_command);
    MU_RUN_TEST(test_passing_a_input_command);
    MU_RUN_TEST(test_passing_a_append_command);
    MU_RUN_TEST(test_passing_a_until_command);
    MU_RUN_TEST(test_passing_only_a_append_command);
    MU_RUN_TEST(test1);
}

void    mu_assert_token_all(t_token *expected, t_token *result)
{
    int i;
    char    str[100];
    ft_bzero(&str, 0);

    while (expected)
    {
        i = 0;
        while (expected->token[i])
        {
            mu_assert_string_eq(expected->token[i], result->token[i]);
            i++;
        }
        mu_assert_int_eq(expected->type, result->type);
        expected = expected->next;
        result = result->next;
    }
    sprintf(str, "expected: %p, but has result: %p\n", expected, result);
    mu_assert(expected == result, str);
}

MU_TEST(test) {
    int NUMBER_OF_TOKENS            = 3;
    t_token *token                  =   CMD_M("echo\ahello", '\a', OP_ECHO);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M(">", '\a', OP_OUTPUT),
                                    CMD_M("ola\aworld", '\a', OP_CMD));
    t_token *expected               = CMD_M(">\aola", '\a', OP_OUTPUT);
                                    set_list(NUMBER_OF_TOKENS - 1,
                                    expected,
                                    CMD_M("echo\ahello\aworld", '\a', OP_ECHO));
    ms.tokens = token;

    prepare_commands(&ms);

    mu_assert_token_all(expected, token);
    ft_token_free(&token);
    ft_token_free(&expected);
}

MU_TEST(test_passing_a_until_command_with_text_in_the_end_and_a_echo_before_should_be_realloc_text) {
    int NUMBER_OF_TOKENS            = 3;
    t_token *token                 = CMD_M("echo\ahello", '\a', OP_ECHO);
                                    set_list(NUMBER_OF_TOKENS,
                                    token,
                                    CMD_M("<<\aola", '\a', OP_UNTIL),
                                    CMD_M("\aworld!", '\a', OP_CMD));
    t_token *expected               = CMD_M("echo\ahello\aworld!", '\a', OP_ECHO);
                                    set_list(NUMBER_OF_TOKENS - 1,
                                    expected,
                                    CMD_M("<<\aola", '\a', OP_UNTIL));


    realloc_strings(token, token->next->next);

    mu_assert_token_all(expected, token);

    free_node_only(&token);
    ft_token_free(&expected);
}

MU_TEST_SUITE(test_suite_realloc_extra_strings)
{
    //MU_RUN_TEST(test);
    //MU_RUN_TEST(test_passing_a_until_command_with_text_in_the_end_and_a_echo_before_should_be_realloc_text);
}

int main() {
	MU_RUN_SUITE(test_suite_files_handle);
    MU_RUN_SUITE(test_suite_realloc_extra_strings);
	MU_REPORT();
	return MU_EXIT_CODE;
}
