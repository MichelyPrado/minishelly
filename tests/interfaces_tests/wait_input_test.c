#include "../includes/tests_includes.h"

typedef struct wait_input_test
{
	char	**line;
	char	**expected_str;
	t_err	*err;
	int		*props;
}		t_wait_input;

char			*c_env[] = { "BALU=dapaulin",
							 "TERM=xterm-256color",
							 "OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly",
							 "PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
							 "LANG=pt",
							 NULL
							};

void	clean_sys_config(t_sys_config *mini)
{
	int	i;

	i = 0;
	clean_env(mini->env);
	if (mini->str)
		free(mini->str);
	i = 0;
	clean_strlist(&mini->prompt);
	clean_strlist(&mini->path);
	if (mini->new_parser)
		free(mini->new_parser);
	if (mini)
		free(mini);
}

void	run_mu_test(t_sys_config *mini, t_wait_input *wait , int prop) {
	int		i = 0;
	t_err	err;

	err = NO_ERR;
	while (1) {
		err = wait_input(mini, &prop, wait->line[i]);
		mu_assert_int_eq(wait->props[i], prop);
		mu_assert_int_eq(wait->err[i], err);
		mu_assert_string_eq(wait->expected_str[i], mini->str);
		if (err == NO_ERR || err == ONLY_ENTER)
			break;
		i++;
	}
}

MU_TEST(test) {
	// CONFIG
	t_sys_config	*mini = start_sys((char **)c_env);
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

MU_TEST(test1) {
	// CONFIG
	t_sys_config	*mini = start_sys((char **)c_env);
	t_wait_input	wait = (t_wait_input) {0};	
	wait.line = ft_split("echo \"testando isso aqui\nfinal\"", '\n');
	wait.expected_str = (char *[]){"echo \"testando isso aqui", "echo \"testando isso aqui\nfinal\""};
	wait.err = (t_err []) {ERR_QUOTES, NO_ERR};
	wait.props = (int []){1, 0};

	// ACT
	run_mu_test(mini, &wait, 0);
	clean_sys_config(mini);
	if (wait.line)
		free(wait.line);
}

MU_TEST(test2) {
	// CONFIG
	t_sys_config	*mini = start_sys((char **)c_env);
	t_wait_input	wait = (t_wait_input) {0};	
	wait.line = ft_split("echo 'testando isso aqui\nfinal'", '\n');
	wait.expected_str = (char *[]){"echo 'testando isso aqui", "echo 'testando isso aqui\nfinal'"};
	wait.err = (t_err []) {ERR_QUOTES, NO_ERR};
	wait.props = (int []){1, 0};

	// ACT
	run_mu_test(mini, &wait, 0);
	clean_sys_config(mini);
	if (wait.line)
		free(wait.line);
}

MU_TEST(test3) {
	// CONFIG
	t_sys_config	*mini = start_sys((char **)c_env);
	t_wait_input	wait = (t_wait_input) {0};	
	wait.line = (char *[]){ft_strdup("echo 'testando isso aqui"), \
						   ft_strdup(""), \
						   ft_strdup(""), \
						   ft_strdup("final'")};
	wait.expected_str = (char *[]) {"echo 'testando isso aqui", \
									"echo 'testando isso aqui\n", \
									"echo 'testando isso aqui\n\n", \
									"echo 'testando isso aqui\n\n\nfinal'"};
	wait.err = (t_err []) {ERR_QUOTES, ERR_QUOTES, ERR_QUOTES, NO_ERR};
	wait.props = (int []){1, 1, 1, 0};

	// ACT
	run_mu_test(mini, &wait, 0);
	clean_sys_config(mini);
}

MU_TEST(test4) {
	// CONFIG
	t_sys_config	*mini = start_sys((char **)c_env);
	t_wait_input	wait = (t_wait_input) {0};	
	wait.line = (char *[]){ ft_strdup(""), NULL};
	wait.expected_str = (char *[]) {NULL};
	wait.err = (t_err []) {ONLY_ENTER};
	wait.props = (int []){1};

	// ACT
	run_mu_test(mini, &wait, 1);
	clean_sys_config(mini);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
	MU_RUN_TEST(test1);
	MU_RUN_TEST(test2);
	MU_RUN_TEST(test3);
	MU_RUN_TEST(test4);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
