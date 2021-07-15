#include "philosophers.h"

uint64_t	time_diff(uint64_t timestamp)
{
	return (time_now() - timestamp);
}

void	usleep_timer(uint64_t mils_needed)
{
	uint64_t	start;

	start = time_now();
	while (time_diff(start) < mils_needed)
	{
		usleep(500);
	}
}

void	eat_timer(t_philo *philo)
{
	uint64_t	start;

	start = time_now();
	philo->meals_done++;
	while (time_diff(start) < philo->data.t_eat)
	{
		usleep(500);
	}
	//philo->last_meal = time_now();
}

uint64_t	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec * 0.001);
}

void	*ft_calloc(int size_of, int n)
{
	void	*memory;

	memory = (void *)malloc(size_of * n);
	memset(memory, 0, size_of * n);
	return (memory);
}
