#include<stdio.h>
#define x 5
void main()
{
        int i,n,burst[x],wait[x],turn[x],temp[x];
        float average_wait=0,average_turnaround_time=0;

        printf("Enter the no. of process: ");
        scanf("%d",&n);
        printf("Enter the burst time of the process: ");
        for(i=0;i<n;i++)
            scanf("%d",&burst[i]);


        temp[0]=0;
        wait[0]=0;
        turn[0]=0;
        printf("Process\t   Burst time\t  Waiting time\t  Turn around time");
        for(i=0;i<n;i++)
        {

            temp[i+1]=temp[i]+burst[i];
            wait[i]=temp[i];
            turn[i]=wait[i]+burst[i];
            average_wait=average_wait+wait[i];
            average_turnaround_time=average_turnaround_time+turn[i];
            printf("\n%d\t\t%d\t\t%d\t\t%d\n",i+1,burst[i],wait[i],turn[i]);
        }
        average_wait=average_wait/n;
        average_turnaround_time=average_turnaround_time/n;
        printf("\nAverage waiting time: %.3f\n",average_wait);
        printf("\nAverage turn around time: %.3f\n",average_turnaround_time);
}
