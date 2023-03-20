#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(passando_a_variavel_USER_deve_retornar_1) {
	// CONFIG
	char			*key = "USER";
	int				expected_index = 1;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(passando_a_variavel_TERM_deve_retornar_36) {
	// CONFIG
	char			*key = "TERM";
	int				expected_index = 32;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(Passando_uma_variavel_inexistente_retonar_menos_1) {
	// CONFIG
	char			*key = "PIMENTA";
	int				expected_index = -1;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(passando_uma_variavel_vazia_retornar_menos_1) {
	// CONFIG
	char			*key = "";
	int				expected_index = -1;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(passando_uma_variavel_nula_retorna_menos_1) {
	// CONFIG
	char			*key = NULL;
	int				expected_index = -1;
	int				result_index;
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.e);
}

MU_TEST(passando_um_env_nulo_retornar_menos_1) {
	// CONFIG
	char			*key = "BANANADA";
	int				expected_index = -1;
	int				result_index;
	t_minishelly	mini = (t_minishelly) {0};
	extern char		**environ;

	// ACT
	result_index = search_envp(mini.e, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(passando_a_variavel_USER_deve_retornar_1);
	MU_RUN_TEST(passando_a_variavel_TERM_deve_retornar_36);
	MU_RUN_TEST(Passando_uma_variavel_inexistente_retonar_menos_1);
	MU_RUN_TEST(passando_uma_variavel_vazia_retornar_menos_1);
	MU_RUN_TEST(passando_uma_variavel_nula_retorna_menos_1);
	MU_RUN_TEST(passando_um_env_nulo_retornar_menos_1);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
