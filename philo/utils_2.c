#include "philosophers.h"

uint64_t	time_diff(uint64_t timestamp)
{
	return (time_now() - timestamp);
}

void	usleep_timer(uint64_t mils_needed)
{
	uint64_t	start;

	start = time_now();
	while (time_diff(start) < mils_needed)
	{	
	}
}

void	ft_free(t_table *table)
{
	if (table)
	{
		if (table->data)
			free(table->data);
		if (table->forks)
			free(table->forks);
		if (table->philos)
			free(table->philos);
		free(table);
	}
}

int	philo_death(t_table *table, int i)
{
	pthread_mutex_lock(&table->print);
	printf("\033[0;31m");
	printf("%lld %d just passed away...\n",
		time_diff((table->philos)[i].data.start_time), i + 1);
	return (DIEDED);
}

int	philo_finished(t_table *table)
{
	pthread_mutex_lock(&table->print);
	printf("\033[0;32m");
	printf("%lld Well, that was a torture for them anyway...\n",
		time_diff((table->philos)[0].data.start_time));
	return (FINISHED);
}
