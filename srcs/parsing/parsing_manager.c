#include "../../includes/minishell.h"

// 2048 is max characters in command line

//Second part checking quotes
static void  check_quotes(char c, int *b_quote, int *quotes)
{
    if (c == '"' || c == '\'')
    {
        if (*b_quote == 0)
        {
            *quotes += 1;
            if (c == '"')
                *b_quote = 1;
            else
                *b_quote = 2;
        }
        else
        {
            if ((*b_quote == 1 && c == '"') || (*b_quote == 2 && c == '\''))
            {
                *quotes += 1;
                *b_quote = 0;
            }
        }
    }
}

//Checking quotes functions
static int check_quotes_is_valid(char *line)
{
    int i;
    int quotes;
    int b_quote;

    i = -1;
    quotes = 0;
    b_quote = 0;
    while (line[++i])
        check_quotes(line[i], &b_quote, &quotes);
    if (quotes % 2 != 0)
        return (0);
    return (1);
}

// Checking pipes are valids functions
static int check_pipes_is_valid(char *line)
{
    int i;
    int b_pipe;

    if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
        return (0);
    i = -1;
    b_pipe = 0;
    while (line[++i])
    {
        if (line[i] == '|' && b_pipe == 0)
            b_pipe = 1;
        else if (line[i] != '|' && line[i] != ' ' && b_pipe == 1)
            b_pipe = 0;
        else if (line[i] == '|' && b_pipe == 1)
            return (0);
    }
    return (1);
}

//Erase quotes function
/* static void erase_double_quotes(char *line)
{
    int i;
    int b_quote;
    char    new_line[2048];
    int     j;

    i = 0;
    b_quote = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '"' && b_quote == 0)
        {
            b_quote = 1;
            i++;
        }
        else if ((line[i] == '"' && b_quote == 1) || (line[i] == '\'' && b_quote == 2))
        {
            b_quote = 0;
            i++;
        }
        if (line[i] != '\''|| line[i] != '"')
            new_line[j++] = line[i++];
        else
            new_line[j++] = line[i];
    }
    new_line[j] = '\0';
    printf("Valeur de new_line: %s\n", new_line);

} */

void	split_quotes_in_token(t_token *token, char *line, int *i, char quote)
{
	int	j;
	char	val[1000];

	j = 0;
	val[j++] = line[*i]; 
	while (line[++(*i)] != quote)
		val[j++] = line[*i];
	val[j++] = quote;
	val[j] = '\0';
	token_list_pushBack(token, val);
}

void    split_line_in_tokens(t_token *token, char *line)
{
    int	i;
	int	j;
	char	val[1000];

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '"')
			split_quotes_in_token(token, line, &i, '"');
		else if (line[i] == '\'')
			split_quotes_in_token(token, line, &i, '\'');
		else if (line[i] && line[i] != ' ')
		{
			while (line[i] && line[i] != ' ')
				val[j++] = line[i++];
			val[j] = '\0';
			token_list_pushBack(token, val);
			j = 0;
		}
	}
}

char    *erase_excess_spaces(char *line)
{
    char    new_line[1000];
    int     b_quote;
    int     i;
    int     j;

    b_quote = 0;
    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '"' && b_quote == 0)
            b_quote = 1;
        else if (line[i] == '\'' && b_quote == 0)
            b_quote = 2;
        else if (line[i] == ' ' && line[i + 1] && line[i + 1] == ' ' && b_quote == 0)
        {
            while (line[i] == ' ' && line[i + 1] && line[i + 1] == ' ')
                i++;
        }
        else if ((line[i] == '"' && b_quote == 1) || (line[i] == '\'' && b_quote == 2))
            b_quote = 0;
        new_line[j++] = line[i++];
    }
    new_line[j] = '\0';
    //free(line);
    line = ft_strdup(new_line);
    if (line == NULL)
        return (NULL);
    return (line);
}

void	tokens_analyse(t_token *token)
{
	t_token_node *node;

	node = token->first;
	while (node)
	{
		if (node->token[0] == '|' && ft_strlen(node->token) == 1)
		{
			token_list_erase_node(token, node);
			node->prev->is_piped = 1;
		}
		node = node->next;
	}
	return ;
}

void    assign_b_quote_value(char c, int *b_quote)
{
    if (c == '"' && *b_quote == 0)
        *b_quote = 1;
    else if (c == '\'' && *b_quote == 0)
        *b_quote = 2;
    else if (c == '"' && *b_quote == 1)
        *b_quote = 0;
    else if (c == '\'' && *b_quote == 2)
        *b_quote = 0;
}

