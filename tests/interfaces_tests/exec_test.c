#include "../includes/tests_includes.h"

char			*c_env[] = { "USER=dapaulin",
                             "HOME=/nfs/homes/dapaulin",
							 "TERM=xterm-256color",
							 "OLDPWD=/nfs/homes/dapaulin/ls/minishelly",
							 "PWD=/nfs/homes/dapaulin/ls/minishelly/tests",
							 "LANG=pt",
							 NULL
							};

void    set_list(int amount, ...)
{
    int     i;
    t_token *token;
    va_list ap;

    i = 1;
    token = NULL;
    va_start(ap, amount);
    token = va_arg(ap, t_token *);
    while (i < amount)
    {
        if (!token)
            break ;
        token->next = va_arg(ap, t_token *);
        token = token->next;
        i++;
    }
    va_end(ap);
}

char extern     **environ;
char            *name[] = { "./test1.txt",
                            "./test2.txt",
                            "./test3.txt",
                            "./test4.txt",
                            "./test_1_echo.txt",
                            "./test_1_pwd.txt",
                            "./test_1_exit.txt",
                            "./test_1_env.txt",
                            "./test_1_export.txt",
                            "./test_1_unset.txt",
                            "./testes_files/google.tx",
                            "./ola.txt"   };
int             i = 0;

void	run_function(t_sys_config *mini)
{
    int bkp = dup(1);
	int fd = open(name[i], O_RDWR | O_CREAT, S_IRWXU );
	dup2(fd, 1);
	close(fd);
	exec(mini);
	dup2(bkp, 1);
}

static void	assert_result(char *expected)
{
    char            tmp[1000];
	ft_bzero(tmp, 1000);
	int fd = open(name[i], O_RDONLY, S_IRWXU);
    read(fd, tmp, 1000);
    mu_assert_string_eq(expected, tmp);
	close(fd);
	remove(name[i]);
}

static void	assert_result_fd(char *expected, char *fd1, char *fd2)
{
    char            tmp[1000];
	ft_bzero(tmp, 1000);
	int fd = open(name[i], O_RDONLY, S_IRWXU);
    read(fd, tmp, 1000);
    mu_assert(0 < open(fd1, O_RDWR), "file don't exist!");
    mu_assert(0 < open(fd2, O_RDWR), "file don't exist!");
    mu_assert_string_eq(expected, tmp);
	close(fd);
	remove(name[i]);
}

MU_TEST(test_passing_1_cat_cmd_should_be_the_text_inside)
{
    t_token *token = CAT_T;
    set_list(1, token);
    // Comando testado: /usr/bin/cat .testes-files/vinculo.txt
    t_sys_config mini = (t_sys_config) {.env = environ, .tokens = token};

    run_function(&mini);

    assert_result("vida dificil\ngalo");
    clean_exec(&mini.exec);
    i++;
}

MU_TEST(test_passing_cat_pipe_grep_should_be_return_the_lines_with_the_word_in_grep)
{
    t_token *token = PIPE_T;
    set_list(4, token, CAT_T, PIPE_T, GREP_T);
    // Comando testado: /usr/bin/cat .testes-files/vinculo.txt | grep galo
    t_sys_config mini = (t_sys_config) {.env = environ, .tokens = token};

    run_function(&mini);
    
    assert_result("galo\n");
    clean_exec(&mini.exec);
    i++;
}

MU_TEST(test_passing_a_cat_pipe_grep_pipe_wc_should_be_number_of_words)
{
    t_token *token = PIPE_T;
    set_list(6, token, CAT_T, PIPE_T, GREP_T, PIPE_T, WC_T);
    // Comando testado: /usr/bin/cat .testes-files/vinculo.txt | grep galo | wc -c
    t_sys_config mini = (t_sys_config) {.env = environ, .tokens = token};

    run_function(&mini);

    assert_result("5\n");
    clean_exec(&mini.exec);
    i++;
}

