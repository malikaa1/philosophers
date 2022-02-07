/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:56:43 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/07 10:29:06 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_end(void *args)
{
	t_philo		**philos;
	int			i;
	int			max_meals;

	i = 0;
	philos = (t_philo **)args;
	max_meals = philos[i]->info->nb_of_philo * philos[i]->info->max_times_to_eat;
	while (1)
	{
		while (philos[i] != NULL)
		{
			if (nb_meals_philos(philos, max_meals, i))
				return (NULL);
			if (is_still_alive(philos[i]) == 0)
			{
				pthread_mutex_lock(&philos[i]->info->print_lock);
				mark_as_dead(philos[i]);
				mark_as_stop(philos[i]->info);
				unlock_all_forks(philos[i]);
				log_is_dead(philos[i]);
				pthread_mutex_unlock(&philos[i]->info->print_lock);
				return (NULL);
			}
			i++;
		}
		usleep((10) * 1000);
		i = 0;
	}
}

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

void	mark_as_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead_lock);
	philo->is_dead = 1;
	pthread_mutex_unlock(&philo->info->dead_lock);
}

void	unlock_all_forks(t_philo *philo)
{
	int		i;
       
	i = 0;
	while (i < philo->info->nb_of_philo)
	{
		pthread_mutex_unlock(&philo->info->fork_locks[i]);
		i++;
	}
}

int	nb_meals_philos(t_philo **philos, int meals, int index)
{
	int		i;
	int		nb_of_philo;
	int		sum_meals;

	sum_meals = 0;
	i = 0;
	nb_of_philo = philos[i]->info->nb_of_philo;
	while (i < nb_of_philo)
	{
		pthread_mutex_lock(&philos[i]->info->meals_lock);
		sum_meals = sum_meals + philos[i]->meals;
		pthread_mutex_unlock(&philos[i]->info->meals_lock);
		i++;
	}
	if (meals == sum_meals)
	{
		printf("max meals reached\n");
		mark_as_stop(philos[index]->info);
		unlock_all_forks(philos[index]);
		return (1);
	}
	return (0);
}
