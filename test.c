#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define NUM_T 10

void	counter(void *arg)
{
	int32_t	*pt;
	
	pt = (int*)arg;
	++*((int*)arg);
	printf("%d\n", *pt);
}

int main(void)
{
	pthread_t	thread[NUM_T];
	int32_t		*num;
	int32_t		i;

	i = 0;
	num = (int32_t*)calloc(sizeof(int32_t), 1);
	*num = 10;
	while (i < NUM_T)
	{
		pthread_create(&thread[i], NULL, (void*)counter, (void*)num);
		++i;
	}
	i = 0;
	while (i < NUM_T)
	{
		pthread_join(thread[i], NULL);
		++i;
	}

}
