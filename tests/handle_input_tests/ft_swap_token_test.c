#include "../includes/tests_includes.h"

void    set_list(int amount, ...);
void    mu_assert_token(t_token *expected, t_token *result);

MU_TEST(test_passing_a_list_of_tokens_with_2_items_and_swap_in_the_init) {
    int     NUMBER_OF_TOKENS        = 2;
    t_token *t                      = CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO);
                                    set_list(  NUMBER_OF_TOKENS,
                                    t,
                                    CMD_M(">\aMakefile", '\a', OP_OUTPUT));
    t_token *expected               = CMD_M(">\aMakefile", '\a', OP_OUTPUT);
                                    set_list(  NUMBER_OF_TOKENS,
                                    expected,
                                    CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO));
    t_token *head                   = t;

    ft_swap_token(&head, &(t), &(t->next));

    mu_assert_token(expected, head);
    ft_token_free(&head);
    ft_token_free(&expected);
}

MU_TEST(test_passing_a_list_of_tokens_and_swap_in_the_init) {
    int     NUMBER_OF_TOKENS        = 4;
    t_token *t                      = CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO);
                                    set_list(  NUMBER_OF_TOKENS,
                                    t,
                                    CMD_M(">\aMakefile", '\a', OP_OUTPUT),
                                    CMD_M(">\agato", '\a', OP_OUTPUT),
                                    CMD_M("echo\avida", '\a', OP_ECHO));
                                    
    t_token *expected               = CMD_M(">\aMakefile", '\a', OP_OUTPUT);
                                    set_list(  NUMBER_OF_TOKENS,
                                    expected,
                                    CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO),
                                    CMD_M(">\agato", '\a', OP_OUTPUT),
                                    CMD_M("echo\a", '\a', OP_ECHO));
    t_token *head                   = t;


    ft_swap_token(&head, &t, &t->next);

    mu_assert_token(expected, head);
    ft_token_free(&head);
    ft_token_free(&expected);
}

MU_TEST(test_passing_a_list_of_tokens_and_swap_a_middle_item) {
    int     NUMBER_OF_TOKENS        = 4;
    t_token *t                      = CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO);
                                    set_list(  NUMBER_OF_TOKENS,
                                    t,
                                    CMD_M(">\aMakefile", '\a', OP_OUTPUT),
                                    CMD_M(">\agato", '\a', OP_OUTPUT),
                                    CMD_M("echo\avida", '\a', OP_ECHO));
                                    
    t_token *expected               = CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO);
                                    set_list(  NUMBER_OF_TOKENS,
                                    expected,
                                    CMD_M(">\agato", '\a', OP_OUTPUT),
                                    CMD_M(">\aMakefile", '\a', OP_OUTPUT),
                                    CMD_M("echo\a", '\a', OP_ECHO));
    t_token *head                   = t;


    ft_swap_token(&head, &t->next, &t->next->next);

    mu_assert_token(expected, head);
    ft_token_free(&head);
    ft_token_free(&expected);
}

MU_TEST(test_passing_a_list_of_tokens_and_swap_a_end_item) {
    int     NUMBER_OF_TOKENS        = 4;
    t_token *t                      = CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO);
                                    set_list(  NUMBER_OF_TOKENS,
                                    t,
                                    CMD_M(">\aMakefile", '\a', OP_OUTPUT),
                                    CMD_M(">\agato", '\a', OP_OUTPUT),
                                    CMD_M("echo\avida", '\a', OP_ECHO));
                                    
    t_token *expected               = CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO);
                                    set_list(  NUMBER_OF_TOKENS,
                                    expected,
                                    CMD_M(">\aMakefile", '\a', OP_OUTPUT),
                                    CMD_M("echo\a", '\a', OP_ECHO),
                                    CMD_M(">\agato", '\a', OP_OUTPUT));
    t_token *head                   = t;


    ft_swap_token(&head, &t->next->next, &t->next->next->next);

    mu_assert_token(expected, head);
    ft_token_free(&head);
    ft_token_free(&expected);
}

MU_TEST(test_passing_dest_NULL) {
    int     NUMBER_OF_TOKENS        = 4;
    t_token *t                      = CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO);
                                    set_list(  NUMBER_OF_TOKENS,
                                    t,
                                    CMD_M(">\aMakefile", '\a', OP_OUTPUT),
                                    CMD_M(">\agato", '\a', OP_OUTPUT),
                                    CMD_M("echo\avida", '\a', OP_ECHO));
                                    
    t_token *expected               = CMD_M("echo\a\"Hello World!\"", '\a', OP_ECHO);
                                    set_list(  NUMBER_OF_TOKENS,
                                    expected,
                                    CMD_M(">\aMakefile", '\a', OP_OUTPUT),
                                    CMD_M(">\agato", '\a', OP_OUTPUT),
                                    CMD_M("echo\a", '\a', OP_ECHO));
    t_token *head                   = t;


    ft_swap_token(&head, &t->next->next->next, &t->next->next->next->next);

    mu_assert_token(expected, head);
    ft_token_free(&head);
    ft_token_free(&expected);
}

MU_TEST_SUITE(test_swap) {
    MU_RUN_TEST(test_passing_a_list_of_tokens_with_2_items_and_swap_in_the_init);
    MU_RUN_TEST(test_passing_a_list_of_tokens_and_swap_in_the_init);
    MU_RUN_TEST(test_passing_a_list_of_tokens_and_swap_a_middle_item);
    MU_RUN_TEST(test_passing_a_list_of_tokens_and_swap_a_end_item);
    MU_RUN_TEST(test_passing_dest_NULL);
}

MU_TEST_SUITE(test_outputs) {

}

int main() {
    MU_RUN_SUITE(test_swap);
    MU_RUN_SUITE(test_outputs);
	MU_REPORT();
	return MU_EXIT_CODE;
}

void    mu_assert_token(t_token *expected, t_token *result)
{
    while (expected)
    {
        mu_assert_string_eq(*expected->token, *result->token);
        mu_assert_int_eq(expected->type, result->type);
        expected = expected->next;
        result = result->next;
    }
    mu_assert(expected == result, "Tokens is not null in the end!\n");
}

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
