#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(alter_o_valor_da_variavel_USER_para_cruz) {
	// CONFIG
	char			*key = "USER";
	char			*value = "cruz";
	char			*expected_str = "USER=cruz";
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	edit_envp(&mini, key, value);

	// ASSERTS
	mu_assert_string_eq(mini.e[search_envp(environ, key)], expected_str);
	clean_env(mini.e);
}

MU_TEST(passar_uma_key_nula_e_um_valor_valido_env_deve_ser_a_mesma) {
	// CONFIG
	int				i;
	char			*key = NULL;
	char			*value = "cruz";
	char			*expected_str = NULL;
	t_minishelly	*mini = &((t_minishelly) {0});
	extern char		**environ;

	// ACT
	get_envp(environ, mini);
	edit_envp(mini, key, value);

	// ASSERTS
	i = 0;
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], mini->e[i]);
		i++;
	}
	clean_env(mini->e);
}

MU_TEST(passar_variavel_USER_com_value_NULL_deve_ser_USER_eq) {
	// CONFIG
	char			*key = "USER";
	char			*value = NULL;
	char			*expected_str = "USER=";
	t_minishelly	*mini = &((t_minishelly) {0});
	extern char		**environ;

	// ACT
	get_envp(environ, mini);
	edit_envp(mini, key, value);

	// ASSERTS
	mu_assert_string_eq(mini->e[search_envp(environ, key)], expected_str);
	clean_env(mini->e);
}

MU_TEST(passar_variavel_USER_com_value_dapaulin_e_env_NULL_deve_ser_env_NULL) {
	// CONFIG
	char			*key = "USER";
	char			*value = "dapaulin";
	char			*expected_str = NULL;
	t_minishelly	*mini = &((t_minishelly) {0});
	extern char		**environ;

	// ACT
	edit_envp(mini, key, value);

	// ASSERTS
	mu_assert(NULL == mini->e, "Position is not NULL");
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
