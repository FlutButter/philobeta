#include "philo.h"

void	ft_igestion(t_philo *p, t_info *i)
{
	pthread_mutex_lock(&i->forks[p->l_fork]);
	ft_action_print(i, p->id, "взял левую вилку");
	pthread_mutex_lock(&i->forks[p->r_fork]);
	ft_action_print(i, p->id, "взял правую вилку");
	pthread_mutex_lock(&i->meal_check);
	ft_action_print(i, p->id, "ест");
	p->time_last_eat = time_manager();
	pthread_mutex_unlock(&i->meal_check);
	ft_usleep(i->time_eat);
	p->count_meals++;
	pthread_mutex_lock(&i->forks[p->l_fork]);
	pthread_mutex_lock(&i->forks[p->r_fork]);
}

void	*philo_thread(void *ptr)
{
	t_philo	*p;
	t_info	*i;

	p = (t_philo *)ptr;
	i = p->in;
	if (p.id % 2)
		usleep(10000);
	while (!(c->i.dead_body))
	{
		ft_igestion(p, i);
		if (i->all_wellfed)
			break;
		ft_action_print(i, p->id, "спит");
		ft_usleep(i->time_sleep);
		ft_action_print(i, p->id, "думает");
	}
	return (NULL);
}

void	pulse_monitor(t_connect *c)
{
	while(!c->i.all_wellfed)
	{
		while(!(c->i.dead_body) && (++i < c->i.num_philos))
		{
			//проверка времени: если прошедшее время > время смерти = Х_Х
		}
		if (c->i.dead_body)
			break;
		//проверка что все поели 
	}
}

int	create_threads(t_connect *c)
{
	int	i;

	i = -1;
	while (++i < c->i.num_philos)
	{
		c->p[i].in = &c->i;
		if (pthread_create(&c->p[i].thread, NULL, philo_thread, &c->p[i]) != 0) //&c?
			return (1);
		c->p[i].time_last_eat = time_manager();
	}
	pulse_monitor(&c);
	ft_shut_down(&c);
	return (0);
}
