#include "../philo.h"

int	getting_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->total);
	if (!philo)
		return (ft_errors(data, MEM));
	i = 0;
	while (i < data->total)
	{
		if (pthread_mutex_init(&philo[i].right, NULL) != 0)
			ft_errors(data, MUTEX);
		philo[i].meal_count = 0;
		philo[i].dead = 0;
		philo[i].name = i;
		philo[i].data = data;
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
	data->dead_philo = 0;
	if (argc == 6)
		data->total_meals = ft_atoi(argv[5]);
	else
		data->total_meals = -1;
	if (getting_philo(data) == -1)
		return (-1);
	return (0);
}

void	ft_usleep(int wait)
{
	long long int	start;

	start = get_time(0);
	while(1)
	{
		if (get_time(start) > (long long int) wait)
		{
			break ;
		}
	}
}
void	stiff_philo(t_philo *philo)
{
	if (philo->data->dead_philo)
		return ;
	philo->data->dead_philo = 1;
	printf("%sOh shit, philosopher %d is dead%s\n", WHITE, philo->name, RESET);
	return ;
}

int	nap_time(t_philo *philo)
{
	long long int	start;

	start = get_time(0);
	printf("%sPhilosopher %d is sleeping%s\n", BLUE, philo->name, RESET);
	ft_usleep(philo->data->tt_sleep);
	if (get_time(start) > philo->data->tt_die)
	{
		stiff_philo(philo);
		return (-1);
	}
	return (0);
}

void	lunch_time(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->right) == 0)
	{
		printf("\033[1;33mPhilosopher %d RIGHT fork\n\033[0m", philo->name);
	}
	if (pthread_mutex_lock(philo->left) == 0)
	{
		printf("\033[1;33mPhilosopher %d LEFT fork\n\033[0m", philo->name);
	}
	printf("%sPhilosopher %d is eating (%d)%s\n", GREEN, philo->name, philo->meal_count, RESET);
	ft_usleep(philo->data->tt_eat);
	pthread_mutex_unlock(&philo->right);
	pthread_mutex_unlock(philo->left);
	printf("\033[1;31mPhilosopher %d LEFT fork\n\033[0m", philo->name);
	printf("\033[1;31mPhilosopher %d RIGHT fork\n\033[0m", philo->name);
	philo->meal_count++;
	philo->last_meal = get_time(0);
}

void	*ft_loop(t_philo *philo)
{
	printf("loop name %d\n", philo->name);
	if (philo->name % 2 == 0)
		ft_usleep(philo->data->tt_eat);
	while (!philo->dead || (philo->data->total_meals && philo->meal_count < philo->data->total_meals))
	{
		lunch_time(philo);
		if (nap_time(philo) == -1)
		{
			return (NULL);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc < 5 || argc >= 7)
		return (ft_errors(&data, ARGS));
	if (getting_input(argc, argv) == -1)
		return (ft_errors(&data, INPUT));
	initializing_data(argc, argv, &data);
	i = 0;
	while (i < data.total)
	{
		if (pthread_create(&(data.philo[i].id), NULL, (void *)ft_loop, &data.philo[i]) != 0)
			return (ft_errors(&data, THREAD));
		i++;
	}
	while (--i >= 0)
	{
		pthread_join((data.philo[i].id), NULL);
	}
	return (0);
}
