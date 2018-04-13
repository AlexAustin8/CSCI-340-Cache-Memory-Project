# CSCI-340-Cache-Memory-Project
Repo for CSCI-340 team project on cache memory

To Do: Everything :(
Edit: Above Statement Status-Accurate

#Update 1:
Upon spending some time attempting to structure something that may end up meeting specifications, a few things have been learned, notably the existence of the timeval struct from the <sys/time.h> which has higher resolution than the standard time() function that I was attempting to use. This higher resolution is doubtlessley more proper for the specifications for this project. Also, as far as empirical data gathering goes, the only thing that I have been able to ascertain thus far is that for the simple code provided as of the lastest commit, when we move through the array in a linear fashion (i+=1), there is a tendency for the time taken to be 1-2 microsecond. Meanwhile, if we move through larger iterations (i+=99) that attempt to remoce spatial locality cache loading, there is more of a tendency for things to take 4-5 nanoseconds. Although there is naturally much more to be done, this yields a bit of evidence pointing towards main memory accesses taking ~2-3x longer than cache accesses. 
