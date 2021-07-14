#include "philosophers.h"


void	do_work(void)
{
	printf("Hello from child!\n");
	sleep(1);
	exit(0);
}

int	run_forks(t_table *table, t_philo *philos)
{
	int				i;
	int				n_phil;
	int				pid_i;

	i = 0;
	n_phil = table->data->n_philos;
	while (i < n_phil)
	{
		philos[i].data = *(table->data);
		philos[i].meals_done = 0;
		if ((pid_i = fork()) < 0)
			error_throw("Fork error failed", table);
		else if (pid_i == 0)
		{
			philos[i].pid = pid_i;
			process_routine(&philos[i]);
			//do_work();
		}
		else
		{
			;
			//parent stuff for supervision
		}
		++i;
	}
	table->data->start_time = time_now();
	/* Wait for children to exit. */
	int status;
	pid_t pid;
	while (i > 0)
	{
		pid = wait(&status);
		printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
		--i;  // TODO(pts): Remove pid from the pids array.
	}
		//if (pthread_create(&(philos[i].thread), NULL,
		//		&thread_routine, (void *)(&philos[i])))
		//	return (int_error("Failed to init pthread of a philo.", table));
		++i;
		//usleep_timer(1);
	return (0);
}

//int	supervise(t_table *table, t_philo *philos)
//{
//	int				i;
//	int				meals_done_flag;

//	i = 0;
//	while (1)
//	{
//		meals_done_flag = 1;
//		while (i < table->data->n_philos)
//		{
//			meals_done_flag *= (int)(philos[i].status);
//			if (time_diff(philos[i].last_meal) > philos[i].data.t_die)
//				return (philo_death(table, i));
//			++i;
//		}
//		if (meals_done_flag)
//			return (FINISHED);
//		i = 0;
//		usleep(5);
//	}
//	return (0);
//}

//int	finish_thread_stuff(t_table *table)
//{
//	int				i;

//	i = 0;
//	pthread_mutex_destroy(&(table->print));
//	while (i < table->data->n_philos)
//	{
//		pthread_mutex_destroy(&(table->forks)[i]);
//		pthread_mutex_destroy(&(table->print));
//		pthread_join((table->philos)[i].thread, NULL);
//	}
//	return (0);
//}

//int	philo_death(t_table *table, int i)
//{
//	pthread_mutex_lock(&table->print);
//	printf("\033[0;31m");
//	printf("%lld %d just passed away...\n",
//		time_diff((table->philos)[i].data.start_time), i + 1);
//	return (DIEDED);
//}

//int	philo_finished(t_table *table)
//{
//	pthread_mutex_lock(&table->print);
//	printf("\033[0;32m");
//	printf("%lld Well, that was a torture for them anyway...\n",
//		time_diff((table->philos)[0].data.start_time));
//	return (FINISHED);
//}
