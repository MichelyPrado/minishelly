#include "../includes/tests_includes.h"

char			*environ[] = {"USER=dapaulin",
							 "TERM=xterm-256color",
							 "OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly",
							 "PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
							 "LANG=pt",
							 NULL
							};

#define PATH "./files/"

typedef struct s_b_export_test
{
	
	int				fd;
	int				bkp;
	char			*line;
	char			*file_name;
	char			**show;
	char			**act;
	t_sys_config	*mini;
}				t_tests;

static void			unset_config(t_tests *vars);
static int			show_export(t_tests *vars, t_process_func f);
static t_tests		*config(char **cmds);
static void			assert_env(t_tests *vars, char **expected);

MU_TEST(test_passing_only_export_should_be_export_env) {
	// CONFIG
	t_tests			*vars = config(ft_split("export ", 32));
	vars->file_name = ft_strjoin(PATH, "export_1.txt");
	vars->show 		= vars->mini->tokens->token;
	char			*expected_env[] 	= { "USER=dapaulin",
											"TERM=xterm-256color",
											"OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly", 
											"PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
											"LANG=pt",
											NULL};
	char			*expected_exp_env[] = {	"declare -x USER=\"dapaulin\"",
											"declare -x TERM=\"xterm-256color\"",
											"declare -x OLDPWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly\"", 
											"declare -x PWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly/tests\"",
											"declare -x LANG=\"pt\"",
											NULL};
	// ACT
	show_export(vars, b_export);
	assert_env(vars, expected_exp_env);
	show_export(vars, ft_env);
	assert_env(vars, expected_env);
	unset_config(vars);
}

MU_TEST(passing_export_TEST_without_value_should_only_add_in_export_env) {
	// CONFIG
	t_tests			*vars = config(ft_split("export\aTEST", 7));
	vars->file_name = ft_strjoin(PATH, "export_2.txt");
	vars->act 		= vars->mini->tokens->token;
	vars->show		= ft_split("export\a", 7);
	char			*expected_env[] 	= { "USER=dapaulin",
											"TERM=xterm-256color",
											"OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly", 
											"PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
											"LANG=pt",
											NULL};
	char			*expected_exp_env[] = {	"declare -x USER=\"dapaulin\"",
											"declare -x TERM=\"xterm-256color\"",
											"declare -x OLDPWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly\"", 
											"declare -x PWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly/tests\"",
											"declare -x LANG=\"pt\"",
											"declare -x TEST",
											NULL};
	// ACT
	b_export(vars->mini);
	show_export(vars, ft_env);
	assert_env(vars, expected_env);
	vars->mini->tokens->token = vars->show;
	show_export(vars, b_export);
	assert_env(vars, expected_exp_env);
	unset_config(vars);
}

MU_TEST(passing_export_TEST_with_a_empty_value_should_add_in_export_env_and_env) {
	// CONFIG
	t_tests			*vars = config(ft_split("export\aTEST=", 7));
	vars->file_name = ft_strjoin(PATH, "export_3.txt");
	vars->act 		= vars->mini->tokens->token;
	vars->show		= ft_split("export\a", 7);
	char			*expected_env[] 	= { "USER=dapaulin",
											"TERM=xterm-256color",
											"OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly", 
											"PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
											"LANG=pt",
											"TEST=",
											NULL};
	char			*expected_exp_env[] = {	"declare -x USER=\"dapaulin\"",
											"declare -x TERM=\"xterm-256color\"",
											"declare -x OLDPWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly\"", 
											"declare -x PWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly/tests\"",
											"declare -x LANG=\"pt\"",
											"declare -x TEST=\"\"",
											NULL};
	// ACT
	b_export(vars->mini);
	show_export(vars, ft_env);
	assert_env(vars, expected_env);
	vars->mini->tokens->token = vars->show;
	show_export(vars, b_export);
	assert_env(vars, expected_exp_env);
	unset_config(vars);
}

MU_TEST(passing_export_TEST_with_90_in_value_should_add_in_export_env_and_env) {
	// CONFIG
	t_tests			*vars = config(ft_split("export\aTEST=98", 7));
	vars->file_name = ft_strjoin(PATH, "export_4.txt");
	vars->act 		= vars->mini->tokens->token;
	vars->show		= ft_split("export\a", 7);
	char			*expected_env[] 	= { "USER=dapaulin",
											"TERM=xterm-256color",
											"OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly", 
											"PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
											"LANG=pt",
											"TEST=98",
											NULL};
	char			*expected_exp_env[] = {	"declare -x USER=\"dapaulin\"",
											"declare -x TERM=\"xterm-256color\"",
											"declare -x OLDPWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly\"", 
											"declare -x PWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly/tests\"",
											"declare -x LANG=\"pt\"",
											"declare -x TEST=\"98\"",
											NULL};
	// ACT
	b_export(vars->mini);
	show_export(vars, ft_env);
	assert_env(vars, expected_env);
	vars->mini->tokens->token = vars->show;
	show_export(vars, b_export);
	assert_env(vars, expected_exp_env);
	unset_config(vars);
}

