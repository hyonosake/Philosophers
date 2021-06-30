#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct	s_input
{
	int			n_philo;
	int			t_die;
	int			t_sleep;
	int			t_eat;
	int			t_think;
	int			n_mandatory;

}				t_input;
int						ft_atoi(char *char_num);
void					ft_print_input(t_input *input_data);

#endif
