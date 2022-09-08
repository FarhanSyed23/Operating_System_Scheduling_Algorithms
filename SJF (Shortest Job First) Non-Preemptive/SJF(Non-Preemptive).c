#include<stdio.h>
#define x 5
void main()
{
        int i,j,n,burst[x],wait[x],turn[x],temp[x],total=0,sum=0,position; // total is the sum of waiting times, sum is the sum of turnaround times, temp is for swapping values, position is for comparing
        float average_wait=0,average_turnaround_time=0;

        printf("Enter the no. of process: ");
        scanf("%d",&n);

        for(i=0;i<n;i++)
        {
            printf("Enter the burst time of P%d: ",i+1);
            scanf("%d",&burst[i]);
        }

        // Finding out the shortest job using selection sorting
        for(i=0;i<n;i++)
        {
            position=i;
            for(j=i+1;j<n;j++)
            {
                // Sorting the shortest jobs using selection sorting, finding out the minimum values
                if(burst[j]<burst[position])
                    position=j;
            }
            // Swapping for minimum value
            temp[i]=burst[i];
            burst[i]=burst[position];
            burst[position]=temp[i];
        }

        printf("Process\t   Burst time\t  Waiting time\t  Turn around time");

        // For counting total waiting time, total turnaround time, average waiting time, average turnaround time
        for(i=0;i<n;i++)
        {
            wait[i]=0;                  //wait[index] will be assigned 0 every time
            for(j=0;j<i;j++)
                wait[i]=wait[i]+burst[j];  // Equation for the waiting time

            total=total+wait[i];       // total is the summation of the waiting times

            turn[i]=wait[i]+burst[i];  // Equation for turnaround time
            sum=sum+turn[i];           // sum is the summation of the turnaround times
            printf("\nP%d\t\t%d\t\t%d\t\t%d\n",i+1,burst[i],wait[i],turn[i]);
        }

        average_wait=total/n;
        average_turnaround_time=sum/n;
        printf("\nAverage waiting time: %.3f\n",average_wait);
        printf("\nAverage turn around time: %.3f\n",average_turnaround_time);
}

// End
