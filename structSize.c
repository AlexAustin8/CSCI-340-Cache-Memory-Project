#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>




int main(){
	struct timespec start;
	unsigned long y;
	int x,z,l;

	x = sizeof(start);
	z = sizeof(x);
	l = sizeof(y);



	printf("Struct: %d, int: %d, long: %d\n", x, z, l);


}