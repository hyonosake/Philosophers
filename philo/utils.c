#include "philosophers.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

int	int_error(char *s, t_table *table)
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

int	ft_atoi(char *s)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (s[i] >= '0' && s[i] <= '9')
		num = num * 10 + (s[i++] - '0');
	if (s[i])
		return (-1);
	return (num);
}

uint64_t	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec * 0.001);
}
