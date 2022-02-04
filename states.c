/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:56:43 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/04 20:13:04 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_philo *philo)
{
    int is_dead;
    
    is_dead = 0;
    pthread_mutex_lock(&philo->info->dead_lock);
    is_dead = philo->is_dead;
    pthread_mutex_unlock(&philo->info->dead_lock);
    return (is_dead);
}

void set_is_dead(t_philo *philo, int is_dead)
{
    pthread_mutex_lock(&philo->info->dead_lock);
    philo->is_dead = is_dead;
    pthread_mutex_unlock(&philo->info->dead_lock);
}

int is_still_alive(t_philo *philo)
{
    unsigned long int current_time;
    unsigned long int time;

    current_time = get_time();
    time = current_time - philo->last_meal_time;
    if (time > (philo->info->time_to_die))
        return (0);
    return (1);
}

void unlock_all_forks(t_philo *philo)
{
    int i;
    
    i = 0;
    while (i < philo->info->nb_of_philo)
    {
        pthread_mutex_unlock(&philo->info->fork_locks[i]);
        i++;
    }
}