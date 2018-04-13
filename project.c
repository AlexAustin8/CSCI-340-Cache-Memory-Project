#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


/* This is a base from which
   our empirical procedures will grow
   */


//Declaring a static variable so that it Stays off of stack.
//For the purpose of this project I am attempting to declare a massive array
//Which actually overload the stack and causes a segmentation fault upon declaration
static int array[10000][10000];


int main(){
	//long double array[100000][100000];

    struct timeval start, end;
	unsigned long res;
	int x;

	for(int i = 0; i<10000; i += 99){
        gettimeofday(&start,NULL);
		x = array[i][i];
		gettimeofday(&end,NULL);
		res = end.tv_usec - start.tv_usec;
		//printf("Times: %f, %f", (float)start, (float)end);
		printf("Take %d: %lu\n", i, res);
	}
}