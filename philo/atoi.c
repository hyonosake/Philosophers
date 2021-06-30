#include "./philosophers.h"

void					ft_print_input(t_input *input_data)
{
	printf("There are %d philosophers\n", input_data->n_philo);
	printf("Time to die = %d ms\n", input_data->t_die);
	printf("Time to eat = %d ms\n", input_data->t_eat);
	printf("Time to sleep = %d ms\n", input_data->t_sleep);
	printf("They mist eat at least %d times\n", input_data->n_mandatory);
	printf("Time to think = %d ms\n", input_data->t_think);
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
	while (*char_num > '0' && *char_num <= '9')
	{
		num = num * 10 + (*char_num - '0');
		char_num++;
	}
    return(num);
}