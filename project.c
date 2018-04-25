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


double findMode(int arraySize, double values[]){
	double maxval, temp;
	int max = 0;

	for(int i=0;i<arraySize; ++i){
		int count = 0;
		for(int j = 0; j < arraySize; ++j){
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
double findMedian(int arraySize, double values[]){
	qsort((void*)values, arraySize, sizeof(values[0]), comparator);

   
	if(arraySize%2 == 0){
		return((values[arraySize/2] + values[arraySize/2 -1]) / 2.0);
	}
	else{
		return values[arraySize/2];
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
		sizeVals[j] = (tend.tv_nsec - tstart.tv_nsec);
	}
}

void getTime() {
	double timeVals[10000];
	double lowLevelTotal = 0;
	int lowLevelCount = 0;
	double highLevelTotal = 0;
	int highLevelCount = 0;	
	double mainMemoryTotal = 0;
	int mainMemoryCount = 0;
	
	for (int i = 0; i < 100; i++) {
		timeAccesses(100, 10000, timeVals);

 		double lowTotal = 0;
		int lowCount = 0;	
		double highTotal = 0;	
		int highCount = 0;

		for (int k = 0; k < 10000; k++) {
			if (timeVals[k] < 10) {
				lowTotal += timeVals[k];
				lowCount++;
			}			
			else if (timeVals[k] > 10 && timeVals[k] < 35) {
				highTotal += timeVals[k];
				highCount++;
			}
		}
		if (lowTotal/lowCount > 0) {
			lowLevelTotal += (lowTotal/lowCount);
			lowLevelCount++;
		}
		if (highTotal/highCount > 0) {
			highLevelTotal += (highTotal/highCount);
			highLevelCount++;
		}
	}
	printf("The average access time for the lower level caches is: %lf nanoseconds.\n", lowLevelTotal/lowLevelCount);
	printf("The average access time for the higher level caches is: %lf nanoseconds.\n", highLevelTotal/highLevelCount);

	for (int i = 0; i < 100; i++) {
		timeAccesses(1, 10000, timeVals);

		double memoryTotal = 0;
		int memoryCount = 0;

		for (int k = 0; k < 10000; k++) {
			if (timeVals[k] > 100 && timeVals[k] < 150) {
				memoryTotal += timeVals[k];
				memoryCount++;
			}
		}
		if (memoryTotal/memoryCount > 0) {
			mainMemoryTotal += (memoryTotal/memoryCount);
			mainMemoryCount++;
		}
	}
	printf("The average access time for the main memory is: %lf nanoseconds.\n", mainMemoryTotal/mainMemoryCount);

}

void getSize() {
	double sizeVals[5];
	double median, lastMedian;
	double mode, lastMode;
	int interval;

	double intervals[100];
	for(int o = 0; o < 100; o++){
		median = 0, lastMedian = 0;
		interval = 1;
		
		while(interval < 32768){
			cacheSizes(interval, 1024, 5, sizeVals);
			median = findMedian(5, sizeVals);
			if(median/lastMedian > 2 && lastMedian != 0){
				break;
			}
			interval = interval * 2;
			lastMedian = median;	 
		}
		intervals[o] = interval;
	}
	mode = findMode(100, intervals);
	printf("The approximate total cache size is between: %0.0f - %0.0f Kilo-bytes.\n", (mode/2), mode);	

	mode = 0, lastMode = 0;
	interval = 1;
	while(interval < 2048){
		cacheSizes(interval, 100000, 5, sizeVals);
		mode = findMode(5, sizeVals);
		if(mode/lastMode > 1.5 && lastMode != 0){
			break;
		}
		interval *= 2;
		lastMode = mode;	 
	}
	printf("The approximate cache block size of level one cache is: %d bytes.\n", interval);
}



int main(int argc, char** argv){
	getTime();
	getSize();
}