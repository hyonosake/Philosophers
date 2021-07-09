#include "philososphers.h"

int		ft_strlen(char *s)
{
	int	i;
	i = 0;
	while (s[i])
		++i;
	return (i);
}

int		int_error(char *s, t_table *table)
{
	ft_free(table);
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	return (1);
}

void	*null_error(char *s, t_table *table)
{
	ft_free(table);
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	return (NULL);
}

int		ft_atoi(char *s)
{
	int	i;
	int	num;

	i = 0;
	num = 0;

	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 + (s[i] - '0'); 
		++i;
	}
	if (s[i])
		return (-1);
	return (num);
}


void		print_data(t_data *data)
{
	printf("=== DATA ===\n");
	printf("address: %p\n", data);
}

uint64_t	time_now()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec * 0.001);
}

uint64_t	time_diff(uint64_t timestamp)
{
	return	(time_now() - timestamp);
}

void		usleep_timer(uint64_t mils_needed)
{
	uint64_t	start;
	start = time_now();
	while (time_diff(start) < mils_needed)
	{
		
	}
}

void		ft_free(t_table *table)
{
	if (table)
	{
		if (table->data)
			free(table->data);
		if (table->forks)
			free(table->forks);
		if (table->philos)
			free(table->philos);
		free(table);
	}
}