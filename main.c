
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
	if (take_fork(philo) == 1)
	{
		philo->last_meal_time = get_time();
		log_eating(philo);
		usleep(philo->info->time_to_eat * 1000);
		drop_fork(philo);
		philo->meals = philo->meals + 1;
	}
	else
	{
		if (is_still_alive(philo) == 0)
		{
			philo->is_dead = 1;
			return;
		}
	}
}

void thinking(t_philo *philo)
{
	if (is_still_alive(philo) == 1 && philo->is_dead == 0)
		log_thinking(philo);
}

int is_still_alive(t_philo *philo)
{
	unsigned long int current_time;
	unsigned long int time;

	current_time = get_time();
	time = current_time - philo->last_meal_time;
	if (time > philo->info->time_to_die)
		return 0;
	return 1;
}

int sleeping(t_philo *philo)
{
	unsigned long int sleep_time;
	sleep_time = 0;
	if (is_still_alive(philo) == 1 && philo->is_dead == 0)
	{
		// printf("%d sleeping is_dead = %d\n", philo->id, philo->is_dead);
		log_sleeping(philo);
		while (is_still_alive(philo) == 1 && sleep_time < philo->info->time_to_sleep)
		{
			sleep_time += 1;
			usleep(1000);
			if (is_still_alive(philo) == 0)
			{
				return (0);
			}
		}
	}
	return (0);
}

void *start(void *args)
{
	t_philo *philo;
	int to_sleep;
	philo = (t_philo *)args;

	while (philo->is_dead == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->is_dead == 1)
		{
			log_is_dead(philo);
			break;
		}
	}
}

void create_threads(t_info *info, t_philo **philos)
{
	int i;
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
	if (pthread_mutex_init(&args->fork_lock, NULL) != 0)
	{
		printf("\n mutex init has failed\n");
		return (1);
	}
	// print_args(*args);
	philos = create_philos(args);
	// print_philos(philos, args->nb_of_philo);
	create_threads(args, philos);
	return (0);
}