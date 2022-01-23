/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 23:58:30 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/23 22:44:24 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// void print_forks_state(t_philo *philo)
// {
// 	int i;
// 	i = 0;
// 	pthread_mutex_lock(&philo->info->fork_lock);
// 	while (philo->info->forks[i] != -1)
// 	{
// 		printf("%d ", philo->info->forks[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	pthread_mutex_unlock(&philo->info->fork_lock);
// }
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

	id = philo->id - 1;
	left_id = philo->id;
	if (philo->id == philo->info->nb_of_philo)
		left_id = 0;
	pthread_mutex_lock(&philo->info->fork_locks[id]);
	pthread_mutex_lock(&philo->info->fork_locks[left_id]);
	pthread_mutex_lock(&philo->info->print_lock);
	log_taking_fork(philo, id + 1);
	log_taking_fork(philo, left_id + 1);
	pthread_mutex_unlock(&philo->info->print_lock);
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
	pthread_mutex_unlock(&philo->info->fork_locks[id]);
	pthread_mutex_unlock(&philo->info->fork_locks[left_id]);
	// philo->info->forks[id] = 1;
	// philo->info->forks[left_id] = 1;
	// philo->has_forks = 0;
	printf("%ld : Philo %d has dropped forks #%d and #%d\n", get_d_time(philo), philo->id, id + 1, left_id + 1);
	// pthread_mutex_unlock(&philo->info->fork_lock);
}
