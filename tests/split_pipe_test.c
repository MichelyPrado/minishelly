#include "../minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(test1) {
	// CONFIG
	char			*cmds			= "echo test";
	char			*expected_cmds	= "echo test";
	char			*result_cmds	= NULL;

	// ACT
	result_cmds = symbol_delimiter(cmds);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, result_cmds);
	free(result_cmds);
}

MU_TEST(test2) {
	// CONFIG
	char			*cmds_pipe		= "echo test | michely";
	char			*expected_cmds 	= "echo test *|* michely";
	char			*result_cmds	= NULL;

	// ACT
	result_cmds = symbol_delimiter(cmds_pipe);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(result_cmds));
	mu_assert_string_eq(expected_cmds, result_cmds);
	free(result_cmds);
}

MU_TEST(test3) {
	// CONFIG
	char			*cmds_pipe		= "echo test | michely | davy";
	char			*expected_cmds 	= "echo test *|* michely *|* davy";
	char			*result_cmds	= NULL;

	// ACT
	result_cmds = symbol_delimiter(cmds_pipe);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(result_cmds));
	mu_assert_string_eq(expected_cmds, result_cmds);
	free(result_cmds);
}

MU_TEST(test4) {
	// CONFIG
	char			*cmds_pipe		= "echo test |michely |davy";
	char			*expected_cmds 	= "echo test *|*michely *|*davy";
	char			*result_cmds	= NULL;

	// ACT
	result_cmds = symbol_delimiter(cmds_pipe);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(result_cmds));
	mu_assert_string_eq(expected_cmds, result_cmds);
	free(result_cmds);
}

MU_TEST(test5) {
	// CONFIG
	char			*cmds_pipe		= NULL;
	char			*expected_cmds 	= NULL;
	char			*result_cmds	= "Errou";

	// ACT
	result_cmds = symbol_delimiter(cmds_pipe);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(result_cmds));
	mu_assert_string_eq(expected_cmds, result_cmds);
	free(result_cmds);

}

MU_TEST(test6) {
	// CONFIG
	char			*cmds_pipe		= "echo test > michely";
	char			*expected_cmds 	= "echo test *>* michely";
	char			*result_cmds	= NULL;

	// ACT
	result_cmds = symbol_delimiter(cmds_pipe);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(result_cmds));
	mu_assert_string_eq(expected_cmds, result_cmds);
	free(result_cmds);

}

MU_TEST(test7) {
	// CONFIG
	char			*cmds_pipe		= "echo test | michely > davy > banana";
	char			*expected_cmds 	= "echo test *|* michely *>* davy *>* banana";
	char			*result_cmds	= NULL;

	// ACT
	result_cmds = symbol_delimiter(cmds_pipe);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(result_cmds));
	mu_assert_string_eq(expected_cmds, result_cmds);
	free(result_cmds);

}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test1);
	MU_RUN_TEST(test2);
	MU_RUN_TEST(test3);
	MU_RUN_TEST(test4);
	MU_RUN_TEST(test5);
	MU_RUN_TEST(test6);
	MU_RUN_TEST(test7);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

