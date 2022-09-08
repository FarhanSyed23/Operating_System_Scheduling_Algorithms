#include<stdio.h>
#define max 5
void main()
{
    int i,n,burst[max],remaining[max],ProRemains,waitingTime=0,ExecutionTime=0,t_Quantum,flag=0; //remaining is for remaining time,ProRemains is for the processes that are remaining
    float total_Waiting_Time=0,total_turnaround_Time=0;
    printf("Enter the Number of Process: ");
    scanf("%d",&n);
    ProRemains=n;

    printf("\nEnter Burst Time: \n");
    for(i=0;i<n;i++){
        printf("For P[%d]: ",i+1);
        scanf("%d",&burst[i]);
        remaining[i]=burst[i]; // initially assuming that remaining time for any process is equal to it's burst time
    }
    printf("\nEnter Time Quantum: ");
    scanf("%d",&t_Quantum);

    printf("\n");
    printf("Process\t   Burst time\t  Waiting time\t  Turnaround time");
    for(i=0;ProRemains!=0;)

    /* This below condition is to check the remaining time for any process if it is less than
        or equal with the time quantum slice or not and also to check the remaining time is greater than 0 or not.
        If both conditions are true that means the process can execute fully at once. */

    {
     /* It is for those processes which are equal or smaller than time quantum. Sets flag 1 so that these process can be declared finished later in another if loop. */
        if(remaining[i]<=t_Quantum && remaining[i]>0)
            {
            ExecutionTime=ExecutionTime+remaining[i];
            remaining[i]=0; // declares that the process has no time remaining
            flag=1; //sets flag 1
            waitingTime=ExecutionTime-burst[i];
            }

     /* It is for those process which are greater than time quantum. */
        else if(remaining[i]>t_Quantum && remaining[i]>0)
            {
            remaining[i]=remaining[i]-t_Quantum; //Saves remaining time of a process
            ExecutionTime=ExecutionTime+t_Quantum;

            }

    /* It is for those processes which have ended execution and they are printed here after executing. */
        if(flag==1 && remaining[i]==0)
            {

            printf("\nP[%d]\t\t %d\t\t %d\t\t%d\n",i+1,burst[i],waitingTime,ExecutionTime);
            total_Waiting_Time=total_Waiting_Time+waitingTime;
            total_turnaround_Time=total_turnaround_Time+ExecutionTime;
            flag=0;  //Flag is set 0
            ProRemains--; //The executed process is removed.
           }

  // This is to check if the round is completed or not. If completed, then sets the process index to 0.
        if(i==n-1)
            i=0;
    // This is for the next process in the round.
        else if(burst[i+1]<=ExecutionTime)
            {
            i++;
            }

    }

    total_Waiting_Time=total_Waiting_Time/n;
    total_turnaround_Time=total_turnaround_Time/n;
    printf("\nThe Average Waiting Time : %.5f \n",total_Waiting_Time);
    printf("\nThe Average Turnaround Time : %.5f \n",total_turnaround_Time);

}




