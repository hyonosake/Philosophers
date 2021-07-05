# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>

#define NUM_T 20

pthread_mutex_t mutex;

void	counter(void *arg)
{
	int32_t	*pt;
	pthread_mutex_lock(&mutex);
	pt = (int*)arg;
	printf("Hi from thread %d\n", *pt);
	//++*pt;
	free(arg);
	sleep(1);
	pthread_mutex_unlock(&mutex);
}

int main(void)
{
	pthread_t	thread[NUM_T];
	int32_t		*num;
	int32_t		i;

	i = 0;
	//num = (int32_t*)calloc(sizeof(int32_t), 1);
	//*num = 10;
	pthread_mutex_init(&mutex, NULL);
	while (i < NUM_T)
	{
		num = (int32_t*)calloc(sizeof(int32_t), 1);
		*num = i;
		pthread_create(&thread[i], NULL, (void*)counter, (void*)num);
		++i;
	}
	i = 0;
	while (i < NUM_T)
	{
		pthread_join(thread[i], NULL);
		++i;
	}
	pthread_mutex_destroy(&mutex);
}
