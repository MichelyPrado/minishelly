#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

void	clean_sys_config(t_sys_config *mini)
{
	int	i;

	i = 0;
	clean_env(mini->env);
	if (mini->str)
		free(mini->str);
	while (mini->prompt[i])
		free(mini->prompt[i++]);
	if (mini->prompt)
		free(mini->prompt);
	if (mini->new_parser)
		free(mini->new_parser);
	if (mini)
		free(mini);
}

MU_TEST(test) {
	// CONFIG
	extern char		**envirion;
	t_sys_config	*mini = start_sys();
	int				prop = 0;
	char			*line = ft_strdup("echo testando isso aqui");
	char			*expected_str = "echo testando isso aqui";
	t_err			err_expected = NO_ERR;
	t_err			err;

	// ACT
	err = wait_input(mini, &prop, line);

	// ASSERTS
	mu_assert_string_eq(expected_str, mini->str);
	mu_assert_int_eq(err_expected, err);
	clean_sys_config(mini);

}

typedef struct wait_input_test
{
	char	**line;
	char	**expected_str;
	t_err	*err;
	int		*props;
}		t_wait_input;


void	run_mu_test(t_sys_config *mini, t_wait_input *wait) {
	int		i = 0;
	int		prop = 0;
	t_err	err;

	err = NO_ERR;
	while (1) {
		err = wait_input(mini, &prop, wait->line[i]);
		mu_assert_string_eq(wait->expected_str[i], mini->str);
		mu_assert_int_eq(wait->props[i], prop);
		mu_assert_int_eq(wait->err[i], err);
		if (err == NO_ERR)
			break;
		i++;
	}
}

MU_TEST(test1) {
	// CONFIG
	extern char		**envirion;
	t_sys_config	*mini = start_sys();
	t_wait_input	wait = (t_wait_input) {0};	
	wait.line = ft_split("echo \"testando isso aqui\nfinal\"", '\n');
	wait.expected_str = (char *[]){"echo \"testando isso aqui", "echo \"testando isso aqui\nfinal\""};
	wait.err = (t_err []) {ERR_QUOTES, NO_ERR};
	wait.props = (int []){1, 0};

	// ACT
	run_mu_test(mini, &wait);
	free(wait.line);
	clean_sys_config(mini);

}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
	MU_RUN_TEST(test1);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}