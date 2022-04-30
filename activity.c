#include "philo.h"

void	*philo_thread(void *ptr)
{
	t_connect	c;

	c = (t_connect *)ptr;
	if (c->p.id % 2)
		usleep(10000);
	while (!(c->i.dead_body))
	{
		ft_igestion(&c);
	}
	return (NULL);
}

int	create_threads(t_connect *c)
{
	int	i;

	i = -1;
	while (++i < c->i.num_philos)
	{
		if (pthread_create(&(c->p[i].thread), NULL, philo_thread, &c))
			return (1);
		c->p[i].time_last_eat = time_manager();
	}
	pulse_monitor(&c);
	ft_shut_down(&c);
	return (0);
}
