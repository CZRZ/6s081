#include "kernel/types.h"
#include "user/user.h"

void seive(int pfd[2])
{
    close(pfd[1]); // close write end first, or while loop never ends
    int p;
    read(pfd[0], &p, 4);
    fprintf(1, "prime %d\n", p);
    int n = p;
    int new_pipe[2] = {0};
    int status;
    while (read(pfd[0], &n, 4) != 0)
    {
        //fprintf(1, "n is %d\n", n);
        if (n != 0 && n % p != 0)
        {
            if (new_pipe[0] == 0 && new_pipe[1] == 0)
            {
                pipe(new_pipe);
                if (fork() == 0)
                {
                    close(pfd[0]);
                    seive(new_pipe);
                    exit(0);
                }
            }
            write(new_pipe[1], &n, 4);
        }
    }
    close(pfd[0]);
    close(new_pipe[0]);
    close(new_pipe[1]);
    while (wait(&status) != -1)
    {
        sleep(1);
    }
    exit(0);
}

int main()
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        seive(p);
        exit(0);
    }
    close(p[0]);
    for (int i = 2; i <= 35; i++)
    {
        write(p[1], &i, 4);
    }
    close(p[1]);
    int status;
    while (wait(&status) != -1)
    {
        sleep(1);
    }
    exit(0);
}
