#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <semaphore.h>

typedef struct s_info
{
	int				num_philos;
	int				num_meals;
	int				time_eat;
	int				time_sleep;
	int				time_death;
	int				dead_body;
	long long int	time_start;
	sem_t	*forks;
	sem_t	*meal_check;
	sem_t	*write;
	sem_t	*death;
}	t_info;

typedef struct s_philo
{
	int				id;
	pid_t			id_process;
	int				r_fork;
	int				l_fork;
	int				count_meals;
	long long int	time_last_eat;
	t_info			*in;
}	t_philo;

typedef struct s_connect
{
	t_philo	*p;
	t_info	i;
}	t_connect;

#endif