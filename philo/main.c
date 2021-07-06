#include "philosophers.h"

int			main(int ac, char **av)
{
	// free needed //
	t_data	*data;
	t_table	*dining;
	t_philo	*philosophers;

	dining->data = data;
	// 1. Data input + check
	if (parse_input(ac, av, data))
		return (1);
	// 2. Table with threads and mutexes
	if (create_table(dining))
		return (1);	
	// 3. Philos with pointers
	if (init_philosophers(dining, philosophers))
		return (1);
	if (run_threads(philosophers))
		return (1);	
	//free all vals
	return (0);
}