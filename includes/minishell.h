#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

/* Variable globale */
extern int	g_return_value;

/* Liste variables d'environnements */
typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct  s_env_node	*prev;
	struct	s_env_node 	*next;
}				t_env_node;

typedef struct s_env
{
	struct s_env_node *first;
	struct s_env_node *last;
}				t_env;

typedef struct s_token_node
{
	char	*token;
	int		is_quoted; // 0 = no_quote, 1 = double_quotes, 2 = simple_quotes
	int		is_piped; // 0 si il n y avait pas de pipe avant, 1 si pipe avant
	int		type; // Permet de determiner le type du token: cmd, opt, args, others
	struct s_token_node *prev;
	struct s_token_node *next;
}				t_token_node;

typedef struct s_token
{
	struct s_token_node *first;
	struct s_token_node *last;
}				t_token;


/* functions for handle environments */
t_env	*copy_envp(char **envp);
void    env_init_list(t_env *env);
int		list_pushBack(t_env *env, char *value);
int		list_pushFront(t_env *env, char *value);
int		list_popBack(t_env *env);
int		list_popFront(t_env *env);
void    clear_env(t_env *env);

/* Functions for token list */
void	token_init_list(t_token *token);
int	token_list_pushBack(t_token *token, char *value);
int	token_list_pushFront(t_token *token, char *value);
int	token_list_popBack(t_token *token);
int	token_list_popFront(t_token *token);
void	token_list_erase_node(t_token *token, t_token_node *node);
void	clear_token(t_token *token);

/* Parsing functions */
int ft_parsing_management(char *line, t_env *env);

/* Signals functions */
int		handle_signal(void);
void    sigquit_handler(int sig);
void    sigint_handler(int sig);

/* Error functions */
int		print_error_int(char *s, int return_value);
char	*print_error_null(char *s);

/* debug functions */
void    print_env_debug(t_env *env);
void	print_token_debug(t_token *token);

/* builtins */
int		ft_env(t_env *env);
int 	ft_pwd(void);
/* int		ft_echo(); */

/* execution */
int		ft_exec(t_token *token, t_env *env);

#endif