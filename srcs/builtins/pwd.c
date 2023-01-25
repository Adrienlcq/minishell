#include "../../includes/minishell.h"

int ft_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
    {
        perror("getcwd error\n");
        return (1);
    }
    return (0);
}
