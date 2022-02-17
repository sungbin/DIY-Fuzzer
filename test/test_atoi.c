#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
main (int argc, char* argv[])
{

	char buf[4096];
	scanf("%s", buf);

	printf("%d\n",atoi(buf));

	return 0;
}
