/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 23:58:30 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/31 22:35:44 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int *init_forks(t_info *info)
{
	int i;
	int *forks;

	i = 0;
	forks = ft_malloc((info->nb_of_philo + 1) * sizeof(int));
	if (forks == NULL)
		return (NULL);
	while (i < info->nb_of_philo)
	{
		forks[i] = 1;
		i++;
	}
	forks[i] = -1;
	return (forks);
}

void take_fork(t_philo *philo)
{
	int id;
	int left_id;

	if (philo->info->nb_of_philo <= 1)
	{
		set_is_dead(philo, 1);
		log_is_dead(philo);
		return;
	}
	id = philo->id - 1;
	left_id = philo->id;
	if (philo->id == philo->info->nb_of_philo)
		left_id = 0;
	pthread_mutex_lock(&philo->info->take_fork_locks[philo->id -1]);
	pthread_mutex_lock(&philo->info->fork_locks[id]);
	pthread_mutex_lock(&philo->info->fork_locks[left_id]);
	pthread_mutex_unlock(&philo->info->take_fork_locks[philo->id -1]);
	log_taking_fork(philo, id + 1);
	log_taking_fork(philo, left_id + 1);
	philo->has_forks = 1;
}

void drop_fork(t_philo *philo)
{
	int id;
	int left_id;
	int forks_available = 0;

	id = philo->id - 1;
	left_id = philo->id;
	if (philo->id == philo->info->nb_of_philo)
		left_id = 0;
	pthread_mutex_lock(&philo->info->take_fork_locks[philo->id -1]);
	pthread_mutex_unlock(&philo->info->fork_locks[id]);
	pthread_mutex_unlock(&philo->info->fork_locks[left_id]);
	pthread_mutex_unlock(&philo->info->take_fork_locks[philo->id -1]);
	log_drop_fork(philo);
}
