#include "philosophers.h"

void	print_message(t_philo *philo, char *msg)
{
	sem_wait(philo->print);
	printf("%lld %d %s\n", time_now() - philo->data->start_time,philo->pos, msg);
	sem_post(philo->print);
}

void	philo_cycle(t_philo *philo)
{
	sem_wait(philo->forks);
	print_message(philo, "has taken a fork");
	sem_wait(philo->forks);
	print_message(philo, "has taken a fork");
	philo->last_meal = time_now();
	print_message(philo, "is eating.");
	eat_timer(philo);
	sem_post(philo->forks);
	sem_post(philo->forks);
	print_message(philo, "is sleeping.");
	usleep_timer(philo->data->t_sleep);
}

void	*process_routine(t_philo *philo)
{
	philo->last_meal = time_now();
	while (philo->data->n_meals && philo->status == START)
	{
		print_message(philo, "is thinking.");
		philo_cycle(philo);
		if (philo->meals_done == philo->data->n_meals)
			break ;
		if (time_diff(philo->last_meal) > philo->data->t_die)
		{
			printf("Here\n");
			sem_post(philo->dead);
		}
	}
	philo->status = FINISHED;
	return (NULL);
}

