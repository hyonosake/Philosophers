#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table			*table;
	int				res;
	int				i;
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
	i = 0;
	while (i < table->data->n_philos)
	{
		kill(table->philos[i].pid, SIGKILL);
		++i;
	}
	ft_free(table);
	return (res);
}
