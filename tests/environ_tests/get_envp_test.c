#include "../includes/tests_includes.h"

MU_TEST(prim_arg) {
	// CONFIG
	t_sys_config	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);

	// ASSERTS
	mu_assert_string_eq("GJS_DEBUG_TOPICS=JS ERROR;JS LOG", (mini.env)[0]);
	clean_env(mini.env);
}

MU_TEST(testa_se_os_dois_primeiras_variaveis_de_ambiente_foram_alocadas) {
	// CONFIG
	t_sys_config	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);

	// ASSERTS
	mu_assert_string_eq("GJS_DEBUG_TOPICS=JS ERROR;JS LOG", (mini.env)[0]);
	mu_assert_string_eq("USER=dapaulin", (mini.env)[1]);
	clean_env(mini.env);
}

MU_TEST(test) {
	// CONFIG
	int				i = 0;
	t_sys_config	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);

	// ASSERTS
	while (environ[i])
	{
		mu_assert_string_eq(environ[i], (mini.env)[i]);
		i++;
	}
	clean_env(mini.env);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(prim_arg);
	MU_RUN_TEST(testa_se_os_dois_primeiras_variaveis_de_ambiente_foram_alocadas);
	MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

