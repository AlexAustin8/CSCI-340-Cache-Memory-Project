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
static int arrLength = 1000000;
static int array[1000000];
static unsigned long arr[1000000];


int main(){

    struct timespec start, end;
	unsigned long res = 0, maxval, temp;
	int x, max = 0, y=0;
	/*  Used as a way to change distance between each reference
	    for different experiments. All tests done now have been in powers of 
	    10 (1, 10, 100, etc.), but we may want to do a little math with the
	    size of an int so we move in byte amounts that are a power of 2 */
	int interval = 1;

    //Go through the loop and meaure the time it takes for variable x to be assigned a value
    //from a position in an array. Sets the difference to a temp variable that is placed in arr[]
    //which serves as an array of the time values taken on each reference and used for other 
    //calculations such as mode.
	for(int i = 0; i<arrLength; i += interval){
        timespec_get(&start,TIME_UTC);
		x = array[i];
		timespec_get(&end,TIME_UTC);
        temp = end.tv_nsec - start.tv_nsec;
		arr[i] = temp;
		res += temp;
		y++;
	}
	float avg = (float)res / y;
	printf("Average: %f\n", avg);
   
    //Calculate the mode of the time values
	for(int i=0;i<arrLength; i+=interval){
		int count = 0;

		for(int j = 0; j < arrLength; j+= interval){
			if(arr[j] == arr[i]){
				++count;
			}
		}
		if(count > max){
			max = count;
			maxval = arr[i];
		}

	}

	printf("Mode: %lu\n", maxval);

}
