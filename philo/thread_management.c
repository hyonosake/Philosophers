#include "./philosophers.h"

int				run_threads(t_table *dining, t_philo *philos, t_data *data)
{
	int			i;

	i = 0;
	//printf("dining->dat->bla %d\n", dining->data->n_meals);
	dining->supervisor = (pthread_t *)malloc(sizeof(pthread_t));
	while (i < data->n_philos)
	{
		(*philos[i])->start_time = get_time();
		printf("starttime %llu\n", (*philos[i]).start_time);
		(*philos[i]).last_meal = get_time();
		if (pthread_create((*philos[i]).thread,
			NULL, &thread_routine, (void *)(philos[i])))
			return(error_throw("Philosopher threads were not created."));
		++i;
		usleep(1);
	}
	usleep(100);
	if (pthread_create(dining->supervisor, NULL, &monitor_death, (void *)dining))
		return(error_throw("Supervisor thread was not created."));
	return (0);
}

void			*monitor_death(void *arg)
{
	int			i;
	t_table		*dining;
	uint64_t	timestamp;

	dining = (t_table *)arg;
	while(1)
	{
		i = 0;
		while (i < (dining->data)->n_philos)
		{
			if (time_diff(dining->philos[i].last_meal, get_time()) > (uint64_t)(dining->data->t_die))
			{
				dining->philos[i].status = DIEDED;
				dining->status = DIEDED;
				break ;
			}
			++i;
		}
		if (dining->status != 0)
		{
			timestamp = get_time() - dining->data->start_time;
			if (dining->status == DIEDED)
				printf("%llu philo %d is dieded", timestamp, 10);
			else if (dining->status == ENDED)
				printf("%llu Philosophers finished eatin'\n", timestamp);
			break ;
		}
	}
	return (NULL);
}


void	 take_forks(t_philo *philo)
{
	uint64_t	timestamp;
	
	timestamp = time_diff(philo->start_time, get_time());
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

void		*thread_routine(void *arg)
{
	t_philo	*philosopher;
	//uint64_t	cycle;
	uint64_t	sleeping;
	philosopher = (t_philo *)arg;
	while (1)
	{
		if (time_diff(philosopher->last_meal, get_time()) > (uint64_t)philosopher->t_die)
			philosopher->status = DIEDED;
		take_forks(philosopher);
		printf("%llu Philosopher %d is eating\n", philosopher->last_meal, philosopher->pos);
		while (time_diff(philosopher->last_meal, get_time()) < (uint64_t)philosopher->t_eat)
		{
		}
		philosopher->last_meal = get_time();
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
		philosopher->status = SLEEP;
		printf("%llu Philosopher %d is sleeping\n", get_time() - philosopher->start_time, philosopher->pos);
		sleeping = get_time();
		while (time_diff(sleeping, get_time()) < (uint64_t)philosopher->t_sleep)
		{
		}
		printf("%llu Philosopher %d is thinking", get_time() - philosopher->start_time, philosopher->pos);
	}
	return (NULL);
}