/*
 *      Yehonatan Arama 207938903
 *      Dvir Zaguri     315602284
        This program was written by us and only by us.
        Every attempt to copy the code or part of it, will consider as theft and will handle accordingly
*/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "mpi.h"

int main(int argc, char  **argv)
{
        int num_of_throws = 2147483647; //value of INT_MAX
        int num_of_tasks;
        int num_of_throws4task;
        float pi;
        int rank;
        int my_time = (int)time(NULL);
        int hits = 0;
        double startTime;
        double endTime;
        int sum_number_of_hits;
        MPI_Status status;
        MPI_Init(&argc,&argv);                                                  //stating the MPI section!
        if (MPI_SUCCESS != MPI_Comm_size(MPI_COMM_WORLD,&num_of_tasks)){        //getting the number of task from the MPI interface... if not successful we abort the program.. was written for debug perpuses and we left it as is, for good practice.
                MPI_Abort(MPI_COMM_WORLD, 1);
        }
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);                                    //getting the rank of the current process
        startTime = MPI_Wtime();                                                //saving the current time
        num_of_throws4task = num_of_throws/num_of_tasks;                        //Each process is getting equal number of throws
        srand(my_time*rank);                                                    //Setting Unique SEED each run for each process 
        for (int i = 0; i < num_of_throws4task; i++)                    
        {
                float x = (((float)rand()) / (float)(RAND_MAX/2) )-1;           //Each process looping for the number of throws, and randomize x value and y value. "throw darts and count if hit." 
                float y = (((float)rand()) / (float)(RAND_MAX/2) )-1;
                float rad = (x*x) + (y*y);
                if (rad <= 1){
                        hits++;
                }
        }
        MPI_Reduce(&hits , &sum_number_of_hits , 1 , MPI_INT , MPI_SUM , 0 , MPI_COMM_WORLD);   //We believe that Reduce is the best function for this program, because we need to sum up all the hits from each process to one variable for calculating pi 
        if (rank == 0){                                                                         //only one chosen process is calculating the value of pi and printing the result to the user
                pi =4*((float) sum_number_of_hits/num_of_throws);
                endTime = MPI_Wtime();                                                          //again - sampling the current time
                printf("pi is:%lf\nThe time of the run is:%lf\n\n\n",pi,endTime-startTime);
       }
       MPI_Finalize();                                                                          //finishing the MPI sequence
       return 0;                                                                                //returning 0 to signal the parent program for a successful execution
}