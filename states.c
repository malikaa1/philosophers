/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:56:43 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/31 20:54:28 by mrahmani         ###   ########.fr       */
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
    if (time > (philo->info->time_to_die + 10))
        return (0);
    return (1);
}