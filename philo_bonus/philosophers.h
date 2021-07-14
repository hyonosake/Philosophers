#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

# define START 0
# define EAT 1
# define FINISHED 2
# define DIEDED 3

typedef struct s_data
{
	uint64_t		start_time;
	uint64_t		t_die;
	uint64_t		t_sleep;
	uint64_t		t_eat;
	uint64_t		n_philos;
	uint64_t		n_meals;
}					t_data;

typedef struct s_philo
{
	uint64_t		last_meal;
	t_data			data;
	pid_t			pid;
	sem_t			*print;
	sem_t			*forks;
	pthread_t		thread;
	bool			odd;
	int				pos;
	int				meals_done;
	char			status;
}					t_philo;

typedef struct s_table
{
	t_data			*data;
	t_philo			*philos;
	sem_t			*print;
	sem_t			*forks;
}					t_table;

int					ft_strlen(char *s);
void				error_throw(char *s, t_table *table);
void				usleep_timer(uint64_t mils_needed);
void				print_data(t_data *data);
uint64_t			time_now(void);
uint64_t			time_diff(uint64_t timestamp);
t_data				*data_init(int ac, char **av, t_table **table);
void				semaphores_init(t_table *table);
t_philo				*philos_init(t_table *table);
int					run_forks(t_table *table, t_philo *philos);
int					supervise(t_table *table, t_philo *philos);
void				*process_routine(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_take_forks(t_philo *philo);
int					finish_thread_stuff(t_table *table);
void				ft_free(t_table *table);
int					philo_death(t_table *table, int i);
int					philo_finished(t_table *table);
void				eat_timer(t_philo *philo);
void				*ft_calloc(int size_of, int n);
#endif