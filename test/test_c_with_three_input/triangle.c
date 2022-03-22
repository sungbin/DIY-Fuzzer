#include <stdio.h>

#include "./trace-pc.h"

FILE * bcov_fp = 0x0;

int 
main ()
{
	bcov_fp = fopen("./temp.bcov", "wb");

	int a, b, c ;
	int match ;

	scanf("%d %d %d", &a, &b, &c) ;

	match = 0 ;
	if (a == b)
		match = match + 1 ;
	if (a == c)
		match = match + 2 ;
	if (b == c)
		match = match + 3 ;

	if (match == 0) {
		if ((a + b) <= c)
			printf("Not a triangle\n") ;
		else if ((b + c) <= a)
			printf("Not a triangle\n") ;
		else if ((a + c) <= b)
			printf("Not a triangle\n") ;
		else
			printf("Scalene\n") ;
	}
	else if (match == 1) {
		if ((a + c) <= b)
			printf("Not a triangle\n") ;
		else 
			printf("Isosceles\n") ;
	}
	else if (match == 2) {
		if ((a + c) <= b)
			printf("Not a triangle\n") ;
		else 
			printf("Isosceles\n") ;
	}
	else if (match == 3) {
		if ((b + c) <= a)
			printf("Not a triangle\n") ;
		else
			printf("Isosceles\n") ;
	}
	else {
		printf("Equilateral\n") ;
	}

	fclose(bcov_fp);

	return 0 ;
}
