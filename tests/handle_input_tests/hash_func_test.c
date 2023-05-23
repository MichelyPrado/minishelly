#include "../includes/tests_includes.h"

t_keyword_map keyword[] = {
    {"|", OP_PIPE},
    {">", OP_OUTPUT},
    {"<", OP_INPUT},
    {"<<", OP_UNTIL},
    {">>", OP_APPEND},
    {"exit", OP_EXIT},
    {"cd", OP_CD},
    {"env", OP_ENV},
    {"unset", OP_UNSET},
    {"export", OP_EXPORT},
    {"pwd", OP_PWD},
    {"echo", OP_ECHO}
};

MU_TEST(test) {
	mu_assert_int_eq(0, hash_func("   ", keyword));
	mu_assert_int_eq(0, hash_func(NULL, keyword));
	mu_assert_int_eq(5, hash_func("|", keyword));
	mu_assert_int_eq(6, hash_func("||", keyword));
	mu_assert_int_eq(1, hash_func(">", keyword));
	mu_assert_int_eq(2, hash_func("<", keyword));
	mu_assert_int_eq(3, hash_func("<<", keyword));
	mu_assert_int_eq(4, hash_func(">>", keyword));
	mu_assert_int_eq(7, hash_func("exit", keyword));
	mu_assert_int_eq(8, hash_func("cd", keyword));
	mu_assert_int_eq(9, hash_func("env", keyword));
	mu_assert_int_eq(10, hash_func("unset", keyword));
	mu_assert_int_eq(11, hash_func("export", keyword));
	mu_assert_int_eq(12, hash_func("pwd", keyword));
	mu_assert_int_eq(13, hash_func("echo", keyword));
	mu_assert_int_eq(6, hash_func("&&", keyword));
	mu_assert_int_eq(6, hash_func("awk", keyword));
	mu_assert_int_eq(6, hash_func("&", keyword));
	mu_assert_int_eq(6, hash_func("dwp", keyword));
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

