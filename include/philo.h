#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_philo
{
    int id;
    int is_eating;
    int is_sleeing;
    int is_thinking;
    unsigned long int start_time;
    int is_dead;
    int has_forks;


} t_philo;

typedef struct s_info
{
    int nb_of_philo;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;

    int nb_of_forks;

    pthread_mutex_t lock;

    t_philo* philos;

} t_info;

int ft_atoi(const char *str);
t_info init_arg(int argc, char** argv);


#endif