#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


/* When run from the command line, this requires three parameters: first being the interval
  between each index, the second being the number of runs to do for each test, and the third 
  being the number of tests to do.

 */



static double arrLength = 1000000000;
static char array[1000000000];         //Switched from int to char array due to S I N G L E - B Y T E N E S S
static int arr[100000000];
int interval, numRuns, numTests, k;



int findMode(){
	int maxval, temp;
	int max = 0;

	for(int i=0;i<numTests; ++i){
		int count = 0;
		// printf("%d\n", i);

		for(int j = 0; j < numTests; ++j){
			if(arr[j] == arr[i]){
				++count;
			}
		}
		if(count > max){
			max = count;
			maxval = arr[i];
		}
	}
    return maxval;
}


//Simple comparator function for sorting purposes, functions akin to Java compareTo()
int comparator(const void* x, const void* y){
	return ( *(int*)x - *(int*)y);
}



//Find Median value of results by sorting list returns the mean of 2 middle elements
//if there is an even number of elements, else returns middle element
int findMedian(){
	qsort((void*)arr, k, sizeof(arr[0]), comparator);
	
   
	if(k%2 == 0){
		return((arr[k/2] + arr[k/2 -1]) / 2.0);
	}else{
		return arr[k/2];
	}

}



int main(int argc, char** argv){


    struct timespec start, end;
	unsigned long res = 0;
	int x, temp = 0, y;
	//interval issed as a way to change distance between each reference for different experiments
	interval = atoi(argv[1]);
	numRuns = atoi(argv[2]);
	numTests = atoi(argv[3]);

    //To avoid segmentation faults :^)
    if((interval * numRuns) > arrLength){
    	printf("Error, given interval/run values will go beyond array bounds, highest index must be less then %f\n", arrLength);
    	exit(0);
    }


    /*Runs the number of tests specified by user, where 
      each test times a loop of user specified number of runs with a specified interval
      between each index into the array */
    for(k = 0; k<numTests; ++k){
	    y = 0;


	    timespec_get(&start,TIME_UTC);
		for(int i = 0; i<(numRuns*interval); i += interval){
			x = array[i];
		}
		x = array[0];
	    timespec_get(&end,TIME_UTC);
	    temp = end.tv_nsec - start.tv_nsec;
        printf("Test: %d: %d\n",k, temp);
	    arr[k] = temp;
	    res += temp;
    }


	float avg = (float)res / y;
    int mode = findMode();

    int median = findMedian();

	printf("Average: %f\n", avg);
    printf("Mode: %d\n", mode);
    printf("Median: %d\n", median);

  //  for(int q = 0; q < 50; q++){
    //	printf("%d\n", arr[q]);
    //}


}
   