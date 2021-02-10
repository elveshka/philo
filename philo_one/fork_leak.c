#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	fork();
	while (1)
		;
	return 0;
}