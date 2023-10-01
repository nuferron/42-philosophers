#include "../philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	return (nb * neg);
}

int	getting_input(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (is_valid(argv[i]) == 0)
			i++;
		else
			return (-1);
	}
	return (0);
}

int	is_valid(char *str)
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

int	ft_errors(t_data *data, char *error)
{
	if (data->philo)
		free(data->philo);
	printf("%s\n", error);
	return (-1);
}
