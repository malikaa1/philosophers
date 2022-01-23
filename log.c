/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:49:18 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/23 22:14:32 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void log_eating(t_philo *philo)
{
    printf("%ld : Philo %d is eating\n", get_d_time(philo), philo->id);
}

void log_done_eating(t_philo *philo)
{
    printf("%ld : Philo %d finished eating\n", get_d_time(philo), philo->id);
}

void log_taking_fork(t_philo *philo, int index)
{
    printf("%ld : Philo %d has taken a fork #%d\n", get_d_time(philo), philo->id, index);
}

void log_sleeping(t_philo *philo)
{
    printf("%ld : Philo %d is sleeping \n", get_d_time(philo), philo->id);
}

void log_done_sleeping(t_philo *philo)
{
    printf("%ld : Philo %d has finished sleeping \n", get_d_time(philo), philo->id);
}

void log_thinking(t_philo *philo)
{
    printf("%ld : Philo %d is thinking \n", get_d_time(philo), philo->id);
}

void log_is_dead(t_philo *philo)
{
    printf("%ld : Philo %d is dead \n", get_d_time(philo), philo->id);
}