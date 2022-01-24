/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:13:12 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/24 21:20:16 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdigit(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int ft_atoi(const char *str)
{
	unsigned int result;
	int sign;

	sign = 1;
	result = 0;

	while (*str == '\f' || *str == '\t' || *str == '\v' || *str == '\r' || *str == '\n' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = 10 * result + (*str - 48);
		str++;
		if (result > INT_MAX)
			break;
	}
	if ((result == (unsigned int)INT_MAX + 1 && sign == -1) || result <= INT_MAX)
		return (sign * result);
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int check_error(int ac, char **av)
{
	int i;
	int k;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Usage : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [max_meals]\n");
		return (0);
	}
	k = ac - 1;
	while (k > 0)
	{
		i = 0;
		while (av[k][i] != '\0')
		{
			if (ft_isdigit(av[k][i]) == 0)
			{
				printf("args must be int\n");
				return (0);
			}
			i++;
		}
		k--;
	}
	return (1);
}

int must_stop(t_philo *philo)
{
    int must_stop;

    must_stop = 0;
    pthread_mutex_lock(&philo->info->stop_lock);
    must_stop = philo->info->must_stop;
    pthread_mutex_unlock(&philo->info->stop_lock);
    return (must_stop);
}