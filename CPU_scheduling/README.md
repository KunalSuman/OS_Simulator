In Child_Parent  7 child process were created each hiving a different pid and parent waits for each of the child process to complete seeded the random rand() with getpid() so that   each program runs use of rand()%100 to fix the range for the random number as specified in the question and + 1 as a modifier which will shift the values by 1 so excluding 0.

In Child_Parent_binary Binarysearch is implemented so that everytime the array is divided into 2 parths that is excluding the part where one half is removed to look for target  value a new child is created using fork(), this way log(n) effeciency is maintained and completing the objective given in question 2

In Local_Operations 3 different programs are being runned by the main program whic created a new child for each process and exec is used to jump to different program and getting rid of main to conserve space all the files in the q3 folder are compiled using make as mentioned in question along with a clean command to get rid of all exe files.
in cal.c ussed the zellers formula to construct a callender of tthe given month and arguments can be passed through the commandline to get for specific month . this file is also being used in date.c hence (argc == 4)condition so that i can get the day from this file. in callender the -1 represents that month doesn't start from that day;
ex : for this month
Mon Tue Wed Thus Fri Sat  Sun

 -1   -1   -1   -1   -1   -1   1
 2   3   4   5   6   7   8
 9   10   11   12   13   14   15
 16   17   18   19   20   21   22
 23   24   25   26   27   28   29
 30
In date.c I have read the system files to get the system information and printed in the form of linux shell and day from the cal.c program. i have done string manupiltion to read rtc_time and Utc_time and printed in the format it is same as in unix based system ex :Sun Sep 15 22:44:03 IST 2024
In uptime.c same methord is used to find the total uptime of the system in HH::MM::SS format


In Scheduling algorithms : implementation of FIFO , SRTF ,SJF and round robin is simulated by different methords . overall i have usede bubble sort in all the progams to first sort by order or arrival then by bursttime in  SJF for rr i have use clock and subtracted it form the burst time and rotated the values till the burst timeof all process are 0 formula used for the ATT and RT are [turnaround time/total processses] and [response time / total process]
