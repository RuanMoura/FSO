#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<signal.h>

void trata_sinal(int s)
{
    signal(SIGUSR1, trata_sinal);
}

void shell(char *path, char *arg)
{
    execl((const char *) path, (const char *) path, (const char *) arg, (char*) NULL);
}

void count_time()
{
    struct timeval initial_time, end_time;

    gettimeofday(&initial_time, NULL);
    pause();
    gettimeofday(&end_time, NULL);

    double initial_sec = (double) initial_time.tv_sec;
    double initial_usec = (double) initial_time.tv_usec/1000000;
    double end_sec = (double) end_time.tv_sec;
    double end_usec = (double) end_time.tv_usec/1000000;

    double initial = initial_sec + initial_usec;
    double end = end_sec + end_usec;

    double delta_time = end - initial;

    printf("> Demorou %.1lf segundos, retornou 0\n", delta_time);
    
    kill(getpid(), SIGKILL);
}

int main()
{
    signal(SIGUSR1, trata_sinal);

    char path[255], arg[255];
    pid_t pid;

    while (scanf(" %s %[^\n]%*c", path, arg) == 2)
    {
        pid = fork();
        if(pid == 0)
        {
            shell(path, arg);
        }
        else
        {
            pid = fork();
            if(pid == 0)
            {
                count_time();
            }
            else
            {
                wait(NULL);
                kill(pid, SIGUSR1);
                wait(NULL);
            }
        }
    }
    
    return 0;
}