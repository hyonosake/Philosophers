#include "philosophers.h"

int	run_threads(t_table *table, t_philo *philos)
{
	int				i;
	int				n_phil;

	i = 0;
	n_phil = table->data->n_philos;
	while (i < n_phil)
	{
		if (pthread_create(&(philos[i].thread), NULL,
				&thread_routine, (void *)(&philos[i])))
			return (int_error("Failed to init pthread of a philo.", table));
		++i;
	}
	table->data->start_time = philos[0].data.start_time;
	usleep_timer(50);
	return (supervise(table, table->philos));
}

int	supervise(t_table *table, t_philo *philos)
{
	int				i;
	int				meals_done_flag;

	i = 0;
	while (1)
	{
		meals_done_flag = 1;
		while (i < table->data->n_philos)
		{
			meals_done_flag *= philos[i].status;
			if (time_diff(philos[i].last_meal) > philos[i].data.t_die)
				return (philo_death(table, i));
			++i;
			if (philos[i].status == FINISHED)
				return(philo_finished(table));
		}
		i = 0;
	}
	return (0);
}

int	finish_thread_stuff(t_table *table)
{
	int				i;

	i = 0;
	pthread_mutex_destroy(&(table->print));
	while (i < table->data->n_philos)
	{
		pthread_mutex_destroy(&(table->forks)[i]);
		pthread_mutex_destroy(&(table->print));
		pthread_join((table->philos)[i].thread, NULL);
	}
	return (0);
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
