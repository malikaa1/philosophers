/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:49:18 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/31 21:38:50 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_putstr(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        write(1, &s[i], 1);
        i++;
    }
}

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putnbr(long long nb)
{
    if (nb < 0)
    {
        nb = -nb;
    }
    if (nb >= 10)
    {
        ft_putnbr(nb / 10);
        ft_putnbr(nb % 10);
    }
    else
        ft_putchar(nb + '0');
}

void log_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d is eating\n", get_d_time(philo), philo->id);
    pthread_mutex_unlock(&philo->info->print_lock);
}

void log_done_eating(t_philo *philo, long int elapsed)
{
    if (philo->info->must_stop)
        return;
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d finished eating in %ld\n", get_d_time(philo), philo->id, elapsed);
    pthread_mutex_unlock(&philo->info->print_lock);
}

void log_taking_fork(t_philo *philo, int index)
{
    if (philo->info->must_stop)
        return;
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d has taken a fork #%d\n", get_d_time(philo), philo->id, index);
    pthread_mutex_unlock(&philo->info->print_lock);
}

void log_drop_fork(t_philo *philo)
{
    if (philo->info->must_stop)
        return;
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d has dropped forks\n", get_d_time(philo), philo->id);
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

void log_done_sleeping(t_philo *philo, long int elapsed)
{
    if (philo->info->must_stop)
        return;
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d has finished sleeping for %ld\n", get_d_time(philo), philo->id, elapsed);
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