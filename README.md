# CPP-multithreading-basic

An introduction to pthreads in CPP. A specific input is given in the same format everytime (this is a gurantee) it includes # of symbols 
a key and binary message. We must use 1 set of threads to decode the binary message and another set of threads to determine the frequency of 
each symbol.

I approached this by first getting all the inputs, storing them in a class, then converting my key to binary and determining the frequency using
1 set of pthreads. Next I decoded the message using a second set of pthreads. To handle sychronizing the threads I simply passed a vector of objects to the threads
so each thread didn't have access to the same object.
