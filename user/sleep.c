#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(2, "Usage: sleep ticks...\n");
    exit(1);
  }

  uint32 t = atoi(argv[1]);
  if (t < 0)
  {
    fprintf(2, "sleep time should be larger than 0\n");
    exit(1);
  }
  else
    sleep(t);

  exit(0);
}
