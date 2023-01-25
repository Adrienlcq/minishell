#include "../../includes/minishell.h"

/* ctrl-c */
void    sigint_handler(int sig)
{
    (void)sig;
    rl_on_new_line();
    rl_redisplay();
    ft_putstr_fd(" \b\b", 0);
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_return_value = 1;
}

/* ctrl-\ */
void    sigquit_handler(int sig)
{
    (void)sig;
    rl_on_new_line();
    rl_redisplay();
    ft_putstr_fd(" \b\b", 0);
}

int handle_signal(void)
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        return (0);
    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
        return (0);
    return (1);
}