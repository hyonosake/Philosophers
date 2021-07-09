#include "philosophers.h"


void			*start_threads(t_table *dining, t_philo *philos)
{
	int			i;
	uint64_t	timestamp;
	pthread_t	supervisor;

	i = 0;
	timestamp = time_now();
	while (i < dining->data->n_philos)
	{
		philos[i].start_time = timestamp;
		philos[i].meals_done = 0;
		philos[i].t_meal = timestamp;
		//printf("%lld\n", philos[i].t_meal = timestamp);
		if (pthread_create(philos[i].thread, NULL,
				&thread_routine, (void *)(&philos[i])))
			return(error_null("Failed to create thread =(\n", dining));
		++i;
		usleep(1);
	}
	usleep(100);
	if (pthread_create(&supervisor, NULL,
			&supervisor_routine, (void *)dining))
		return(error_null("Failed to create supervisor =(\n", dining));
	return (NULL);
}

void			*thread_routine(void *arg)
{
	t_philo		*philosopher;
	int			pos;
	uint64_t	timestamp;

	philosopher = (t_philo *)arg;
	pos = philosopher->pos;
	timestamp = philosopher->start_time;
	while (1)
	{
		//printf("%lld\n", time_now());
		//printf("%lld\n", philosopher->data.start_time);
		if (time_diff(philosopher->t_meal) > philosopher->data.t_die)
		{
			printf("meal = %lld\n", time_diff(philosopher->t_meal));
			printf("die = %lld\n", philosopher->data.t_die);
			philosopher->status = DIEDED;
			break ;
		}
		take_forks(philosopher);
		eat_timer(philosopher);
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
		sleep_timer(philosopher);
		printf("%lld %d is thinking\n", time_diff(timestamp), pos);
		//philosopher->t_meal = time_now();
	}
	return (NULL);
}