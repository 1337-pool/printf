#include "includes/printf.h"
#include <stdio.h>

int main()
{
	int i;
  int c = ft_printf("%u", -21);
  //int c = 0;
  int j = printf("\n%u\n", -21);
  printf("my %d, origin: %d", c, j);
}