MU_TEST(test_passing_cat_pipe_grep_pipe_wc_pipe_tr_should_alter_the_number)
{
    t_token *token = PIPE_T;
    set_list(8, token, CAT_T, PIPE_T, GREP_T, PIPE_T, WC_T, PIPE_T, TR_T);
    // Comando testado: /usr/bin/cat .testes-files/vinculo.txt | grep galo | wc -c | tr 5 2
    t_sys_config mini = (t_sys_config) {.env = environ, .tokens = token};

    run_function(&mini);

    assert_result("2\n");
    i++;
    clean_exec(&mini.exec);
}

//###################### BUILTINS #######################//
MU_TEST(test_passing_a_echo_cmd_should_be_the_menssage)
{
    t_token *token = ECHO_T;
    set_list(1, token);
    // Comando testado: echo "taca lhe pau no carrinho marcos!"
    t_sys_config mini = (t_sys_config) {.env = environ, .tokens = token};

    run_function(&mini);

    assert_result("taca lhe pau no carrinho marcos!\n");
    i++;
    clean_exec(&mini.exec);
}

MU_TEST(test_passing_a_pwd_cmd_should_be_actual_dir)
{
    t_token *token = PWD_T;
    set_list(1, token);
    // Comando testado: pwd
    t_sys_config mini = (t_sys_config) {.env = environ, .tokens = token};

    run_function(&mini);

    assert_result("/nfs/homes/dapaulin/ls/minishelly/tests\n");
    i++;
    clean_exec(&mini.exec);
}

MU_TEST(test_passing_a_env_cmd_should_be_environ)
{
    t_token *token = ENV_T;
    set_list(1, token);
    // Comando testado: env
    t_sys_config mini = (t_sys_config) {.env = c_env, .tokens = token};

    run_function(&mini);

    assert_result("USER=dapaulin\nHOME=/nfs/homes/dapaulin\nTERM=xterm-256color\nOLDPWD=/nfs/homes/dapaulin/ls/minishelly\nPWD=/nfs/homes/dapaulin/ls/minishelly/tests\nLANG=pt\n");
    i++;
    clean_exec(&mini.exec);
}

MU_TEST(test_passing_a_cd_cmd_should_be_home_dir)
{
    t_token *token = NULL;
    ft_token_add_end(&token, ft_token_new(ft_split("cd", 32), OP_CD));
    set_list(1, token);
    // Comando testado: cd 
    t_sys_config mini = (t_sys_config) {.env = NULL, .tokens = token,
    .exec = NULL, .prompt = NULL, .new_parser = NULL, .path = NULL};
    get_envp(environ, &mini);

    run_function(&mini);

    char *str = getcwd(NULL, 0);
    mu_assert_string_eq("/nfs/homes/dapaulin", str);
    i++;
    clean_exec(&mini.exec);
    clean_strlist(&mini.env);
    ft_token_free(&token);
    free(str);
    if (chdir("./ls/minishelly/tests") == -1)
        ft_printf("ERROR: change director\n");
}

MU_TEST(test_passing_a_export_cmd_should_be_environ_more_one)
{
    // Comando testado: export PL=vida
    t_sys_config mini = (t_sys_config) {.env = NULL, .tokens = EXPORT_T,
    .exec = NULL, .prompt = NULL, .new_parser = NULL, .path = NULL};
    get_envp(c_env, &mini);

    exec(&mini);
    clean_exec(&mini.exec);
    mini.tokens = ENV_T;
    run_function(&mini);

    assert_result("USER=dapaulin\nHOME=/nfs/homes/dapaulin\nTERM=xterm-256color\nOLDPWD=/nfs/homes/dapaulin/ls/minishelly\nPWD=/nfs/homes/dapaulin/ls/minishelly/tests\nLANG=pt\nPL=vida\n");
    i++;
    clean_exec(&mini.exec);
    clean_strlist(&mini.env);
}

