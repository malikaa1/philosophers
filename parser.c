/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:46:54 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/06 10:39:54 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info *init_arg(int argc, char **argv)
{
	t_info *info;

	info = ft_malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->nb_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_times_to_eat = ft_atoi(argv[5]);
	else
		info->max_times_to_eat = -1;
	info->fork_locks = ft_malloc(info->nb_of_philo * sizeof(pthread_mutex_t));
	if (info->fork_locks == NULL)
		return (NULL);
	info->must_stop = 0;
	return (info);
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

int is_valid(char *value)
{
	if (ft_atoi(value) == -1)
	{
		printf("invalid %s value\n", value);
		return (0);
	}
	return (1);
}

int check_error(int ac, char **av)
{
	int k;

	if (ac != 5 && ac != 6)
	{
		printf("Usage : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [max_meals]\n");
		return (0);
	}
	k = ac - 1;
	while (k > 0)
	{
		if (check_args(av[k]) == 0 || is_valid(av[k]) == 0)
			return (0);
		if (ft_atoi(av[k]) <= 0)
	{
		printf("arg should be greater than 0\n");
		return (0);
	}
		k--;
	}
	
	if (ft_atoi(av[1]) >= 1000)
	{
		printf("nb of philo is too big\n");
		return (0);
	}
	return (1);
}

int check_args(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0 && s[0] != '-' && s[0] != '+')
		{
			printf("args must be int\n");
			return (0);
		}
		i++;
	}
	return (1);
}
