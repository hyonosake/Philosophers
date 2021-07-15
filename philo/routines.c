#include "philosophers.h"

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d %s\n", time_now() - philo->data.start_time,philo->pos, msg);
	pthread_mutex_unlock(philo->print);
}

void	philo_cycle(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[philo->odd]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->forks[!(philo->odd)]);
	print_message(philo, "has taken a fork");
	philo->last_meal = time_now();
	print_message(philo, "is eating.");
	eat_timer(philo);
	pthread_mutex_unlock(philo->forks[philo->odd]);
	pthread_mutex_unlock(philo->forks[!(philo->odd)]);
	print_message(philo, "is sleeping.");
	usleep_timer(philo->data.t_sleep);
}

void	*thread_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_meal = time_now();
	//if (philo->odd)
	//	usleep_timer(philo->data.t_eat - 10);
	while (philo->data.n_meals && philo->status == START)
	{
		print_message(philo, "is thinking.");
		philo_cycle(philo);
		if (philo->meals_done == philo->data.n_meals)
			break ;
	}
	philo->status = FINISHED;
	return (NULL);
}
