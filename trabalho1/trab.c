#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void shell(char *path, char *arg)
{
    execl((const char *) path, (const char *) path, (const char *) arg, (char*) NULL);
}

int main()
{
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
            wait(NULL);
        }
    }
    
    return 0;
}