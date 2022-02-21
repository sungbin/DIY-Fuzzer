#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int 
main (int argc, char* argv[])
{
	int in_t;
	scanf("%d", &in_t);

	int start, end;
	start = (int)clock() / CLOCKS_PER_SEC;

	printf("sleep infinity secconds...\n");
	while (1) { }

	return 0;
}
