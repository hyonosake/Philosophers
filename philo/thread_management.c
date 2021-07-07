#include "./philosophers.h"


int				philosophers_init(t_table *dining, t_philo **philos)
{
	int 		i;
	i = 0;
	*philos = (t_philo *)malloc(sizeof(t_philo) * dining->n_philos);
	if (!*philos)
		return(error_throw("Memory allocation for philos failed."));
	while(i < dining->n_philos)
	{
		(*philos)->data = dining->data;
		(*philos)[i].rfork = &dining->forks[i];
		(*philos)[i].lfork = &dining->forks[(i+1) % dining->n_philos];
		(*philos)[i].meals_done = 0;
		(*philos)[i].status = 0;
		(*philos)[i].pos = i + 1;
		((*philos)[i]).thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!((*philos)[i]).thread)
			return(error_throw("Malloc for thread i failed."));
		printf("philo's %d forks are: |r %d| |l %d|\n",(*philos)[i].pos, i, (i+1) % dining->n_philos);
		++i;
	}
	return (0);
}

void			*monitor_death(void *arg)
{
	int			i;
	char		flag;
	t_table		*dining;

	dining = (t_table *)arg;
	while(1)
	{
		i = 0;
		while (i < dining->n_philos)
		{
			if (time_diff(dining->philos[i].last_meal, get_time()) > (uint64_t)(dining->data->t_die))
			{
				flag = 1;
				dining->philos[i].status = DIEDED;
				break ;
			}
			++i;
		}
		if (dining->philos[i].status == DIEDED)
		{
			printf("%llu Philosopher %d is dieded\n", get_time() - dining->data->start_time, dining->philos[i].pos);
			break ;
		}
	}
	return (NULL);
}

int				run_threads(t_table *dining, t_philo *philos)
{
	pthread_t	supervisor;
	int			i;

	i = 0;
	while (i < dining->n_philos)
	{
		philos[i].data->start_time = get_time();
		printf("starting %llu\n", philos[i].data->start_time);
		philos[i].last_meal = get_time();
		if (pthread_create(philos[i].thread,
			NULL, &thread_routine, (void *)(&philos[i])))
			return(error_throw("Philosopher threads were not created."));
		i++;
		usleep(1);
	}
	usleep(100);
	if (pthread_create(dining->supervisor, NULL, &monitor_death, (void *)philos))
		return(error_throw("Supervisor thread was not created."));
	return (0);
}
void	 take_forks(t_philo *philo)
{
	uint64_t	timestamp;
	
	timestamp = time_diff((*(philo->data)).start_time, get_time());
	if (philo->pos % 2 == 1)
	{
		pthread_mutex_lock(philo->lfork);
		printf("%llu Philosopher %d has taken his left fork\n", timestamp, philo->pos);
		pthread_mutex_lock(philo->rfork);
		printf("%llu Philosopher %d has taken his right fork \n", timestamp, philo->pos);
		philo->status = EAT;
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		printf("%llu Philosopher %d has taken his right fork \n", timestamp, philo->pos);
		pthread_mutex_lock(philo->lfork);
		printf("%llu Philosopher %d has taken his left fork\n", timestamp, philo->pos);
		philo->status = EAT;
	}
}

//void 	msg_display(uint64_t timestamp, int number, char status)
//{
//	//if (status == TOOK_FORKS)
//	//	printf("%lu Philosopher %d took %dfork\n")
//	if (status == EAT)
//		printf("%llu Philosopher %d is eating\n", timestamp, number);
//	else if (status == SLEEP)
//		printf("%llu Philosopher %d is sleeping\n", timestamp, number);
//	else if (status == THINK)
//		printf("%llu Philosopher %d is thinking\n", timestamp, number);
//	else if (status == DIEDED)
//		printf("%llu Philosopher %d is dead\n", timestamp, number);

//}

void		*thread_routine(void *arg)
{
	t_philo	*philosopher;
	//uint64_t	cycle;
	uint64_t	sleeping;
	philosopher = (t_philo *)arg;
	while (1)
	{
		if (time_diff(philosopher->last_meal, get_time()) > (uint64_t)philosopher->data->t_die)
			philosopher->status = DIEDED;
		take_forks(philosopher);
		printf("%d Philosopher %d is eating\n", philosopher->last_meal, philosopher->pos);
		while (time_diff(philosopher->last_meal, get_time()) < (uint64_t)philosopher->data->t_eat)
		{
		}
		philosopher->last_meal = get_time();
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
		philosopher->status = SLEEP;
		printf("%llu Philosopher %d is sleeping\n", get_time() - philosopher->data->start_time, philosopher->pos);
		sleeping = get_time();
		while (time_diff(sleeping, get_time()) < (uint64_t)philosopher->data->t_sleep)
		{
		}
		printf("%llu Philosopher %d is thinking", get_time() - philosopher->data->start_time, philosopher->pos);
	}
	return (NULL);
}