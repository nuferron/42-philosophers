#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define MEM	"Woops, it seems that malloc has gone on vacation 🏖\n"
# define MUTEX	"Oh-oh, mutex is not having it...\n"
# define ARGS	"Invalid number of arguments\n"
# define INPUT	"Watch out! This input is wrong... 😩\n"
# define THREAD	"Oh no! Threads were not created\n"
# define MEALS	"Do you want them to throw up?\n"

# define FORKS	1
# define EAT	2
# define SLEEP	3
# define THINK	4
# define DIED	5

# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define PURPLE	"\033[1;35m"
# define CYAN	"\033[1;36m"
# define WHITE	"\033[1;37m"
# define RESET	"\033[0m"

typedef struct s_data
{
	int				total;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				t_meals;
	int				dead;
	long long int	time;
	struct s_philo	*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_meals;
	pthread_mutex_t	mutex_dead;
}	t_data;

typedef struct s_philo
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
	pthread_mutex_t	mutex_last;
	pthread_mutex_t	mutex_count;
	t_data			*data;
}	t_philo;

int				ft_atoi(char *str);
int				getting_input(int argc, char **argv);
int				is_valid(char *str);
int				ft_errors(t_data *data, char *error);

long long int	get_time(long long int flag);
void			ft_usleep(int wait);

void			print_msg(t_philo *philo, char *str, int event);

#endif
