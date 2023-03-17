#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(Passando_key_como_MINISHELL_value_com_Minishelly_e_as_variaveis_de_ambiente_precisa_ter_MINISHELL_eq_MiniSHelly_como_ultimo_item_de_envp) {
	// CONFIG
	int				i = 0;
	int				j = 0;
	char			*key = "MINISHELL";
	char			*value = "Minishelly";
	char			*expected_insert = "MINISHELL=Minishelly";
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	add_envp_item(&mini, key, value);

	// ASSERTS
	while (environ[i])
	{
		mu_assert_string_eq(environ[i + j], (mini.e)[i]);
		i++;
	}
	mu_assert_string_eq(expected_insert, (mini.e)[i]);
	clean_env(mini.e);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(Passando_key_como_MINISHELL_value_com_Minishelly_e_as_variaveis_de_ambiente_precisa_ter_MINISHELL_eq_MiniSHelly_como_ultimo_item_de_envp);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
