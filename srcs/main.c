#include "../includes/minishell.h"

int g_return_value;

char    *ft_strcpy(char *dst, char *src)
{
    int i;

    i = -1;
    while (src[++i])
        dst[i] = src[i];
    dst[i] = '\0';
    return (dst);
}

int	while_read(t_env *env)
{
	(void)env;
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = ft_strjoin(getenv("USER"), "@minishell:");
		if (prompt == NULL)
			return (print_error_int("Error: Memory allocation failed", 0));
		prompt = ft_strjoin(prompt, getenv("PWD"));
		if (prompt == NULL)
			return (print_error_int("Error: Memory allocation failed", 0));
		prompt = ft_strjoin(prompt, "$> ");
		if (prompt == NULL)
			return (print_error_int("Error: Memory allocation failed", 0));
		line = readline(prompt);
		if (line == NULL)
			break ;
		if (ft_strlen(line) > 0)
			add_history(line);
		//ft_parse_line(line, env);
		line = ft_strtrim(line, " \f\t\n\r\v");
		if (line == NULL)
			return (print_error_int("Error: Memory allocation failed", 0));
		ft_parsing_management(line, env);
		free(line);
		free(prompt);
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
    t_env   env;
    g_return_value = 0;
    int	i;

    (void)av;
	if (ac != 1)
		return (print_error_int("Error: Usage: ./minishell\n", 1));
	if (handle_signal() == 0)
		return (print_error_int("Error: Signal handling failed\n", 1));
    env_init_list(&env);
	i = -1;
	while (envp[++i])
    	if (list_pushBack(&env, envp[i]) == 0)
			return (print_error_int("Error: Memory allocation failed\n", 1));
	while_read(&env);
	clear_env(&env);
	return (0);
}