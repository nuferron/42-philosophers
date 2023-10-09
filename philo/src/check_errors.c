/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:49:52 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/08 23:16:23 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*int	ft_atoi(char *str)
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
}*/

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

/*int	getting_input(int argc, char **argv)
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
}*/

int	getting_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
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
			return (-1);
	}
	return (0);
}

int	ft_errors(t_data *data, char *error, int flag)
{
	if (flag == 2)
		free(data->philo);
	printf("%s%s%s", RED, error, RESET);
	return (-1);
}
