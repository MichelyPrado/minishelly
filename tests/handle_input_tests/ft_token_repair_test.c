#include "../includes/tests_includes.h"

MU_TEST(test1) {
	// CONFIG
    char    *token = ft_strdup("echo batata doce");
    char    *expected = "echo*batata*doce";
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
}

MU_TEST(test2) {
	// CONFIG
    char    *token = ft_strdup("echo \"batata doce\"");
    char    *expected = "echo**batata doce*";
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
}

MU_TEST(test3) {
	// CONFIG
    char    *token1 = ft_strdup("echo \'batata doce\'");
    char    *expected = "echo**batata doce*";
    char    *result;

    // ACT
    result = ft_token_repair(token1);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token1);
}

MU_TEST(test4) {
	// CONFIG
    char    *token = ft_strdup("echo \'batata  \"d    \'oce\" caramelo");
    char    *expected = "echo**batata  \"d    *oce\"*caramelo";
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
}

MU_TEST(test5) {
	// CONFIG
    char    *token = ft_strdup("echo \"batata  \'d    \"oce\' caramelo");
    char    *expected = "echo**batata  \'d    *oce'*caramelo";
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
}

MU_TEST(test6) {
	// CONFIG
    char    *token = ft_strdup("\"'' ! ''\" 'HUMOR AMOR '\"!\"'X\"\"\"\"\"\"\"' ");
    char    *expected = "*'' ! ''***HUMOR AMOR **!**X\"\"\"\"\"\"\"**";
    char    *result;

    // ACT
    result = ft_token_repair(token);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(token);
}

MU_TEST_SUITE(test_suite) {
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
