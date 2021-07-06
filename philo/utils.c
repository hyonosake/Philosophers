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

int			create_table(t_table *dining)
{
	int i;
	int n_phil;

	n_phil = dining->data->n_philos;
	i = 0;
	dining = (t_table *)malloc(sizeof(t_table));
	if (!dining)
		return(error("Memory allocation for table failed."));
	dining->threads = (pthread_t *)malloc(sizeof(pthread_t) * n_phil);
	if (!dining->threads)
		return(error("Memory allocation for threads failed."));
	dining->exec_finished = 0;
	dining->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_phil);
	if (!dining->forks)
		return(error("Memory allocation for forks(mutex) failed."));
	while (i < dining->data->n_philos)
		if (pthread_mutex_init(&dining->forks[i++]))
			return(error("Initializing forks(mutex) failed."));
	return (0);
}

uint64_t			get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return(tv.tv_usec);
}

uint64_t			time_diff(uint64_t start, uint64_t now)
{
	return (now - start);
}
