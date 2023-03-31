#include "./minunit-42/minunit.h"
#include "../srcs/minishell.h"
#include "../srcs/libft/libft.h"



MU_TEST(test1) {
	// CONFIG
    char    *cmd = "cd";
    t_types expected = OP_BUILTIN;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST(test2) {
	// CONFIG
    char    *cmd = "|";
    t_types expected = OP_PIPE;
    t_types result;

    // ACT
    result = tag_token(cmd);
    
    //ASSERT
    mu_assert_int_eq(expected, result);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test1);
    MU_RUN_TEST(test2);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
