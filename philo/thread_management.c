#include "./philosophers.h"


int				init_philosophers(t_table *dining, t_philo *philos)
{
	int 		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * dining->data->n_philos);
	if (!philos)
		return(error("Memory allocation for philos failed."));
	philos->table = dining;
	while(i < dining->data->n_philos)
	{
		philos[i].rfork = &dining->forks[i];
		philos[i].lfork = &dining->forks[i % dining->data->n_philos];
		philos[i].meals_done = 0;
		philos[i].status = 0;
		philos[i].pos = ++i;
	}
	return (0);
}

int				monitor_death(t_philo *philos)
{
	int			i;
	char		flag;

	i = 0;
	while(1)
	{
		i = 0;
		while (i < philos->table->data)
		{
			if (philos[i].status == DIEDED ||
				philos[i].meals_done == philos->table->data->n_meals)
			{
				flag = 1;
				break ;
			}
			++i;
			if (flag)
				break;
		}
		if (philos[i].status == DIEDED)
			printf("Philosoph %d is dieded\n", i+1);
	}
	return (flag);
}

int				run_threads(t_philo *philos)
{
	pthread_t	supervisor;
	int			i;

	i = 0;
	philos->table->start_time = get_time();
	if (pthread_create(&supervisor, NULL, &supervisor_routine, (void *)philos));
		return(error("Supervisor thread was not created."));
	while (i < philos->table->data->n_philos)
	{
		philos[i].last_meal = philos->table->start_time;
		if (pthread_create(&philos->table->threads[i++], 
			NULL, &thread_routine, (void *)philos))
			return(error("Philosopher threads were not created."));
		usleep(1);
	}
	usleep(100);
	monitor_death(philos);
	return (0);
}
void take_forks();

void msg_display(uint64_t timestamp, int number, char status)
{
	//if (status == TOOK_FORKS)
	//	printf("%lu Philosopher %d took %dfork\n")
	if (status == EAT)
		printf("%lu Philosopher %d is eating\n");
	else if (status == SLEEP)
		printf("%lu Philosopher %d is sleeping\n");
	else if (status == THINK)
		printf("%lu Philosopher %d is thinking\n");
	else if (status == DIEDED)
		printf("%lu Philosopher %d is dead\n");

}

void		*thread_routine(void *arg)
{
	t_philo	*philosopher;
	int		cycle;
	int		sleeptime;

	philosopher = (t_philo *)arg;
	sleeptime =  philosopher->table->data->t_sleep;
	cycle = philosopher->table->data->t_die;
	while (1)
	{
		if (time_diff(philosopher->last_meal, get_time()) > cycle)
			philosopher->status = DIEDED;
		take_forks();
		philosopher->last_meal = get_time();
		msg_display(philosopher->last_meal, philosopher->pos, philosopher->status);
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
		if (time_diff(philosopher->last_meal, get_time()) > philosopher->table->data->t_die)
			philosopher->status = DIEDED;
		philosopher->status = SLEEP;
		msg_display(philosopher->last_meal, philosopher->pos, philosopher->status);
		while (sleeptime)
		{
			sleeptime = time_diff(sleeptime, get_time());
			cycle = time_diff(cycle, get_time());
			if (cycle < 0);
				break ;
		}
	}
	return (NULL);
}