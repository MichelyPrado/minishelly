#include "../includes/tests_includes.h"

#define BUFFER 256
char *g_path[] =    {   "/nfs/homes/dapaulin/bin",
						"/nfs/homes/dapaulin/bin",
						"/usr/local/sbin",
						"/usr/local/bin",
						"/usr/sbin",
						"/usr/bin",
						"/sbin",
						"/bin",
						"/usr/games",
						"/usr/local/games",
						"/snap/bin"
					};

void	assert_token(char **exp_token, char **token, char *str_err)
{
	int	i;

	i = 0;
	while (exp_token && exp_token[i])
	{
		mu_assert_string_eq(exp_token[i], token[i]);
		i++;
	}
	sprintf(str_err, "expected %s, result %s", exp_token[i], token[i]);
	mu_assert(exp_token[i] == token[i], str_err);
}

MU_TEST(passing_a_file_with_no_permission_should_return_status_code_127)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split("./files/goma\a", '\a');
	char	*exp_token[] 		= {"./files/goma", NULL};
	int     expectd 			= -1;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	mu_assert_int_eq(127, *get_status_code());
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(passing_a_valid_absolute_command_should_be_return_1)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split("/usr/bin/cat\a", '\a');
	char	*exp_token[] 		= {"/usr/bin/cat", NULL};
	int     expectd 			= 1;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	mu_assert_int_eq(0, *get_status_code());
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(passing_a_valid_command_should_be_return_1)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split("cat\a", '\a');
	char	*exp_token[] 		= {"/usr/bin/cat", NULL};
	int     expectd 			= 1;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	mu_assert_int_eq(0, *get_status_code());
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(passing_a_commando_with_no_exit_the_file_should_be_status_code_126)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split("./junior\a", '\a');
	char	*exp_token[] 		= {"./junior", NULL};
	int     expectd 			= 0;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	mu_assert_int_eq(126, *get_status_code());
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(passing_a_token_with_NULL_value_should_be_status_code_126)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split(" ", ' ');
	char	*exp_token[] 		= {NULL};
	int     expectd 			= 0;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	mu_assert_int_eq(126, *get_status_code());
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(passing_a_null_token_should_be_status_code_126)
{
	int     result;
	char	str_err[BUFFER];
	int     expectd 			= 0;

	result = cmd_path_valid(NULL, g_path);

	mu_assert_int_eq(expectd, result);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(passing_a_file_with_no_permission_should_return_status_code_127);
	MU_RUN_TEST(passing_a_valid_absolute_command_should_be_return_1);
	MU_RUN_TEST(passing_a_valid_command_should_be_return_1);
	MU_RUN_TEST(passing_a_commando_with_no_exit_the_file_should_be_status_code_126);
	MU_RUN_TEST(passing_a_token_with_NULL_value_should_be_status_code_126);
	MU_RUN_TEST(passing_a_null_token_should_be_status_code_126);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
