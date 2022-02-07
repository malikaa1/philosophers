/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:32:05 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/07 10:32:05 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**create_philos(t_info *info)
{
	t_philo		**philos;
	int			i;

	i = 0;
	philos = ft_malloc((info->nb_of_philo + 1) * sizeof(t_philo *));
	if (philos == NULL)
		return (NULL);
	while (i < info->nb_of_philo)
	{
		philos[i] = ft_malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (NULL);
		philos[i]->id = i + 1;
		philos[i]->start_time = get_time();
		philos[i]->thread_id = 0;
		philos[i]->info = info;
		philos[i]->meals = 0;
		philos[i]->last_meal_time = get_time();
		philos[i]->is_dead = 0;
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

int	create_threads(t_info *info, t_philo **philos)
{
	int			nb_philo;
	pthread_t	id;

	nb_philo = info->nb_of_philo;
	if (pthread_create(&id, NULL, &check_end, philos) != 0)
		return (-1);
	while (nb_philo)
	{
		nb_philo--;
		if (pthread_create(&philos[nb_philo]->thread_id, NULL, &start,
				philos[nb_philo]) != 0)
			return (-1);
	}
	nb_philo = info->nb_of_philo;
	while (nb_philo)
	{
		nb_philo--;
		if (pthread_join(philos[nb_philo]->thread_id, NULL) != 0)
			return (-1);
	}
	if (pthread_join(id, NULL) != 0)
		return (-1);
	return (1);
}

int	init_mutex(t_info *args)
{
	int		i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_mutex_init(&args->fork_locks[i++], NULL) != 0)
			return (-1);
	}
	if (pthread_mutex_init(&args->dead_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&args->print_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&args->stop_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&args->meals_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&args->meal_time_lock, NULL) != 0)
		return (-1);
	return (1);
}
