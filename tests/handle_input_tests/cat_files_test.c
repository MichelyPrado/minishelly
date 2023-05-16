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

MU_TEST(test) {
    t_token *token = CMD_M("echo\aminishell 2", '\a', OP_ECHO);

    set_list(3, token, CMD_M(">", '\a', OP_OUTPUT), CMD_M("amigo", '\a', OP_CMD))
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
