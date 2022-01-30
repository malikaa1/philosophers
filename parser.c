/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:46:54 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/30 22:59:15 by mrahmani         ###   ########.fr       */
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
	info->forks = init_forks(info);
	info->fork_locks = ft_malloc(info->nb_of_philo * sizeof(pthread_mutex_t));
	info->take_fork_locks = ft_malloc(info->nb_of_philo * sizeof(pthread_mutex_t));
	info->must_stop = 0;
	return (info);
}
