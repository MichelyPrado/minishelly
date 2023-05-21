#include "../includes/tests_includes.h"

MU_TEST(passing_a_space_should_be_default_operation) {
	// CONFIG
    char    *cmd = " ";
    t_types expected = OP_DEFAULT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_AND_should_be_AND_operation) {
	// CONFIG
    char    *cmd = "&&";
    t_types expected = OP_CMD;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_OR_should_be_OR_operation) {
	// CONFIG
    char    *cmd = "||";
    t_types expected = OP_CMD;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_PIPE_should_be_PIPE_operation) {
	// CONFIG
    char    *cmd = "|";
    t_types expected = OP_PIPE;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_OUTPUT_should_be_OUTPUT_operation) {
	// CONFIG
    char    *cmd = ">";
    t_types expected = OP_OUTPUT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_INPUT_should_be_INPUT_operation) {
	// CONFIG
    char    *cmd = "<";
    t_types expected = OP_INPUT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_UNTIL_should_be_UNTIL_operation) {
	// CONFIG
    char    *cmd = "<<";
    t_types expected = OP_UNTIL;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_APPEN_should_be_APPEND_operation) {
	// CONFIG
    char    *cmd = ">>";
    t_types expected = OP_APPEND;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_COMMAND_should_be_CMD_operation) {
	// CONFIG
    char    *cmd = "grep";
    t_types expected = OP_CMD;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_exit_should_be_EXIT_operation) {
	// CONFIG
    char    *cmd = "exit";
    t_types expected = OP_EXIT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_cd_should_be_CD_operation) {
	// CONFIG
    char    *cmd = "cd";
    t_types expected = OP_CD;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_env_should_be_ENV_operation) {
	// CONFIG
    char    *cmd = "env";
    t_types expected = OP_ENV;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_unset_should_be_UNSET_operation) {
	// CONFIG
    char    *cmd = "unset";
    t_types expected = OP_UNSET;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_export_should_be_EXPORT_operation) {
	// CONFIG
    char    *cmd = "export";
    t_types expected = OP_EXPORT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_pwd_should_be_PWD_operation) {
	// CONFIG
    char    *cmd = "pwd";
    t_types expected = OP_PWD;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_echo_should_be_ECHO_operation) {
	// CONFIG
    char    *cmd = "echo";
    t_types expected = OP_ECHO;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_space_tab_space_tab_should_be_default_operation) {
	// CONFIG
    char    *cmd = " \t \t";
    t_types expected = OP_DEFAULT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_space_sed_should_be_COMMAND_operation) {
	// CONFIG
    char    *cmd = " sed";
    t_types expected = OP_CMD;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(passing_NULL_should_be_default_operation) {
	// CONFIG
    char    *cmd = NULL;
    t_types expected = OP_DEFAULT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(passing_a_space_should_be_default_operation);
	MU_RUN_TEST(passing_AND_should_be_AND_operation);
    MU_RUN_TEST(passing_OR_should_be_OR_operation);
    MU_RUN_TEST(passing_PIPE_should_be_PIPE_operation);
    MU_RUN_TEST(passing_OUTPUT_should_be_OUTPUT_operation);
    MU_RUN_TEST(passing_INPUT_should_be_INPUT_operation);
    MU_RUN_TEST(passing_UNTIL_should_be_UNTIL_operation);
    MU_RUN_TEST(passing_APPEN_should_be_APPEND_operation);
    MU_RUN_TEST(passing_COMMAND_should_be_CMD_operation);
    MU_RUN_TEST(passing_exit_should_be_EXIT_operation);
    MU_RUN_TEST(passing_cd_should_be_CD_operation);
    MU_RUN_TEST(passing_env_should_be_ENV_operation);
    MU_RUN_TEST(passing_unset_should_be_UNSET_operation);
    MU_RUN_TEST(passing_export_should_be_EXPORT_operation);
    MU_RUN_TEST(passing_pwd_should_be_PWD_operation);
    MU_RUN_TEST(passing_echo_should_be_ECHO_operation);
    MU_RUN_TEST(passing_space_tab_space_tab_should_be_default_operation);
    MU_RUN_TEST(passing_space_sed_should_be_COMMAND_operation);
    MU_RUN_TEST(passing_NULL_should_be_default_operation);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
