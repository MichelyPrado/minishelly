#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(test) {
	// CONFIG
	char    *expected_cmds[4] = {"ls", "-l", "-a", NULL};
    int     expected_type = OP_CMD;
    t_token *node = (t_token *){0};

    // ACT
    node = ft_token_new(expected_cmds, expected_type);

    //ASSERT
    int i = 0;
    while (expected_cmds[i])
    {
        mu_assert_string_eq(expected_cmds[i], node->token[i]);
        i++;
    }
    mu_assert_int_eq(expected_type, node->type);
    mu_assert(NULL == node->next, "Next node isn't NULL");
    free(node);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

