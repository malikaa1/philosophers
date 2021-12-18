
#include "philo.h"

void print_args(t_info philo)
{
	printf("%-42s : %d\n", "number of philosophers", philo.nb_of_philo);
	printf("%-42s : %d\n", "number of times each philosopher must eat", philo.number_of_times_each_philosopher_must_eat);
	printf("%-42s : %d\n", "time to die", philo.time_to_die);
	printf("%-42s : %d\n", "time to eat", philo.time_to_eat);
	printf("%-42s : %d\n", "time to sleep", philo.time_to_sleep);
}

void print_philo(t_philo philo)
{
	printf("%-42s : %d\n", "id", philo.id);
}

void print_philos(t_philo *philos, int nb_of_philos)
{
	int i;
	i = 0;
	
	while (i < nb_of_philos)
	{
		print_philo(philos[i]);
		i++;
	}
}

t_info init_arg(int argc, char **argv)
{
	t_info philo_arg;

	philo_arg.nb_of_philo = ft_atoi(argv[1]);
	philo_arg.time_to_die = ft_atoi(argv[2]);
	philo_arg.time_to_eat = ft_atoi(argv[3]);
	philo_arg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_arg.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		philo_arg.number_of_times_each_philosopher_must_eat = -1;
	philo_arg.nb_of_forks = philo_arg.nb_of_philo;
	return (philo_arg);
}

t_philo *create_philos(t_info info)
{

	t_philo *philos;
	int i;
	i = 0;

	philos = malloc(info.nb_of_philo * sizeof(t_philo) + 1);
	while (i < info.nb_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].is_dead = 0;
		philos[i].is_eating = 0;
		philos[i].is_sleeing = 0;
		philos[i].is_thinking = 0;
		philos[i].start_time = 0;
		philos[i].has_forks = 0;
		i++;
	}
	return philos;
}

long int get_time()
{
	struct timeval tv;
	struct timezone tz;

	if (gettimeofday(&tv, &tz) == 0)
		return (tv.tv_sec * 1000);
	return (0);
}

int get_forks(t_info *info)
{
	int forks;
	pthread_mutex_lock(&info->lock);

	if (info->nb_of_forks >= 2)
	{
		info->nb_of_forks -= 2;
		pthread_mutex_unlock(&info->lock);

		return (2);
	}
	return (0);
}

void *taking_fork(void *arg)
{
	t_info *info;
	info = (t_info *)arg;
	int i;
	i = 0;
}

void start(t_info *info)
{

}

void *eating(void *arg)
{
	t_info *info;
	t_philo philo;
	info = (t_info *)arg;
	philo = info->philos[0];

	printf("%ld %d is eating\n", get_time(), philo.id);

	philo.start_time = get_time();

	while (philo.start_time + info->time_to_eat > get_time())
	{
	}
}

int main(int argc, char **argv)
{
	t_info args;
	t_philo *philos;

	int i = 0;

	if (argc != 5 && argc != 6)
	{
		printf("Usage : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	args = init_arg(argc, argv);
	print_args(args);
	philos = create_philos(args);
	print_philos(philos, args.nb_of_philo);

	args.philos = philos;

	if (pthread_mutex_init(&args.lock, NULL) != 0)
	{
		printf("\n mutex init failed\n");
		return 1;
	}
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &eating, &args);
	pthread_join(thread_id, NULL);

	return (0);
}