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
// int jumpVal, numTests, numRuns;


double findMode(int numTests, double values[]){
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
double findMedian(int numTests, double values[]){
	qsort((void*)values, numTests, sizeof(values[0]), comparator);

   
	if(numTests%2 == 0){
		return((values[numTests/2] + values[numTests/2 -1]) / 2.0);
	}
	else{
		return values[numTests/2];
	}

}
void timeAccesses(int numRuns, int numTests, double timeVals[]) {
	char k;
	struct timespec tstart, tend;

	for (int j = 0; j < numTests; j++) {
		clock_gettime(CLOCK_MONOTONIC, &tstart);
		for (int i = 0; i <= numRuns; i++) {
			k = array[(i + (numRuns * j))];
		}
		clock_gettime(CLOCK_MONOTONIC, &tend);
		timeVals[j] = ((tend.tv_nsec - tstart.tv_nsec)/(double)numRuns);
	}
}

void cacheSizes(int interval, int numRuns, int numTests, double sizeVals[]) {
	char k;
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
}

void getTime() {
	double highAvg = 0;
	int highTotal = 0;
	double lowAvg = 0;
	int lowTotal = 0;	
	for (int i = 0; i < 100; i++) {
		double timeVals[10000];
		timeAccesses(100, 10000, timeVals);
		double mode = findMode(10000, timeVals);
		double median = findMedian(10000, timeVals);
		// // // printf("Average: %f\n", avg/numRuns);
		// printf("Mode: %lf\n", mode);
		// printf("Median: %lf\n", median);
		double average = 0;
		double lowaverage = 0;
		int averageVals = 0;
		int lowaverageVals = 0;
		for (int k = 0; k < 10000; k++) {
			if (timeVals[k] > 10 && timeVals[k] < 35) {
				// printf("%lf\n", timeVals[k]);
				average += timeVals[k];
				averageVals++;
			}
			else if (timeVals[k] < 10) {
				lowaverage += timeVals[k];
				lowaverageVals++;
			}
		}
		// printf("%lf\n", (average/averageVals));
		if (average/averageVals > 0) {
			highAvg += (average/averageVals);
			highTotal++;
		}
		if (lowaverage/lowaverageVals > 0) {
			lowAvg += (lowaverage/lowaverageVals);
			lowTotal++;
		}
	}
	printf("%lf\n", lowAvg/lowTotal);
	printf("%lf\n", highAvg/highTotal);
	double sumAvgs = 0;
	double sumTotal = 0;
	for (int i = 0; i < 100; i++) {
		double timeVals[10000];
		timeAccesses(1, 10000, timeVals);
		double mode = findMode(10000, timeVals);
		double median = findMedian(10000, timeVals);
		// // // printf("Average: %f\n", avg/numRuns);
		// printf("Mode: %lf\n", mode);
		// printf("Median: %lf\n", median);
		double average = 0;
		int averageVals = 0;
		for (int k = 0; k < 10000; k++) {
			if (timeVals[k] > 50 && timeVals[k] < 200) {
				// printf("%lf\n", timeVals[k]);
				average += timeVals[k];
				averageVals++;
			}
		}
		// printf("%lf\n", (average/averageVals));
		if (average/averageVals > 0) {
			sumAvgs += (average/averageVals);
			sumTotal++;
		}
	}
	printf("%lf\n", sumAvgs/sumTotal);

}


int main(int argc, char** argv){
	getTime();
	int jumpVal = atoi(argv[1]);
	int numRuns = atoi(argv[2]);
	int numTests = atoi(argv[3]);
	// double timeVals[numTests];
	// long double totalTime = timeAccesses(numRuns, numTests, timeVals);
	double sizeVals[numTests];

 //    printf("%Lf nanoseconds\n", totalTime/numTests);
	// printf("%Lf nanoseconds\n", totalSizes/numTests);
	int intervals[100];
	double median = 0, lastMedian = 0;
	for(int o = 0; o < 100; o++){
		median = 0, lastMedian = 0;
		int jumpInterval = 1;
		while(jumpInterval < 32000){
			cacheSizes(jumpInterval, 1024, 5, sizeVals);
			median = findMedian(5, sizeVals);
			// printf("MID:%lf\n", (median));
			// printf("%lf\n", median/lastMedian);
			if(median/lastMedian > 2 && lastMedian != 0){
				break;
			}
			jumpInterval = jumpInterval *2;
			lastMedian = median;	 
		}
		intervals[o] = jumpInterval;
	}

	for(int u = 0; u < 100; u++){
		printf("Interval: %d\n", intervals[u]);
	}


	// printf("%Lf nanoseconds\n", totalTime/numTests);
	// printf("%Lf nanoseconds\n", totalSizes/numTests);


 //    // float avg = (float)res / y;
	// double mode = findMode(timeVals);
	// median = findMedian(timeVals);
 //    // // // printf("Average: %f\n", avg/numRuns);
	// printf("Mode: %lf\n", mode);
	// printf("Median: %lf\n", median);
	// for (int k = 0; k < numTests; k++) {
 //   	 if (timeVals[k] < (median)) {
 //   		 printf("%lf\n", timeVals[k]);
 //   	 }

	// }


	// // // float avg = (float)res / y;
	// mode = findMode(sizeVals);
	// median = findMedian(sizeVals);
 //    // // // printf("Average: %f\n", avg/numRuns);
	// printf("Mode: %lf\n", mode);
	// printf("Median: %lf\n", median);




	// // float avg = (float)res / y;
 //    double mode = findMode(timeVals);
 //    double median = findMedian(timeVals);
	// // // // printf("Average: %f\n", avg/numRuns);
 //    printf("Mode: %lf\n", mode);
 //    printf("Median: %lf\n", median);
 //    for (int k = 0; k < numTests; k++) {
 //    	if (timeVals[k] < (median)) {
 //    		printf("%lf\n", timeVals[k]);
 //    	}

 //    }


 //    // // float avg = (float)res / y;
	double mode = findMode(numTests, sizeVals);
	median = findMedian(numTests, sizeVals);
	// // // printf("Average: %f\n", avg/numRuns);
	printf("Mode: %lf\n", mode);
	printf("Median: %lf\n", median);


}