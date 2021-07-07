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
	int				n_philos;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				t_think;
	int				n_meals;
}					t_data;


typedef struct		s_table
{
	uint64_t	    start_time;
	t_data			*data;
	pthread_t		*threads;
	pthread_t		supervisor;
	pthread_mutex_t	*forks;
	char			exec_finished; // 0 start; -1 if dieded; 1 if ended meals;
}					t_table;

typedef struct		s_philo
{
	uint64_t	    time_left;
	t_table			*table;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	//pthread_t		thread;
	int				pos;
	int				last_meal;
	int				meals_done;
	char			status;
	
}					t_philo;

int			error_throw(char *err_str);
int			input_error_check(t_data *data); // basic check for input vals
t_data		*parse_input(int ac, char **av); // data malloc, parse vals and check them
int			ft_atoi(char *char_num);
t_table*			create_table(t_data *data);	//dining malloc, mutex malloc and init, threads malloc
t_philo		*init_philosophers(t_table *dining);
uint64_t	get_time(void);
//void		*supervisor_routine(void *arg);
void		*thread_routine(void *arg);
void		*monitor_death(void *arg);
uint64_t	time_diff(uint64_t start, uint64_t now);
int			run_threads(t_philo *philos);
void	 take_forks(t_philo *philo);
#endif