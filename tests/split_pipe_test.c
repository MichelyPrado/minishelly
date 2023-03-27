#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(test1) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds			= "echo test";
	char			*expected_cmds	= "echo test";

	// ACT
	symbol_delimiter(cmds, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	free(conf.new_parser);
}

MU_TEST(test2) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo test | michely";
	char			*expected_cmds 	= "echo test *|* michely";

	// ACT
	symbol_delimiter(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	free(conf.new_parser);
}

MU_TEST(test3) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo test | michely | davy";
	char			*expected_cmds 	= "echo test *|* michely *|* davy";

	// ACT
	symbol_delimiter(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	free(conf.new_parser);
}

MU_TEST(test4) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo test |michely |davy";
	char			*expected_cmds 	= "echo test *|*michely *|*davy";

	// ACT
	symbol_delimiter(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	free(conf.new_parser);
}

MU_TEST(test5) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= NULL;
	char			*expected_cmds 	= NULL;

	// ACT
	symbol_delimiter(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	free(conf.new_parser);

}

MU_TEST(test6) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo test > michely";
	char			*expected_cmds 	= "echo test *>* michely";

	// ACT
	symbol_delimiter(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	free(conf.new_parser);

}

MU_TEST(test7) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo test | michely > davy > banana";
	char			*expected_cmds 	= "echo test *|* michely *>* davy *>* banana";

	// ACT
	symbol_delimiter(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	free(conf.new_parser);

}

MU_TEST(test8) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo test || michely";
	char			*expected_cmds 	= "echo test *||* michely";

	// ACT
	symbol_delimiter(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	free(conf.new_parser);

}

MU_TEST(test9) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo \"test | test\" | michely";
	char			*expected_cmds 	= "echo \"test | test\" *|* michely";

	// ACT
	symbol_delimiter(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	free(conf.new_parser);

}

MU_TEST(test10) {
	// CONFIG
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo test & test && michely";
	char			*expected_cmds 	= "echo test & test *&&* michely";

	// ACT
	symbol_delimiter(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	free(conf.new_parser);

}


MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test1);
	MU_RUN_TEST(test2);
	MU_RUN_TEST(test3);
	MU_RUN_TEST(test4);
	MU_RUN_TEST(test5);
	MU_RUN_TEST(test6);
	MU_RUN_TEST(test7);
	MU_RUN_TEST(test8);
	MU_RUN_TEST(test9);
	MU_RUN_TEST(test10);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
