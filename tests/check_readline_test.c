#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(passing_a_string_echo_test_should_be_no_err_and_same_string) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds			= "echo test";
	char			*expected_cmds	= "echo test";

	// ACT
	err = check_readline(cmds, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);
}

MU_TEST(passing_a_string_with_two_cmds_and_one_pipe_should_be_no_err_and_divided_one_time) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo test | michely";
	char			*expected_cmds 	= "echo test *|* michely";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);
}

MU_TEST(passing_all_operators_should_be_the_operator_with_NO_PRINT_around) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo | michely & davy && wc < > << >> || ";
	char			*expected_cmds 	= "echo *|* michely & davy *&&* wc *<* *>* *<<* *>>* *||* ";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);
}

MU_TEST(passing_a_single_pipe_should_be_NO_PRINT_PIPE_NO_PRINT) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "|";
	char			*expected_cmds 	= "*|*";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);
}

MU_TEST(passing_a_double_pipe_should_be_NO_PRINT_PIPE_PIPE_NO_PRINT) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "||";
	char			*expected_cmds 	= "*||*";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);
}

MU_TEST(passing_all_operators_with_no_spaces_should_be_the_operator_with_NO_PRINT_around) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo|michely&davy&&wc<><<>>||";
	char			*expected_cmds 	= "echo*|*michely&davy*&&*wc*<**>**<<**>>**||*";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);
}

MU_TEST(passing_a_null_string_should_be_ERR_NOLINE_and_null) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= NULL;
	char			*expected_cmds 	= NULL;

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ERR_NOLINE, err);
	free(conf.new_parser);

}

MU_TEST(passing_a_string_with_open_and_close_double_quotes_must_ignore_operators_between_quotes) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo \"test | test\" | michely";
	char			*expected_cmds 	= "echo \"test | test\" *|* michely";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);

}

MU_TEST(passing_a_string_with_open_and_close_simple_quotes_must_ignore_operators_between_quotes) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo \'test > test\' | michely";
	char			*expected_cmds 	= "echo \'test > test\' *|* michely";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);

}

MU_TEST(passing_a_string_with_many_spaces_must_keep_the_spaces) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo test |                  |  cat";
	char			*expected_cmds 	= "echo test *|*                  *|*  cat";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);

}

MU_TEST(passing_a_string_with_open_and_no_close_simple_quotes_should_be_error_flag_and_string_unchanged) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo \'test > test | michely";
	char			*expected_cmds 	= NULL;

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_int_eq(ERR_QUOTES, err);

}

MU_TEST(passing_a_string_with_open_and_no_close_double_quotes_should_be_error_flag_and_string_unchanged) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo \"test > test | michely";
	char			*expected_cmds 	= NULL;

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_int_eq(ERR_QUOTES, err);
}

MU_TEST(passing_all_operators_with_no_spaces_and_operators_start_and_finish_the_string_should_be_the_operator_with_NO_PRINT_around) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "|michely&davy&&wc<><<>>||";
	char			*expected_cmds 	= "*|*michely&davy*&&*wc*<**>**<<**>>**||*";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(NO_ERR, err);
	free(conf.new_parser);
}

MU_TEST(test) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo \"test | test\"\" | michely\"";
	char			*expected_cmds 	= "echo \"test | test\"\" | michely\"";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(NO_ERR, err);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	free(conf.new_parser);
}

MU_TEST(test2) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo \"test | test\"' | michely'";
	char			*expected_cmds 	= "echo \"test | test\"' | michely'";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(NO_ERR, err);
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	free(conf.new_parser);
}

MU_TEST(test3) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo 'test | test'' | michely'";
	char			*expected_cmds 	= "echo 'test | test'' | michely'";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(NO_ERR, err);
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	free(conf.new_parser);
}

MU_TEST(test4) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo 'test | test'\" | michely\"";
	char			*expected_cmds 	= "echo 'test | test'\" | michely\"";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(NO_ERR, err);
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	free(conf.new_parser);
}

MU_TEST(test5) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo 'test | test'";
	char			*expected_cmds 	= "echo 'test | test'";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(NO_ERR, err);
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	free(conf.new_parser);
}

MU_TEST(test6) {
	// CONFIG
	t_err			err;
	t_sys_config	conf			= (t_sys_config){0};
	char			*cmds_pipe		= "echo \"test | test\"";
	char			*expected_cmds 	= "echo \"test | test\"";

	// ACT
	err = check_readline(cmds_pipe, &conf);

	// ASSERTS
	mu_assert_int_eq(NO_ERR, err);
	mu_assert_string_eq(expected_cmds, conf.new_parser);
	mu_assert_int_eq(ft_strlen(expected_cmds), ft_strlen(conf.new_parser));
	free(conf.new_parser);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(passing_a_string_echo_test_should_be_no_err_and_same_string);
	MU_RUN_TEST(passing_a_string_with_two_cmds_and_one_pipe_should_be_no_err_and_divided_one_time);
	MU_RUN_TEST(passing_all_operators_should_be_the_operator_with_NO_PRINT_around);
	MU_RUN_TEST(passing_a_single_pipe_should_be_NO_PRINT_PIPE_NO_PRINT);
	MU_RUN_TEST(passing_a_double_pipe_should_be_NO_PRINT_PIPE_PIPE_NO_PRINT);
	MU_RUN_TEST(passing_all_operators_with_no_spaces_should_be_the_operator_with_NO_PRINT_around);
	MU_RUN_TEST(passing_a_null_string_should_be_ERR_NOLINE_and_null);
	MU_RUN_TEST(passing_a_string_with_open_and_close_double_quotes_must_ignore_operators_between_quotes);
	MU_RUN_TEST(passing_a_string_with_open_and_close_simple_quotes_must_ignore_operators_between_quotes);
	MU_RUN_TEST(passing_a_string_with_many_spaces_must_keep_the_spaces);
	MU_RUN_TEST(passing_a_string_with_open_and_no_close_simple_quotes_should_be_error_flag_and_string_unchanged);
	MU_RUN_TEST(passing_a_string_with_open_and_no_close_double_quotes_should_be_error_flag_and_string_unchanged);
	MU_RUN_TEST(passing_all_operators_with_no_spaces_and_operators_start_and_finish_the_string_should_be_the_operator_with_NO_PRINT_around);
	MU_RUN_TEST(test);
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
