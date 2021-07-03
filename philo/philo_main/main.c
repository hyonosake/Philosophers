#include "philosophers.h"


//philosophers = threads
//forks = shared data(+mutex)

void	*routine(void *num)
{
	static int i;
	if (!num)
		printf("wh loop %i\n", i++);
	else
	// printf("Hello from thread %d!\n", *((int*)num));
	printf("Hello from thread %d!\n", i);
	//printf("Hello ffrom thread %d!\n", num);
	return NULL;
}

int main(int ac, char **av)
{
	pthread_t	*philo_threads;
	t_input		input;
	int			i;

	i = 0;
	if (!check_input(&input, ac, av))
		return (error_exit("Error: Invalid input data.", 1));
	philo_threads = (pthread_t *)malloc(sizeof(pthread_t) * input.n_philo);
	if (!philo_threads)
		return(error_exit("Error: Malloc failed.", 2));
	while (i < input.n_philo)
	{
		pthread_create(&philo_threads[i], NULL, &routine, (void *)&i);
		i++;
	}
	i = 0;
	// while (i < 5)
	// {
	// 	routine(NULL);
	// 	i++;
	// }
	while (i < input.n_philo)
		pthread_join(philo_threads[i++], NULL);
	if (!input.not_ok)
		ft_print_input(&input);
	return(input.not_ok);
}