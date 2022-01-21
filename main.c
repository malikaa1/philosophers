
#include "philo.h"

int nb_meals_reached(t_philo *philo)
{
	if (philo->info->max_times_to_eat == -1)
		return (0);
	return (philo->meals > philo->info->max_times_to_eat);
}

void eating(t_philo *philo)
{
	// if (nb_meals_reached(philo))
	// 	return;
	if (must_stop(philo))
		return;
	if (take_fork(philo) == 1)
	{
		philo->last_meal_time = get_time();
		pthread_mutex_lock(&philo->info->print_lock);
		log_eating(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
		usleep(philo->info->time_to_eat * 1000);
		drop_fork(philo);
		philo->meals = philo->meals + 1;
	}
	else
	{
		if (is_still_alive(philo) == 0 || philo->is_dead == 1)
		{
			set_is_dead(philo, 1);
			philo->info->must_stop = 1;
			pthread_mutex_lock(&philo->info->print_lock);
			log_is_dead(philo);
			pthread_mutex_unlock(&philo->info->print_lock);
			return;
		}
	}
}

void thinking(t_philo *philo)
{
	if (must_stop(philo))
		return;
	if (is_still_alive(philo) == 1)
	{
		pthread_mutex_lock(&philo->info->print_lock);
		log_thinking(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
	}
}

void sleeping(t_philo *philo)
{
	unsigned long int sleep_time;
	
	if (must_stop(philo))
		return;
	sleep_time = 0;
	if (is_still_alive(philo) == 1)
	{
		pthread_mutex_lock(&philo->info->print_lock);
		log_sleeping(philo);
		pthread_mutex_unlock(&philo->info->print_lock);
		while (is_still_alive(philo) == 1 && sleep_time < philo->info->time_to_sleep)
		{
			sleep_time += 1;
			usleep(1000);
			if (is_still_alive(philo) == 0)
				return;
		}
	}
	return;
}

void *start(void *args)
{
	t_philo *philo;
	int to_sleep;

	philo = (t_philo *)args;
	while (!is_dead(philo) && !must_stop(philo) &&  philo->info->max_times_to_eat > philo->meals)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (is_dead(philo) == 1)
		{
			pthread_mutex_lock(&philo->info->stop_lock);
			philo->info->must_stop = 1;
			pthread_mutex_unlock(&philo->info->stop_lock);
			break;
		}
	}
}

void create_threads(t_info *info, t_philo **philos)
{
	int i;
	pthread_t id;

	i = 0;
	while (i < info->nb_of_philo)
	{
		pthread_create(&philos[i]->thread_id, NULL, &start, philos[i]);
		i++;
	}
	i = 0;
	while (i < info->nb_of_philo)
	{
		pthread_join(philos[i]->thread_id, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_info *args;
	t_philo **philos;

	int i = 0;

	if (argc != 5 && argc != 6)
	{
		printf("Usage : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [max_meals]\n");
		return (0);
	}
	args = init_arg(argc, argv);
	pthread_mutex_init(&args->fork_lock, NULL);
	pthread_mutex_init(&args->dead_lock, NULL);
	pthread_mutex_init(&args->print_lock, NULL);
	pthread_mutex_init(&args->stop_lock, NULL);
	philos = create_philos(args);
	create_threads(args, philos);
	return (0);
}