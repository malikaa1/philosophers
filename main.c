/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:04:59 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/04 19:11:33 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void eating(t_philo *philo)
{
	if (can_run(philo) && is_still_alive(philo))
	{
		log_eating(philo);
		philo->last_meal_time = get_time();
		_sleep(philo->info->time_to_eat);
		drop_fork(philo);
		philo->meals = philo->meals + 1;
	}
}

void thinking(t_philo *philo)
{
	if (can_run(philo) == 1 && is_still_alive(philo))
	{
		log_thinking(philo);
	}
}

void sleeping(t_philo *philo)
{
	if (can_run(philo) == 1 && is_still_alive(philo))
	{
		log_sleeping(philo);
		_sleep(philo->info->time_to_sleep);
	}
}

void *start(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (can_run(philo))
	{
		take_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
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