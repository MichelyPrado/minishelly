#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"

MU_TEST(test0) {
	// CONFIG
    char    *cmd = " ";
    t_types expected = OP_DEFAULT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test1) {
	// CONFIG
    char    *cmd = "&&";
    t_types expected = OP_AND;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test2) {
	// CONFIG
    char    *cmd = "||";
    t_types expected = OP_OR;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test3) {
	// CONFIG
    char    *cmd = "|";
    t_types expected = OP_PIPE;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test4) {
	// CONFIG
    char    *cmd = ">";
    t_types expected = OP_OUTPUT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test5) {
	// CONFIG
    char    *cmd = "<";
    t_types expected = OP_INPUT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test6) {
	// CONFIG
    char    *cmd = "<<";
    t_types expected = OP_UNTIL;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test7) {
	// CONFIG
    char    *cmd = ">>";
    t_types expected = OP_APPEND;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test8) {
	// CONFIG
    char    *cmd = "grep";
    t_types expected = OP_CMD;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test9) {
	// CONFIG
    char    *cmd = "exit";
    t_types expected = OP_EXIT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test10) {
	// CONFIG
    char    *cmd = "cd";
    t_types expected = OP_CD;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test11) {
	// CONFIG
    char    *cmd = "env";
    t_types expected = OP_ENV;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test12) {
	// CONFIG
    char    *cmd = "unset";
    t_types expected = OP_UNSET;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test13) {
	// CONFIG
    char    *cmd = "export";
    t_types expected = OP_EXPORT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test14) {
	// CONFIG
    char    *cmd = "pwd";
    t_types expected = OP_PWD;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test15) {
	// CONFIG
    char    *cmd = "echo";
    t_types expected = OP_ECHO;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test16) {
	// CONFIG
    char    *cmd = "       ";
    t_types expected = OP_DEFAULT;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test0);
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
    MU_RUN_TEST(test11);
    MU_RUN_TEST(test12);
    MU_RUN_TEST(test13);
    MU_RUN_TEST(test14);
    MU_RUN_TEST(test15);
    MU_RUN_TEST(test16);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
