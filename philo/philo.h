#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int	philo;
	int	death;
	int	eat;
	int	sleep;
	int	eat_to_die;
}				t_data;

typedef struct s_philo
{
	int	id;
	int	left;
	int	right;
	int	eat;
	int	dead;
}			t_philo;

int	ft_atoi(char *str);

#endif
