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
    printf("%8ld : Philo %d is eating\n", get_d_time(philo), philo->id);
}

void log_done_eating(t_philo *philo)
{
    printf("%8ld : Philo %d finished eating\n", get_d_time(philo), philo->id);
}

void log_taking_fork(t_philo *philo, int index)
{
    printf("%8ld : Philo %d has taken a fork #%d\n", get_d_time(philo), philo->id, index);
}

void log_drop_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->print_lock);
    printf("%8ld : Philo %d has dropped forks\n", get_d_time(philo), philo->id);
    pthread_mutex_unlock(&philo->info->print_lock);
}

void log_sleeping(t_philo *philo)
{
    printf("%8ld : Philo %d is sleeping \n", get_d_time(philo), philo->id);
}

void log_done_sleeping(t_philo *philo)
{
    printf("%8ld : Philo %d has finished sleeping \n", get_d_time(philo), philo->id);
}

void log_thinking(t_philo *philo)
{
    printf("%8ld : Philo %d is thinking \n", get_d_time(philo), philo->id);
}

void log_is_dead(t_philo *philo)
{
    printf("%8ld : Philo %d is dead \n", get_d_time(philo), philo->id);
}