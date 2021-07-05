#include "philosophers.h"
#include <time.h>

pthread_mutex_t	lock;

//philosophers = threads
//forks = shared data(+mutex)

void	*routine(void *num)
{
	int	*i;

	// printf("Hello from thread %d!\n", *((int*)num));
	pthread_mutex_lock(&lock);
	i = (int *)num;
	printf("Hello from thread %d!\n", (*i+1));
	free(num);
	sleep(1);
	pthread_mutex_unlock(&lock);
	//printf("Hello ffrom thread %d!\n", num);
	return NULL;
}


t_input		*struct_init()
{
	t_input	*dining;

	dining = (t_input *)malloc(sizeof(t_input));
	if (!dining)
		return (NULL);
	dining->exec_finished = 0;
	dining->p_threads = (pthread_t *)malloc(sizeof(pthread_t)*dining->input.n_philos);
	if (!dining->p_threads)
		return (NULL);
	dining->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)*dining->input.n_philos);
	if (!dining->forks)
		return (NULL);
}



int	threads_init(t_input *dining)
{
	int i;

	i = 0;

	//waiter function must be passed
	if (pthread_create(&dining->supervisor, NULL, &routine, (void *)dining))
		return (1);
	pthread_detach(dining->supervisor);
	gettimeofday(&dining->tv_usec, NULL);
	while(i < dining->input.n_philos)
	{
		//main function must be passed
		if (pthread_create(&dining->p_threads[i], NULL, &routine, (void *)dining))
			return (1);
		++i;
	}
	i = 0;
	while (i < dining->input.n_philos)
	{
		if (pthread_join(dining->p_threads[i], NULL))
			return (1);
	}
	return (0);

}

int

int main(int ac, char **av)
{
	t_input		*dining;
	int			i;
	int			*ptr_count;
	//pthread_mutex_init(&lock,NULL);
	i = 0;
	if (!check_input(&dining->input, ac, av))
		return (error_exit("Error: Invalid input data.", 1));
		return(error_exit("Error: Malloc failed.", 2));
	struct_init(dining);
	while (i < dining->p_threads)
	{
		ptr_count = (int32_t*)calloc(sizeof(int32_t), 1);
		*ptr_count = i;
		//printf("*ptr = %d\n", *ptr_count);
		pthread_create(&dining->p_threads[i], NULL, &routine, (void *)ptr_count);
		++i;
	}
	i = 0;
	// while (i < 5)
	// {
	// 	routine(NULL);
	// 	i++;
	// }
	while (i < dining->input.n_philos)
	{
		pthread_join(dining->p_threads[i], NULL);
	}
	if (!dining->exec_finished)
		ft_print_input(&dining);
	pthread_mutex_destroy(&lock);
	return(dining->exec_finished);
}