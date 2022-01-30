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
        philos[i]->mark_stop = 0;
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
    pthread_create(&id, NULL, &check_end, philos);
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
    pthread_join(id, NULL);
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
    while (i < args->nb_of_philo)
    {
        pthread_mutex_init(&args->take_fork_locks[i++], NULL);
    }
}

int nb_meals_philos(t_philo **philos)
{
    int i;
    int  nb_of_philo;
    int sum_meals;

    sum_meals = 0;
    i = 0;
    nb_of_philo = philos[i]->info->nb_of_philo;
    while (i < nb_of_philo)
    {
        sum_meals = sum_meals + philos[i]->meals;
        i++;
    }
    return (sum_meals);
}
void *check_end(void *args)
{
    t_philo **philos;
    int i;
    int alive;

    i = 0;
    alive = 1;
    philos = (t_philo **)args;
    while (alive)
    {
        while (philos[i] != NULL)
        {
            if (is_dead(philos[i]) == 1 || nb_meals_philos(philos) == (philos[i]->info->nb_of_philo * philos[i]->info->max_times_to_eat))
            {
                alive = 0;
                mark_as_stop(philos);
                return NULL;
            }
            i++;
        }
        i = 0;
    }
}

void mark_as_stop(t_philo **philos)
{
    int i;
    int nb;
    
    i = 0;
    nb  = philos[i]->info->nb_of_philo;
    if (philos == NULL || philos[0] == NULL)
        return;
    pthread_mutex_lock(&philos[i]->info->stop_lock);
    philos[i]->info->must_stop = 1;
    pthread_mutex_unlock(&philos[i]->info->stop_lock);
}