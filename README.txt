# CSCI-340-Cache-Memory-Project
# Completed by Alexander Austin and Kyle Sheeley

To execute our project, run the following commands in the terminal:
1. "cd" to the location of the project.c file (this location should also contain the Makefile and the README.txt)
2. "make"
3. "./runProject"
(No input arguements are necessary to run the file) 

Running the "./runProject" command in the terminal should produce an output of five lines:
Line 1. Lower level cache speed
Line 2. Higher level cache speed
Line 3. Main memory speed
Line 4. Total cache size
Line 5. Cache block size

To calculate the time of cache accesses vs. main memory accesses, we ran a long loop of indexing from an array and used the total time to calculate the average time per index, and noticed leaps in time taken at regular intervals. We deduced that these leaps arose when the requested memory location was not in the cache and required a main memory access. The difference between these times is that the cache access speed range is about 5-25 ns and the main memory access speed range is about 100-150 ns. To calculate cache size, we did continuous memory indexes with increasing distance on each and at the end of each set of indices the first index of the array was accessed again, with the idea being that once we reached a point where the amount of blocks needed surpassed cache size, the block containing the first index would be kicked out to make room for the new required block, and thus we would see a time increase once the interval x num accesses value met or exceeded the cache size. Block size worked in a somewhat similar manner, but worked by accessing fewer times with a more confined interval.