char	*add_spaces_for_pipes_and_redirection(char *line)
{
	char	new_line[1000];
	int		i;
	int		j;
	int		b_quote;

	i = -1;
	b_quote = 0;
	j = 0;
	while (line[++i])
	{
		assign_b_quote_value(line[i], &b_quote);
		if (line[i] == '|' && b_quote == 0 && line[i - 1] && line[i - 1] != ' ')
			new_line[j++] = ' ';
        else if (line[i] == '|' && b_quote == 0 && line[i + 1] && line[i + 1] != ' ')
        {
            new_line[j++] = line[i];
            new_line[j++] = ' ';
            continue ;
        }
		new_line[j++] = line[i];
	}
	new_line[j] = '\0';
	line = ft_strdup(new_line);
	if (line == NULL)
		return (NULL);
	return (line);
}

void    check_if_token_is_quoted(t_token *token)
{
    t_token_node *node;

    node = token->first;
    while (node)
    {
        if (node->token[0] == '"')
            node->is_quoted = 1;
        else if (node->token[0] == '\'')
            node->is_quoted = 2;
        node = node->next;
    }
}

// ATTENTION FONCTION A DEBUG ET RECHECKER
void    erase_double_quotes_in_tokens(t_token *token)
{
    t_token_node *node;
    //int             i;

    node = token->first;
    while (node)
    {
        if (node->token[0] == '"'/*  || node->token[0] == '\'' */ && ft_strlen(node->token) > 2) // Pour l instant on ne traite que les doubles quotes
            node->token = ft_substr(node->token, 1, ft_strlen(node->token) - 2);
        /* else
        {
            i = -1;
            while (node->token[++i])
            {
                if ()
            }
        } */
        node = node->next;
    }
}

// Fonction qui permet de recuperer la valeur d une variable d environnement directement a partir de notre list env
char    *get_env_value(t_env *env, char *var)
{
    t_env_node *node;

    node = env->first;
    while (node)
    {
        if (ft_strncmp_check_len(node->value, var, ft_strlen(var)) == 0)
            return (node->value);
        node = node->next;
    }
    return (NULL);
}

char    *extract_env_var(char *str, int i)
{
    char *var;
    int j;
    int len;

    len = 0;
    while (str[i + len] && str[i + len] != ' ' && str[i + len] != '$')
    {
        len++;
    }
    var = malloc(sizeof(char) * (len + 1));
    if (var == NULL)
        return (NULL);
    j = 0;
    while (j < len)
    {
        var[j] = str[i + j];
        j++;
    }
    var[j] = '\0';
    return (var);
}

void    replace_environment_variables(t_token *token, t_env *env)
{
    (void)env;
    t_token_node *node;
    char    *var;
    //char    *value;
    int     i;

    node = token->first;
    while (node)
    {
        if (node->token[0] == '\'')
        {
            node = node->next;
            continue ;
        }
        i = -1;
        while (node->token[++i])
        {
            if (node->token[i] == '$')
            {
                var = extract_env_var(node->token, i);
                if (var == NULL)
                    continue ;
                printf("Valeur de var: %s\n", var);
            }
        }
        node = node->next;
    }
}

int ft_parsing_management(char *line, t_env *env)
{
    t_token token;

    (void)env;
    if (check_pipes_is_valid(line) == 0)
        return (print_error_int("minishell: syntax error near unexpected token `|\'\n", 0));
    if (check_quotes_is_valid(line) == 0)
        return (print_error_int("Error: Unmatched quotes\n", 0));
    line = erase_excess_spaces(line);
	line = add_spaces_for_pipes_and_redirection(line); // Faudra rajouter la gestion des redirections
    token_init_list(&token);
    split_line_in_tokens(&token, line);
    print_token_debug(&token);
    printf("C est juste apres le split dans les tokens\n");
	free(line);
	line = NULL;
    //print_token_debug(&token);

	tokens_analyse(&token);
    check_if_token_is_quoted(&token);
    erase_double_quotes_in_tokens(&token);
    //replace_environment_variables(&token, env);
	print_token_debug(&token);
    //erase_double_quotes(line);
    //split_line_in_tokens(line);
    ft_exec(&token, env); // A mettre dans le main normalement
    return (1);
}
