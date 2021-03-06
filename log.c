/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:49:18 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/07 09:54:31 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_eating(t_philo *philo)
{
	if (must_stop(philo))
		return ;
	printf("%8ld : Philo %d is eating\n", get_d_time(philo), philo->id);
}

void	log_taking_fork(t_philo *philo)
{
	printf("%8ld : Philo %d has taken a fork\n", get_d_time(philo), philo->id);
}

void	log_sleeping(t_philo *philo)
{
	if (must_stop(philo))
		return ;
	printf("%8ld : Philo %d is sleeping \n", get_d_time(philo), philo->id);
}

void	log_thinking(t_philo *philo)
{
	if (must_stop(philo))
		return ;
	printf("%8ld : Philo %d is thinking \n", get_d_time(philo), philo->id);
}

void	log_is_dead(t_philo *philo)
{
	printf("%8ld : Philo %d is dead\n",
		get_d_time(philo), philo->id);
}
