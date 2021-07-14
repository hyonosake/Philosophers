#include "philosophers.h"

int	check_errors(t_table *table)
{
	if (table->data->t_eat < 0)
		return (int_error("Time to eat must be a positive value.", table));
	if (table->data->t_sleep < 0)
		return (int_error("Time to sleep must be a positive value.", table));
	if (table->data->t_die < 0)
		return (int_error("Time to live must be a positive value.", table));
	return (0);
}

t_data	*data_init(int ac, char **av, t_table **table)
{
	t_data	*data;

	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (null_error("Memory alloc for data failed.", *table));
	if (ac < 5 || ac > 6)
		return (null_error("N arguments is invalid.", *table));
	data->n_philos = atoi(av[1]);
	data->t_die = atoi(av[2]);
	data->t_eat = atoi(av[3]);
	data->t_sleep = atoi(av[4]);
	data->n_meals = 0;
	(*table)->data = data;
	if (av[5])
	{
		data->n_meals = atoi(av[5]);
		if (data->n_meals < 1)
			return (null_error("N meals must be more than 1.", *table));
	}
	if (check_errors(*table))
		return (NULL);
	return (data);
}

pthread_mutex_t	*forks_init(t_table *table)
{
	pthread_mutex_t	*forks;
	int				fork_size;
	int				i;

	fork_size = sizeof(pthread_mutex_t);
	forks = (pthread_mutex_t *)ft_calloc(fork_size, table->data->n_philos);
	if (!forks)
		return (null_error("Memory alloc for forks failed.", table));
	i = 0;
	pthread_mutex_init(&(table->print), NULL);
	while (i < table->data->n_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (null_error("Initializing forks failed.", table));
		++i;
	}
	return (forks);
}

t_philo	*philos_init(t_table *table, pthread_mutex_t *forks)
{
	t_philo			*philos;
	int				i;
	pthread_mutex_t	*threads;
	int				n_philos;

	n_philos = table->data->n_philos;
	i = 0;
	philos = (t_philo *)ft_calloc(sizeof(t_philo), n_philos);
	if (!philos)
		return (null_error("Memory alloc for philos failed", table));
	table->data->start_time = time_now();
	while (i < n_philos)
	{
		philos[i].data = *table->data;
		philos[i].pos = i + 1;
		philos[i].status = 0;
		philos[i].odd = (philos[i].pos % 2 == 1);
		philos[i].forks[0] = &forks[i];
		philos[i].forks[1] = &forks[(i + 1) % n_philos];
		philos[i].meals_done = 0;
		philos[i].print = &(table->print);
		++i;
	}
	return (philos);
}
