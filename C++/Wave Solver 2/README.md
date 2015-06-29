
---- Functionality of the code to solve wave equation----
The code can run using either a banded matrix or a full matrix in the following way:
1) For banded matrix run:
	make clean
	make banded
	./waveSolver waveparms.txt

2) For the full matrix run:
	make clean
	make full
	./waveSolver waveparms.txt


---- Comments ----

From the run it was noted that the code takes approximately 93.61 sec to run the full matrix while it significanly improves performance when using the banded matrix taking only 0.003392 sec to run. As a general rule, if the matrix is to become larger, i.e., more grid points or even decreasing the time step, then a full matrix will not be convenient since adding all those zeros to the operator slows down the process.
