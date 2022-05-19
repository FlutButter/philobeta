#include "philo_bonus.h"

static int	init_sem_philo(t_connect *c)
{
	int	j;

	j = -1;
	sem_unlink("/p_forks");
	sem_unlink("/p_write");
	sem_unlink("/p_meal_check");
	c->i.forks = sem_open("/p_forks", O_CREAT, 0666, c->i.num_philos);
	c->i.write = sem_open("/p_write", O_CREAT, 0666, c->i.num_philos);
	c->i.meal_check = sem_open("/p_meal_check", O_CREAT, 0666, c->i.num_philos);
	if (c->i.forks <= 0 || c->i.write <= 0 || c->i.meal_check <= 0)
		return (1);
	while (++j < c->i.num_philos)
	{
		c->p[j].id = j;
		c->p[j].time_last_eat = 0;
		c->p[j].count_meals = 0;
	}
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
	if (argc == 6)
		c->i.num_meals = ft_atoi_v2(argv[5]);
	if (c->i.num_philos < 1 || c->i.num_philos > 200 || c->i.time_death <= 0
		|| c->i.time_eat <= 0 || c->i.time_sleep <= 0 || c->i.num_meals <= 0)
		return (1);
	c->p = malloc(sizeof(t_philo) * c->i.num_philos);
	if (!c->p)
		return (2);
	if (init_sem_philo(c))
		return (3);
	return (0);
}
