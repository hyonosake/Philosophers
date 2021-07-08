#include "./philosophers.h"

int			input_error_check(t_data *data)
{
	if (data->n_philos < 2)
		return(error_throw("Number of philos must be 2 or more."));
	if (data->t_eat < 0)
		return(error_throw("Time to eat must be a positive value."));
	if (data->t_sleep < 0)
		return(error_throw("Time to sleep must be a positive value."));
	if (data->t_die < 0)
		return(error_throw("Time to live (die) must be a positive value."));
	return (0);
}

int	parse_input_data(int ac, char **av, t_data **data)
{

	(*data = (t_data *)malloc(sizeof(t_data)));
	if (!(*data))
		return(error_throw("Memory allocation for data failed."));
	if (ac < 5 || ac > 6)
		return(error_throw("Invalid amount of args."));
	(*data)->n_philos = ft_atoi(av[1]);
	(*data)->t_die = ft_atoi(av[2]);
	(*data)->t_eat = ft_atoi(av[3]);
	(*data)->t_sleep = ft_atoi(av[4]);
	(*data)->n_meals = -1;
	if (av[5])
	{
		(*data)->n_meals = ft_atoi(av[5]);
		if ((*data)->n_meals < 1)
			return(error_throw("Number of meals must be a positive value."));
	}
	return (input_error_check(*data));
}

int			create_dining_table(t_table **dining, t_data *data)
{
	int		i;

	i = 0;
	(*dining = (t_table *)malloc(sizeof(t_table)));
	if (!(*dining))
		return(error_throw("Memory allocation for dining table failed."));
	
	(*dining)->data = data;
	(*dining)->philos =
	(t_philo *)malloc(sizeof(t_philo) * (*dining)->data->n_philos);
	((*dining)->philos)->last_meal = 1222;
	printf("LAST MEAL PLEASE %llu\n", ((*dining)->philos)->last_meal);
	if (!((*dining)->philos))
		return(error_throw("Memory allocation for philosophers failed."));
	while (i < (*dining)->data->n_philos)
	{
		(*dining)->philos[i].thread =
			(pthread_t *)malloc(sizeof(pthread_t));
		++i;;
	}
	(*dining)->status = 0;
	return (0);
}

int					mutex_init(t_table *dining, t_data *data)
{
	int				i;
	int				fork_size;

	i = 0;
	fork_size = sizeof(pthread_mutex_t);
	dining->forks = (pthread_mutex_t *)malloc(fork_size * data->n_philos);
	if (!dining->forks)
		return(error_throw("Memory allocation for forks(mutex) failed."));
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&dining->forks[i], NULL))
			return(error_throw("Initializing forks(mutex) failed."));
		++i;
	}
	return (0);
}
int				philosophers_init(t_philo *philos, t_data *data, t_table *dining)
{
	int 		i;

	i = 0;
	while (i < data->n_philos)
	{
		philos[i].rfork = &dining->forks[i];
		philos[i].lfork = &dining->forks[(i+1) % data->n_philos];
		philos[i].meals_done = 0;
		philos[i].status = 0;
		philos[i].pos = i + 1;
		philos[i].thread = (pthread_t *)malloc(sizeof(pthread_t));
		philos[i].t_die = dining->data->t_die;
		philos[i].t_eat = dining->data->t_eat;
		philos[i].t_sleep = dining->data->t_sleep;
		if (!(philos[i].thread))
			return(error_throw("Malloc for thread i failed."));
		printf("philo's %d forks are: |r %d| |l %d|\n",philos[i].pos, i, (i+1) % data->n_philos);
		++i;
	}
	return (0);
}