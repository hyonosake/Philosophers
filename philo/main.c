#include "philosophers.h"


//philosophers = threads
//forks = shared data(+mutex)


int main(int ac, char **av)
{
	t_input	input;
	if (ac < 5 || ac > 6)
	{
		printf("ArgErr\n");
		return 0;
	}
	input.n_philo = ft_atoi(av[1]);
	input.t_die = ft_atoi(av[2]);
	input.t_eat = ft_atoi(av[3]);
	input.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		input.n_mandatory = ft_atoi(av[5]);
	input.t_think = input.t_die - input.t_eat - input.t_sleep;
	if (input.n_philo < 0 || input.t_die < 0 ||
		input.t_eat < 0 || input.t_sleep < 0 ||
		input.t_think < 0 || input.n_mandatory < 0)
	{
		printf("Input Error.\n");
		ft_print_input(&input);
		return(0);
	}
	ft_print_input(&input);
	return(0);
}