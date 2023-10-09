/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:58:55 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/08 23:20:43 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_msg(t_philo *philo, char *str, int event)
{
	if (!pthread_mutex_lock(&philo->data->print))
	{
		if (event == FORKS)
			printf(CYAN);
		if (event == EAT)
			printf(GREEN);
		if (event == SLEEP)
			printf(BLUE);
		if (event == THINK)
			printf(YELLOW);
		if (event == DIED)
			printf(WHITE);
		if (!philo->data->dead)
			printf("%lld ms\t%d\t%s", get_time(philo->data->time), \
					philo->name, str);
		printf(RESET);
	}
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}

void	*ft_loop(t_philo *philo)
{
	if (philo->name % 2 == 0)
		ft_usleep(60);
	while (!pthread_mutex_lock(&philo->data->mutex_dead) && !philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		lunch_time(philo);
		if (!pthread_mutex_lock(&philo->data->mutex_meals))
		{
			if (philo->meal_count == philo->data->t_meals)
			{
				pthread_mutex_unlock(&philo->data->mutex_meals);
				break ;
			}
		}
		pthread_mutex_unlock(&philo->data->mutex_meals);
		nap_time(philo);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	return (NULL);
}

void	*just_one(t_philo *philo)
{
	printf("%s%lld ms\t%d\t", YELLOW, get_time(philo->data->time), philo->name);
	if (!pthread_mutex_lock(&philo->right))
		printf("has taken a fork\n%s", RESET);
	pthread_mutex_unlock(&philo->right);
	ft_usleep(philo->data->tt_die);
	printf("%s%lld ms\t%d\t", WHITE, get_time(philo->data->time), philo->name);
	printf("has died\n%s", RESET);
	return (NULL);
}

void	ft_threads(t_data *data)
{
	int			i;
	pthread_t	deads;

	i = 0;
	while (i < data->total)
	{
		if (pthread_create(&data->philo[i].id, NULL, \
					(void *)ft_loop, &data->philo[i]))
		{
			ft_errors(data, THREAD, 1);
			return ;
		}
		i++;
	}
	if (pthread_create(&deads, NULL, (void *)stiff_philo, data) != 0)
	{
		ft_errors(data, THREAD, 1);
		return ;
	}
	while (--i >= 0)
		pthread_join(data->philo[i].id, NULL);
	pthread_join(deads, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc >= 7)
		return (ft_errors(&data, ARGS, 1));
	if (getting_input(argc, argv) == -1)
		return (ft_errors(&data, INPUT, 1));
	initializing_data(argc, argv, &data);
	if (data.total == 1)
	{
		if (pthread_create(&(data.philo[0].id), NULL, \
					(void *)just_one, &data.philo[0]))
			return (ft_errors(&data, THREAD, 1));
		pthread_join(data.philo[0].id, NULL);
		return (0);
	}
	ft_threads(&data);
	return (0);
}
