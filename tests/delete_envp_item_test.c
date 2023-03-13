#include "../minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(test) {
	// CONFIG
	int				i = 0;
	int				j = 0;
	char			*deleted_item = "GJS_DEBUG_TOPICS";
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	delete_envp_item(&mini, deleted_item);

	// ASSERTS
	while (environ[i])
	{
		if (ft_strncmp(environ[i], deleted_item, ft_strlen(deleted_item)) == 0)
			j = 1;
		mu_assert_string_eq(environ[i + j], (mini.e)[i]);
		i++;
	}
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

