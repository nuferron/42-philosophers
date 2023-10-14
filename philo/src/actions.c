/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:20:56 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/14 17:09:52 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lunch_time(t_philo *philo)
{
	if (print_msg(philo, "is thinking\n", THINK)
		&& pthread_mutex_lock(&philo->right) == 0)
		print_msg(philo, "has taken a fork\n", FORKS);
	if (pthread_mutex_lock(philo->left) == 0)
		print_msg(philo, "has taken a fork\n", FORKS);
	print_msg(philo, "is eating\n", EAT);
	if (!pthread_mutex_lock(&philo->mutex_last))
		philo->last_meal = get_time(0);
	pthread_mutex_unlock(&philo->mutex_last);
	if (!pthread_mutex_lock(&philo->mutex_count))
		philo->meal_count++;
	pthread_mutex_unlock(&philo->mutex_count);
	ft_usleep(philo->data->tt_eat);
	pthread_mutex_unlock(&philo->right);
	pthread_mutex_unlock(philo->left);
}

void	nap_time(t_philo *philo)
{
	long long int	start;

	start = get_time(0);
	print_msg(philo, "is sleeping\n", SLEEP);
	ft_usleep(philo->data->tt_sleep);
}

int	still_there(t_data *data, int i)
{
	static int	not_there = 0;

	if (not_there == data->total - 1)
		return (-1);
	if (!pthread_mutex_lock(&data->mutex_meals))
	{
		if (!pthread_mutex_lock(&data->philo[i].mutex_count)
			&& data->philo[i].meal_count == data->t_meals)
		{
			pthread_mutex_unlock(&data->mutex_meals);
			pthread_mutex_unlock(&data->philo[i].mutex_count);
			not_there++;
			return (0);
		}
	}
	pthread_mutex_unlock(&data->mutex_meals);
	pthread_mutex_unlock(&data->philo[i].mutex_count);
	return (1);
}

void	stiff_philo(t_data *data)
{
	int	i;

	while (!pthread_mutex_lock(&data->mutex_dead) && !data->dead)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		i = 0;
		while (i < data->total)
		{
			if (data->t_meals != -1 && still_there(data, i) == -1)
				return ;
			if (pthread_mutex_lock(&data->philo[i].mutex_last) == 0)
			{
				if (get_time(data->philo[i].last_meal) > data->tt_die)
				{
					print_msg(&data->philo[i], "died\n", DIED);
					data->dead = 1;
					break ;
				}
				pthread_mutex_unlock(&data->philo[i++].mutex_last);
			}
		}
	}
	pthread_mutex_unlock(&data->philo[i].mutex_last);
	pthread_mutex_unlock(&data->mutex_dead);
}
