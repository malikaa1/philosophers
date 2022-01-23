#include "philo.h"

t_philo **create_philos(t_info *info)
{
    t_philo **philos;
    int i;

    i = 0;
    philos = ft_malloc(info->nb_of_philo * sizeof(t_philo *) + 1);
    if (philos == NULL)
        return (NULL);
    while (i < info->nb_of_philo)
    {
        philos[i] = ft_malloc(sizeof(t_philo));
        if (philos[i] == NULL)
            return (NULL);
        philos[i]->id = i + 1;
        philos[i]->is_dead = 0;
        philos[i]->start_time = get_time();
        philos[i]->thread_id = 0;
        philos[i]->info = info;
        philos[i]->meals = 0;
        philos[i]->last_meal_time = get_time();
        philos[i]->has_forks = 0;
        i++;
    }
    philos[i] = NULL;
    return philos;
}

void create_threads(t_info *info, t_philo **philos)
{
    int nb_philo;
    pthread_t id;

    nb_philo = info->nb_of_philo;
    while (nb_philo)
    {
        nb_philo--;
        pthread_create(&philos[nb_philo]->thread_id, NULL, &start, philos[nb_philo]);
    }
    nb_philo = info->nb_of_philo;
    while (nb_philo)
    {
        nb_philo--;
        pthread_join(philos[nb_philo]->thread_id, NULL);
    }
}

void init_mutex(t_info *args)
{
    int i;
    i = 0;
    while (i < args->nb_of_philo)
    {
        pthread_mutex_init(&args->fork_locks[i++], NULL);
    }

    pthread_mutex_init(&args->dead_lock, NULL);
    pthread_mutex_init(&args->print_lock, NULL);
    pthread_mutex_init(&args->stop_lock, NULL);
}