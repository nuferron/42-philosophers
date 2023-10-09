/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:10:01 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/08 22:49:44 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long int	get_time(long long int flag)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (flag == 0)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - flag);
}

void	ft_usleep(int wait)
{
	long long int	start;

	start = get_time(0);
	while (1)
	{
		if (get_time(start) >= (long long int) wait)
		{
			break ;
		}
		usleep(100);
	}
}
