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
	if (parse_input_data(ac, av, &data))
		return (1);
	if (create_dining_table(&dining, data))
		return (1);
	if (mutex_init(dining, data))
		return (1);
	if (philosophers_init(dining->philos, data, dining))
		return (1);
	// print_dining_table(dining);
	printf(">???\n");
	if (run_threads(dining, &philos, data))
		return (1);
	//free all vals
	return (0);
}