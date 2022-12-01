#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int status;
    char c;
    char params[MAXARG][100];
    char *exec_args[MAXARG];

    memset(params, 0, MAXARG * 100);
    for (int i = 1; i < argc; i++)
    {
        strcpy(params[i - 1], argv[i]);
    }

    int word_index = 0;
    int arg_index = argc - 1;

    while (read(0, &c, 1) != 0)
    {
        if (c == ' ')
        {
            arg_index++;
            word_index = 0;
            continue;
        }
        else if (c == '\n')
        {
            for (int i = 0; i <= arg_index; i++)
            {
                exec_args[i] = params[i];
            }

            if (fork() == 0)
            {
                exec(argv[1], exec_args);
                exit(0);
            }
            memset(params, 0, MAXARG * 100);

            word_index = 0;
            arg_index = argc - 1;
            continue;
        }
        else
        {
            params[arg_index][word_index] = c;
            word_index++;
        }
    }

    while (wait(&status) != -1)
    {
    };
    exit(0);
}