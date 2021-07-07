#include "./philosophers.h"

int			ft_atoi(char *char_num)
{
    int		num;
    int		sign_flag;

    sign_flag = 0;
    num = 0;
    if (!char_num)
        return(num);
	while(*char_num == ' ' || (*char_num > 8 && *char_num < 14))
		char_num++;
    while(*char_num == '+' || *char_num == '-')
    {
        if (*char_num == '-')
			return(-1);
    }
	while (*char_num >= '0' && *char_num <= '9')
	{
		num = num * 10 + (*char_num - '0');
		char_num++;
	}
	if (*char_num)
		return -1;
    return(num);
}

t_table			*create_table(t_data *data)
{
	int i;
	int n_phil;
	t_table	*dining;

	i = 0;
	dining = (t_table *)malloc(sizeof(t_table));
	dining->data = data;
	n_phil = dining->data->n_philos;
	if (!dining)
		//return(error_throw("Memory allocation for table failed."));
		return (NULL);
	dining->threads = (pthread_t *)malloc(sizeof(pthread_t) * n_phil);
	if (!dining->threads)
		return (NULL);
		//return(error_throw("Memory allocation for threads failed."));
	dining->exec_finished = 0;
	dining->forks = (pthread_mutex_t *)calloc(sizeof(pthread_mutex_t), n_phil);
	if (!dining->forks)
		//return(error_throw("Memory allocation for forks(mutex) failed."));
		return (NULL);
	while (i < dining->data->n_philos)
	{
		if (pthread_mutex_init(&dining->forks[i], NULL))
			//return(error_throw("Initializing forks(mutex) failed."));
			return (NULL);
		i++;
		printf("%d\n", i);
	}
	return (dining);
}

uint64_t			get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec * 0.001);
}

uint64_t			time_diff(uint64_t start, uint64_t now)
{
	return (now - start);
}


void				free_struct(t_philo *philo)
{
	if(philo)
	{

		if (philo->table->data)
			free(philo->table->data);
		if (philo->table->threads)
			free(philo->table->threads);
		if (philo->table->forks)
			free(philo->table->forks);
		if (philo->table)
			free(philo->table);
		free(philo);
	}
}
