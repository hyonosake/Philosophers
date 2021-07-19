#include "philosophers.h"


int	run_forks(t_table *table, t_philo *philos)
{
	int				i;
	int				n_phil;
	int				pid_i;
	int				status;

	i = 0;
	n_phil = table->data->n_philos;
	sem_unlink("/dead");
	table->dead = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
	sem_wait(table->dead);
	while (i < n_phil)
	{
		(philos + i)->data = table->data;
		// philos[i].meals_done = 0;
		(philos + i)->dead = table->dead;
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			error_throw("Unable to create a fork", table);
		else if (philos[i].pid == 0)
		{
			process_routine((philos + i));
			//printf("Process %d exitedededed\n", getpid());
			exit(0);
		}
		++i;
		usleep(100);
	}
	usleep_timer(table->data->t_eat);
	if (pthread_create(&table->monitor, NULL, &supervise, (void *)table))
		error_throw("Failed to run philo monitor thread,", table);
	//printf("THREAD HELLO???\n");
	while (i)
	{
		waitpid(philos[i].pid, &status, 0);
		--i;
	}
	//printf("I'm here actually...\n");
	philo_finished(table);
	return (0);
}
void	*supervise(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	i = 0;
	sem_wait(table->dead);
	while(i < table->data->n_philos)
	{
		//printf("Woopsie\n");
		kill((table->philos+i)->pid, SIGTERM);
		++i;
	}
	exit(0);
	return (NULL);
}

int	philo_finished(t_table *table)
{
	//printf("Entered. Waiting for sem to open.\n");
	sem_wait(table->print);
	sem_wait(table->print);
	printf("\033[0;32m");
	printf("%lld Well, that was a torture for them anyway...\n",
		time_diff(table->philos->data->start_time));
	exit(0);
	return (FINISHED);
}
