/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:04:59 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/05 23:41:42 by mrahmani         ###   ########.fr       */
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
		// printf("iiii===========> %d\n", philo->info->must_stop);
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
	}
	return (NULL);
}

void free_philos(t_philo **philo)
{
	t_philo **temp = philo;
	int i = 0;
	while (temp[i] != NULL)
	{
		ft_free(temp[i]);
		i++;
	}
	ft_free(temp);
}

int exit_with_error(char *message)
{
	printf("%s\n", message);
	return (1);
}

void free_all(t_info *args, t_philo **philos)
{
	ft_free(args->fork_locks);
	free_philos(philos);
	ft_free(args);
}

int main(int argc, char **argv)
{
	t_info *args;
	t_philo **philos;

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