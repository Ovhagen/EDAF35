#include <stdio.h>

volatile int	a = 32;
volatile int	b = 10;
volatile int	i;

int main()
{
	a += a / b;
	printf("first: %d\n", a);
	b -= a / b;
	printf("second: %d\n", b);
	for (i = 0; i < 2; i += 1){
		a *= a / b;
		printf("loop: %d\n", a);
	}

	printf("\ngoodbye\n");

	return 0;
}
