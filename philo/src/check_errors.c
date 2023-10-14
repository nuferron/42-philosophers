/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:49:52 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/14 21:06:07 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atol(char *str)
{
	int		i;
	long	num;
	int		neg;

	i = 0;
	num = 0;
	neg = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * neg);
}

int	getting_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid(argv[i]))
			return (-1);
		if (ft_atol(argv[i]) < 0 || ft_atol(argv[i]) > INT_MAX)
			return (-1);
		i++;
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
			return (0);
	}
	return (1);
}

int	ft_errors(t_data *data, char *error, int flag)
{
	if (flag == 2)
		free(data->philo);
	printf("%s%s%s", RED, error, RESET);
	return (-1);
}
