/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 23:58:30 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/23 15:37:31 by mrahmani         ###   ########.fr       */
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

int take_fork(t_philo *philo)
{
	int id;
	int left_id;
	int forks_available = 0;
	printf("%ld : philo %d has checked forks\n", get_time(), philo->id);
	print_forks_state(philo);
	id = philo->id - 1;
	left_id = philo->id;
	// if (philo->info->nb_of_philo == 1)
	// {
	// 	set_is_dead(philo, 1);
	// 	return (-1);
	// }
	pthread_mutex_lock(&philo->info->fork_lock);
	if (philo->id == philo->info->nb_of_philo)
		left_id = 0;
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
	if (philo->has_forks)
		print_forks_state(philo);
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
