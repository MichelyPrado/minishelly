#include "../includes/tests_includes.h"

char			*c_env[] = { "USER=dapaulin",
							 "TERM=xterm-256color",
							 "OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly",
							 "PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
							 "LANG=pt",
							 NULL
							};

void	comp_strs(char **environ, char *expected, t_sys_config *mini, char *key)
{
	char	*p = NULL;
	int		i = 0;

	while (environ[i])
	{
		p = ft_strchr(environ[i], '=');
		if (p == NULL)
			break ;
		if (!ft_strncmp(environ[i], key, p - environ[i]))
			mu_assert_string_eq(expected, mini->env[i]);
		else
			mu_assert_string_eq(environ[i], mini->env[i]);
		if (!environ[i])
			break ;
		i++;
	}
}

MU_TEST(Passando_key_como_MINISHELL_value_com_Minishelly_e_as_variaveis_de_ambiente_precisa_ter_MINISHELL_eq_MiniSHelly_como_ultimo_item_de_envp) {
	// CONFIG
	int				i = 0;
	char			*key = "MINISHELL=";
	char			*value = "Minishelly";
	char			*expected_insert = "MINISHELL=Minishelly";
	t_sys_config	*mini = &((t_sys_config){0});
	extern char		**environ;

	// ACT
	get_envp(environ, mini);
	ft_export(&mini->env, key, value);

	// ASSERTS
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->env[i]);
		i++;
	}
	mu_assert_string_eq(expected_insert, mini->env[i]);
	clean_env(mini->env);
}

MU_TEST(Passando_uma_variavel_existente_KEY_como_PATH_e_outro_value_da_variavel_tem_que_ser_atualizado) {
	// CONFIG

	extern char		**environ;
	char			*key = "PATH=";
	int				i = search_envp(environ, key);
	char			*value = "/go";
	char			*expected_insert = "PATH=/go";
	t_sys_config	*mini = &((t_sys_config){0});

	// ACT
	get_envp(environ, mini);
	ft_export(&mini->env, key, value);

	// ASSERTS
	i = 0;
	comp_strs(environ, expected_insert, mini, key);
	clean_env(mini->env);
}

MU_TEST(Passando_key_como_NULL_com_value_WHAT_o_env_deve_permanecer_o_mesmo) {
	// CONFIG
	extern char		**environ;
	char			*key = NULL;
	char			*value = "test";
	char			*expected_insert = NULL;
	t_sys_config	*mini = &((t_sys_config){0});
	int				i;

	// ACT
	get_envp(environ, mini);
	ft_export(&mini->env, key, value);

	// ASSERTS
	i = 0;
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->env[i]);
		i++;
	}
	mu_assert_string_eq(expected_insert, mini->env[i]);
	clean_env(mini->env);
}

MU_TEST(Passando_key_como_KLEYTON_com_value_NULL_o_env_possuir_a_variavel_KLEYTON_eq_NULL) {
	// CONFIG
	extern char		**environ;
	char			*key = "KLEYTON=";
	char			*value = NULL;
	char			*expected_insert = "KLEYTON=";
	t_sys_config	*mini = &((t_sys_config){0});
	int				i;

	// ACT
	get_envp(environ, mini);
	ft_export(&mini->env, key, value);

	// ASSERTS
	i = 0;
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->env[i]);
		i++;
	}
	mu_assert_string_eq(expected_insert, mini->env[i]);
	clean_env(mini->env);
}

MU_TEST(Passando_key_como_KLEYTON_com_value_RASTA_para_um_env_nulo_o_env_deve_possuir_somente_a_nova_variavel) {
	// CONFIG
	extern char		**environ;
	char			*key = "KLEYTON=";
	char			*value = "RASTA";
	t_sys_config	*mini = &((t_sys_config){0});
	int				i;

	// ACT
	ft_export(&mini->env, key, value);

	// ASSERTS
	mu_assert_string_eq("KLEYTON=RASTA", mini->env[0]);
	mu_assert(NULL == mini->env[1], "Position is not NULL");
	clean_env(mini->env);
}

MU_TEST(Passando_key_como_KLEYTON_sem_eq_deve_possuir_somente_a_nova_variavel) {
	// CONFIG
	char			*key = "KLEYTON";
	char			*value = NULL;
	t_sys_config	*mini = &((t_sys_config){0});
	int				i;
	char			*expected_env[] = { "USER=dapaulin",
							 "TERM=xterm-256color",
							 "OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly",
							 "PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
							 "LANG=pt",
							 "KLEYTON",
							 NULL
							};

	// ACT
	get_envp(c_env, mini);
	ft_export(&mini->env, key, value);

	// ASSERTS
	i = 0;
	while (expected_env[i])
	{
		mu_assert_string_eq(expected_env[i], mini->env[i]);
		i++;
	}
	mu_assert_string_eq(expected_env[i], mini->env[i]);
	clean_env(mini->env);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(Passando_key_como_MINISHELL_value_com_Minishelly_e_as_variaveis_de_ambiente_precisa_ter_MINISHELL_eq_MiniSHelly_como_ultimo_item_de_envp);
	MU_RUN_TEST(Passando_uma_variavel_existente_KEY_como_PATH_e_outro_value_da_variavel_tem_que_ser_atualizado);
	MU_RUN_TEST(Passando_key_como_NULL_com_value_WHAT_o_env_deve_permanecer_o_mesmo);
	MU_RUN_TEST(Passando_key_como_KLEYTON_com_value_NULL_o_env_possuir_a_variavel_KLEYTON_eq_NULL);
	MU_RUN_TEST(Passando_key_como_KLEYTON_com_value_RASTA_para_um_env_nulo_o_env_deve_possuir_somente_a_nova_variavel);
	MU_RUN_TEST(Passando_key_como_KLEYTON_sem_eq_deve_possuir_somente_a_nova_variavel);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
