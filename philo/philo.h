#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define MEM "Woops, it seems that malloc has gone on vacation 🏖"
# define MUTEX "Oh-oh, mutex is not having it..."
# define ARGS "Invalid number of arguments"
# define INPUT "Watch out! This input is wrong... 😩"
# define THREAD "Oh no! Threads were not created"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RESET "\033[0m"

typedef struct s_data
{
	int				total;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				total_meals;
	int				dead_philo;
	long long int	time;
	struct s_philo	*philo;
}				t_data;

typedef struct	s_philo
{
	int				name;
	int				eating;
	int				dead;
	int				asleep;
	int				meal_count;
	long long int	last_meal;
	pthread_t		id;
	pthread_mutex_t	*left;
	pthread_mutex_t	right;
	t_data			*data;
}				t_philo;

int	ft_atoi(char *str);
int	getting_input(int argc, char **argv);
int	is_valid(char *str);
int	ft_errors(t_data *data, char *error);

long long int	get_time( long long int flag);

#endif
