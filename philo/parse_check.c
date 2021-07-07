#include "./philosophers.h"

int			error_throw(char *err_str)
{
	printf("Error: %s\n", err_str);
	return (1);
}

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
t_data			*parse_input(int ac, char **av)
{
	t_data		*data;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
		//return(error_throw("Memory allocation for data failed."));
	if (ac < 5 || ac > 6)
		return (NULL);
		//return(error_throw("Invalid amount of args."));
	data->n_philos = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->n_meals = -1;
	if (av[5])
	{
		data->n_meals = ft_atoi(av[5]);
		if (data->n_meals < 1)
			//return(error_throw("Number of meals must be a positive value."));
			return (NULL);
	}
	return (data);
}