#include "../includes/tests_includes.h"

#define CONST_ENVP "USER=dapaulin TERM=xterm-256color OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests L=shell LANGUAGE=en LANG=pt"

MU_TEST(passando_a_variavel_USER_deve_retornar_1) {
	// CONFIG
	char			*key = "USER";
	int				expected_index = 0;
	int				result_index;
	t_sys_config	mini;
	char			**envp = ft_split(CONST_ENVP, ' ');

	// ACT
	get_envp(envp, &mini);
	result_index = search_envp(mini.env, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.env);
	free_cmds(envp);
}

MU_TEST(passando_a_variavel_TERM_deve_retornar_31) {
	// CONFIG
	char			*key = "TERM";
	int				expected_index = 1;
	int				result_index;
	t_sys_config	mini;
	char			**envp = ft_split(CONST_ENVP, ' ');

	// ACT
	get_envp(envp, &mini);
	result_index = search_envp(mini.env, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.env);
	free_cmds(envp);
}

MU_TEST(Passando_uma_variavel_inexistente_retonar_menos_1) {
	// CONFIG
	char			*key = "PIMENTA";
	int				expected_index = -1;
	int				result_index;
	t_sys_config	mini;
	char			**envp = ft_split(CONST_ENVP, ' ');

	// ACT
	get_envp(envp, &mini);
	result_index = search_envp(mini.env, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.env);
	free_cmds(envp);
}

MU_TEST(passando_uma_variavel_vazia_retornar_menos_1) {
	// CONFIG
	char			*key = "";
	int				expected_index = -1;
	int				result_index;
	t_sys_config	mini;
	char			**envp = ft_split(CONST_ENVP, ' ');

	// ACT
	get_envp(envp, &mini);
	result_index = search_envp(mini.env, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.env);
	free_cmds(envp);
}

MU_TEST(passando_uma_variavel_nula_retorna_menos_1) {
	// CONFIG
	char			*key = NULL;
	int				expected_index = -1;
	int				result_index;
	t_sys_config	mini;
	char			**envp = ft_split(CONST_ENVP, ' ');

	// ACT
	get_envp(envp, &mini);
	result_index = search_envp(mini.env, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.env);
	free_cmds(envp);
}

MU_TEST(passando_um_env_nulo_retornar_menos_1) {
	// CONFIG
	char			*key = "BANANADA";
	int				expected_index = -1;
	int				result_index;
	t_sys_config	mini = (t_sys_config) {0};
	extern char		**environ;

	// ACT
	result_index = search_envp(mini.env, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
}

MU_TEST(passando_a_variavel_LANG_should_be_LANG_eq_pt) {
	// CONFIG
	char			*key = "LANG";
	int				expected_index = 6;
	int				result_index;
	t_sys_config	mini = (t_sys_config) {0};
	char			**envp = ft_split(CONST_ENVP, ' ');

	// ACT
	get_envp(envp, &mini);
	result_index = search_envp(mini.env, key);

	// ASSERTS
	mu_assert_int_eq(expected_index, result_index);
	clean_env(mini.env);
	free_cmds(envp);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(passando_a_variavel_USER_deve_retornar_1);
	MU_RUN_TEST(passando_a_variavel_TERM_deve_retornar_31);
	MU_RUN_TEST(Passando_uma_variavel_inexistente_retonar_menos_1);
	MU_RUN_TEST(passando_uma_variavel_vazia_retornar_menos_1);
	MU_RUN_TEST(passando_uma_variavel_nula_retorna_menos_1);
	MU_RUN_TEST(passando_um_env_nulo_retornar_menos_1);
	MU_RUN_TEST(passando_a_variavel_LANG_should_be_LANG_eq_pt);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
