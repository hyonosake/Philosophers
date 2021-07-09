#include "philosophers.h"

size_t			ft_strlen(char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
		++i;
	return(i);
}

void		*error_null(char *str, t_table *dining)
{
	free_structs(dining);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (NULL);
}

int			error_int(char *str, t_data *data)
{
	free(data);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (1);
}

uint32_t	ft_atoi(char *s)
{
	int		num;
	int		i;

	num = 0;
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 + (s[i] - '0');
		i++;
	}
	if (s[i])
		return (-1);
	return (num);
}


void	free_structs(t_table *dining)
{
	if (dining)
	{
		if (dining->philos)
		{
			if ((dining->philos)->thread)
				free((dining->philos)->thread);
			free(dining->philos);
		}
		if (dining->data)
			free(dining->data);
		if (dining->forks)
			free(dining->forks);
		free(dining);
	}
}

uint64_t	time_now()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

uint64_t	time_diff(uint64_t timestamp)
{
	return (time_now() - timestamp);
}