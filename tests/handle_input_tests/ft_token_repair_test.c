#include "../includes/tests_includes.h"

void    alter_no_print(char *line, char s, int in)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == s)
            line[i] = in;
        i++;
    }
}

MU_TEST(test1) {
	// CONFIG
    char    *token = ft_strdup("echo batata doce");
    char    *expected = ft_strdup("echo*batata*doce");
    alter_no_print(expected, '*', -1);
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
    free(expected);
}

MU_TEST(test2) {
	// CONFIG
    char    *token = ft_strdup("echo \"batata doce\"");
    char    *expected = ft_strdup("echo*\abatata doce\a");
    alter_no_print(expected, '*', -1);
    alter_no_print(expected, '\a', -42);
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
    free(expected);
}

MU_TEST(test3) {
	// CONFIG
    char    *token1 = ft_strdup("echo \'batata doce\'");
    char    *expected = ft_strdup("echo*\fbatata doce\f");
    alter_no_print(expected, '*', -1);
    alter_no_print(expected, '\f', -21);
    char    *result;

    // ACT
    result = ft_token_repair(token1);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token1);
    free(expected);
}

MU_TEST(test4) {
	// CONFIG
    char    *token = ft_strdup("echo \'batata  \"d    \'oce\" caramelo");
    char    *expected = ft_strdup("echo*\fbatata  \"d    \foce\"*caramelo");
    alter_no_print(expected, '*', -1);
    alter_no_print(expected, '\f', -21);
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
    free(expected);
}

MU_TEST(test5) {
	// CONFIG
    char    *token = ft_strdup("echo \"batata  \'d    \"oce\' caramelo");
    char    *expected = ft_strdup("echo*\abatata  \'d    \aoce'*caramelo");
    alter_no_print(expected, '*', -1);
    alter_no_print(expected, '\a', -42);
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
    free(expected);
}

MU_TEST(test6) {
	// CONFIG
    char    *token = ft_strdup("\"'' ! ''\" 'HUMOR AMOR '\"!\"\'X\"\"\"\"\"\"\"\' ");
    char    *expected = ft_strdup("-'' ! ''-*+HUMOR AMOR +-!-+X\"\"\"\"\"\"\"+*");
    alter_no_print(expected, '*', -1);
    alter_no_print(expected, '-', -42);
    alter_no_print(expected, '+', -21);
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
    free(expected);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test1);
	MU_RUN_TEST(test2);
    MU_RUN_TEST(test3);
    MU_RUN_TEST(test4);
    MU_RUN_TEST(test5);
    //MU_RUN_TEST(test6);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
