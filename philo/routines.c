#include "philosophers.h"


void			take_forks(t_philo *philosopher)
{
	int			pos;
	uint64_t	timestamp;

	pos = philosopher->pos;
	timestamp = philosopher->start_time;
	if (pos % 2 == 1)
	{
		pthread_mutex_lock(philosopher->lfork);
		printf("%lld %d has taken right fork\n", time_diff(timestamp), pos);
		pthread_mutex_lock(philosopher->rfork);
		printf("%lld %d has taken left fork\n", time_diff(timestamp), pos);
	}
	else
	{
		pthread_mutex_lock(philosopher->rfork);
		printf("%lld %d has taken left fork\n", time_diff(timestamp), pos);
		pthread_mutex_lock(philosopher->lfork);
		printf("%lld %d has taken right fork\n", time_diff(timestamp), pos);
	}
}

void		eat_timer(t_philo *philosopher)
{
	int			pos;
	uint64_t	local_time;

	// sleep(1);
	pos = philosopher->pos;
	local_time = time_diff(philosopher->start_time);
	philosopher->t_meal = time_now();
	philosopher->cycle = philosopher->data.t_die;
	printf("%lld %d is eating\n", local_time, pos);
	while (time_diff(local_time) < (uint64_t)philosopher->data.t_eat)
	{
	}     
	philosopher->cycle -= philosopher->data.t_eat;
	philosopher->meals_done++;
}

void		sleep_timer(t_philo *philosopher)
{
	int			pos;
	uint64_t	local_time;
	uint64_t	delta;
	pos = philosopher->pos;
	local_time = time_diff(philosopher->start_time);
	printf("%lld %d is sleeping\n", local_time, pos);
	local_time = time_now();
	printf("t_slip = %d\n", philosopher->data.t_sleep);
	while (time_diff(local_time) < (uint64_t)philosopher->data.t_sleep)
	{
		//cycle = cycle - delta
		//delta = time_now - time_of sleep beginning
		delta = time_now() - time_diff(local_time);
		philosopher->cycle -= delta;
		if (philosopher->cycle < 0)
		{
			printf("DID\n");
			philosopher->status = DIEDED;
			break ;
		}
	}
}

void			*supervisor_routine(void *arg)
{
	//t_table		*dining;
	//int			i;
	//dining = (t_table *)arg;
	//while (1)
	//{
	//	i = 0;
	//	while (i < dining->data->n_philos)
	//	{
	//		if (dining->philos[i].status)
	//		{

	//			if (dining->philos[i].status == DIEDED)
	//				printf("%lld %d just dieded...\n", time_diff(dining->data->start_time), i + 1);
	//			if (dining->philos[i].status == ENDED)
	//				printf("%lld simulation ended with %d meals...\n", time_diff(dining->data->start_time),
	//					dining->philos[i].meals_done);
	//			dining->status = dining->philos[i].status;
	//		}
	//		break ;
	//	}
	//	if (dining->status)
	//		break ;

	//}
	//return (NULL);
	return (NULL);
}