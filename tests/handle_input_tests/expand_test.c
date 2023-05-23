#include "../includes/tests_includes.h"

char			*c_env[] = { "USER=dapaulin",
                             "CORONA=cerveja",
							 "TERM=xterm-256color",
							 "OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly",
							 "PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
							 "LANG=pt",
                             "URSO=jobin$CORONA",
							 NULL
							};
#define DOLAR '$'

MU_TEST(test_passing_a_dolar_with_the_var_USER_should_be_dapaulin) {
    char    *line = ft_strdup("$USER");
    char    *expected = "dapaulin";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_4_spaces_with_the_var_USER_should_be_4_spaces_dapaulin) {
    char    *line = ft_strdup("    $USER");
    char    *expected = "    dapaulin";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_4_spaces_USER_4_spaces_should_be_4_spaces_dapaulin_4_spaces) {
    char    *line = ft_strdup("    $USER    ");
    char    *expected = "    dapaulin    ";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_a_var_with_another_var_inside_should_expand_both) {
    char    *line = ft_strdup("    $URSO    ");
    char    *expected = "    jobincerveja    ";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_a_nonexistent_variable_should_be_nothing) {
    char    *line = ft_strdup("    $CRUZ    ");
    char    *expected = "        ";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_a_null_line_should_be_null)
{
    char    *line = NULL;
    char    *expected = NULL;

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
}

MU_TEST(test_passing_a_string_with_only_$_should_be_$) {
    char    *line = ft_strdup("    $");
    char    *expected = "    $";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_a_string_with_only_$_between_double_quotes_should_be_$_between_double_quotes) {
    char    *line = ft_strdup("\"    $    \"");
    char    *expected = "\"    $    \"";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_a_string_with_only_$USER_double_quotes_should_be_dapaulin_between_double_quotes) {
    char    *line = ft_strdup("\"    $USER    \"");
    char    *expected = "\"    dapaulin    \"";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_a_string_with_only_$USER_single_quotes_should_be_$USER_between_single_quotes) {
    char    *line = ft_strdup("'    $USER    '");
    char    *expected = "'    dapaulin    '";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_a_string_with_only_$USER_with_double_quotes_and_inside_single_quotes_should_be_dapaulin_between_single_quotes_double_quotes) {
    char    *line = ft_strdup("\"'    $USER    '\"");
    char    *expected = "\"'    dapaulin    '\"";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test_passing_$_question_mark_should_be_status_code) {
    char    *line = ft_strdup("\"'    $?    '\"");
    char    *expected = "\"'    0    '\"";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST(test) {
    char    *line = ft_strdup("\"$PWD\"");
    char    *expected = "\"/nfs/homes/dapaulin/Documents/project-42/minishelly/tests\"";

    search_for_symbol(&line, DOLAR, c_env);

    mu_assert_string_eq(expected, line);
    if (line)
        free(line);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test_passing_a_dolar_with_the_var_USER_should_be_dapaulin);
    MU_RUN_TEST(test_passing_4_spaces_with_the_var_USER_should_be_4_spaces_dapaulin);
    MU_RUN_TEST(test_passing_4_spaces_USER_4_spaces_should_be_4_spaces_dapaulin_4_spaces);
    MU_RUN_TEST(test_passing_a_var_with_another_var_inside_should_expand_both);
    MU_RUN_TEST(test_passing_a_nonexistent_variable_should_be_nothing);
    MU_RUN_TEST(test_passing_a_null_line_should_be_null);
    MU_RUN_TEST(test_passing_a_string_with_only_$_should_be_$);
    MU_RUN_TEST(test_passing_a_string_with_only_$_between_double_quotes_should_be_$_between_double_quotes);
    MU_RUN_TEST(test_passing_a_string_with_only_$USER_double_quotes_should_be_dapaulin_between_double_quotes);
    MU_RUN_TEST(test_passing_a_string_with_only_$USER_single_quotes_should_be_$USER_between_single_quotes);
    MU_RUN_TEST(test_passing_a_string_with_only_$USER_with_double_quotes_and_inside_single_quotes_should_be_dapaulin_between_single_quotes_double_quotes);
    MU_RUN_TEST(test_passing_$_question_mark_should_be_status_code);
    MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}