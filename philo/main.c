#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table			*table;
	int				res;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (!data_init(ac, av, &table))
		return (1);
	table->forks = forks_init(table);
	if (!table->forks)
		return (1);
	table->philos = philos_init(table, table->forks);
	if (!(table->philos))
		return (1);
	res = run_threads(table, table->philos);
	ft_free(table);
	return (res);
}
