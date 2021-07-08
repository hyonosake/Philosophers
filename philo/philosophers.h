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
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
}					t_data;

typedef struct		s_philo
{
	uint64_t	    start_time;
	uint64_t		last_meal;
	// t_data			*data;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_t		*thread;
	int				pos;
	int				meals_done;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				t_think;
	char			status;
}					t_philo;

typedef struct		s_table
{
	t_data			*data;
	pthread_t		*supervisor;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				meals_done;
	char			status; // 0 start; -1 if dieded; 1 if ended meals;
}					t_table;

int			error_throw(char *err_str);
int			parse_input_data(int ac, char **av, t_data **data);
int			input_error_check(t_data *data); // basic check for input vals 
int			ft_atoi(char *char_num);
int			create_dining_table(t_table **dining, t_data *data);
int			philosophers_init(t_philo *philos, t_data *data, t_table *dining);
uint64_t	get_time(void);
int			mutex_init(t_table *dining, t_data *data);
//void		*supervisor_routine(void *arg);
void		*thread_routine(void *arg);
void		*monitor_death(void *arg);
uint64_t	time_diff(uint64_t start, uint64_t now);
int				run_threads(t_table *dining, t_philo **philos,  t_data *data);
void	 	take_forks(t_philo *philo);
void		print_dining_table(t_table *dining);
#endif