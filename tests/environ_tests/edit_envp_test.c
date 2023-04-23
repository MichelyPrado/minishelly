#include "../includes/tests_includes.h"

char			*c_env[] = { "USER=dapaulin",
							 "TERM=xterm-256color",
							 "OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly",
							 "PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
							 "LANG=pt",
							 NULL
							};

char		**environ = (char **)c_env;

MU_TEST(alter_o_valor_da_variavel_USER_para_cruz) {
	// CONFIG
	char			*key = "USER=";
	char			*value = "cruz";
	char			*expected_str = "USER=cruz";
	t_sys_config	mini;
	

	// ACT
	get_envp(environ, &mini);
	edit_envp(&mini.env, key, value);

	// ASSERTS
	mu_assert_string_eq(mini.env[search_envp(environ, key)], expected_str);
	clean_env(mini.env);
}

MU_TEST(passar_uma_key_nula_e_um_valor_valido_env_deve_ser_a_mesma) {
	// CONFIG
	int				i;
	char			*key = NULL;
	char			*value = "cruz";
	char			*expected_str = NULL;
	t_sys_config	*mini = &((t_sys_config) {0});

	// ACT
	get_envp(environ, mini);
	edit_envp(&mini->env, key, value);

	// ASSERTS
	i = 0;
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->env[i]);
		i++;
	}
	clean_env(mini->env);
}

MU_TEST(passar_variavel_USER_com_value_NULL_deve_ser_USER_eq) {
	// CONFIG
	char			*key = "USER=";
	char			*value = NULL;
	char			*expected_str = "USER=";
	t_sys_config	*mini = &((t_sys_config) {0});

	// ACT
	get_envp(environ, mini);
	edit_envp(&mini->env, key, value);

	// ASSERTS
	mu_assert_string_eq(mini->env[search_envp(environ, key)], expected_str);
	clean_env(mini->env);
}

MU_TEST(passar_variavel_USER_com_value_dapaulin_e_env_NULL_deve_ser_env_NULL) {
	// CONFIG
	char			*key = "USER=";
	char			*value = "dapaulin";
	char			*expected_str = NULL;
	t_sys_config	*mini = &((t_sys_config) {0});

	// ACT
	edit_envp(&mini->env, key, value);

	// ASSERTS
	mu_assert(NULL == mini->env, "Position is not NULL");
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(alter_o_valor_da_variavel_USER_para_cruz);
	MU_RUN_TEST(passar_uma_key_nula_e_um_valor_valido_env_deve_ser_a_mesma);
	MU_RUN_TEST(passar_variavel_USER_com_value_NULL_deve_ser_USER_eq);
	MU_RUN_TEST(passar_variavel_USER_com_value_dapaulin_e_env_NULL_deve_ser_env_NULL);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
