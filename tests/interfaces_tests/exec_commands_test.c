#include "../includes/tests_includes.h"


char			*c_env[] = { "USER=dapaulin",
							 "TERM=xterm-256color",
							 "OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly",
                             "PATH=/nfs/homes/dapaulin/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
							 "PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
							 "LANG=pt",
							 NULL
							};

char            **c_environ = (char **)c_env;

typedef struct s_tests 
{
    int             fd;
    int             bkp;
    char            *file_name;
    t_sys_config    *mini;
}               t_tests;

void    alter_no_print(char *line, char s)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == s)
            line[i] = -1;
        i++;
    }
}

static int	run_function(t_tests *vars)
{
	int	bkp;
	int	err;

	vars->fd = open(vars->file_name, O_RDWR | O_CREAT, S_IRWXU);
	dup2(vars->fd, 1);
	close(vars->fd);
	exec_commands(vars->mini);
	dup2(vars->bkp, 1);
    close(vars->bkp);
	return (err);
}

static void	assert_result(t_tests *vars, char *expected)
{
	char	*tmp;

	vars->fd = open(vars->file_name, O_RDONLY, S_IRWXU);
    tmp = get_next_line(vars->fd);
    mu_assert_string_eq(expected, tmp);
    if (tmp)
        free(tmp);
        get_next_line(vars->fd);
	close(vars->fd);
	remove(vars->file_name);
}

t_tests *config(char *line)
{
    t_tests         *vars = malloc(sizeof(t_tests));
    vars->file_name = ft_strdup("files/test.txt");
    vars->fd = 0;
    vars->bkp = dup(1);
    vars->mini = start_sys(c_environ);
    check_readline(line, vars->mini);
    alter_no_print(vars->mini->new_parser, 7);
    vars->mini->tokens = ft_create_tokens(vars->mini);
    t_token         *cleaner = vars->mini->tokens;
    return (vars);
}

void    free_all_test(t_tests *vars, t_token *cleaner)
{
    vars->mini->tokens = cleaner;
    if (vars->file_name)
        free(vars->file_name);
    clean_sys(vars->mini);
    if (vars)
        free(vars);
}

MU_TEST(test) {
    // CONFIG
    t_tests         *vars = config("cat ./testes_files/banana.txt | grep banana");
    t_token         *cleaner = vars->mini->tokens;
    char            *expected   = "banana batida\n";

    // ACT
    run_function(vars);

    // ASSERT
    assert_result(vars, expected);
    free_all_test(vars, cleaner);
}

MU_TEST(test1) {
    // CONFIG
    t_tests         *vars = config("cat ./testes_files/banana.txt|grep banana | wc -l");
    t_token         *cleaner = vars->mini->tokens;
    char            *expected   = "1\n";

    // ACT
    run_function(vars);

    // ASSERT
    assert_result(vars, expected);
    free_all_test(vars, cleaner);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
    MU_RUN_TEST(test1);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
