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
		// printf("%d\n", i);

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
long double timeAccesses(double timeVals[]) {
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
	    printf("%lf\n", timeVals[j]);
	}
    for (int j = 0; j < numTests; j++) {
    	totalTime = totalTime + timeVals[j];
    }
    return totalTime;
}

long double cacheSizes(double sizeVals[]) {
	char k;
	long double totalTime = 0;
   	struct timespec tstart, tend;

    for (int j = 0; j < numTests; j++) {
	    clock_gettime(CLOCK_MONOTONIC, &tstart);
	    for (int i = 0; i <= (numRuns*jumpVal); i+=jumpVal) {
	    	// printf("%d\n", i);
			k = array[i];
	    }
	    clock_gettime(CLOCK_MONOTONIC, &tend);
	    sizeVals[j] = ((tend.tv_nsec - tstart.tv_nsec)/(double)numRuns);
	    // printf("%lf\n", sizeVals[j]);
	}
    for (int j = 0; j < numTests; j++) {
    	totalTime = totalTime + sizeVals[j];
    }
    return totalTime;
}



int main(int argc, char** argv){
	numRuns = atoi(argv[2]);
	numTests = atoi(argv[3]);
	double timeVals[numTests];
	long double totalTime = timeAccesses(timeVals);
	double sizeVals[numTests];
	long double totalSizes = cacheSizes(sizeVals);

    printf("%Lf nanoseconds\n", totalTime/numTests);
    printf("%Lf nanoseconds\n", totalSizes/numTests);
    // for (int j = 0; j < numTests; j++) {
    // 	printf("%f\n", timeVals[j]);
    // }





























 // //    struct timespec start, end;
	// // unsigned long res = 0;0.0002273834
	// // int x, temp = 0, y;
	// // //interval issed as a way to change distance between each reference for different experiments
	// // interval = atoi(argv[1]);
	// // numRuns = atoi(argv[2]);
	// // numTests = atoi(argv[3]);

 // //    //To avoid segmentation faults :^)
 // //    if((interval * numRuns) > arrLength){
 // //    	printf("Error, given interval/run values will go beyond array bounds, highest index must be less then %f\n", arrLength);
 // //    	exit(0);
 // //    }


 // //    Runs the number of tests specified by user, where 
 // //      each test times a loop of user specified number of runs with a specified interval
 // //      between each index into the array 
 // //    for(k = 0; k<numTests; ++k){
	// //     y = 0;
	// //     timespec_get(&start,TIME_UTC);
	// //     // printf("%d\n", start.tv_nsec);
	// 	// for(int i = 0; y<numRuns; i += interval){
	// 	// 	x = array[i];
	// 	// 	y++;
	// 	// }
	// //     timespec_get(&end,TIME_UTC);
	// //     // printf("%d\n", end.tv_nsec);
	// //     temp = end.tv_nsec - start.tv_nsec;
	// //     printf("%d\n", temp/numRuns);
	// //     arr[k] = temp;
	// //     res += temp;
 // //    }


	// // float avg = (float)res / y;
    double mode = findMode(timeVals);
    double median = findMedian(timeVals);
	// // // printf("Average: %f\n", avg/numRuns);
    printf("Mode: %lf\n", mode);
    printf("Median: %lf\n", median);


    // // float avg = (float)res / y;
    mode = findMode(sizeVals);
    median = findMedian(sizeVals);
	// // // printf("Average: %f\n", avg/numRuns);
    printf("Mode: %lf\n", mode);
    printf("Median: %lf\n", median);


}