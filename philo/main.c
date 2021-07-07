#include "philosophers.h"

int			main(int ac, char **av)
{
	// free needed //
	t_data	*data;
	t_philo	*philos;
	t_table	*dining;

	philos = NULL;
	data = NULL;
	dining = NULL;
	// 1. Data input + check
	//parse_input(ac, av, &data, &dining);
	if (parse_input(ac, av, &data, &dining))
		return (1);
	if (mutex_init(dining))
		return (1);
	if (philosophers_init(dining, &philos))
		return (1);
	if (run_threads(dining, philos))
		return (1);
	//free all vals
	return (0);
}