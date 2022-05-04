#include "philo.h"

static int	init_mutex_philo(t_connect *c)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(c->i.write), NULL))
		return (1);
	if (pthread_mutex_init(&(c->i.meal_check), NULL))
		return (1);
	while (++i <= c->i.num_philos)
	{
		c->p[i].id = i;
		c->p[i].l_fork = i;
		c->p[i].r_fork = (i + 1) % c->i.num_philos;
		c->p[i].time_last_eat = 0;
		c->p[i].count_meals = 0;
		if (pthread_mutex_init(&(c->i.forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(c->i.write), NULL))
		return (1);
	if (pthread_mutex_init(&(c->i.meal_check), NULL))
		return (1);
	return (0);
}

int	ft_initialize(t_connect *c, int argc, char **argv)
{
	c->i.num_philos = ft_atoi_v2(argv[1]);
	c->i.time_death = ft_atoi_v2(argv[2]);
	c->i.time_eat = ft_atoi_v2(argv[3]);
	c->i.time_sleep = ft_atoi_v2(argv[4]);
	c->i.dead_body = 0;
	c->i.all_wellfed = 0;
	c->i.num_meals = -1;
	c->i.time_start = time_manager();
	if (argc == 6)
		c->i.num_meals = ft_atoi_v2(argv[5]);
	if (c->i.num_philos < 2 || c->i.num_philos > 200 || c->i.time_death <= 0
		|| c->i.time_eat <= 0 || c->i.time_sleep <= 0 || c->i.num_meals == 0)
		return (1);
	c->i.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* c->i.num_philos);
	c->p = (t_philo *)malloc(sizeof(t_philo) * c->i.num_philos);
	if (!c->p || !c->i.forks)
		return (2);
	if (init_mutex_philo(c))
		return (3);
	return (0);
}
