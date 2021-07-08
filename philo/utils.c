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

int			error_throw(char *err_str)
{
	printf("Error: %s\n", err_str);
	return (1);
}

void				print_dining_table(t_table *dining)
{
	printf("==== DINING TABLE ====\n");
	printf("\t---DATA---\n");
	printf("n_philos %d\n", (dining->data)->n_philos);
	printf("t_die\t %d\n", (dining->data)->t_die);
	//printf("dining->philos[i].pos", (dining->philos[2]).pos);
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
