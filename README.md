# Multi-threaded sorting program
Divide and conquer
A list of integers is divided into two smaller lists of equal size.
Two separate threads (which we will term sorting threads) 
sort each sub-list using selection sort algorithm. The two sub-lists are 
then merged by a third thread—a merging thread
—which merges the two sub-lists into a single sorted list using merge sort algorithm.

To divide the array into 2 threads I will use work-sharing construct "sections"
in Open MP
