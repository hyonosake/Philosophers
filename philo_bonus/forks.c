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
	table->data->start_time = time_now();
	while (i < n_phil)
	{
		(philos + i)->data = table->data;
		philos[i].meals_done = 0;
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			error_throw("Failed to fork.", table);
		else if (!philos[i].pid)
		{
			printf("Gone in routine, bruh\n");
			process_routine(&(philos[i]));
			exit(0);
		}
		usleep(100);
		++i;
	}

	usleep(1000);
	//return (supervise(table, table->philos));
	return (0);
}

int	supervise(t_table *table, t_philo *philos)
{
	int				i;
	int				meals_done_flag;

	i = 0;
	while (1)
	{
		sem_wait(table->dead);
		sem_wait(table->print);
		printf("\033[0;31m");
		printf("%lld Someone just passed away...\n",
		time_diff((table->philos + i)->data->start_time));
		break ;
	}
	return (0);
}

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

int	philo_death(t_table *table, int i)
{
	sem_wait(table->forks);
	printf("\033[0;31m");
	printf("%lld %d just passed away...\n",
		time_diff((table->philos + i)->data->start_time), i + 1);
	return (DIEDED);
}

//int	philo_finished(t_table *table)
//{
//	pthread_mutex_lock(&table->print);
//	printf("\033[0;32m");
//	printf("%lld Well, that was a torture for them anyway...\n",
//		time_diff((table->philos)[0].data.start_time));
//	return (FINISHED);
//}