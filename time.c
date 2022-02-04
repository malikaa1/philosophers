/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:24:14 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/04 19:11:54 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int get_time()
{
	struct timeval tv;
	struct timezone tz;

	if (gettimeofday(&tv, &tz) == 0)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (0);
}

long int get_d_time(t_philo *philo)
{
	return get_time() - philo->start_time;
}
