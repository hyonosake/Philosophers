#include "./philosophers.h"

int			main(int ac, char **av)
{
	t_table	*dining;
	t_philo	*philos;
	t_data	*data;

	data = data_init(ac, av); // data
	if (!data)
		return (1);
	
	dining = dining_init(data); // dining + forks
	if (!dining)
		return (1);
	//dining->data = data;
	philos = philos_init(dining);
	if (!philos)
	{
		printf("GG\n");
		return (1);
	}
	dining->philos = philos; // philos + threads per philo
	if (!dining->philos)
		return (1);
	printf("he\n");
	start_threads(dining, philos);
	//while(status)
	return (0);
}

