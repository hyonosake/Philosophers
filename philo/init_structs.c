#include "philosophers.h"


int			check_data(t_data *data)
{
	if (data->n_philos < 2)
	{
		free(data);
		return(error_int("Number of philos must be 2 or more.", data));
	}
	if (data->t_eat < 0)
	{
		free(data);
		return(error_int("Time to eat must be a positive value.", data));
	}
	if (data->t_sleep < 0)
	{
		free(data);
		return(error_int("Time to sleep must be a positive value.", data));
	}
	if (data->t_die < 0)
	{
		free(data);
		return(error_int("Time to live (die) must be a positive value.", data));
	}
	return (0);
}

t_data		*data_init(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (error_null("Invalid amount of args\n", NULL));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_philos = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->n_meals = -1;
	if (av[5])
	{
		data->n_meals = ft_atoi(av[5]);
		if (data->n_meals < 1)
		{
			free(data);
			return(error_null("Number of meals must be a positive value.\n", NULL));
		}
	}
	if (check_data(data))
		return (NULL);
	return (data);
}

t_table		*dining_init(t_data *data)
{
	t_table *dining;
	int		size_fork;
	int		i;
	size_fork = sizeof(pthread_mutex_t);
	dining = (t_table *)malloc(sizeof(t_table));
	if (!dining)
		return (NULL);
	dining->data = data;
	dining->forks = (pthread_mutex_t *)malloc(sizeof(size_fork * data->n_philos));
	if (!dining->forks)
		return(error_null("Memory alloc for dining failed\n", dining));
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&(dining->forks[i]), NULL))
			return(error_null("Mutex init failed.\n", dining));
		++i;
	}
	return (dining);
}

t_philo		*philos_init(t_table *dining)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * dining->data->n_philos);
	if (!philo)
		error_null("Memory alloc for philos failed.\n", dining);
	while (i < dining->data->n_philos)
	{
		philo[i].data = *(dining->data);
		philo[i].rfork = &(dining->forks[i]);
		philo[i].lfork = &(dining->forks[(i + 1) % dining->data->n_philos]);
		philo[i].pos = i + 1;
		philo[i].thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philo[i].thread)
			return (error_null("Memory alloc for dining failed\n", dining));
		philo[i].meals_done = 0;
		philo[i].status = 0;
		++i;
	}
	return (philo);
}

