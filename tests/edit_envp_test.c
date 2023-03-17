#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(test) {
	// CONFIG
	char			*key = "USER";
	char			*value = "dapaulin";
	char			*expected_str = "USER=dapaulin";
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	edit_envp(&mini, key, value);

	// ASSERTS
	mu_assert_string_eq(mini.e[1], expected_str);
	clean_env(mini.e);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
