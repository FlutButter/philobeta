#include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				r_fork;
	int 			l_fork;
	int				count_meals;
	long long int	time_last_eat;
	pthread_t		thread;
	//t_info			*ptr;

}	t_philo;

typedef struct s_info
{
	int				num_philos;
	int				num_meals;
	int				all_wellfed;
	int				time_eat;
	int				time_sleep;
	int				time_death;
	int				dead_body;
	long long int	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	write;

}	t_info;

typedef struct s_connect
{
	t_philo	*p;
	t_info	i;
}	t_connect;

int	init_mutex_philo(t_connect *c)
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
		//c->p[i].ptr = c->i;
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
	c->i.num_philos = ft_atoi(argv[1]);
	c->i.time_death = ft_atoi(argv[2]);
	c->i.time_eat = ft_atoi(argv[3]);
	c->i.time_sleep = ft_atoi(argv[4]);
	c->i.dead_body = 0;
	c->i.all_wellfed = 0;
	c->i.num_meals = -1;
	if (c->i.num_philos < 2 || c->i.num_philos > 200 || c->i.time_death <= 0 || 
		c->i.time_eat <= 0 || c->i.time_sleep <= 0 || )
		return (1);
	c->i.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* c->i.num_philos);
	c->p = (t_philo *)malloc(sizeof(t_philo) * c->i.num_philos);
	if (!c->p || !c->i.forks)
		return (2);
	if (argc == 5)
		c->i.num_meals = ft_atoi(argv[5])
	if (init_mutex_philo(c));
		return (3);
	return (0);
}

/*void	free_all(t_connect *c)
{
	if (c->i.forks)
		free(c->i.forks);
	if (c->p)
		free(c->p);
}*/

int	check_error(t_connect *c, int res)
{
	if (res == 1)
		printf("Аргументы братишка поправь.\n");
	else if (res == 2)
		printf("Память не была выделена.\n");
	else if (res == 3)
		printf("Ошибка инициализации mutex.\n");
	//free_all(c);
	return (1);
}

long long int	time_manager(void) // для вывода времени потоков
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_start(t_connect *c)
{
	int	i;

	i = 0;
	c->i.start_time = time_manager();

}

int main(int argc, char **argv)
{
	t_connect c;

	int	res;

	res = ft_initialize(&c, argc, argv);
	if (res)
		return (check_error(&c, res));
	ft_start(&c);
	return (0);
}