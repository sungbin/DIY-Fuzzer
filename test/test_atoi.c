#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
main(int argc, char* argv[])
{

	char buf[1024];
//	fgets(buf, 1024, stdin);
//	buf[strlen(buf) - 1] = '\0';

	scanf("%s", buf);

	printf("%d\n",atoi(buf));

	return 0;
}
