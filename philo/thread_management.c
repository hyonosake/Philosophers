#include "./philosophers.h"


t_philo		*init_philosophers(t_table *dining)
{
	int 		i;
	t_philo		*philos;
	i = 0;
	philos = (t_philo *)calloc(sizeof(t_philo), dining->data->n_philos);
	if (!philos)
		//return(error_throw("Memory allocation for philos failed."));
		return NULL;
	philos->table = dining;
	while(i < dining->data->n_philos)
	{
		philos[i].rfork = &dining->forks[i];
		philos[i].lfork = &dining->forks[(i+1) % dining->data->n_philos];
		philos[i].meals_done = 0;
		philos[i].status = 0;
		philos[i].pos = i + 1;
		printf("philo's %d forks are: |r %d| |l %d|\n",philos[i].pos, i, (i+1) % dining->data->n_philos);
		++i;
	}
	return (philos);
}

void			*monitor_death(void *arg)
{
	int			i;
	char		flag;
	t_philo		*philos;

	philos = (t_philo *)arg;
	while(1)
	{
		i = 0;
		while (i < philos->table->data->n_philos)
		{
			if (time_diff(philos[i].last_meal, get_time()) > (uint64_t)philos->table->data->t_die)
			{
				flag = 1;
				philos[i].status = DIEDED;
				break ;
			}
			++i;
		}
		if (philos[i].status == DIEDED)
		{
			printf("%llu Philosopher %d is dieded\n", get_time() - philos->table->start_time, philos[i].pos);
			break ;
		}
	}
	return (NULL);
}

int				run_threads(t_philo *philos)
{
	pthread_t	supervisor;
	int			i;

	i = 0;
	//printf("pos = %d\n", philos->pos);
	philos->table->start_time = get_time();
	while (i < philos->table->data->n_philos)
	{
		philos[i].last_meal = philos->table->start_time;
		printf("here %d\n", i+1);
		if (pthread_create(&philos->table->threads[i], 
			NULL, &thread_routine, (void *)(&philos[i])))
			return(error_throw("Philosopher threads were not created."));
		i++;
		//usleep(1);
		printf("after here\n");
	}
	usleep(100);
	printf("after here\n");
	if (pthread_create(&supervisor, NULL, &monitor_death, (void *)philos))
		return(error_throw("Supervisor thread was not created."));
	monitor_death(philos);
	return (0);
}
void	 take_forks(t_philo *philo)
{
	uint64_t	timestamp;
	
	//printf("hee\n");
	timestamp = time_diff(philo->table->start_time, get_time());
	//printf("%llu is\n", timestamp);
	//printf("%llu starttime\n", philo->table->start_time);
	if (philo->pos % 2 == 1)
	{
		pthread_mutex_lock(philo->lfork);
		printf("%llu Philosopher %d has taken his left fork\n", timestamp, philo->pos);
		pthread_mutex_lock(philo->rfork);
		printf("%llu Philosopher %d has taken his right fork \n", timestamp, philo->pos);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		printf("%llu Philosopher %d has taken his right fork \n", timestamp, philo->pos);
		pthread_mutex_lock(philo->lfork);
		printf("%llu Philosopher %d has taken his left fork\n", timestamp, philo->pos);
	}
}




void 	msg_display(uint64_t timestamp, int number, char status)
{
	//if (status == TOOK_FORKS)
	//	printf("%lu Philosopher %d took %dfork\n")
	if (status == EAT)
		printf("%llu Philosopher %d is eating\n", timestamp, number);
	else if (status == SLEEP)
		printf("%llu Philosopher %d is sleeping\n", timestamp, number);
	else if (status == THINK)
		printf("%llu Philosopher %d is thinking\n", timestamp, number);
	else if (status == DIEDED)
		printf("%llu Philosopher %d is dead\n", timestamp, number);

}

void		*thread_routine(void *arg)
{
	t_philo	*philosopher;
	//uint64_t	cycle;
	uint64_t	sleeping;
	philosopher = (t_philo *)arg;
	while (1)
	{
		//if (time_diff(philosopher->last_meal, get_time()) > (uint64_t)philosopher->table->data->t_die)
		//	philosopher->status = DIEDED;
		take_forks(philosopher);
		philosopher->last_meal = get_time();
		printf("%llu Philosopher %d is eating\n", get_time() - philosopher->table->start_time, philosopher->pos);     
		while (time_diff(philosopher->last_meal, get_time()) < (uint64_t)philosopher->table->data->t_sleep)
		{
		}
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
		//cycle = get_time() - philosopher->table->start_time;
		//philosopher->status = SLEEP;
		printf("%llu Philosopher %d is sleeping\n", get_time() - philosopher->table->start_time, philosopher->pos);
		printf("seg");
		sleeping = get_time();
		while (time_diff(sleeping, get_time()) < (uint64_t)philosopher->table->data->t_sleep)
		{
		}
	}
	return (NULL);
}