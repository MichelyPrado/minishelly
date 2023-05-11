#include "../includes/tests_includes.h"

#define CONST_ENVP "USER=dapaulin TERM=xterm-256color OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests L=shell LANGUAGE=en LANG=pt"

int	findlast(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i - 1);
}

void	comp_strs(char **environ, char *deleted_item, t_sys_config *mini)
{
	char	*p = NULL;
	int		i = 0;
	int		j = 0;

	while (environ[i + j])
	{
		p = ft_strchr(environ[i + j], '=');
		if (p == NULL)
			break ;
		if (!ft_strncmp(environ[i + j], deleted_item, p - environ[i + j]))
			j = 1;
		mu_assert_string_eq(environ[i + j], mini->env[i]);
		if (!environ[i + j])
			break ;
		i++;
	}
}

MU_TEST(Passando_uma_variavel_de_ambiente_existente_o_resultado_deve_ser_envp_sem_a_variavel_informada) {
	// CONFIG
	char			*deleted_item = "USER";
	t_sys_config	*mini = &((t_sys_config) {0});
	char			**environ = ft_split(CONST_ENVP, ' ');

	// ACT
	get_envp(environ, mini);
	ft_unset(mini, deleted_item);

	// ASSERTS
	comp_strs(environ, deleted_item, mini);
	clean_env(mini->env);
	clean_strlist(&environ);
}

MU_TEST(Passando_uma_variavel_de_ambiente_nula_o_resultado_deve_ser_o_mesmo_da_entrada) {
	// CONFIG
	int				i = 0;
	char			*deleted_item = NULL;
	t_sys_config	*mini = &((t_sys_config) {0});
	extern char		**environ;

	// ACT
	get_envp(environ, mini);
	ft_unset(mini, deleted_item);

	// ASSERTS
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->env[i]);
		i++;
	}
	clean_env(mini->env);
}

MU_TEST(passando_a_variavel_de_ambiente_PATH_o_env_deve_ser_todas_as_outras_variaveis_menos_PATH) {
	// CONFIG
	char			*deleted_item = "PATH";
	t_sys_config	*mini = &((t_sys_config) {0});
	extern char		**environ;

	// ACT
	get_envp(environ, mini);
	ft_unset(mini, deleted_item);

	// ASSERTS
	comp_strs(environ, deleted_item, mini);
	clean_env(mini->env);
}

MU_TEST(Passando_uma_estrutura_nula_o_resultado_deve_ser_o_mesmo_da_entrada) {
	// CONFIG
	char			*deleted_item = "USER";
	t_sys_config	*mini = &((t_sys_config) {0});
	extern char		**environ;

	// ACT
	ft_unset(mini, deleted_item);
	// ASSERTS
	mu_assert(NULL == mini->env, "The return env is not null");
}

MU_TEST(passando_a_ultima_variavel_de_ambiente__o_resultado_deve_ser_env_sem_a_ultima_variavel) {
	// CONFIG
	extern char		**environ;
	int				last = findlast(environ);
	char			*deleted_item = ft_substr(environ[last], 0, keylen(environ[last]));
	t_sys_config	*mini = &((t_sys_config) {0});

	// ACT
	get_envp(environ, mini);
	ft_unset(mini, deleted_item);

	// ASSERTS
	comp_strs(environ, deleted_item, mini);
	clean_env(mini->env);
	if (*deleted_item)
		free(deleted_item);
}

MU_TEST(passando_uma_variavel_inexistente_deve_retornar_o_mesmo_env) {
	// CONFIG
	char			*deleted_item = "BANANADA";
	t_sys_config	*mini = &((t_sys_config) {0});
	extern char		**environ;

	// ACT
	get_envp(environ, mini);
	ft_unset(mini, deleted_item);

	// ASSERTS
	comp_strs(environ, deleted_item, mini);
	clean_env(mini->env);
}

MU_TEST(Passando_a_variavel_TERM_o_resultado_deve_ser_env_sem_a_variavel_TERM_nenhuma_outra_fora_essa) {
	// CONFIG
	char			*deleted_item = "TERM";
	t_sys_config	*mini = &((t_sys_config) {0});
	extern char		**environ;

	// ACT
	get_envp(environ, mini);
	ft_unset(mini, deleted_item);

	// ASSERTS
	comp_strs(environ, deleted_item, mini);
	clean_env(mini->env);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(Passando_uma_variavel_de_ambiente_existente_o_resultado_deve_ser_envp_sem_a_variavel_informada);
	MU_RUN_TEST(Passando_uma_variavel_de_ambiente_nula_o_resultado_deve_ser_o_mesmo_da_entrada);
	MU_RUN_TEST(passando_a_variavel_de_ambiente_PATH_o_env_deve_ser_todas_as_outras_variaveis_menos_PATH);
	MU_RUN_TEST(Passando_uma_estrutura_nula_o_resultado_deve_ser_o_mesmo_da_entrada);
	MU_RUN_TEST(passando_a_ultima_variavel_de_ambiente__o_resultado_deve_ser_env_sem_a_ultima_variavel);
	MU_RUN_TEST(passando_uma_variavel_inexistente_deve_retornar_o_mesmo_env);
	MU_RUN_TEST(Passando_a_variavel_TERM_o_resultado_deve_ser_env_sem_a_variavel_TERM_nenhuma_outra_fora_essa);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
