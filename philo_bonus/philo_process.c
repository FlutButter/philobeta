#include "philo_bonus.h"

void	*pulse_monitor(void *ptr)
{
	t_philo	*p;
	t_info	*i;

	p = (t_philo *)ptr;
	i = p->in;
	pthread_detach(i->death);
	while (1)
	{
		sem_wait(i->meal_check)
		if (time_manager() - (p->time_last_eat)) > i->time_death)
		{
			ft_action_print(r, p->id, "Андрюха у нас труп, возможно криминал");
			i->dead_body = 1;
			sem_wait(i->write);
		}
		sem_post(i->meal_check);
		if (i->dead_body)
			break ;
		if (p->count_meals >= i->num_meals && i->num_meals != -1)
			break ;
	}
	return (NULL);
}

void	ft_igestion(t_philo *p, t_info *i)
{
	sem_wait(i->forks);
	ft_action_print(i, p->id, "взял вилку");
	sem_wait(i->forks);
	ft_action_print(i, p->id, "взял вилку");
	sem_wait(i->meal_check);
	ft_action_print(i, p->id, "ест");
	p->time_last_eat = time_manager();
	sem_post(i->meal_check);
	ft_usleep(i, i->time_eat);
	sem_wait(i->meal_check);
	p->count_meals++;
	sem_post(i->meal_check);
	sem_post(i->forks);
	sem_post(i->forks);
}

void	philo_process(void *ptr)
{
	t_philo	*p;
	t_info	*i;

	p = (t_philo *)ptr;
	i = p->in;
	if (pthread_create(&p->death, NULL, pulse_monitor, ptr) != 0)
		exit(1);
	if (p->id % 2)
		usleep(10000);
	while (1)
	{
		if (i->dead_body)
			break ;
		ft_igestion(p, i);
		if (p->count_meals >= i->num_meals && i->num_meals != -1)
			break ;
		ft_action_print(i, p->id, "спит");
		ft_usleep(i, i->time_sleep);
		ft_action_print(i, p->id, "думает");
	}
	if (i->dead_body)
		exit(1);
	exit(0);
}

void	ft_shut_down(t_connect *c)
{
	int	j;
	int status;

	j = -1;
	while (++j < c->i.num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			j = -1;
			while (++j < c->i.num_philos)
				kill(c->p[j].id_process,);
			break ;
		}
	}
	sem_close(c->i.forks);
	sem_close(c->i.write);
	sem_close(c->i.meal_check);
	sem_unlink("/p_forks");
	sem_unlink("/p_write");
	sem_unlink("/p_meal_check");
	if (c->p)
		free(c->p);
}

int	create_process(t_connect *c)
{
	int	j;

	j = -1;
	c->i.time_start = time_manager();
	while (++j < c->i.num_philos)
	{
		c->p[j].in = &c->i;
		c->p[j].id_process = fork();
		if (c->p[j].id_process < 0)
			return(1);
		if (c->p[j].id_process == 0)
			philo_process(&c->p[j]);
	}
	ft_shut_down(c);
	return (0);
}