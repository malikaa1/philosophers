/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:04:59 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/31 22:35:07 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void _sleep(int time_ms)
{
	long int s_time = get_time();
	// struct timespec remainig, request = {0, time_ms * 1000 * 1000};

	// nanosleep(&request, &remainig);

	int elapsed = 0;

	// while (elapsed <= time_ms)
	// {
	// 	long int start = get_time();
	// 	usleep(1000);
	// 	long int end = get_time();
	// 	elapsed+= (end - start);
	// }

	usleep(time_ms * 1000);

	long int e_time = get_time();

	printf("---------------------------------------------------------> %ld\n", e_time - s_time);
}

void eating(t_philo *philo)
{

	// if (!is_still_alive(philo))
	// {
	// 	if(philo->info->must_stop)
	// 		return;
	// 	pthread_mutex_lock(&philo->info->stop_lock);
	// 	set_is_dead(philo, 1);
	// 	philo->info->must_stop = 1;
	// 	log_is_dead(philo);
	// 	pthread_mutex_unlock(&philo->info->stop_lock);
	// 	return;
	// }
	if (can_run(philo))
	{
		philo->last_meal_time = get_time();
		log_eating(philo);
		long int start = get_d_time(philo);
		_sleep(philo->info->time_to_eat);
		drop_fork(philo);
		long int end = get_d_time(philo);
		log_done_eating(philo, end - start);
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
	long int start;
	long int end;
	start = get_d_time(philo);
	if (must_stop(philo))
		return;
	if (can_run(philo) == 1 && is_still_alive(philo))
	{
		log_sleeping(philo);
		_sleep(philo->info->time_to_sleep);
	}
	end = get_d_time(philo);
	log_done_sleeping(philo, end - start);
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
	if (philo->id % 2 == 0)
		usleep(10 * 1000);

	while (can_run(philo))
	{
		take_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		// if (is_dead(philo) == 1)
		// {
		// 	pthread_mutex_lock(&philo->info->stop_lock);
		// 	philo->info->must_stop = 1;
		// 	pthread_mutex_unlock(&philo->info->stop_lock);
		// 	break;
		// }
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