MU_TEST(test_passing_a_unset_cmd_should_be_environ_minus_one)
{
    // Comando testado: unset PWD
    t_sys_config mini = (t_sys_config) {.env = NULL, .tokens = UNSET_T,
    .exec = NULL, .prompt = NULL, .new_parser = NULL, .path = NULL};
    get_envp(c_env, &mini);

    exec(&mini);
    clean_exec(&mini.exec);
    mini.tokens = ENV_T;
    run_function(&mini);

    assert_result("USER=dapaulin\nHOME=/nfs/homes/dapaulin\nTERM=xterm-256color\nOLDPWD=/nfs/homes/dapaulin/ls/minishelly\nLANG=pt\n");
    i++;
    clean_exec(&mini.exec);
    clean_strlist(&mini.env);
}

//###################### OUTPUT #######################//
MU_TEST(test_passing_a_echo_cmd_for_a_file_should_insert_the_text_in_file) {
    t_token *token = OUT_M;
    set_list(2, token, ECHO_M);
    // Comando testado: echo taca lhe pau no carrinho marcos! > ./testes_files/google.tx
    t_sys_config mini = (t_sys_config) {.env = NULL, .tokens = token,
    .exec = NULL, .prompt = NULL, .new_parser = NULL, .path = NULL};

    run_function(&mini);

    assert_result("taca lhe pau no carrinho marcos!\n");
    i++;
    clean_exec(&mini.exec);
    ft_token_free(&token);
}

MU_TEST(test) {
    t_token *token = CMD_M(">\aoi", '\a', OP_OUTPUT);
    // Comando testado: echo t3 t2 t4 > oi > oie > ola
    set_list(4, token,
            CMD_M(">\aoie", '\a', OP_OUTPUT),
            CMD_M(">\aola.txt", '\a', OP_OUTPUT),
            CMD_M("echo\at3\at2\at4", '\a', OP_ECHO));
    t_sys_config mini = (t_sys_config) {.env = NULL, .tokens = token,
    .exec = NULL, .prompt = NULL, .new_parser = NULL, .path = NULL};

    run_function(&mini);

    assert_result_fd("t3 t2 t4\n", "oi", "oie");
    i++;
    clean_exec(&mini.exec);
    ft_token_free(&token);
}

MU_TEST_SUITE(test_suite_pipes) {
    MU_RUN_TEST(test_passing_1_cat_cmd_should_be_the_text_inside);
    MU_RUN_TEST(test_passing_cat_pipe_grep_should_be_return_the_lines_with_the_word_in_grep);
    MU_RUN_TEST(test_passing_a_cat_pipe_grep_pipe_wc_should_be_number_of_words);
    MU_RUN_TEST(test_passing_cat_pipe_grep_pipe_wc_pipe_tr_should_alter_the_number);
}

MU_TEST_SUITE(test_suite_builtins) {
    MU_RUN_TEST(test_passing_a_echo_cmd_should_be_the_menssage);
    MU_RUN_TEST(test_passing_a_pwd_cmd_should_be_actual_dir);
    MU_RUN_TEST(test_passing_a_env_cmd_should_be_environ);
    MU_RUN_TEST(test_passing_a_cd_cmd_should_be_home_dir);
    MU_RUN_TEST(test_passing_a_export_cmd_should_be_environ_more_one);
    MU_RUN_TEST(test_passing_a_unset_cmd_should_be_environ_minus_one);
    //MU_RUN_TEST(test_passing_a_exit_cmd_should_be_msg);
}

MU_TEST_SUITE(test_suite_output) {
    MU_RUN_TEST(test_passing_a_echo_cmd_for_a_file_should_insert_the_text_in_file);
    MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite_pipes);
    MU_RUN_SUITE(test_suite_builtins);
    MU_RUN_SUITE(test_suite_output);
	MU_REPORT();
	return MU_EXIT_CODE;
}

// MU_TEST(test_passing_a_exit_cmd_should_be_msg)
// {
//     t_token *token = NULL;
//     ft_token_add_end(&token, ft_token_new(ft_split("exit", 32), OP_EXIT));
//     set_list(1, token);

//     t_sys_config mini = (t_sys_config) {.env = NULL, .tokens = token,
//     .exec = NULL, .prompt = NULL, .new_parser = NULL, .path = NULL};

//     run_function(&mini);

//     assert_result("Você saiu do Minishelly!\n");
//     mu_assert_int_eq(__wrap_exit, 0);
//     i++;
// }