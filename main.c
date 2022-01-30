/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:04:59 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/30 23:05:39 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating(t_philo *philo)
{
	if (can_run(philo) == 0)
	{
		set_is_dead(philo, 1);
		philo->info->must_stop = 1;
		pthread_mutex_lock(&philo->info->print_lock);
		log_is_dead(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
		return;
	}
	take_fork(philo);
	if (can_run(philo))
	{
		pthread_mutex_lock(&philo->info->print_lock);
		philo->last_meal_time = get_time();
		log_eating(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
		usleep(philo->info->time_to_eat * 1000);
		drop_fork(philo);
		philo->meals = philo->meals + 1;
	}
}

void thinking(t_philo *philo)
{
	if (can_run(philo) == 1)
	{
		pthread_mutex_lock(&philo->info->print_lock);
		log_thinking(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
	}
}

void sleeping(t_philo *philo)
{
	unsigned long int sleep_time;
	int last_meal;

	if (must_stop(philo))
		return;
	sleep_time = 0;
	if (can_run(philo) == 1)
	{
		pthread_mutex_lock(&philo->info->print_lock);
		log_sleeping(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
		usleep(philo->info->time_to_sleep * (1000));
	}
}

int can_run(t_philo *philo)
{
	if (is_dead(philo))
		return (0);
	if (must_stop(philo))
		return (0);
	if ((philo->meals >= philo->info->max_times_to_eat && philo->info->max_times_to_eat != -1))
		return (0);
	return (1);
}

void *start(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while (can_run(philo))
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
		if (philo->info->max_times_to_eat == philo->meals)
			break;
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
	//	ft_free(args);
	//	ft_free(args->forks);
	//	ft_free(philos);
	return (0);
}