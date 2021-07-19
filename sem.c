#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct	s_useless
{
	sem_t		*sema;
}				t_useless;

int main(void)
{

	t_useless *useless;
	sem_t	*sem;

	useless = (t_useless *)malloc(sizeof(useless));
	sem_unlink("/sema");
	useless->sema = sem_open("/sema", O_CREAT | O_EXCL, 6644, 1);
	//sem_unlink("/sem");
	//sem_t	*sem = sem_open("/sem", O_CREAT | O_EXCL, 6644, 1);;
	sem_wait(useless->sema);
	sem_wait(useless->sema);
	printf("I broke it, the fuck???\n");
	return 0;
}