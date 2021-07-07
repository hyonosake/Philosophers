#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdlib.h>

enum	e_state
{
	EAT,
	TOOK_FORKS,
	SLEEP,
	THINK,
	ENDED,
	DIEDED
};

typedef struct		s_data
{
	uint64_t	    start_time;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				t_think;
}					t_data;

typedef struct		s_philo
{
	t_data			*data;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_t		*thread;
	int				pos;
	int				last_meal;
	int				meals_done;
	char			status;
}					t_philo;

typedef struct		s_table
{
	t_data			*data;
	pthread_t		*supervisor;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				n_philos;
	int				n_meals;
	char			exec_finished; // 0 start; -1 if dieded; 1 if ended meals;
}					t_table;

int			parse_input(int ac, char **av, t_data **data, t_table **table); // data malloc, parse vals and check them
int			error_throw(char *err_str);
int			input_error_check(t_table *dining); // basic check for input vals 
int			ft_atoi(char *char_num);
t_table*	create_table(t_data *data);	//dining malloc, mutex malloc and init, threads malloc
int			philosophers_init(t_table *dining, t_philo **philos);
uint64_t	get_time(void);
int			mutex_init(t_table *dining);
//void		*supervisor_routine(void *arg);
void		*thread_routine(void *arg);
void		*monitor_death(void *arg);
uint64_t	time_diff(uint64_t start, uint64_t now);
int			run_threads(t_table *dining, t_philo *philos);
void	 	take_forks(t_philo *philo);
#endif