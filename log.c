/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:49:18 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/04 20:05:19 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void log_eating(t_philo *philo)
{
    if (philo->info->must_stop)
        return;
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d is eating\n", get_d_time(philo), philo->id);
    pthread_mutex_unlock(&philo->info->print_lock);
}

void log_taking_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d has taken a fork\n", get_d_time(philo), philo->id);
    pthread_mutex_unlock(&philo->info->print_lock);
}

void log_sleeping(t_philo *philo)
{
    if (philo->info->must_stop)
        return;
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d is sleeping \n", get_d_time(philo), philo->id);
    pthread_mutex_unlock(&philo->info->print_lock);
}

void log_thinking(t_philo *philo)
{
    if (philo->info->must_stop)
        return;
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d is thinking \n", get_d_time(philo), philo->id);
    pthread_mutex_unlock(&philo->info->print_lock);
}

void log_is_dead(t_philo *philo)
{
    printf("\033[0;31m");
    long int since = get_d_time(philo) - (philo->last_meal_time - philo->start_time) - philo->info->time_to_eat - philo->info->time_to_sleep;
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d is dead since %ld\n", get_d_time(philo), philo->id, since);
    pthread_mutex_unlock(&philo->info->print_lock);
    printf("\033[0m");
}