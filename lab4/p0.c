#include <stdio.h>

volatile int	a = 32;
volatile int	b = 10;
volatile int	i;

int main()
{
	a += a / b;
	b -= a / b;

	for (i = 0; i < 2; i += 1)
		a *= a / b;

	printf("goodbye\n");

	return 0;
}
