
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
	printf("%-10s : %d\n", "Id", philo.id);
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

t_info init_arg(int argc, char** argv)
{
	t_info philo_arg;

	philo_arg.nb_of_philo = ft_atoi(argv[1]);
	philo_arg.time_to_die = ft_atoi(argv[2]);
	philo_arg.time_to_eat = ft_atoi(argv[3]);
	philo_arg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_arg.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);

	philo_arg.nb_of_forks = philo_arg.nb_of_philo / 2;
	philo_arg.nb_of_available_forks = philo_arg.nb_of_forks;

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
		i++;
	}
	return philos;
}

int main(int argc, char **argv)
{
	t_info philo_arg;
	t_philo *philos;

	int i = 0;

	if (argc != 5 && argc != 6)
	{
		printf("Usage : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	philo_arg = init_arg(argc, argv);
	print_args(philo_arg);
	philos = create_philos(philo_arg);
	print_philos(philos, philo_arg.nb_of_philo);
	return (0);
}