#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(test) {
	// CONFIG
	char			*key = "USER";
	int				expected_index = 1;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(test1) {
	// CONFIG
	char			*key = "TERM";
	int				expected_index = 66;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(test2) {
	// CONFIG
	char			*key = "PIMENTA";
	int				expected_index = 0;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(test3) {
	// CONFIG
	char			*key = "";
	int				expected_index = 0;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(test4) {
	// CONFIG
	char			*key = NULL;
	int				expected_index = 0;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(test5) {
	// CONFIG
	char			*key = "BANANADA";
	int				expected_index = 0;
	int				result_index;
	t_minishelly	mini = (t_minishelly) {0};
	extern char		**environ;

	// ACT
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
	MU_RUN_TEST(test1);
	MU_RUN_TEST(test2);
	MU_RUN_TEST(test3);
	MU_RUN_TEST(test4);
	MU_RUN_TEST(test5);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
