#include "philo.h"

void	all_free(t_connect *c)
{
	if (c->p != NULL)
		free(c->p);
	/*if (c->i.forks != NULL)
		free(c->i.forks);*/
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
	all_free(c);
	return (1);
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
