#include "../../includes/minishell.h"

int	print_error_int(char *s, int return_value)
{
	ft_putstr_fd(s, 2);
	return (return_value);
}

char	*print_error_null(char *s)
{
	ft_putstr_fd(s, 2);
	return (NULL);
}