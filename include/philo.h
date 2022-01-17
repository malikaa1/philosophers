#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_info
{
    int nb_of_philo;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int max_times_to_eat;

    pthread_mutex_t fork_lock;

    int* forks;

} t_info;

typedef struct s_philo
{
    int id;
    int is_eating;
    int is_sleeing;
    int is_thinking;
    unsigned long int start_time;
    int is_dead;
    pthread_t thread_id;
    unsigned long int last_meal_time;
    int meals;
    int has_forks;
    t_info* info;
    pthread_mutex_t dead_lock;

} t_philo;




int ft_atoi(const char *str);
long int get_time();
void print_args(t_info philo);
t_info *init_arg(int argc, char **argv);
void print_philo(t_philo* philo);
void print_philos(t_philo **philos, int nb_of_philos);
t_philo **create_philos(t_info* info);
void *ft_malloc(size_t size);
void ft_free(void *ptr);

void log_start(t_philo* philo);
void log_eating(t_philo* philo);
void log_taking_fork(t_philo *philo, int index);
void log_thinking(t_philo *philo);
void log_sleeping(t_philo *philo);
void log_is_dead(t_philo *philo);
int is_still_alive(t_philo *philo);
int take_fork(t_philo *philo);
void drop_fork(t_philo *philo);
#endif