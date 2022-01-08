#include "philo.h"

void *ft_malloc(size_t size)
{
    void *result;
    result = malloc(size);
    if (result == NULL)
        return (NULL);

    return (result);
}

void ft_free(void *ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }
}