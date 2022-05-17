#include "philo_bonus.h"

void	philo_process(void *ptr)
{
	t_philo	*p;
	t_info	*i;

	p = (t_philo *)ptr;
	i = p->in;
	//to be continued
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
	shut_down(c);
	return (0);
}