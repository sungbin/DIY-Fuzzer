#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int 
main(int argc, char* argv[])
{

	int in_t;
	scanf("%d", &in_t);
	printf("sleep %d secconds...\n", in_t);

	int start, end;
	start = (int)clock() / CLOCKS_PER_SEC;

	while ((end - start) < in_t) {

		end = (((int)clock()) / CLOCKS_PER_SEC);
	}

	//sleep(100 * in_t);

	return 0;
}
