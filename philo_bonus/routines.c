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

void *death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	//printf("Lmeal = %lld\n", philo->last_meal);
	while (1)
	{
		if (time_diff(philo->last_meal) > philo->data->t_die)
		{
			//printf("ARGHR\n");
			//sem_wait(philo->print);
			sem_wait(philo->print);
			printf("\033[0;31m");
			printf("%lld %d just passed away...\n",
			time_diff(philo->data->start_time), philo->pos);
			//printf("????\n");
			sem_post(philo->dead);
			break ;
		}
	}
	//printf("Broke in thread from dead\n");
	return (NULL);
}

void	*process_routine(t_philo *philo)
{
	//printf("Lmeal_routine = %lld\n", philo->last_meal);
	if (pthread_create(&philo->thread, NULL, &death_monitor, (void *)philo))
		error_throw("Failed to run philo monitor thread,", NULL);
	philo->last_meal = time_now();
	while (1)
	{
		print_message(philo, "is thinking.");
		philo_cycle(philo);
		if (philo->meals_done == philo->data->n_meals)
			break ;
	}
	//printf("Broke from loop\n");
	sem_post(philo->print);
	philo->status = FINISHED;
	return (NULL);
}

