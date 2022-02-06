/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:56:43 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/05 23:44:30 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_still_alive(t_philo *philo)
{
	long int	current_time;
	long int	time;

	current_time = get_time();
	pthread_mutex_lock(&philo->info->meal_time_lock);
	time = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->info->meal_time_lock);
	if (time > (philo->info->time_to_die))
		return (0);
	return (1);
}

void	unlock_all_forks(t_philo *philo)
{
	int i = 0;
	while (i < philo->info->nb_of_philo)
	{
		pthread_mutex_unlock(&philo->info->fork_locks[i]);
		i++;
	}
}