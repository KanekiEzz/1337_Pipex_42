#include <stdio.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For NULL

size_t ft_strlen(char *str)
{
    size_t i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strjoin(char const *s1, char const *s2)
{
    size_t size;
    char *ptr;
    size_t i, j;

    if (!s1 || !s2)
        return NULL;
    size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
    ptr = malloc(size + 1);
    if (!ptr)
        return NULL;
    i = 0;
    if (size > 0) {
        j = 0;
        while (s1[j])
            ptr[i++] = s1[j++];
        j = 0;
        while (s2[j])
            ptr[i++] = s2[j++];
    }
    ptr[i] = '\0';
    return ptr;
}

int main(int ac, char **av, char **env)
{
    if (ac > 1)
	{
        printf("%s\n", av[1]);

        if (ac > 1)
		{
            char *l = ft_strjoin(av[1], env[11]);
            if (l != NULL)
			{
                printf("%s\n", l);
                free(l); // Free allocated memory
            }
			else
                fprintf(stderr, "Memory allocation failed\n");
        }
		else 
            fprintf(stderr, "Invalid access: av[11] or env[1] does not exist\n");
    }
    return 0;
}

