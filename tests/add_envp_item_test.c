#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(Passando_key_como_MINISHELL_value_com_Minishelly_e_as_variaveis_de_ambiente_precisa_ter_MINISHELL_eq_MiniSHelly_como_ultimo_item_de_envp) {
	// CONFIG
	int				i = 0;
	char			*key = "MINISHELL";
	char			*value = "Minishelly";
	char			*expected_insert = "MINISHELL=Minishelly";
	t_minishelly	*mini = &((t_minishelly){0});
	extern char		**environ;

	// ACT
	get_envp(environ, mini);
	add_envp_item(mini, key, value);

	// ASSERTS
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->e[i]);
		i++;
	}
	mu_assert_string_eq(expected_insert, mini->e[i]);
	clean_env(mini->e);
}

MU_TEST(Passando_uma_variavel_existente_key_como_PATH_value_com_PATHS_e_as_variaveis_de_ambiente_precisa_ter_NULL_como_ultimo_item_de_envp) {
	// CONFIG
	extern char		**environ;
	char			*key = "PATH";
	int				i = search_envp(environ, key);
	char			*value = environ[i] + keylen(environ[i]);
	char			*expected_insert = NULL;
	t_minishelly	*mini = &((t_minishelly){0});

	// ACT
	get_envp(environ, mini);
	add_envp_item(mini, key, value);

	// ASSERTS
	i = 0;
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->e[i]);
		i++;
	}
	mu_assert_string_eq(expected_insert, mini->e[i]);
	clean_env(mini->e);
}

MU_TEST(Passando_key_como_NULL_com_value_WHAT_o_env_deve_permanecer_o_mesmo) {
	// CONFIG
	extern char		**environ;
	char			*key = NULL;
	char			*value = "test";
	char			*expected_insert = NULL;
	t_minishelly	*mini = &((t_minishelly){0});
	int				i;

	// ACT
	get_envp(environ, mini);
	add_envp_item(mini, key, value);

	// ASSERTS
	i = 0;
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->e[i]);
		i++;
	}
	mu_assert_string_eq(expected_insert, mini->e[i]);
	clean_env(mini->e);
}

MU_TEST(Passando_key_como_KLEYTON_com_value_NULL_o_env_possuir_a_variavel_KLEYTON_eq_NULL) {
	// CONFIG
	extern char		**environ;
	char			*key = "KLEYTON";
	char			*value = NULL;
	char			*expected_insert = "KLEYTON=";
	t_minishelly	*mini = &((t_minishelly){0});
	int				i;

	// ACT
	get_envp(environ, mini);
	add_envp_item(mini, key, value);

	// ASSERTS
	i = 0;
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->e[i]);
		i++;
	}
	mu_assert_string_eq(expected_insert, mini->e[i]);
	clean_env(mini->e);
}

MU_TEST(Passando_key_como_KLEYTON_com_value_RASTA_para_um_env_nulo_o_env_deve_possuir_somente_a_nova_variavel) {
	// CONFIG
	extern char		**environ;
	char			*key = "KLEYTON";
	char			*value = "RASTA";
	t_minishelly	*mini = &((t_minishelly){0});
	int				i;

	// ACT
	add_envp_item(mini, key, value);

	// ASSERTS
	mu_assert_string_eq("KLEYTON=RASTA", mini->e[0]);
	mu_assert(NULL == mini->e[1], "Position is not NULL");
	clean_env(mini->e);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(Passando_key_como_MINISHELL_value_com_Minishelly_e_as_variaveis_de_ambiente_precisa_ter_MINISHELL_eq_MiniSHelly_como_ultimo_item_de_envp);
	MU_RUN_TEST(Passando_uma_variavel_existente_key_como_PATH_value_com_PATHS_e_as_variaveis_de_ambiente_precisa_ter_NULL_como_ultimo_item_de_envp);
	MU_RUN_TEST(Passando_key_como_NULL_com_value_WHAT_o_env_deve_permanecer_o_mesmo);
	MU_RUN_TEST(Passando_key_como_KLEYTON_com_value_NULL_o_env_possuir_a_variavel_KLEYTON_eq_NULL);
	MU_RUN_TEST(Passando_key_como_KLEYTON_com_value_RASTA_para_um_env_nulo_o_env_deve_possuir_somente_a_nova_variavel);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
