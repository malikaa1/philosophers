
#include "philo.h"

void *start(void *args)
{
	pthread_mutex_lock(args);
	t_targs *targs;
	targs = (t_targs *)args;
	
	log_start(targs->info, targs->philo);
	pthread_mutex_unlock(args);
}

void create_threads(t_info* info, t_philo **philos)
{
	int i;
	t_targs *args;
	i = 0;
	args = ft_malloc(sizeof(t_targs));
	if(args == NULL)
		return;
	args->info = info;
	while (i < info->nb_of_philo)
	{
		args->philo = philos[i];
		pthread_create(&philos[i]->thread_id, NULL, &start, args);
		i++;
	}
	i = 0;
	while (i < info->nb_of_philo)
	{
		pthread_join(philos[i]->thread_id, NULL);
		i++;
	}
	ft_free(args);
}

int main(int argc, char **argv)
{
	t_info* args;
	t_philo **philos;

	int i = 0;

	if (argc != 5 && argc != 6)
	{
		printf("Usage : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	args = init_arg(argc, argv);
	if (pthread_mutex_init(&args->log_lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return (1);
    }
	print_args(*args);
	philos = create_philos(*args);
	print_philos(philos, args->nb_of_philo);
	create_threads(args, philos);
	return (0);
}