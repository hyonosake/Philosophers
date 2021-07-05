#include "./philosophers.h"

int							check_input(t_data *input, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (0);
	input->n_philos = ft_atoi(av[1]);
	input->t_die = ft_atoi(av[2]);
	input->t_eat = ft_atoi(av[3]);
	input->t_sleep = ft_atoi(av[4]);
	input->n_mandatory = -1;
	if (av[5])
	{
		input->n_mandatory = ft_atoi(av[5]);
		if (input->n_mandatory == 0)
		{
			return (0);
			input->n_mandatory = -1;
		}
	}
	input->t_think = input->t_die - input->t_eat - input->t_sleep;
	if (input->n_philos < 2 || input->t_die <= 0 ||
		input->t_eat < 0 || input->t_sleep < 0 ||
		input->t_think < 0 || input->n_mandatory < 0)
		return (0);
	return (1);
}

void					ft_print_input(t_input *data)
{
	printf("There are %d philosophers\n", data->input.n_philos);
	printf("Time to die = %d ms\n", data->input.t_die);
	printf("Time to eat = %d ms\n", data->input.t_eat);
	printf("Time to sleep = %d ms\n", data->input.t_sleep);
	printf("They must eat at least %d times\n", data->input.n_mandatory);
	printf("Time to think = %d ms\n", data->input.t_think);
}

int						ft_atoi(char *char_num)
{
    int					num;
    int					sign_flag;

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