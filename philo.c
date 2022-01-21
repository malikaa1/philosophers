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
        philos[i]->is_eating = 0;
        philos[i]->is_sleeing = 0;
        philos[i]->is_thinking = 0;
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