#include "philosophers.h"

pthread_mutex_t	lock;

//philosophers = threads
//forks = shared data(+mutex)

void	*routine(void *num)
{
	int	*i;

	// printf("Hello from thread %d!\n", *((int*)num));
	pthread_mutex_lock(&lock);
	i = (int *)num;
	printf("Hello from thread %d!\n", *i);
	pthread_mutex_unlock(&lock);
	//printf("Hello ffrom thread %d!\n", num);
	return NULL;
}

int main(int ac, char **av)
{
	pthread_t	*philo_threads;
	t_input		input;
	int			i;
	int			*ptr_count;
	pthread_mutex_init(&lock,NULL);
	i = 0;
	if (!check_input(&input, ac, av))
		return (error_exit("Error: Invalid input data.", 1));
	philo_threads = (pthread_t *)malloc(sizeof(pthread_t) * input.n_philo);
	if (!philo_threads)
		return(error_exit("Error: Malloc failed.", 2));
	while (i < input.n_philo)
	{
		ptr_count = (int *)malloc(sizeof(int));
		*ptr_count = i;
		pthread_create(&philo_threads[i], NULL, &routine, (void *)ptr_count);
		free(ptr_count);
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
	pthread_mutex_destroy(&lock);
	free(ptr_count);
	return(input.not_ok);
}