#include "philo.h"

void	ft_action_print(t_info *i, int id, char *str)
{
	pthread_mutex_lock(&(i->write));
	pthread_mutex_lock(&(i->death));
	if (!i->dead_body)
	{
		printf("[%lld] ", time_manager() - i->time_start);
		printf("%d %s\n", id + 1, str);
	}
	pthread_mutex_unlock(&(i->death));
	pthread_mutex_unlock(&(i->write));
}

void	ft_usleep(t_info *i, long long int time)
{
	long long int	start;

	start = time_manager();
	pthread_mutex_lock(&(i->death));
	if (!(i->dead_body)
	{
		while ((time_manager() - start) < time)
			usleep(50);
	}
	pthread_mutex_unlock(&(i->death));
}

long long int	time_manager(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	check_and_eat(t_philo *p, t_info *i)
{
	pthread_mutex_lock(&(i->death));
	if (i->dead_body)
	{
		pthread_mutex_unlock(&(i->death));
		return (1);
	}
	pthread_mutex_unlock(&(i->death));
	ft_igestion(p, i);
	pthread_mutex_lock(&(i->meal_check));
	if (i->all_wellfed)
	{
		pthread_mutex_unlock(&(i->meal_check));
		return (1);
	}
	pthread_mutex_unlock(&(i->meal_check));
	return (0);
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
