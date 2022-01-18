
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
	if (must_stop(philo) == 1)
		return;
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
			set_is_dead(philo, 1);
			return;
		}
	}
}

int must_stop(t_philo *philo)
{
	int must_stop;

	must_stop = 0;
	pthread_mutex_lock(&philo->info->stop_lock);
	// printf("checking is_dead by -----]%d\n", philo->id);
	must_stop = philo->must_stop;
	pthread_mutex_unlock(&philo->info->stop_lock);
	return must_stop;
}

int is_dead(t_philo *philo)
{
	int is_dead;
	is_dead = 0;
	pthread_mutex_lock(&philo->info->dead_lock);
	is_dead = philo->is_dead;
	pthread_mutex_unlock(&philo->info->dead_lock);

	return is_dead;
}

void set_is_dead(t_philo *philo, int is_dead)
{
	pthread_mutex_lock(&philo->info->dead_lock);
	philo->is_dead = is_dead;
	pthread_mutex_unlock(&philo->info->dead_lock);
}

void thinking(t_philo *philo)
{
	if (must_stop(philo) == 1)
		return;
	if (is_still_alive(philo) == 1)
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

void sleeping(t_philo *philo)
{
	unsigned long int sleep_time;

	sleep_time = 0;
	if (must_stop(philo) == 1)
		return;
	if (is_still_alive(philo) == 1)
	{
		// printf("%d sleeping is_dead = %d\n", philo->id, philo->is_dead);
		log_sleeping(philo);
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

	while (!is_dead(philo) && !must_stop(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (is_dead(philo) == 1)
		{
			log_is_dead(philo);
			break;
		}
	}
}

void mark_as_stop(t_philo **philos)
{
	printf("mark as stop\n");
	int i;
	i = 0;

	if (philos == NULL || philos[0] == NULL)
		return;
	pthread_mutex_lock(&philos[i]->info->stop_lock);
	
	while (philos[i] != NULL)
	{
		philos[i]->must_stop = 1;
		i++;
	}
	pthread_mutex_unlock(&philos[i]->info->stop_lock);
	printf("mark as stop done\n");
}

void *check_end(void *args)
{
	t_philo **philos;
	int i;
	int alive;
	i = 0;
	alive = 1;
	philos = (t_philo **)args;

	// printf("start checking for deaths -------->\n");

	while (alive)
	{
		// print_philos(philos, 4);
		// printf("checking for deaths -------->\n");
		while (philos[i] != NULL)
		{
			// printf("checking for %d death -------->\n", philos[i]->id);

			// print_philo(philos[i]);
			// printf("checking for deaths for %d-------->\n", philos[i]->id);
			if (is_dead(philos[i]) == 1)
			{
				printf("philo %d is deaaaaaaaaaaaaaaaaaaaaaaaaad\n", philos[i]->id);
				alive = 0;
				mark_as_stop(philos);
				return NULL;
			}
			i++;
		}
		i = 0;
		// usleep(1000);
	}
	// printf("exit for deaths -------->\n");
}

void create_threads(t_info *info, t_philo **philos)
{
	int i;
	pthread_t id;

	i = 0;
	pthread_create(&id, NULL, &check_end, philos);

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
	pthread_join(id, NULL);
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
	if (pthread_mutex_init(&args->stop_lock, NULL) != 0)
	{
		printf("\n mutex init has failed\n");
		return (1);
	}
	if (pthread_mutex_init(&args->dead_lock, NULL) != 0)
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