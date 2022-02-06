/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:32:05 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/05 23:56:06 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo **create_philos(t_info *info)
{
    t_philo **philos;
    int i;

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

int create_threads(t_info *info, t_philo **philos)
{
    int nb_philo;
    pthread_t id;

    nb_philo = info->nb_of_philo;
    if (pthread_create(&id, NULL, &check_end, philos) != 0)
        return (-1);
    while (nb_philo)
    {
        nb_philo--;
        if (pthread_create(&philos[nb_philo]->thread_id, NULL, &start, philos[nb_philo]) != 0)
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

int init_mutex(t_info *args)
{
    int i;

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

    return (1);
}

int nb_meals_philos(t_philo **philos, int meals, int index)
{
    int i;
    int nb_of_philo;
    int sum_meals;

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

void mark_as_dead(t_philo* philo)
{
    pthread_mutex_lock(&philo->info->dead_lock);
    philo->is_dead = 1;
    pthread_mutex_unlock(&philo->info->dead_lock);
}

void *check_end(void *args)
{
    t_philo **philos;
    int i;
    int max_meals;

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
        usleep((philos[0]->info->time_to_die / 2) * 1000);
        i = 0;
    }
}
