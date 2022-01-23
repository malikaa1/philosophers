#include "philo.h"

long int get_time()
{
	struct timeval tv;
	struct timezone tz;

	if (gettimeofday(&tv, &tz) == 0)
		return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
	return (0);
}

long int get_d_time(t_philo *philo)
{
	long int time;
	return get_time() - philo->start_time;
}
