#include<stdio.h>
#define x 5
void main()
{
      int i,j,n,burst[x],process[x],wait[x],turn[x],priority[x],temp[x],position; // temp is for swapping values, position is for comparing, process is for sorting the process ID's according to priority, priority is for keeping the priority order
      float sum=0,total=0,average_wait,average_turnaround; //total is the sum of waiting times, sum is the sum of turnaround times,
      printf("Enter Total Number of Processes:  ");
      scanf("%d",&n);
      printf("\nEnter Burst Time and Priority For %d Processes\n", n);
      //For input from user of burst time and priority
      for(i=0;i<n;i++)
      {
            printf("\nP[%d]\n",i+1);
            printf("Process Burst Time:\t");
            scanf("%d",&burst[i]);
            printf("Process Priority:\t");
            scanf("%d", &priority[i]);
            process[i]=i+1;
      }
      // Finding out the priority order and their burst times using selection sorting
      for(i=0;i<n;i++)
      {
            position=i;
            for(j=i+1;j<n;j++)
            {
                // Sorting the priority order using selection sorting, finding out the minimum values
                  if(priority[j]<priority[position])
                  {
                        position=j;
                  }
            }
            //Sorting priority in order by swapping
            temp[i]=priority[i];
            priority[i]=priority[position];
            priority[position]=temp[i];
            //Swapping the burst time according to priority order
            temp[i]=burst[i];
            burst[i]=burst[position];
            burst[position]=temp[i];
            //Sorting the process id according to priority order
            temp[i]=process[i];
            process[i]=process[position];
            process[position]=temp[i];
      }

      printf("\nProcess ID\tBurst Time\t Waiting Time\t Turnaround Time\n");

      // For counting total waiting time, total turnaround time, average waiting time, average turnaround time
      for(i=0;i<n;i++)
      {
            wait[i]=0;
            for(j=0;j<i;j++)
            {
                  wait[i]=wait[i]+burst[j];
            }
            total=total+wait[i];

            turn[i]=burst[i]+wait[i];
            sum=sum+turn[i];
            printf("\n  P[%d]\t\t    %d\t\t     %d\t\t      %d\n", process[i],burst[i],wait[i],turn[i]);
      }

      average_wait=total/n;
      average_turnaround=sum/n;
      printf("\nAverage Waiting Time:\t%.2f", average_wait);
      printf("\nAverage Turnaround Time: %.2f\n", average_turnaround);
}

// End
