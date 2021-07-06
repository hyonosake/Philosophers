#include "philosophers.h"
#include <time.h>

pthread_mutex_t	lock;

//philosophers = threads
//forks = shared data(+mutex)
int				eat();
int				sleep();
int				think(t_philo *philo)
{
	printf("Philosopher %d is thinking...");
	return 1;
}

void			*supervisor_routine(void *arg)
{
	t_dining	*dining;
	int			i;
	char		flag;

	flag = 0;
	dining = (t_dining *)arg;
	while (1)
	{
		i = 0;
		while (i < dining->input.n_philos)
		{
			if (dining->philos[i].is_dead)
			{
				flag = dining->philos[i].is_dead;
				break;
			}
			if ()
		}

	}
	return (NULL);
}

void			*routine_per_thread(void *arg)
{
	t_dining		*dining;
	t_philo			*philos;

	while (1)
	{
		pthread_mutex_lock(&philo->l_fork)
		eat();
		sleep();
		think(philo);
		if (philo->is_dead)
			break;
	}
	pthread_mutex_unlock(&lock);
	//printf("Hello from thread %d!\n", num);
	return NULL;
}

void			*split_to_threads(void *arg)
{
	t_dining		*dining;
	t_philo			*philos;
	int				i;
	
	dining = (t_dining *)arg;
	i = 0;
	philos = dining->philos;
	gettimeofday(&dining->tv_usec, NULL);
	//create 
	while(i < dining->input.n_philos)
	{
		//philo = (void *)dining->p_threads[i];
		//main function must be passed
		if (pthread_create(&dining->p_threads[i], NULL, &routine_per_thread, (void *)dining->p_threads[i]))
			return (1);
		++i;
	}
	i = 0;
	while (i < dining->input.n_philos)
	{
		if (pthread_join(dining->p_threads[i], NULL))
			return (1);
	}

	return (NULL);
}

t_dining		*struct_init()
{
	t_dining	*dining;
	int			n_phil;

	dining = (t_dining *)malloc(sizeof(t_dining));
	if (!dining)
		return (NULL);
	n_phil = dining->input.n_philos;
	dining->exec_finished = 0;
	dining->p_threads = (pthread_t *)malloc(sizeof(pthread_t) * n_phil);
	if (!dining->p_threads)
		return (NULL);
	dining->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_phil);
	if (!dining->forks)
		return (NULL);
	if (philos_init(dining))
		return (NULL);
	return (dining);
}

int				main(int ac, char **av)
{
	t_dining	*dining;
	int			i;
	int			*ptr_count;

	i = 0;
	if (!check_input(&dining->input, ac, av))
		return (error_exit("Error: Invalid input data.", 1));
	if (!struct_init(dining))
		return(error_exit("Error: Malloc failed.", 2));
	if (!mutex_init(dining))
		return(error_exit("Error: mutex init failed.", 3));
	if (!threads_init(dining))
		return(error_exit("Error: threads init failed.", 3));
	if (!dining->exec_finished)
		ft_print_dining(&dining);
	pthread_mutex_destroy(&lock);
	return(dining->exec_finished);
}