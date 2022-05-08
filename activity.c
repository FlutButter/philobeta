#include "philo.h"

void	ft_igestion(t_philo *p, t_info *i)
{
	pthread_mutex_lock(&(i->forks[p->l_fork]));
	ft_action_print(i, p->id, "взял левую вилку");
	pthread_mutex_lock(&(i->forks[p->r_fork]));
	ft_action_print(i, p->id, "взял правую вилку");
	pthread_mutex_lock(&(i->meal_check));
	ft_action_print(i, p->id, "ест");
	p->time_last_eat = time_manager();
	pthread_mutex_unlock(&(i->meal_check));
	ft_usleep(i->time_eat);
	pthread_mutex_lock(&(i->meal_check));
	p->count_meals++;
	pthread_mutex_unlock(&(i->meal_check));
	pthread_mutex_unlock(&(i->forks[p->l_fork]));
	pthread_mutex_unlock(&(i->forks[p->r_fork]));
}

void	*philo_thread(void *ptr)
{
	t_philo	*p;
	t_info	*i;

	p = (t_philo *)ptr;
	i = p->in;
	if (p->id % 2)
		usleep(10000);
	while (1)
	{
		pthread_mutex_lock(&(i->death));
		if (i->dead_body)
		{
			pthread_mutex_unlock(&(i->death));
			break ;
		}
		pthread_mutex_unlock(&(i->death));
		ft_igestion(p, i);
		pthread_mutex_lock(&(i->meal_check));
		if (i->all_wellfed)
		{
			pthread_mutex_unlock(&(i->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(i->meal_check));
		ft_action_print(i, p->id, "спит");
		ft_usleep(i->time_sleep);
		ft_action_print(i, p->id, "думает");
	}
	return (NULL);
}

int	ft_meals_check(t_connect *c)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&(c->i.meal_check));
	while (c->i.num_meals != -1 && j < c->i.num_philos
		&& c->p[j].count_meals >= c->i.num_meals)
			j++;
	if (j == c->i.num_philos)
	{
		c->i.all_wellfed = 1;
		pthread_mutex_unlock(&(c->i.meal_check));
		return (1);
	}
	pthread_mutex_unlock(&(c->i.meal_check));
	return (0);
}

void	pulse_monitor(t_connect *c)
{
	int	j;

	while(1)
	{
		j = -1;
		while (++j < c->i.num_philos)
		{
			pthread_mutex_lock(&(c->i.meal_check));
			if ((time_manager() - (c->p[j].time_last_eat)) > c->i.time_death)
			{
				ft_action_print(&c->i, j, "мертв");
				pthread_mutex_lock(&(c->i.death));
				c->i.dead_body = 1;
				pthread_mutex_unlock(&(c->i.death));
				pthread_mutex_unlock(&(c->i.meal_check));
				break ;
			}
			pthread_mutex_unlock(&(c->i.meal_check));
		}
		pthread_mutex_lock(&(c->i.death));
		if (c->i.dead_body)
		{
			pthread_mutex_unlock(&(c->i.death));
			break ;
		}
		pthread_mutex_unlock(&(c->i.death));
		if (ft_meals_check(c))
			break ;
	}
}

int	create_threads(t_connect *c)
{
	int	i;

	i = -1;
	c->i.time_start = time_manager();
	while (++i < c->i.num_philos)
	{
		c->p[i].in = &c->i;
		c->p[i].time_last_eat = time_manager();
		if (pthread_create(&(c->p[i].thread), NULL, philo_thread, &c->p[i]) != 0)
			return (1);
	}
	pulse_monitor(c);
	ft_shut_down(c);
	return (0);
}
