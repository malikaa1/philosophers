/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:04:59 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/07 15:25:28 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (can_run(philo) && is_still_alive(philo))
	{
		pthread_mutex_lock(&philo->info->print_lock);
		log_eating(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
		pthread_mutex_lock(&philo->info->meal_time_lock);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->info->meal_time_lock);
		_sleep(philo->info->time_to_eat);
		drop_fork(philo);
		pthread_mutex_lock(&philo->info->meals_lock);
		philo->meals = philo->meals + 1;
		pthread_mutex_unlock(&philo->info->meals_lock);
	}
}

void	thinking(t_philo *philo)
{
	if (can_run(philo) == 1 && is_still_alive(philo))
	{
		pthread_mutex_lock(&philo->info->print_lock);
		log_thinking(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
	}
}

void	sleeping(t_philo *philo)
{
	if (can_run(philo) == 1 && is_still_alive(philo))
	{
		pthread_mutex_lock(&philo->info->print_lock);
		log_sleeping(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
		_sleep(philo->info->time_to_sleep);
	}
}

void	*start(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (can_run(philo))
	{
		take_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info	*args;
	t_philo	**philos;

	if (check_error(argc, argv) == 0)
		return (1);
	args = init_arg(argc, argv);
	if (args == NULL)
		return (exit_with_error("unbale to creare args"));
	if (init_mutex(args) == -1)
		return (exit_with_error("unable to create mutexes"));
	philos = create_philos(args);
	if (philos == NULL)
		return (exit_with_error("unable to create philos"));
	if (create_threads(args, philos) == -1)
		return (exit_with_error("unable to create threads"));
	free_all(args, philos);
	return (0);
}
