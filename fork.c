/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 23:58:30 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/16 23:58:43 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void print_forks_state(t_philo *philo)
{
	int i;
	i = 0;
	pthread_mutex_lock(&philo->info->fork_lock);

	while (philo->info->forks[i] != -1)
	{
		printf("%d ", philo->info->forks[i]);
		i++;
	}

	printf("\n");
	pthread_mutex_unlock(&philo->info->fork_lock);
}

int take_fork(t_philo *philo)
{
	int id;
	int left_id;
	int forks_available = 0;

	id = philo->id - 1;
	left_id = philo->id;

	if (philo->id == philo->info->nb_of_philo)
		left_id = 0;
	pthread_mutex_lock(&philo->info->fork_lock);

	if (philo->info->forks[id] == 1 && philo->info->forks[left_id] == 1)
	{
		forks_available = 1;
		philo->info->forks[id] = 0;
		log_taking_fork(philo, id + 1);
		philo->info->forks[left_id] = 0;
		log_taking_fork(philo, left_id + 1);
		philo->has_forks = 1;
	}

	pthread_mutex_unlock(&philo->info->fork_lock);
	return (forks_available);
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
	pthread_mutex_lock(&philo->info->fork_lock);

	philo->info->forks[id] = 1;
	philo->info->forks[left_id] = 1;
	philo->has_forks = 0;
	pthread_mutex_unlock(&philo->info->fork_lock);
}
