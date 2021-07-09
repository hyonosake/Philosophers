#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>

enum	e_state
{
	START,
	EAT,
	TOOK_FORKS,
	SLEEP,
	THINK,
	FINISHED,
	DIEDED
}		t_state;

typedef struct		s_data
{
	uint64_t		start_time;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				n_philos;
	int				n_meals;
}					t_data;

typedef struct		s_philo
{
	uint64_t		last_meal;
	t_data			data;
	pthread_mutex_t	*forks[2];
	pthread_t		thread;
	pthread_mutex_t	*print;
	bool			odd;
	int				pos;
	int				meals_done;
	char			status;
}					t_philo;

typedef struct		s_table
{
	t_data			*data;
	t_philo			*philos;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}					t_table;

int					ft_strlen(char *s);
int					int_error(char *s, t_table *table);
void				usleep_timer(uint64_t mils_needed);
void				*null_error(char *s, t_table *table);
void				print_data(t_data *data);
uint64_t			time_now();
uint64_t			time_diff(uint64_t timestamp);
t_data				*data_init(int ac, char **av, t_table **table);
pthread_mutex_t 	*forks_init(t_table *table);
t_philo				*philos_init(t_table *table, pthread_mutex_t *forks);
int					run_threads(t_table *table, t_philo *philos);
int					supervise(t_table *table, t_philo *philos);
void				*thread_routine(void *arg);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_take_forks(t_philo *philo);
int					finish_thread_stuff(t_table *table);
void				ft_free(t_table *table);

#endif