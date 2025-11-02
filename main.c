#include "includes/printf.h"
#include <stdio.h>

int main()
{
	int i;
  int c = ft_printf("cspdiuxX%");
  //int c = 0;
  printf("\n");
  int j = printf("cspdiuxX%");
  printf("\n");
  printf("my %d, origin: %d", c, j);
}
