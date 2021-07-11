#include "philosophers.h"

int	run_threads(t_table *table, t_philo *philos)
{
	int				i;
	int				n_phil;

	i = 0;
	n_phil = table->data->n_philos;
	table->data->start_time = time_now();

	while (i < n_phil)
	{
		philos[i].data.start_time = table->data->start_time;
		philos[i].last_meal = table->data->start_time;
		philos[i].data = *(table->data);
		philos[i].meals_done = 0;
		philos[i].status = START;
		if (pthread_create(&(philos[i].thread), NULL,
				&thread_routine, (void *)(&philos[i])))
			return (int_error("Failed to init pthread of a philo.", table));
		++i;
		//usleep(1);
	}
	usleep_timer(100);
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
			meals_done_flag *= (int)(philos[i].status);
			if (time_diff(philos[i].last_meal) > philos[i].data.t_die)
				return (philo_death(table, i));
			++i;
		}
		if (meals_done_flag)
			return (FINISHED);
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
