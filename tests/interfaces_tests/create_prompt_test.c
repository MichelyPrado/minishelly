#include "../includes/tests_includes.h"

MU_TEST(passing_6_string_should_be_all_then_together) {
	// CONFIG
    char    *expected = "\033[0;32mMinishelly:\033[0;34m dapaulin\033[0;37m> ";
    char    *result;

    // ACT
    result = create_prompt(6, L_GREEN, SHELLNAME, L_BLUE, " dapaulin", L_WHITE, PROP);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(result);
}

MU_TEST(passing_amount_0_should_be_null) {
	// CONFIG
    char    *expected = NULL;
    char    *result;

    // ACT
    result = create_prompt(0, L_GREEN, SHELLNAME, L_BLUE, " dapaulin", L_WHITE, PROP);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(result);
}

MU_TEST(passing_amount_2_without_args_should_be_null) {
	// CONFIG
    char    *expected = NULL;
    char    *result;

    // ACT
    result = create_prompt(2);

    //ASSERT
    mu_assert_string_eq(expected, result);
    free(result);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(passing_6_string_should_be_all_then_together);
    MU_RUN_TEST(passing_amount_0_should_be_null);
    //MU_RUN_TEST(passing_amount_2_without_args_should_be_null); tratar depois
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

