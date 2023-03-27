#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(test1) {
	// CONFIG
	char			*str			= "echo test | | echo bug";
	int				expected		= 26;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(test2) {
	// CONFIG
	char			*str			= "echo test || echo bug && cat ty";
	int				expected		= 35;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(test3) {
	// CONFIG
	char			*str			= "echo < cat << > >> & && | ||";
	int				expected		= 42;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(test4) {
	// CONFIG
	char			*str			= "";
	int				expected		= 0;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(test5) {
	// CONFIG
	char			*str			= NULL;
	int				expected		= 0;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
}

MU_TEST(test6) {
	// CONFIG
	char			*str			= "echo minishelly";
	int				expected		= 15;
	int				result;

	// ACT
	result = count_delimiter(str);

	// ASSERTS
	mu_assert_int_eq(expected, result);
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

