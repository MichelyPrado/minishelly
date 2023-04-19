#include "../includes/tests_includes.h"

void check_result(t_token *expected, t_token *node)
{
    int i;

    i = 0;
    while (expected->cmds[i])
    {
        mu_assert_string_eq(expected->cmds[i], node->cmds[i]);
        i++;
    }
    mu_assert_string_eq(expected->operator, node->operator);
    mu_assert_int_eq(expected->type, node->type);
    if (expected->next > 0)
        mu_assert(expected->next && node->next, "The next node don't has a address");
    else if (expected->next == 0)
        mu_assert(!expected->next && !node->next, "The next node is not null");
}

MU_TEST(test) {
	// CONFIG
    t_token *expected_node1 = ft_token_new(ft_split("ls -l -a", " "), NULL, OP_CMD);
    t_token *expected_node2 = ft_token_new(NULL, "|", OP_PIPE);
    t_token *expected_node3 = ft_token_new(ft_split("grep jorel", " "), NULL, OP_CMD);
    t_token *node = (t_token *){0};

    // ACT
    expected_node1->next = expected_node2;
    expected_node2->next = expected_node3;
    node = ft_create_tokens(node);
    
    //ASSERT
    check_result(expected_node1, node);
    node = node->next;
    check_result(expected_node2, node);
    node = node->next;
    check_result(expected_node3, node);
    node = node->next;
    check_result(expected_node3->next, node);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
