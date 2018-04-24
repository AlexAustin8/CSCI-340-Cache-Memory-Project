#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


/* When run from the command line, this requires three parameters: first being the interval
  between each index, the second being the number of runs to do for each test, and the third 
  being the number of tests to do.

 */

//Switched from int to char array due to S I N G L E - B Y T E N E S S
static char array[100000000];    
int jumpVal, numTests, numRuns;


double findMode(double values[]){
	double maxval, temp;
	int max = 0;

	for(int i=0;i<numTests; ++i){
		int count = 0;
		for(int j = 0; j < numTests; ++j){
			if(values[j] == values[i]){
				++count;
			}
		}
		if(count > max){
			max = count;
			maxval = values[i];
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
double findMedian(double values[]){
	qsort((void*)values, numTests, sizeof(values[0]), comparator);

   
	if(numTests%2 == 0){
		return((values[numTests/2] + values[numTests/2 -1]) / 2.0);
	}
	else{
		return values[numTests/2];
	}

}
long double timeAccesses(int numRuns, int numTests, double timeVals[]) {
	char k;
	long double totalTime = 0;
   	struct timespec tstart, tend;

    for (int j = 0; j < numTests; j++) {
	    clock_gettime(CLOCK_MONOTONIC, &tstart);
	    for (int i = 0; i <= numRuns; i++) {
			k = array[(i + (numRuns * j))];
	    }
	    clock_gettime(CLOCK_MONOTONIC, &tend);
	    timeVals[j] = ((tend.tv_nsec - tstart.tv_nsec)/(double)numRuns);
	}
    for (int j = 0; j < numTests; j++) {
    	totalTime = totalTime + timeVals[j];
    }
    return totalTime;
}

long double cacheSizes(int interval, int numRuns, int numTests, double sizeVals[]) {
	char k;
	long double totalTime = 0;
   	struct timespec tstart, tend;

    for (int j = 0; j < numTests; j++) {
	    clock_gettime(CLOCK_MONOTONIC, &tstart);
	    for (int i = 0; i <= (numRuns*interval); i+=interval) {
			k = array[i];
	    }
	    k = array[0];
	    clock_gettime(CLOCK_MONOTONIC, &tend);
	    sizeVals[j] = ((tend.tv_nsec - tstart.tv_nsec)/(double)numRuns);
	}
    for (int j = 0; j < numTests; j++) {
    	totalTime = totalTime + sizeVals[j];
    }
    return totalTime;
}



int main(int argc, char** argv){
	jumpVal = atoi(argv[1]);
	numRuns = atoi(argv[2]);
	numTests = atoi(argv[3]);
	double timeVals[numTests];
	long double totalTime = timeAccesses(numRuns, numTests, timeVals);
	double sizeVals[numTests];
	long double totalSizes = cacheSizes(jumpVal, numRuns, numTests, sizeVals);

    printf("%Lf nanoseconds\n", totalTime/numTests);
    // printf("%Lf nanoseconds\n", totalSizes/numTests);


	// float avg = (float)res / y;
    double mode = findMode(timeVals);
    double median = findMedian(timeVals);
	// // // printf("Average: %f\n", avg/numRuns);
    printf("Mode: %lf\n", mode);
    printf("Median: %lf\n", median);
    for (int k = 0; k < numTests; k++) {
    	if (timeVals[k] < (median)) {
    		printf("%lf\n", timeVals[k]);
    	}

    }


    // // float avg = (float)res / y;
    mode = findMode(sizeVals);
    median = findMedian(sizeVals);
	// // // printf("Average: %f\n", avg/numRuns);
    printf("Mode: %lf\n", mode);
    printf("Median: %lf\n", median);


}