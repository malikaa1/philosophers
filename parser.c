#include "philo.h"

void print_args(t_info philo)
{
	printf("%-42s : %d\n", "number of philosophers", philo.nb_of_philo);
	printf("%-42s : %d\n", "number of times each philosopher must eat", philo.max_times_to_eat);
	printf("%-42s : %d\n", "time to die", philo.time_to_die);
	printf("%-42s : %d\n", "time to eat", philo.time_to_eat);
	printf("%-42s : %d\n", "time to sleep", philo.time_to_sleep);
}

t_info* init_arg(int argc, char **argv)
{
	t_info* philo_arg;

    philo_arg = ft_malloc(sizeof(t_info));
    if(philo_arg == NULL)
        return (NULL);

	philo_arg->nb_of_philo = ft_atoi(argv[1]);
	philo_arg->time_to_die = ft_atoi(argv[2]);
	philo_arg->time_to_eat = ft_atoi(argv[3]);
	philo_arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_arg->max_times_to_eat = ft_atoi(argv[5]);
	else
		philo_arg->max_times_to_eat = -1;
	return (philo_arg);
}
