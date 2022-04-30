#include "philo.h"

long long int	time_manager(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_atoi_v2(char *str)
{
	int				i;
	long long int	digit;

	i = 0;
	digit = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			digit = digit * 10 + (str[i++] - '0');
		else
			return (0);
	}
	if (digit > 2147483647)
		return (0);
	return ((int)digit);
}
