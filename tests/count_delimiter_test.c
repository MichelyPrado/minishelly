#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(passing_a_string_with_two_pipes_should_be_26) {
	// CONFIG
	char			*str			= "echo test | | echo bug";
	int				expected		= 26;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(passing_a_string_with_OP_AND_and_OP_OR_should_be_35) {
	// CONFIG
	char			*str			= "echo test || echo bug && cat ty";
	int				expected		= 35;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(passing_a_string_with_all_OP_with_spaces_should_be) {
	// CONFIG
	char			*str			= "echo < cat << > >> & && | ||";
	int				expected		= 42;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(passing_a_empty_string_should_be_0) {
	// CONFIG
	char			*str			= "";
	int				expected		= 0;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(passing_a_NULL_should_be_0) {
	// CONFIG
	char			*str			= NULL;
	int				expected		= 0;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(passing_a_string_without_OP_should_be_string_len_15) {
	// CONFIG
	char			*str			= "echo minishelly";
	int				expected		= 15;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(passing_a_string_with_open_and_close_double_quotes_should_be_23) {
	// CONFIG
	char			*str			= "echo \" | > \" minishelly";
	int				expected		= 23;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(passing_a_string_with_open_and_close_simple_quotes_should_be_31) {
	// CONFIG
	char			*str			= "echo \' | caraval > \' minishelly";
	int				expected		= 31;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(passing_a_string_with_open_and_no_close_double_quotes_should_be_minus_1) {
	// CONFIG
	char			*str			= "echo \" | >  minishelly";
	int				expected		= -1;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(passing_a_string_with_open_and_no_close_simple_quotes_should_be_minus_1) {
	// CONFIG
	char			*str			= "echo \' | >  minishelly";
	int				expected		= -1;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(test) {
	// CONFIG
	char			*str			= "echo \' | >  minishelly\'";
	int				expected		= 23;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(passing_a_string_with_two_pipes_should_be_26);
	MU_RUN_TEST(passing_a_string_with_OP_AND_and_OP_OR_should_be_35);
	MU_RUN_TEST(passing_a_string_with_all_OP_with_spaces_should_be);
	MU_RUN_TEST(passing_a_empty_string_should_be_0);
	MU_RUN_TEST(passing_a_NULL_should_be_0);
	MU_RUN_TEST(passing_a_string_without_OP_should_be_string_len_15);
	MU_RUN_TEST(passing_a_string_with_open_and_close_double_quotes_should_be_23);
	MU_RUN_TEST(passing_a_string_with_open_and_close_simple_quotes_should_be_31);
	MU_RUN_TEST(passing_a_string_with_open_and_no_close_double_quotes_should_be_minus_1);
	MU_RUN_TEST(passing_a_string_with_open_and_no_close_simple_quotes_should_be_minus_1);
	MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

