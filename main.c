
#include "philo.h"

int take_fork(t_philo *philo, int take)
{
	int id;
	int left_id;
	int forks_available = 0;

	id = philo->id - 1;
	left_id = philo->id;

	if (philo->id == philo->info->nb_of_philo)
		left_id = 0;
	pthread_mutex_lock(&philo->info->fork_lock);

	if (philo->info->forks[id] == take)
	{
		philo->info->forks[id] == !take;
		if (take)
			log_taking_fork(philo, id + 1);
		philo->info->forks[left_id] == !take;
		if (take)
			log_taking_fork(philo, left_id + 1);
		forks_available = 1;
	}

	pthread_mutex_unlock(&philo->info->fork_lock);
	return (forks_available);
}

void eating(t_philo *philo)
{
	if (take_fork(philo, 1) == 1)
	{
		log_eating(philo);
		usleep(philo->info->time_to_eat * 1000);
		take_fork(philo, 0);
		philo->last_meal_time = get_time();
		philo->meals = philo->meals + 1;
	}
}

void sleeping(t_philo *philo)
{
	log_sleeping(philo);
	// while (philo->is_dead != 1)
	// {
	// 	usleep()
	// }
}

void *start(void *args)
{
	t_philo *philo;
	philo = (t_philo *)args;

	//log_start(philo);

	while (philo->is_dead != 1 
		|| (philo->info->max_times_to_eat != -1 && philo->meals > philo->info->max_times_to_eat))
	{
		eating(philo);
		sleeping(philo);
		//thinking();
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
	//print_args(*args);
	philos = create_philos(args);
	//print_philos(philos, args->nb_of_philo);
	create_threads(args, philos);
	return (0);
}