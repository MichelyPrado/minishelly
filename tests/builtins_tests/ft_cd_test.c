#include "../includes/tests_includes.h"

extern char **environ;

t_sys_config mini = (t_sys_config){0};

typedef struct s_test {
	char			*E_PWD;
	char			*E_OLDPWD;
	char			*R_PWD;
	char			*R_OLDPWD;
	int				err;
} t_test;

void	clear_msg(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	run_func(t_test *t, char *pwd, char *old)
{
	t->E_PWD 			= ft_strjoin(&mini.env[search_envp(mini.env, "HOME")][5], pwd);
	t->E_OLDPWD 		= ft_strjoin(&mini.env[search_envp(mini.env, "HOME")][5], old);
	t->err 				= ft_cd(&mini);
	t->R_PWD 			= &mini.env[search_envp(mini.env, "PWD")][4];
	t->R_OLDPWD 		= &mini.env[search_envp(mini.env, "OLDPWD")][7];
}

void	unset(t_test t)
{
	clear_msg(&t.E_PWD);
	clear_msg(&t.E_OLDPWD);
}

MU_TEST(test_passing_cd_2_dots_backslash_should_alter_pwd_and_oldpwd) {
	t_test 	t 					= (t_test){NULL};
	char	*token[] 			= {"cd", "../", NULL};
			mini.tokens 		= &(t_token){.token = token};

	run_func(&t, "/ls/minishelly", "/ls/minishelly/tests");

	mu_assert_string_eq(t.E_PWD, t.R_PWD);
	mu_assert_string_eq(t.E_OLDPWD, t.R_OLDPWD);
	mu_assert_int_eq(0, t.err);
	unset(t);
}

MU_TEST(test) {
	t_test 	t 					= (t_test){0};
	char	**token 			= ft_split("cd", -1);
			mini.tokens 		= &(t_token){.token = token};

	run_func(&t, "", "/ls/minishelly");

	mu_assert_string_eq(t.E_PWD, t.R_PWD);
	mu_assert_string_eq(t.E_OLDPWD, t.R_OLDPWD);
	mu_assert_int_eq(0, t.err);
	unset(t);
	clean_strlist(&mini.tokens->token);
}

MU_TEST(test1) {
	t_test 	t 					= (t_test){0};
	char	**token 			= ft_split("cd\atests\a../", '\a');
			mini.tokens 		= &(t_token){.token = token};

	run_func(&t, "", "/ls/minishelly");

	mu_assert_string_eq(t.E_PWD, t.R_PWD);
	mu_assert_string_eq(t.E_OLDPWD, t.R_OLDPWD);
	mu_assert_int_eq(1, *get_status_code());
	unset(t);
	clean_strlist(&mini.tokens->token);
}

MU_TEST_SUITE(test_suite) {
	get_envp(environ, &mini);
	MU_RUN_TEST(test_passing_cd_2_dots_backslash_should_alter_pwd_and_oldpwd);
	MU_RUN_TEST(test);
	MU_RUN_TEST(test1);
	clean_strlist(&mini.env);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

