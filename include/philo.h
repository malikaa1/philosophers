/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:49:18 by mrahmani          #+#    #+#             */
/*   Updated: 2022/02/07 09:54:31 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
	int					nb_of_philo;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					max_times_to_eat;
	int					must_stop;
	pthread_mutex_t		*fork_locks;
	pthread_mutex_t		stop_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		meals_lock;
	pthread_mutex_t		meal_time_lock;

}t_info;

typedef struct s_philo
{
	int						id;
	unsigned long int		start_time;
	unsigned long int		last_meal_time;
	int						is_dead;
	int						meals;
	pthread_t				thread_id;
	t_info					*info;
}t_philo;

long int	get_time(void);
long int	get_d_time(t_philo *philo);
t_info		*init_arg(int argc, char **argv);
t_philo		**create_philos(t_info *info);
int			ft_atoi(const char *str);
int			exit_with_error(char *message);
int			check_args(char *s);
int			ft_isdigit(char c);
int			create_threads(t_info *info, t_philo **philos);
int			init_mutex(t_info *args);
int			is_dead(t_philo *philo);
int			must_stop(t_philo *philo);
int			*init_forks(t_info *info);
int			check_must_stop(t_philo **philos);
int			check_error(int ac, char **av);
int			can_run(t_philo *philo);
int			is_still_alive(t_philo *philo);
int			nb_meals_philos(t_philo **philos, int meals, int index);
void		*start(void *args);
void		*ft_malloc(size_t size);
void		ft_free(void *ptr);
void		unlock_all_forks(t_philo *philo);
void		log_eating(t_philo *philo);
void		log_taking_fork(t_philo *philo);
void		log_thinking(t_philo *philo);
void		log_sleeping(t_philo *philo);
void		_sleep(int time_ms);
void		take_fork(t_philo *philo);
void		drop_fork(t_philo *philo);
void		free_all(t_info *args, t_philo **philos);
void		*check_end(void *args);
void		mark_as_stop(t_info *info);
void		log_is_dead(t_philo *philo);
void		mark_as_dead(t_philo *philo);

#endif