/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:13:12 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/07 11:41:01 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

void	_sleep(int time_ms)
{
	usleep(time_ms * 1000);
}

int	must_stop(t_philo *philo)
{
	int	must_stop;

	must_stop = 0;
	pthread_mutex_lock(&philo->info->stop_lock);
	must_stop = philo->info->must_stop;
	pthread_mutex_unlock(&philo->info->stop_lock);
	return (must_stop);
}

int	can_run(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead_lock);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(&philo->info->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->info->dead_lock);
	if (must_stop(philo))
		return (0);
	pthread_mutex_lock(&philo->info->meals_lock);
	if ((philo->meals >= philo->info->max_times_to_eat
			&& philo->info->max_times_to_eat != -1))
	{
		pthread_mutex_unlock(&philo->info->meals_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->info->meals_lock);
	return (1);
}

void	mark_as_stop(t_info *info)
{
	pthread_mutex_lock(&info->stop_lock);
	info->must_stop = 1;
	pthread_mutex_unlock(&info->stop_lock);
}
