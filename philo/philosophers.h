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
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				t_think;
	int				n_philos;
	int				n_meals;
}					t_data;

typedef struct		s_philo
{
	t_data			data;
	uint64_t		start_time;
	uint64_t		t_meal;
	int				cycle;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_t		*thread;
	int				pos;
	int				meals_done;
	char			status;
}					t_philo;

typedef struct		s_table
{
	t_data			*data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				n_philos;
	int				meals_done;
	char			status; // 0 start; -1 if dieded; 1 if ended meals;
}					t_table;

size_t			ft_strlen(char *s);
void		*error_null(char *str, t_table *dining);
int			error_int(char *str, t_data *data);
uint32_t	ft_atoi(char *s);
uint64_t	time_diff(uint64_t timestamp);
t_data		*data_init(int ac, char **av);
t_table		*dining_init(t_data *data);
t_philo		*philos_init(t_table *dining);
void		*start_threads(t_table *dining, t_philo *philos);
uint64_t	time_now();
void		*thread_routine(void *arg);
void		*supervisor_routine(void *arg);
void		take_forks(t_philo *philosopher);
void		eat_timer(t_philo *philosopher);
void		sleep_timer(t_philo *philosopher);
void		free_structs(t_table *dining);
#endif