#include "../includes/tests_includes.h"

# define PIPE_T {.token = (char *[]){"|", NULL}, .type = OP_PIPE, .next = NULL}
# define CAT_T  {.token = (char *[]){"cat", "test", NULL}, .type = OP_CMD, .next = NULL}
# define GREP_T {.token = (char *[]){"grep", "test", NULL}, .type = OP_CMD, .next = NULL}

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

t_token pipes[5] = {PIPE_T, PIPE_T, PIPE_T, PIPE_T, PIPE_T};


MU_TEST(test1)
{
    t_token expected[] = {PIPE_T, CAT_T, PIPE_T, PIPE_T, GREP_T, PIPE_T};
    t_token token[] = {CAT_T, PIPE_T, GREP_T};
    set_list(5, &expected[0], &expected[1], &expected[2], &expected[3], &expected[5]);
    set_list(3, &token[0], &token[1], &token[2]);
    t_token *bkp_exp = &expected[0];
    t_token *bkp_res = &token[0];

    ft_find_pipe(&bkp_res);

    while (bkp_exp)
    {
        mu_assert_string_eq(bkp_exp->token[0], bkp_res->token[0]);
        bkp_res = bkp_res->next;
        bkp_exp = bkp_exp->next;
    }
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test1);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}