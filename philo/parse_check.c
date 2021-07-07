#include "./philosophers.h"

int			error_throw(char *err_str)
{
	printf("Error: %s\n", err_str);
	return (1);
}

int			input_error_check(t_table *dining)
{
	printf("hello\n");
	if (dining->n_philos < 2)
		return(error_throw("Number of philos must be 2 or more."));
	if (dining->data->t_eat < 0)
		return(error_throw("Time to eat must be a positive value."));
	printf("dinner time! n philos = %d\n", dining->n_philos);
	if (dining->data->t_sleep < 0)
		return(error_throw("Time to sleep must be a positive value."));
	if (dining->data->t_die < 0)
		return(error_throw("Time to live (die) must be a positive value."));
	return (0);
}
int			parse_input(int ac, char **av, t_data **data, t_table **dining)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
		return(error_throw("Memory allocation for data failed."));
	(*dining) = (t_table *)malloc(sizeof(t_table));
	if (!(*data))
		return(error_throw("Memory allocation for dining table failed."));
	if (ac < 5 || ac > 6)
		return(error_throw("Invalid amount of args."));
	(*dining)->n_philos = ft_atoi(av[1]);
	(*data)->t_die = ft_atoi(av[2]);
	(*data)->t_eat = ft_atoi(av[3]);
	printf("Eat = %d\n", (*data)->t_eat);
	(*data)->t_sleep = ft_atoi(av[4]);
	(*dining)->n_meals = -1;
	if (av[5])
	{
		(*dining)->n_meals = ft_atoi(av[5]);
		if ((*dining)->n_meals < 1)
			return(error_throw("Number of meals must be a positive value."));
	}
	(*dining)->data = *data;
	return (input_error_check(*dining));
}