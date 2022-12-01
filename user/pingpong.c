#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2];
    int ret = pipe(p);
    if (ret < 0)
    {
        fprintf(2, "failed to create pipe\n");
    }

    if (fork() == 0)
    {
        // in child process
        char read_buffer[16] = {0};
        read(p[0], read_buffer, sizeof(read_buffer));
        fprintf(1, "%s: received ping\n", read_buffer);

        int pid = getpid();
        close(1);
        dup(p[1]);
        fprintf(1, "%d", pid);
        close(p[0]);
        close(p[1]);
        exit(0);
    }
    else
    {
        // in parent process
        int ppid = getpid();
        close(0);
        dup(p[1]);
        close(p[1]);
        fprintf(0, "%d", ppid);

        int status;
        char read_buffer[16] = {0};
        wait(&status);
        read(p[0], read_buffer, sizeof(read_buffer));
        fprintf(1, "%s: received pong\n", read_buffer);
        close(p[0]);
        exit(0);
    }
}