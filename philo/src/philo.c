#include "../philo.h"

int	is_num(char	*str)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			str++;
		else
			return (-1);
	}
	return (0);
}

t_philo	*getting_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->philo);
	i = 0;
	while (i < data->philo)
	{
		philo[i].id = i;
		if (i == 0)
			philo[i].right = data->philo;
		else
			philo[i].right = philo[i].id - 1;
		philo[i].left = philo[i].id;
		philo[i].eat = 0;
		philo[i].dead = 0;
		i++;
	}
	return (philo);
}

t_philo	*initializing(int argc, char **argv, t_data *data)
{
	t_philo	*philo;

	data->philo = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_to_die = ft_atoi(argv[5]);
	else
		data->eat_to_die = -1;
	philo = getting_philo(data);
	return (philo);
}

int	getting_input(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (is_num(argv[i]) == 0)
			i++;
		else
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5 || argc >= 7)
		return (printf("Invalid number of arguments\n"));
	if (getting_input(argc, argv) == -1)
		return (printf("Invalid input\n"));
	philo = initializing(argc, argv, &data);
	printf("philo: %d\ndeath: %d\neat: %d\nsleep %d\nop: %d\n\n", data.philo, data.death, data.eat, data.sleep, data.eat_to_die);
	printf("id %d\nleft %d\nright %d\neat %d\ndead %d\n", philo[0].id, philo[0].left, philo[0].right, philo[0].eat, philo[0].dead);
}
