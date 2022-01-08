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
    pthread_t thread_id;

} t_philo;

typedef struct s_info
{
    int nb_of_philo;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int max_times_to_eat;

    pthread_mutex_t log_lock;

} t_info;

typedef struct s_targs
{
    t_philo* philo;
    t_info* info;
} t_targs;



int ft_atoi(const char *str);
long int get_time();
void print_args(t_info philo);
t_info *init_arg(int argc, char **argv);
void print_philo(t_philo* philo);
void print_philos(t_philo **philos, int nb_of_philos);
t_philo **create_philos(t_info info);
void *ft_malloc(size_t size);
void ft_free(void *ptr);
void log_start(t_info *info, t_philo* philo);

#endif