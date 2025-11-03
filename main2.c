#include "includes/printf.h"
#include <stdio.h>

int main()
{
  int x = ft_printf("%x", 0xffffffff);
  printf("\n");
  int y = printf("%x", 0xffffffff);
  printf("\n");
  printf("my len: %d, the origin len: %d", x, y);
  return 0;
}
