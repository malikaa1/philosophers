#include "philo.h"

void log_start(t_info *info, t_philo* philo)
{
    pthread_mutex_lock(&info->log_lock);
    printf("philo %d starting in thread #%ld .....\n", philo->id, philo->thread_id);
    pthread_mutex_unlock(&info->log_lock);
}