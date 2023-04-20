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

MU_TEST(test)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split("/dgsagdhagd\a", '\a');
	char	*exp_token[] 		= {"/dgsagdhagd", NULL};
	int     expectd 			= -1;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(test1)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split("/usr/bin/cat\a", '\a');
	char	*exp_token[] 		= {"/usr/bin/cat", NULL};
	int     expectd 			= 0;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(test2)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split("cat\a", '\a');
	char	*exp_token[] 		= {"/usr/bin/cat", NULL};
	int     expectd 			= 0;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(test3)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split("grep\a", '\a');
	char	*exp_token[] 		= {"/usr/bin/grep", NULL};
	int     expectd 			= 0;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(test4)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split("grep\a", '\a');
	char	*exp_token[] 		= {"grep", NULL};
	int     expectd 			= -1;

	result = cmd_path_valid(token, NULL);

	mu_assert_int_eq(expectd, result);
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(test5)
{
	int     result;
	char	str_err[BUFFER];
	char    **token 			= ft_split(" ", ' ');
	char	*exp_token[] 		= {NULL};
	int     expectd 			= -1;

	result = cmd_path_valid(token, g_path);

	mu_assert_int_eq(expectd, result);
	assert_token(exp_token, token, str_err);
	clean_strlist(&token);
}

MU_TEST(test6)
{
	int     result;
	char	str_err[BUFFER];
	int     expectd 			= -1;

	result = cmd_path_valid(NULL, g_path);

	mu_assert_int_eq(expectd, result);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
	MU_RUN_TEST(test1);
	MU_RUN_TEST(test2);
	MU_RUN_TEST(test3);
	MU_RUN_TEST(test4);
	MU_RUN_TEST(test5);
	MU_RUN_TEST(test6);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
