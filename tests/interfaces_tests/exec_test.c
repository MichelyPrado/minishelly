#include "../includes/tests_includes.h"

# define PIPE_T {.token = (char *[]){"|", NULL}, .type = OP_PIPE, .next = NULL}
# define CAT_T  {.token = (char *[]){"/usr/bin/cat", "./interfaces_tests/vinculo.txt", NULL}, .type = OP_CMD, .next = NULL}
# define GREP_T {.token = (char *[]){"/usr/bin/grep", "galo", NULL}, .type = OP_CMD, .next = NULL}

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
char            name[] = "./test.txt";
int             fd;
int             bkp;
char            tmp[10000];
t_sys_config    mini;


void	run_function()
{
    bkp = dup(1);
	fd = open(name, O_RDWR | O_CREAT, S_IRWXU);
	dup2(fd, 1);
	close(fd);
	exec(&mini);
	dup2(bkp, 1);
    close(bkp);
}

static void	assert_result(char *expected)
{
	ft_bzero(tmp, 10000);
	fd = open(name, O_RDONLY, S_IRWXU);
    read(fd, tmp, 10000);
    mu_assert_string_eq(expected, tmp);
	close(fd);
	remove(name);
}

t_token token[] = {PIPE_T, CAT_T, PIPE_T, GREP_T, PIPE_T};

MU_TEST(test1)
{
    set_list(1, &token[1]);
    mini = (t_sys_config) {.env = environ, .tokens = &token[1]};

    run_function();

    assert_result("vida dificil\ngalo");
}

MU_TEST(test2)
{
    set_list(4, &token[0], &token[1], &token[2], &token[3]);
    mini = (t_sys_config) {.env = environ, .tokens = &token[0]};

    run_function();

    assert_result("galo\n");
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