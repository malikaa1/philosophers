#include "philo.h"
int ft_isdigit(char c)
{
    if (c <= '9' && c >= '0')
        return (1);
    return (0);
}
int	ft_atoi(const char *str)
{
	unsigned int		result;
	int					sign;
	
	sign = 1;
	result = 0;
	
	while (*str == '\f' || *str == '\t' || *str == '\v'
			|| *str == '\r' || *str == '\n' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = 10 * result + (*str - 48);
		str++;
		if (result > INT_MAX)
			break ;
	}
	if ((result == (unsigned int)INT_MAX + 1 && sign == -1)
			|| result <= INT_MAX)
		return (sign * result);
	if (sign == 1)
		return (-1);
	else
		return (0);
}