/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 23:58:30 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/04 20:07:53 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_fork(t_philo *philo)
{
	int id;
	int left_id;

	id = philo->id - 1;
	left_id = philo->id;
	if (philo->id == philo->info->nb_of_philo)
		left_id = 0;
	if (can_run(philo) == 1 && is_still_alive(philo))
	{
		pthread_mutex_lock(&philo->info->fork_locks[id]);
		if (can_run(philo) == 1 && is_still_alive(philo))
			log_taking_fork(philo);
		pthread_mutex_lock(&philo->info->fork_locks[left_id]);
		if (can_run(philo) == 1 && is_still_alive(philo))
			log_taking_fork(philo);
		philo->has_forks = 1;
	}
}

void drop_fork(t_philo *philo)
{
	int id;
	int left_id;

	id = philo->id - 1;
	left_id = philo->id;
	if (philo->id == philo->info->nb_of_philo)
		left_id = 0;
	pthread_mutex_unlock(&philo->info->fork_locks[id]);
	pthread_mutex_unlock(&philo->info->fork_locks[left_id]);
}
