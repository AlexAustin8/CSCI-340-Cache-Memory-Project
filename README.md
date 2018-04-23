# CSCI-340-Cache-Memory-Project
Repo for CSCI-340 team project on cache memory

To Do: Everything :(
Edit: Above Statement Status-Accurate

#Update 1:
Upon spending some time attempting to structure something that may end up meeting specifications, a few things have been learned, notably the existence of the timeval struct from the <sys/time.h> which has higher resolution than the standard time() function that I was attempting to use. This higher resolution is doubtlessley more proper for the specifications for this project. Also, as far as empirical data gathering goes, the only thing that I have been able to ascertain thus far is that for the simple code provided as of the lastest commit, when we move through the array in a linear fashion (i+=1), there is a tendency for the time taken to be 1-2 microsecond. Meanwhile, if we move through larger iterations (i+=99) that attempt to remoce spatial locality cache loading, there is more of a tendency for things to take 4-5 nanoseconds. Although there is naturally much more to be done, this yields a bit of evidence pointing towards main memory accesses taking ~2-3x longer than cache accesses. 

#Update 2: 
Created Makefile. Modularity will be added when the program is running to specifications successfully
Both makefile and modularity will be editted at later times.

#Update 3: 
Some modularity added w/ mode function, program now takes command line arguments to specify # tests, #runs per test and interval size, and timing is now done
on the entire loop as opposed to the single data access. This loop itself is now placed in a loop that runs for the number of tests

#Update 4: 
Median Function added, as well after some empirical testing, results have been pretty consistent with all results being consistent per jump interval size until it reaches 32768 bytes (32k), which leads me to believe that the block sizes seem to be around 32k. Furthermore, cache accesses take an average of 3000-4000 ms and main memory accesses around 10500 ms, which is a >50% increase in access time. More accurate stats can be performed later 

#Update 5:
Added modularity with the timeAccesses function. Corrected and perfected time measuring standards and devices.
Output status: Unoptimal
Input status: Semioptimal
Code status: better than expected

#Update 6:
Invalid math equation found in code. Issue: rectified.
