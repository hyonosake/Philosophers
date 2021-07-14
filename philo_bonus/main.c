#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table			*table;
	int				res;

	table = (t_table *)ft_calloc(sizeof(t_table), 1);
	if (!table)
		return (1);
	if (!data_init(ac, av, &table))
		return (1);
	semaphores_init(table);
	if (!table->forks)
		return (1);
	table->philos = philos_init(table);
	if (!(table->philos))
		return (1);
	res = run_forks(table, table->philos);
	ft_free(table);
	return (res);
}
