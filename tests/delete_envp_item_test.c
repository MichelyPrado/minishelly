#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(Passando_uma_variavel_de_ambiente_existente_o_resultado_deve_ser_envp_sem_a_variavel_informada) {
	// CONFIG
	int				i = 0;
	int				j = 0;
	char			*deleted_item = "GJS_DEBUG_TOPICS";
	int				size_item = ft_strlen(deleted_item);
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	delete_envp_item(&mini, deleted_item);

	// ASSERTS
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], deleted_item, size_item) && size_item)
			j = 1;
		mu_assert_string_eq(environ[i + j], (mini.e)[i]);
		i++;
	}
	clean_env(mini.e);
}

MU_TEST(Passando_uma_variavel_de_ambiente_nula_o_resultado_deve_ser_o_mesmo_da_entrada) {
	// CONFIG
	int				i = 0;
	int				j = 0;
	char			*deleted_item = NULL;
	int				size_item = ft_strlen(deleted_item);
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	get_envp(environ, &mini);
	delete_envp_item(&mini, deleted_item);

	// ASSERTS
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], deleted_item, size_item) && size_item)
			j = 1;
		mu_assert_string_eq(environ[i + j], (mini.e)[i]);
		i++;
	}
	clean_env(mini.e);
}

MU_TEST(Passando_uma_estrutura_nula_o_resultado_deve_ser_o_mesmo_da_entrada) {
	// CONFIG
	int				i = 0;
	int				j = 0;
	char			*deleted_item = "USER";
	int				size_item = ft_strlen(deleted_item);
	t_minishelly	mini;
	extern char		**environ;

	// ACT
	//mini.e = (char){0};
	delete_envp_item(&mini, deleted_item);
	// ASSERTS
	mu_assert(NULL == mini.e, "The return env is not null");
	clean_env(mini.e);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(Passando_uma_variavel_de_ambiente_existente_o_resultado_deve_ser_envp_sem_a_variavel_informada);
	MU_RUN_TEST(Passando_uma_variavel_de_ambiente_nula_o_resultado_deve_ser_o_mesmo_da_entrada);
	//MU_RUN_TEST(Passando_uma_estrutura_nula_o_resultado_deve_ser_o_mesmo_da_entrada);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
