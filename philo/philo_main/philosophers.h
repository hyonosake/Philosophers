#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>

typedef struct		s_philo
{
	int				*l_fork;
	int				*r_fork;
	int				meals_done;
	char			is_dead;
}					t_philo;

typedef struct		s_data
{
	int				n_philos;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				t_think;
	int				n_mandatory;
}					t_data;


typedef struct		s_input
{
	t_data			input;
	pthread_t		*p_threads;
	pthread_t		supervisor;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	suseconds_t     tv_usec;
	char			exec_finished;
}					t_input;

int					ft_atoi(char *char_num);
void				ft_print_input(t_input *input_data);
int					check_input(t_data *input, int ac, char **av);
int					error_exit(char *msg_err, int n_err);

#endif
