#include "../includes/tests_includes.h"

MU_TEST(test)
{
    char    *token[] = {"dgsagdhagd", NULL};
    char    *path[]  = {"./", "/usr/bin/", NULL};
    int     expectd = -1;
    int     result;

    result = ft_is_cmd(token, path);

    mu_assert_int_eq(expectd, result);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
