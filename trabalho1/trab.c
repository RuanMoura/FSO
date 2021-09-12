#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<signal.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int error = 0;
struct timeval initial_time, end_time;
pid_t child_pid;

void trata_sinal(int);
void shell(char *, char *);
double count_time(struct timeval, struct timeval);


int main()
{
    char path[255], arg[255];
    struct timeval init_prog, end_prog;

    int status;

    gettimeofday(&init_prog, NULL);
    while (scanf(" %s %[^\n]%*c", path, arg) == 2)
    {
        error = 0;
        child_pid = fork();
        if(child_pid == 0)
        {
            shell(path, arg);
        }
        else
        {
            gettimeofday(&initial_time, NULL);
            wait(&status);
            gettimeofday(&end_time, NULL);
            printf("> Demorou %.1lf segundos, retornou %d\n", count_time(initial_time, end_time), WEXITSTATUS(status));
            fflush(stdout);
        }
    }
    gettimeofday(&end_prog, NULL);
    printf(">> O tempo total foi de %.1lf segundos\n", count_time(init_prog, end_prog));
    fflush(stdout);
    return 0;
}

void shell(char *path, char *arg)
{
    int retorno = execl((const char *) path, (const char *) path, (const char *) arg, (char*) NULL);
    if(retorno == -1)
    {
        printf("> Erro: %s\n", strerror(errno));
        fflush(stdout);
    }
    fclose(stdin);
    _exit(errno);
}

double count_time(struct timeval initial_time, struct timeval end_time)
{
    double initial_sec = (double) initial_time.tv_sec;
    double initial_usec = (double) initial_time.tv_usec/1000000.0;
    double end_sec = (double) end_time.tv_sec;
    double end_usec = (double) end_time.tv_usec/1000000.0;

    double initial = initial_sec + initial_usec;
    double end = end_sec + end_usec;

    double delta_time = end - initial;

    return delta_time;
}
