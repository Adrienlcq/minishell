#include "libft.h"

int count_words(char *s, char sep)
{
    int i;
    int count;

    i = -1;
    if (s[0] && s[0] != sep)
        count = 1;
    else
        count = 0;
    while (s[++i])
    {
        if (s[i] == sep)
        {
            while (s[++i] == sep && s[i])
                ;
            if (s[i] != '\0')
                count++;
        }
    }
    return (count);
}

char    *ft_copy_word(char *s, char sep, int *i)
{
    int     len;
    int     start;
    char    *new;

    len = 0;
    start = 0;
    if (s[*i] && s[*i] == sep)
        while (s[*i] && s[*i] == sep)
            *i += 1;
    start = *i;
    while (s[*i] && s[*i] != sep)
    {
        len++;
        *i += 1;
    }
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL)
        return (NULL);
    len = 0;
    while (s[start] && s[start] != sep)
        new[len++] = s[start++];
    new[len] = '\0';
    return (new);
}

char **ft_split(char *s, char sep)
{
    char **tab;
    int words;
    int i;
    int j;

    words = count_words(s, sep);
    tab = malloc(sizeof(char *) * (words + 1));
    if (tab == NULL)
        return (NULL);
    i = 0;
    j = 0;
    while (i < words)
        tab[i++] = ft_copy_word(s, sep, &j);
    tab[words] = NULL;
    return (tab);
}