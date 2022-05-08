#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				num_philos;
	int				num_meals;
	int				all_wellfed;
	int				time_eat;
	int				time_sleep;
	int				time_death;
	int				dead_body;
	long long int	time_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	write;
	pthread_mutex_t	death;

}	t_info;

typedef struct s_philo
{
	int				id;
	int				r_fork;
	int				l_fork;
	int				count_meals;
	long long int	time_last_eat;
	pthread_t		thread;
	t_info			*in;
}	t_philo;

typedef struct s_connect
{
	t_philo	*p;
	t_info	i;
}	t_connect;

int				ft_atoi_v2(char *str);
int				create_threads(t_connect *c);
int				ft_initialize(t_connect *c, int argc, char **argv);
void			all_free(t_connect *c);
void			ft_usleep(long long int	time);
int				ft_meals_check(t_connect *c);
void			*philo_thread(void *ptr);
void			pulse_monitor(t_connect *c);
void			ft_igestion(t_philo *p, t_info *i);
void			ft_shut_down(t_connect *c);
void			ft_action_print(t_info *i, int id, char *str);
long long int	time_manager(void);

#endif