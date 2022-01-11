#include "philo.h"

void print_args(t_info philo)
{
	printf("%-42s : %d\n", "number of philosophers", philo.nb_of_philo);
	printf("%-42s : %d\n", "number of times each philosopher must eat", philo.max_times_to_eat);
	printf("%-42s : %d\n", "time to die", philo.time_to_die);
	printf("%-42s : %d\n", "time to eat", philo.time_to_eat);
	printf("%-42s : %d\n", "time to sleep", philo.time_to_sleep);
}

int *init_forks(t_info* info)
{
	int i;
	int* forks;
	i = 0;
	forks = malloc((info->nb_of_philo + 1) * sizeof(int));
	if(forks == NULL)
		return (NULL);
	
	while (i < info->nb_of_philo)
	{
		forks[i] = 1;
		i++;
	}
	forks[i] = -1;
	return (forks);
}

t_info* init_arg(int argc, char **argv)
{
	t_info* args;

    args = ft_malloc(sizeof(t_info));
    if(args == NULL)
        return (NULL);

	args->nb_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->max_times_to_eat = ft_atoi(argv[5]);
	else
		args->max_times_to_eat = -1;
	args->forks = init_forks(args);
	return (args);
}

// 0 1 2 3 4 5
// 1 2 3 3 5 6
