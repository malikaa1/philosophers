/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:53:51 by mrahmani          #+#    #+#             */
/*   Updated: 2022/01/20 20:56:59 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int must_stop(t_philo *philo)
{
    int must_stop;

    must_stop = 0;
    pthread_mutex_lock(&philo->info->print_lock);
    must_stop = philo->info->must_stop;
    pthread_mutex_unlock(&philo->info->print_lock);
    return (must_stop);
}


