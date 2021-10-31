#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define MAX_RAND 100000

sem_t sem;
int m, b, res;

void *func(void *);

int main()
{
    pthread_t tid1, tid2;
    unsigned int seed1, seed2;
    int i;
    int set1[MAX_RAND];
    int set2[MAX_RAND];
    sem_init(&sem,0,1);

    scanf("%u %u", &seed1, &seed2);
    for (i = 0; i < MAX_RAND; i++)
        set1[i] = rand_r(&seed1);
    for (i = 0; i < MAX_RAND; i++)
        set2[i] = rand_r(&seed2);

    while (scanf("%d %d", &m, &b) == 2)
    {
        res = 0;
        pthread_create(&tid1, NULL, &func, (void *)&set1);
        pthread_create(&tid2, NULL, &func, (void *)&set2);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
        printf("%d\n", res);
    }

    return 0;
}

void *func(void *n)
{
    int *set = (int *)n;
    for (int i = 0; i < MAX_RAND; i++)
    {
        if (set[i] % m == b)
        {
            sem_wait(&sem);
            res++;
            sem_post(&sem);
        }
    }
}