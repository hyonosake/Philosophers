#include "philososphers.h"

void			philo_take_forks(t_philo *philo)
{

	pthread_mutex_lock(philo->forks[philo->odd]);
	pthread_mutex_lock(philo->print);
	printf("%lld %d has taken a fork\n",
				time_diff(philo->data.start_time), philo->pos);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->forks[!(philo->odd)]);
	pthread_mutex_lock(philo->print);
	printf("%lld %d has taken a fork\n",
				time_diff(philo->data.start_time), philo->pos, philo->pos);
	pthread_mutex_unlock(philo->print);
}

void			philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is sleeping.\n", 
		time_diff(philo->data.start_time), philo->pos);
	pthread_mutex_unlock(philo->print);
	usleep_timer(philo->data.t_sleep);
}

void			philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is eating.\n",
		time_diff(philo->data.start_time), philo->pos);
	pthread_mutex_unlock(philo->print);
	philo->last_meal = time_now();
	usleep_timer(philo->data.t_eat);
	pthread_mutex_unlock(philo->forks[philo->odd]);
	pthread_mutex_unlock(philo->forks[!(philo->odd)]);
	philo->meals_done++;
}


void			*thread_routine(void *arg)
{
	t_philo		*philo;
	uint64_t	now;

	philo =  (t_philo *)arg;
	now =  time_now();
	philo->data.start_time = now;
	philo->last_meal = now;
	while (1)
	{
		pthread_mutex_lock(philo->print);
		printf("%lld %d is thinking.\n",
			time_diff(philo->data.start_time), philo->pos);
		pthread_mutex_unlock(philo->print);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		if (philo->meals_done && philo->meals_done == philo->data.n_meals)
			philo->status = FINISHED;
	}
	return (NULL);
}
