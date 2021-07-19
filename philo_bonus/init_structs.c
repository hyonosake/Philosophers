#include "philosophers.h"

int	check_errors(t_table *table)
{
	if (table->data->t_eat < 0)
		error_throw("Time to eat must be a positive value.", table);
	if (table->data->t_sleep < 0)
		error_throw("Time to sleep must be a positive value.", table);
	if (table->data->t_die < 0)
		error_throw("Time to live must be a positive value.", table);
	return (0);
}

t_data	*data_init(int ac, char **av, t_table **table)
{
	t_data	*data;

	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!data)
		error_throw("Memory alloc for data failed.", *table);
	if (ac < 5 || ac > 6)
		error_throw("N arguments is invalid.", *table);
	data->n_philos = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->n_meals = -1;
	(*table)->data = data;
	if (av[5])
	{
		data->n_meals = atoi(av[5]);
		if (data->n_meals < 1)
			error_throw("N meals must be more than 1.", *table);
	}
	if (check_errors(*table))
		return (NULL);
	return (data);
}

void				semaphores_init(t_table *table)
{
	int				fork_size;
	int				i;

	sem_unlink("/forks");
	sem_unlink("/print");
	//sem_unlink("/dead");
	table->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, table->data->n_philos);
	table->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	//table->dead = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
}

t_philo	*philos_init(t_table *table)
{
	t_philo			*philos;
	int				i;
	int				n_philos;

	n_philos = table->data->n_philos;
	i = 0;
	philos = (t_philo *)ft_calloc(sizeof(t_philo), n_philos);
	if (!philos)
		error_throw("Memory alloc for philos failed", table);
	table->data->start_time = time_now();
	while (i < n_philos)
	{
		philos[i].data = table->data;
		philos[i].print = table->print;
		philos[i].forks = table->forks;
		//philos[i].dead = table->dead;
		philos[i].pos = i + 1;
		philos[i].status = 0;
		philos[i].odd = (philos[i].pos % 2 == 1);
		philos[i].meals_done = 0;
		philos[i].status = START;
		++i;
	}
	return (philos);
}
