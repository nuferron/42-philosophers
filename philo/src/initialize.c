/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:06:22 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/14 17:06:27 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	getting_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->total);
	if (!philo)
		return (ft_errors(data, MEM, 2));
	while (i < data->total)
	{
		if (pthread_mutex_init(&philo[i].right, NULL)
			|| pthread_mutex_init(&philo[i].mutex_last, NULL)
			|| pthread_mutex_init(&philo[i].mutex_count, NULL))
			return (ft_errors(data, MUTEX, 2));
		philo[i].meal_count = 0;
		philo[i].dead = 0;
		philo[i].name = i;
		philo[i].data = data;
		philo[i].last_meal = get_time(0);
		if (i > 0)
			philo[i].left = &philo[i - 1].right;
		i++;
	}
	philo[0].left = &philo[data->total - 1].right;
	data->philo = philo;
	return (0);
}

int	initializing_data(int argc, char **argv, t_data *data)
{
	data->total = ft_atol(argv[1]);
	if (data->total == 0)
		return (ft_errors(data, PHILO, 1));
	data->tt_die = ft_atol(argv[2]);
	data->tt_eat = ft_atol(argv[3]);
	data->tt_sleep = ft_atol(argv[4]);
	data->time = get_time(0);
	data->dead = 0;
	if (pthread_mutex_init(&data->print, NULL) != 0)
		ft_errors(data, MUTEX, 1);
	if (pthread_mutex_init(&data->mutex_dead, NULL) != 0)
		ft_errors(data, MUTEX, 1);
	if (pthread_mutex_init(&data->mutex_meals, NULL) != 0)
		ft_errors(data, MUTEX, 1);
	if (argc == 6 && ft_atol(argv[5]) >= 0)
		data->t_meals = ft_atol(argv[5]);
	else if (argc == 6)
		ft_errors(data, MEALS, 1);
	else
		data->t_meals = -1;
	if (getting_philo(data) == -1)
		return (-1);
	return (0);
}
