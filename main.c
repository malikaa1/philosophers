/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:04:59 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/23 00:05:49 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating(t_philo *philo)
{
	if (must_stop(philo))
		return;
	if (take_fork(philo) == 1)
	{
		philo->last_meal_time = get_time();
		pthread_mutex_lock(&philo->info->print_lock);
		log_eating(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
		usleep(philo->info->time_to_eat * 1000);
		drop_fork(philo);
		printf("%ld : philo %d has dropped forks\n", get_time(), philo->id);
		philo->meals = philo->meals + 1;
		philo->fork_attempt = 0;
	}
	else
	{
		printf("%ld : philo %d failed to get forks\n", get_time(), philo->id);
		if (is_still_alive(philo) == 0)
		{
			set_is_dead(philo, 1);
			philo->info->must_stop = 1;
			pthread_mutex_lock(&philo->info->print_lock);
			log_is_dead(philo);
			pthread_mutex_unlock(&philo->info->print_lock);
			return;
		}
		philo->fork_attempt++;
	}
}

void thinking(t_philo *philo)
{
	if (must_stop(philo))
		return;
	if (is_still_alive(philo) == 1)
	{
		pthread_mutex_lock(&philo->info->print_lock);
		log_thinking(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
	}
}

void sleeping(t_philo *philo)
{
	unsigned long int sleep_time;

	if (must_stop(philo))
		return;
	sleep_time = 0;
	if (is_still_alive(philo) == 1)
	{
		pthread_mutex_lock(&philo->info->print_lock);
		log_sleeping(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
		while (is_still_alive(philo) == 1 && sleep_time < philo->info->time_to_sleep)
		{
			sleep_time += 1;
			usleep(1000);
			if (is_still_alive(philo) == 0)
				return;
		}
	}
	return;
}

void *start(void *args)
{
	t_philo *philo;
	int to_sleep;

	philo = (t_philo *)args;
	while (!is_dead(philo) && !must_stop(philo) && (philo->info->max_times_to_eat > philo->meals || philo->info->max_times_to_eat == -1))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (is_dead(philo) == 1)
		{
			pthread_mutex_lock(&philo->info->stop_lock);
			philo->info->must_stop = 1;
			pthread_mutex_unlock(&philo->info->stop_lock);
			break;
		}
	}
}

int main(int argc, char **argv)
{
	t_info *args;
	t_philo **philos;

	if (check_error(argc, argv) == 0)
		return (1);
	args = init_arg(argc, argv);
	init_mutex(args);
	philos = create_philos(args);
	create_threads(args, philos);
	ft_free(args);
	ft_free(args->forks);
	ft_free(philos);
	return (0);
}