/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:55:30 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/07 10:12:11 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		return (NULL);
	return (result);
}

void	ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_philos(t_philo **philo)
{
	t_philo	**temp;
	int		i;

	temp = philo;
	i = 0;
	while (temp[i] != NULL)
	{
		ft_free(temp[i]);
		i++;
	}
	ft_free(temp);
}

int	exit_with_error(char *message)
{
	printf("%s\n", message);
	return (1);
}

void	free_all(t_info *args, t_philo **philos)
{
	ft_free(args->fork_locks);
	free_philos(philos);
	ft_free(args);
}
