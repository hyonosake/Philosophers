#include "philosophers.h"

int			main(int ac, char **av)
{
	// free needed //
	t_data	*data;
	t_table	*dining;
	t_philo	*philosophers;

	philosophers = NULL;
	data = NULL;
	dining = NULL;
	// 1. Data input + check
	data = parse_input(ac, av);
	//if (parse_input(ac, av, &data))
	//	return (1);
	printf("---main---\n");
	printf("n_phil %d\n",data->n_philos);
	printf("t_die %d\n", data->t_die);
	// 2. Table with threads and mutexes
	dining = create_table(data);
	//if (create_table(&dining, data))
	//	return (1);	
	//dining->data = data;
	// 3. Philos with pointers
	philosophers = init_philosophers(dining);
	//if (init_philosophers(dining, &philosophers))
	//	return (1);
	if (run_threads(philosophers))
		return (1);
	//free all vals
	return (0);
}