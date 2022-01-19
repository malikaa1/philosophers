/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:53:51 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/19 14:30:59 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int must_stop(t_philo *philo)
{
    int must_stop;

    must_stop = 0;
    pthread_mutex_lock(&philo->info->print_lock);
    must_stop = philo->must_stop;
    pthread_mutex_unlock(&philo->info->print_lock);
    return must_stop;
}

void mark_as_stop(t_philo **philos)
{
    int i;
    i = 0;

    if (philos == NULL || philos[0] == NULL)
        return;
    pthread_mutex_lock(&philos[0]->info->stop_lock);
    while (philos[i] != NULL)
    {
        philos[i]->must_stop = 1;
        i++;
    }
    pthread_mutex_unlock(&philos[0]->info->stop_lock);
}

void *check_end(void *args)
{
    t_philo **philos;
    int i;
    int alive;

    i = 0;
    alive = 1;
    philos = (t_philo **)args;

    while (alive)
    {
        while (philos[i] != NULL)
        {
            if (is_dead(philos[i]) == 1)
            {
                alive = 0;
                mark_as_stop(philos);
                return NULL;
            }
            i++;
        }
        i = 0;
    }
}

int check_must_stop(t_philo **philos)
{
    int i = 0;

    pthread_mutex_lock(&philos[0]->info->stop_lock);
    while (philos[i] != NULL)
    {
        if (philos[i]->must_stop == 1)
        {
            pthread_mutex_unlock(&philos[0]->info->stop_lock);
            return 1;
        }
    }
    pthread_mutex_unlock(&philos[0]->info->stop_lock);
    return 0;
}