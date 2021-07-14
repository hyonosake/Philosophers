#include "philosophers.h"

void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->print);
	printf("%lld %d has taken a fork\n",
		time_diff(philo->data.start_time), philo->pos);
	sem_post(philo->print);
	sem_wait(philo->forks);
	sem_wait(philo->print);
	printf("%lld %d has taken a fork\n",
		time_diff(philo->data.start_time), philo->pos);
	sem_post(philo->print);
}

void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%lld %d is sleeping.\n",
		time_diff(philo->data.start_time), philo->pos);
	sem_post(philo->print);
	usleep_timer(philo->data.t_sleep);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%lld %d is eating.\n",
		time_diff(philo->data.start_time), philo->pos);
	sem_post(philo->print);
	eat_timer(philo);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	*process_routine(t_philo *philo)
{
	philo->data.start_time = time_now();
	philo->last_meal = philo->data.start_time;
	while (1)
	{
		sem_wait(philo->print);
		printf("%lld %d is thinking.\n",
			time_diff(philo->data.start_time), philo->pos);
		sem_post(philo->print);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		if (philo->meals_done && philo->meals_done == philo->data.n_meals)
			philo->status = FINISHED;
	}
	return (NULL);
}
