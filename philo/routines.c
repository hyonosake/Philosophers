#include "philosophers.h"

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[philo->odd]);
	pthread_mutex_lock(philo->print);
	printf("%lld %d has taken a fork\n",
		time_diff(philo->data.start_time), philo->pos);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->forks[!(philo->odd)]);
	pthread_mutex_lock(philo->print);
	printf("%lld %d has taken a fork\n",
		time_diff(philo->data.start_time), philo->pos);
	pthread_mutex_unlock(philo->print);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is sleeping.\n",
		time_diff(philo->data.start_time), philo->pos);
	pthread_mutex_unlock(philo->print);
	usleep_timer(philo->data.t_sleep);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is eating.\n",
		time_diff(philo->data.start_time), philo->pos);
	philo->last_meal = time_now();
	pthread_mutex_unlock(philo->print);
	eat_timer(philo);
	pthread_mutex_unlock(philo->forks[philo->odd]);
	pthread_mutex_unlock(philo->forks[!(philo->odd)]);
}

void	*thread_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->data.start_time = time_now();
	philo->last_meal = time_now();
	while (1)
	{
		pthread_mutex_lock(philo->print);
		printf("%lld %d is thinking.\n",
			time_diff(philo->data.start_time), philo->pos);
		pthread_mutex_unlock(philo->print);
		//if (philo->odd)
		//	usleep_timer(10);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		if (philo->meals_done && philo->meals_done == philo->data.n_meals)
			philo->status = FINISHED;
	}
	return (NULL);
}
