#include "../includes/tests_includes.h"

t_token *create_token_test(char *token[], t_types type)
{
    t_token *node;

    node = (t_token *) malloc(sizeof(t_token));
    node->token = token;
    node->type = type;
    node->next = NULL;
    return (node);
}

void	clean_test(t_token **node)
{
	t_token	*head;
	t_token	*temp;

	head = *node;
	temp = *node;
	while (temp)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
	*node = NULL;
}

void    mu_tokens(char *expected[], char *result[])
{
    int i;

    i = 0;
    while (expected[i])
    {
        mu_assert_string_eq(expected[i], result[i]);
        i++;
    }
}

void mu_run_test(t_token *expected, t_token *result, int pointer) 
{
    mu_tokens(expected->token, result->token);
    mu_assert_int_eq(expected->type, result->type);
    if (pointer)
        mu_assert(expected->next != NULL && result->next != NULL, "Next pointer is not link");
    else
        mu_assert(expected->next == NULL && result->next == NULL, "Next pointer is not link");
}

MU_TEST(test1) {
	// CONFIG
    t_token *tokens;
    t_sys_config mini = (t_sys_config) {0};
    mini.new_parser = "echo batatinha frita *|* wc";
    char    *n1[] = {"echo", "batatinha", "frita", NULL};
    char    *n2[] = {"|", NULL};
    char    *n3[] = {"wc", NULL};
	t_token *node1 = create_token_test(n1, OP_ECHO);
    t_token *node2 = create_token_test(n2, OP_PIPE);
    t_token *node3 = create_token_test(n3, OP_CMD);
    node1->next = node2;
    node2->next = node3;

    // ACT
    tokens = ft_create_tokens(&mini);

    //ASSERT
    mu_run_test(node1, tokens, 1);
    mu_run_test(node2, tokens->next, 1);
    mu_run_test(node3, tokens->next->next, 0);
    clean_test(&node1);
    ft_token_free(&tokens);
}

MU_TEST(test2) {
	// CONFIG
    t_token *tokens;
    t_sys_config mini = (t_sys_config) {0};
    mini.new_parser = "echo batatinha frita *|*    \t    *|* wc";
    char    *n1[] = {"echo", "batatinha", "frita", NULL};
    char    *n2[] = {"|", NULL};
    char    *n3[] = {"|", NULL};
    char    *n4[] = {"wc", NULL};
	t_token *node1 = create_token_test(n1, OP_ECHO);
    t_token *node2 = create_token_test(n2, OP_PIPE);
    t_token *node3 = create_token_test(n3, OP_PIPE);
    t_token *node4 = create_token_test(n4, OP_CMD);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    // ACT
    tokens = ft_create_tokens(&mini);

    //ASSERT
    mu_run_test(node1, tokens, 1);
    mu_run_test(node2, tokens->next, 1);
    mu_run_test(node3, tokens->next->next, 1);
    mu_run_test(node4, tokens->next->next->next, 0);
    clean_test(&node1);
    ft_token_free(&tokens);
}

MU_TEST(test3) {
	// CONFIG
    t_token *tokens;
    t_sys_config mini = (t_sys_config) {0};
    mini.new_parser = "echo \"batatinha frita\" *|* wc";
    char    *n1[] = {"echo", "batatinha frita", NULL};
    char    *n2[] = {"|", NULL};
    char    *n3[] = {"wc", NULL};
	t_token *node1 = create_token_test(n1, OP_ECHO);
    t_token *node2 = create_token_test(n2, OP_PIPE);
    t_token *node3 = create_token_test(n3, OP_CMD);
    node1->next = node2;
    node2->next = node3;

    // ACT
    tokens = ft_create_tokens(&mini);

    //ASSERT
    mu_run_test(node1, tokens, 1);
    mu_run_test(node2, tokens->next, 1);
    mu_run_test(node3, tokens->next->next, 0);
    clean_test(&node1);
    ft_token_free(&tokens);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test1);
	MU_RUN_TEST(test2);
    MU_RUN_TEST(test3);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

