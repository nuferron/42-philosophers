#include "../philo.h"

int	getting_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->total);
	if (!philo)
		return (ft_errors(data, MEM));
	while (i < data->total)
	{
		if (pthread_mutex_init(&philo[i].right, NULL)
			|| pthread_mutex_init(&philo[i].mutex_last, NULL)
			|| pthread_mutex_init(&philo[i].mutex_count, NULL))
			ft_errors(data, MUTEX);
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
	data->total = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	data->time = get_time(0);
	data->dead = 0;
	if (pthread_mutex_init(&data->print, NULL) != 0)
		ft_errors(data, MUTEX);
	if (pthread_mutex_init(&data->mutex_dead, NULL) != 0)
		ft_errors(data, MUTEX);
	if (pthread_mutex_init(&data->mutex_meals, NULL) != 0)
		ft_errors(data, MUTEX);
	if (argc == 6 && ft_atoi(argv[5]) >= 0)
		data->t_meals = ft_atoi(argv[5]);
	else if (argc == 6)
		ft_errors(data, MEALS);
	else
		data->t_meals = -1;
	if (getting_philo(data) == -1)
		return (-1);
	return (0);
}

int	still_there(t_data *data, int i)
{
	static int	not_there = 0;

	if (not_there == data->total - 1)
		return (-1);
	if (!pthread_mutex_lock(&data->mutex_meals))
	{
		if (data->philo[i].meal_count == data->t_meals)
		{
			pthread_mutex_unlock(&data->mutex_meals);
			not_there++;
			return (0);
		}
	}
	return (1);
}

void	stiff_philo(t_data *data)
{
	int	i;

	while (!data->dead)
	{
		i = 0;
		while (i < data->total)
		{
			if (data->t_meals != -1 && !still_there(data, i))
			{
				i++;
				continue ;
			}
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
			}
			pthread_mutex_unlock(&data->philo[i].mutex_last);
			i++;
		}
	}
	return ;
}

void	print_msg(t_philo *philo, char *str, int event)
{
	if (pthread_mutex_lock(&philo->data->print) == 0)
	{
		if (event == FORKS)
			printf(YELLOW);
		if (event == EAT)
			printf(GREEN);
		if (event == SLEEP)
			printf(BLUE);
		if (event == THINK)
			printf(PURPLE);
		if (event == DIED)
			printf(WHITE);
		if (!philo->data->dead)
			printf("%lld %d %s", get_time(philo->data->time), philo->name, str);
		printf(RESET);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	nap_time(t_philo *philo)
{
	long long int	start;

	start = get_time(0);
	print_msg(philo, "is sleeping\n", SLEEP);
	ft_usleep(philo->data->tt_sleep);
}

void	lunch_time(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->right) == 0)
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

void	*ft_loop(t_philo *philo)
{
	if (philo->name % 2 == 0)
		ft_usleep(philo->data->tt_eat);
	while (!pthread_mutex_lock(&philo->data->mutex_dead) && printf("%d\n", philo->data->dead) && !philo->data->dead)
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
		printf("%sThis is philosopher %d\n", RED, philo->name);
		nap_time(philo);
		printf("%sI'm philosopher %d\n", RED, philo->name);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	printf("%sPhilosopher %d exits\n", PURPLE, philo->name);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	pthread_t	deads;

	if (argc < 5 || argc >= 7)
		return (printf(ARGS));
	if (getting_input(argc, argv) == -1)
		return (-1);
	initializing_data(argc, argv, &data);
	i = 0;
	while (i < data.total)
	{
		if (pthread_create(&(data.philo[i].id), NULL, (void *)ft_loop, &data.philo[i]) != 0)
			return (ft_errors(&data, THREAD));
		i++;
	}
	if (pthread_create(&deads, NULL, (void *)stiff_philo, &data) != 0)
		return (ft_errors(&data, THREAD));
	while (--i >= 0)
	{
		printf("\033[0mjoin i = %d\n", i);
		pthread_join(data.philo[i].id, NULL);
	}
	pthread_join(deads, NULL);
	return (0);
}
