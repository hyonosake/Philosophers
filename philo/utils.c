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

int					mutex_init(t_table *dining)
{
	int				i;

	i = 0;
	dining->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
						dining->n_philos);
	if (!dining->forks)
		return(error_throw("Memory allocation for forks(mutex) failed."));
	while (i < dining->n_philos)
	{
		if (pthread_mutex_init(&dining->forks[i], NULL))
			return(error_throw("Initializing forks(mutex) failed."));
		++i;
	}
	return (0);
}

//void				free_struct(t_philo *philo)
//{
//	if(philo)
//	{

//		if (philo->table->data)
//			free(philo->table->data);
//		if (philo->table->threads)
//			free(philo->table->threads);
//		if (philo->table->forks)
//			free(philo->table->forks);
//		if (philo->table)
//			free(philo->table);
//		free(philo);
//	}
//}
