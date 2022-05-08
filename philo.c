#include "philo.h"

void	all_free(t_connect *c)
{
	if (c->p != NULL)
		free(c->p);
	if (c->i.forks != NULL)
		free(c->i.forks);
}

static int	ft_error_print(t_connect *c, int error)
{
	if (error == 0)
		printf("Неверное количество аргументов! Введите минимум 4.\n");
	else if (error == 1)
		printf("Некорректный вид аргумента!\n");
	else if (error == 2)
		printf("Ошибка при выделении памяти!\n");
	else if (error == 3)
		printf("Ошибка инициализации mutex.\n");
	else if (error == 4)
		printf("Не удалось создать поток.\n");
	if (error >= 2)
		all_free(c);
	return (1);
}

void	ft_shut_down(t_connect *c)
{
	int	j;

	j = -1;
	while(++j < c->i.num_philos)
		pthread_join(c->p[j].thread, NULL);
	if (c->i.all_wellfed == 1)
		printf("Все плотненько покушали\n");
	j = -1;
	while(++j < c->i.num_philos)
		pthread_mutex_destroy(&c->i.forks[j]);
	pthread_mutex_destroy(&c->i.meal_check);
	pthread_mutex_destroy(&c->i.write);
	pthread_mutex_destroy(&c->i.death);
	all_free(c);
}

int	main(int argc, char **argv)
{
	t_connect	c;
	int			res;

	res = 0;
	if (argc != 5 && argc != 6)
		return (ft_error_print(&c, 0));
	res = ft_initialize(&c, argc, argv);
	if (res)
		return (ft_error_print(&c, res));
	if (create_threads(&c))
		return (ft_error_print(&c, 4));
	return (0);
}
