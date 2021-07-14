#include "philosophers.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
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

void	ft_free(t_table *table)
{
	if (table)
	{
		if (table->data)
			free(table->data);
		//if (table->forks)
		//	free(table->forks);
		if (table->philos)
			free(table->philos);
		free(table);
	}
}