MU_TEST(passing_export_TEST_without_value_with_an_existing_variable_TEST_with_90_in_value_must_not_change) {
	// CONFIG
	t_tests			*vars = config(ft_split("export\aTEST", 7));
	vars->file_name = ft_strjoin(PATH, "export_5.txt");
	vars->act 		= vars->mini->tokens->token;
	ft_export(&vars->mini->env, "TEST=", "98");
	vars->show		= ft_split("export\a", 7);
	char			*expected_env[] 	= { "USER=dapaulin",
											"TERM=xterm-256color",
											"OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly", 
											"PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
											"LANG=pt",
											"TEST=98",
											NULL};
	char			*expected_exp_env[] = {	"declare -x USER=\"dapaulin\"",
											"declare -x TERM=\"xterm-256color\"",
											"declare -x OLDPWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly\"", 
											"declare -x PWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly/tests\"",
											"declare -x LANG=\"pt\"",
											"declare -x TEST=\"98\"",
											NULL};
	// ACT
	b_export(vars->mini);
	show_export(vars, ft_env);
	assert_env(vars, expected_env);
	vars->mini->tokens->token = vars->show;
	show_export(vars, b_export);
	assert_env(vars, expected_exp_env);
	unset_config(vars);
}

MU_TEST(test) {
	// CONFIG
	t_tests			*vars = config(ft_split("export\aTEST\aMARIO=curry\aLANG=BR\aVIRUS=", 7));
	vars->file_name = ft_strjoin(PATH, "export_6.txt");
	vars->act 		= vars->mini->tokens->token;
	vars->show		= ft_split("export\a", 7);
	char			*expected_env[] 	= { "USER=dapaulin",
											"TERM=xterm-256color",
											"OLDPWD=/nfs/homes/dapaulin/Documents/project-42/minishelly", 
											"PWD=/nfs/homes/dapaulin/Documents/project-42/minishelly/tests",
											"LANG=BR",
											"MARIO=curry",
											"VIRUS=",
											NULL};
	char			*expected_exp_env[] = {	"declare -x USER=\"dapaulin\"",
											"declare -x TERM=\"xterm-256color\"",
											"declare -x OLDPWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly\"", 
											"declare -x PWD=\"/nfs/homes/dapaulin/Documents/project-42/minishelly/tests\"",
											"declare -x LANG=\"BR\"",
											"declare -x TEST",
											"declare -x MARIO=\"curry\"",
											"declare -x VIRUS=\"\"",
											NULL};
	// ACT
	b_export(vars->mini);
	show_export(vars, ft_env);
	assert_env(vars, expected_env);
	vars->mini->tokens->token = vars->show;
	show_export(vars, b_export);
	assert_env(vars, expected_exp_env);
	unset_config(vars);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test_passing_only_export_should_be_export_env);
	MU_RUN_TEST(passing_export_TEST_without_value_should_only_add_in_export_env);
	MU_RUN_TEST(passing_export_TEST_with_a_empty_value_should_add_in_export_env_and_env);
	MU_RUN_TEST(passing_export_TEST_with_90_in_value_should_add_in_export_env_and_env);
	MU_RUN_TEST(passing_export_TEST_without_value_with_an_existing_variable_TEST_with_90_in_value_must_not_change);
	MU_RUN_TEST(test);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

static t_tests *config(char **cmds)
{
	t_tests	*vars;

	vars = (t_tests *) malloc(sizeof(t_tests));
	vars->file_name = NULL;
	vars->fd = 0;
	vars->bkp = dup(1);
	vars->mini = start_sys(environ);
	vars->mini->tokens = (t_token *) malloc(sizeof(t_token));
	vars->mini->tokens->token = cmds;
	vars->show = NULL;
	vars->act = NULL;
	vars->mini->tokens->next = NULL;
	vars->mini->tokens->type = 0;
	return (vars);
}

static void	unset_config(t_tests *vars)
{
	free(vars->file_name);
	clean_strlist(&(vars->show));
	clean_strlist(&(vars->act));
	free(vars->mini->tokens);
	clean_strlist(&(vars->mini->env));
	clean_strlist(&(vars->mini->prompt));
	free(vars->mini);
	free(vars);
}

static int	show_export(t_tests *vars, t_process_func f)
{
	int	bkp;
	int	err;

	vars->fd = open(vars->file_name, O_RDWR | O_CREAT, S_IRWXU);
	dup2(vars->fd, 1);
	err = f(vars->mini);
	close(1);
	dup2(vars->bkp, 1);
	return (err);
}

static void	assert_env(t_tests *vars, char **expected)
{
	int		i;
	char	*tmp;

	i = 0;
	vars->fd = open(vars->file_name, O_RDONLY, S_IRWXU);
	while (expected[i])
	{
		tmp = get_next_line(vars->fd);
		if (!tmp)
			vars->line = NULL;
		else
			vars->line = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		mu_assert_string_eq(expected[i], vars->line);
		if (tmp)
			free(tmp);
		if (vars->line)
			free(vars->line);
		i++;
	}
	mu_assert_string_eq(expected[i], get_next_line(vars->fd));
	close(vars->fd);
	remove(vars->file_name);
}
