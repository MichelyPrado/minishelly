#include "../includes/tests_includes.h"

static void	assert_result(char *expected)
{
    char            tmp[1000];
	ft_bzero(tmp, 1000);
	int fd = open("./testes_files/google.tx", O_RDONLY, S_IRWXU);
    read(fd, tmp, 1000);
    mu_assert_string_eq(expected, tmp);
	close(fd);
}

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

MU_TEST(test) {
    t_token	*token = OUT_M;
	set_list(2, token, ECHO_M);
	t_sys_config mini = (t_sys_config) {.env = NULL, .tokens = token,
    .exec = NULL, .prompt = NULL, .new_parser = NULL, .path = NULL};

	exec(&mini);

	assert_result("taca lhe pau no carrinho marcos!\n");
	clean_exec(&mini.exec);
    ft_token_free(&token);
	remove("./testes_files/google.tx");
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}