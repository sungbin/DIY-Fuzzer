#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int 
main(int argc, char* argv[])
{

	int temp;
	scanf("%d", &temp);
	printf("sleep %d secconds...\n", temp);

	int start, end;
	start = (int)clock() / CLOCKS_PER_SEC;
	end = (((int)clock()) / CLOCKS_PER_SEC);

	while ( (end - start) < 100) {

	}

	//sleep(100 * temp);

	return 0;
}
