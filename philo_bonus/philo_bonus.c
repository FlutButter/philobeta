#include "philo_bonus.h"

static int	ft_error_print(t_connect *c, int error)
{
	if (error == 0)
		printf("Неверное количество аргументов! Введите минимум 4.\n");
	else if (error == 1)
		printf("Некорректный вид аргумента!\n");
	else if (error == 2)
		printf("Ошибка при выделении памяти!\n");
	else if (error == 3)
		printf("Ошибка инициализации semaphore.\n");
	else if (error == 4)
		printf("Возникла ошибка при создании процессов.\n");
	if (error >= 2)
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
	if (create_process(&c))
		return (ft_error_print(&c, 4));
	return (0);
}