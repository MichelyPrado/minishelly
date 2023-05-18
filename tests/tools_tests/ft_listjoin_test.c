#include "../includes/tests_includes.h"

char    **ls1 = (char *[]){"echo", "2", NULL};
char    **ls2 = (char *[]){"echo", "3", NULL};


MU_TEST(test) {
    int     i;
    char    *expected[] = {"echo", "2", "echo", "3", NULL};
    char    **result;

    result = ft_listjoin(ls1, ls2);

    i = 0;
    while (expected[i])
    {
        mu_assert_string_eq(expected[i], result[i]);
        i++;
    }
    mu_assert_string_eq(expected[i], result[i]);
    if (result)
        free(result);
}

MU_TEST(test1) {
    int     i;
    char    *expected[] = {"echo", "3", NULL};
    char    **result;

    result = ft_listjoin(NULL, ls2);

    i = 0;
    while (expected[i])
    {
        mu_assert_string_eq(expected[i], result[i]);
        i++;
    }
    mu_assert_string_eq(expected[i], result[i]);
}

MU_TEST(test2) {
    int     i;
    char    *expected[] = {"echo", "2", NULL};
    char    **result;

    result = ft_listjoin(ls1, NULL);

    i = 0;
    while (expected[i])
    {
        mu_assert_string_eq(expected[i], result[i]);
        i++;
    }
    mu_assert_string_eq(expected[i], result[i]);
}

MU_TEST(test3) {
    int     i;
    char    **expected = NULL;
    char    **result;

    result = ft_listjoin(NULL, NULL);

    i = 0;
    mu_assert(expected == result, "is not null");
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
    MU_RUN_TEST(test1);
    MU_RUN_TEST(test2);
    MU_RUN_TEST(test3);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}