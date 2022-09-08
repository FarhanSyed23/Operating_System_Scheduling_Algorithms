#include<stdio.h>
#define x 20
int fcfs();  // A function declaration for FCFS
int sjf();   // A function declaration for SJF
int rr();    // A function declaration for Round Robin
int minimum();  // This function calculates the minimum average waiting time for the scheduling algorithms.
int array[x],burst[x],wait[x],turn[x],temp[x],remainTime[x],process[x];  // Arrays are globally declared so that all the functions can use it's index for calculations and store value.
int main()
{
        int i,n,timeQuantum;
        float ret,ret1,ret2; // ret is for FCFS, ret1 is for SJF, ret2 for Round Robin
        float c;             // a variable which holds the value of the minimum from function call

        printf("Enter the no. of process: ");
        scanf("%d",&n);

        printf("\nEnter the burst time: ");
        for(i=0;i<n;i++)
        {
        printf("\nFor P[%d]: ",i+1);
        scanf("%d",&burst[i]);
        process[i]=i+1;             // As index=0
        remainTime[i]=burst[i];     // For round robin
        }
        printf("\nEnter Time Quantum: ");
        scanf("%d",&timeQuantum);

        ret=fcfs(n,i,burst); //FCFS Function call
        ret1=sjf(n,i,burst,process); //SJF Function call
        ret2=rr(n,i,timeQuantum,burst,remainTime);  //Round Robin Function call
        c=minimum(0,10);     /* minimum function is called here where 0 is a value which will be needed for average waiting time calculation,
                                10 is a supposed index number limit passed as an argument for assigning indexes later,
                                c holds the value which is returned by minimum */

        printf("\n\n\nAll the waiting times for different scheduling algorithms are displayed below:");

        printf("\n\nAverage waiting time for FCFS: %.3f milliseconds.",ret);
        printf("\nAverage waiting time for SJF: %.3f milliseconds.",ret1);
        printf("\nAverage waiting time for Round Robin: %.3f milliseconds.",ret2);

        printf("\n\nThe minimum average waiting time is: %.3f milliseconds.",c);

        if(c==ret)  // If minimum happens to be equal to the FCFS average waiting time then.
        printf("\n\nThis average waiting time of %.3f milliseconds belongs to the FCFS.\nThe FCFS algorithm has the lowest average waiting time.\nThus the FCFS algorithm is the best scheduling algorithm for these schedules.\n",c);
    else if(c==ret1)  // If minimum happens to be equal to the SJF average waiting time then.
        printf("\n\nThis average waiting time of %.3f milliseconds belongs to the SJF.\nThe SJF algorithm has the lowest average waiting time.\nThus the SJF algorithm is the best scheduling algorithm for these schedules.\n",c);
    else  // If minimum happens to be equal to the Round Robin average waiting time then.
        printf("\n\nThis average waiting time of %.3f milliseconds belongs to the Round Robin.\nThe Round Robin algorithm has the lowest average waiting time.\nThus the Round Robin algorithm is the best scheduling algorithm for these schedules.\n");


        return 0;

}



int fcfs(int n,int j,int burst[]) //n is total input processes, j is index, burst[] is the burst time
{

        int w; // w is for holding the value of the average waiting time and returning it to the function call
        float average_wait,average_turnaround_time=0;
        temp[0]=0;
        wait[0]=0;
        turn[0]=0;
        printf("\n\n\t\t For First In First Out");
        printf("\n\n\nProcess\t   Burst time\t  Waiting time\t  Turn around time");
        for(j=0;j<n;j++)
        {

            temp[j+1]=temp[j]+burst[j];
            wait[j]=temp[j];
            turn[j]=wait[j]+burst[j];
            average_wait=average_wait+wait[j];
            average_turnaround_time=average_turnaround_time+turn[j];
            printf("\n%d\t\t%d\t\t%d\t\t%d\n",j+1,burst[j],wait[j],turn[j]);
        }
        average_wait=(float)average_wait/n;
        average_turnaround_time=(float)average_turnaround_time/n;
        w=average_wait;   //average_wait is assigned to a variable for returning it to the function call;
        printf("\nAverage waiting time: %.3f\n",average_wait);
        printf("\nAverage turn around time: %.3f\n",average_turnaround_time);
        minimum(w,0);     // Average waiting time is passed with an index 0 assigned to it for FCFS
        return w;

}

int sjf(int n,int i,int burst[],int process[])
{
    int j,total=0,sum=0,position,y; // total is the sum of waiting times, sum is the sum of turnaround times, position is for comparing
        float average_wait=0,average_turnaround_time=0;


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
            temp[i]=process[i];
            process[i]=process[position];
            process[position]=temp[i];
        }

        printf("\n\n\t\t For Shortest Job First");
        printf("\n\n\nProcess\t   Burst time\t  Waiting time\t  Turn around time");

        // For counting total waiting time, total turnaround time, average waiting time, average turnaround time
        for(i=0;i<n;i++)
        {

            wait[i]=0;                  //wait[index] will be assigned 0 every time
            for(j=0;j<i;j++)
                wait[i]=wait[i]+burst[j];  // Equation for the waiting time

            total=total+wait[i];       // total is the summation of the waiting times

            turn[i]=wait[i]+burst[i];  // Equation for turnaround time
            sum=sum+turn[i];           // sum is the summation of the turnaround times
            printf("\nP[%d]\t\t%d\t\t%d\t\t%d\n",process[i],burst[i],wait[i],turn[i]);
        }

        average_wait=(float)total/n;
        average_turnaround_time=(float)sum/n;
        y=average_wait;
        printf("\nAverage waiting time: %.3f\n",average_wait);
        printf("\nAverage turn around time: %.3f\n",average_turnaround_time);
        minimum(y,1);    // Average waiting time is passed with an index 1 assigned to it for SJF
        return y;
}

int rr(int n,int i,int t_Quantum,int burst[],int remaining[])
{
    int waitingTime=0,ExecutionTime=0,flag=0,ProRemains,z; //remaining is for remaining time,ProRemains is for the processes that are remaining
    float total_Waiting_Time=0,total_turnaround_Time=0;
    ProRemains=n;

    printf("\n\n\t\t For Round Robin ");
    printf("\n\n\nProcess\t   Burst time\t  Waiting time\t  Turnaround time");
    for(i=0;ProRemains!=0;)


            /* This below condition is to check the remaining time for any process if it is less than
            or equal with the time quantum slice or not and also to check the remaining time is greater than 0 or not.
            If both conditions are true that means the process can execute fully at once. */


    {

     /* It is for those processes which are equal or smaller than time quantum. Sets flag 1 so that these process can be declared finished
        later in another if loop. */
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
        else
            i=0;

    }

    total_Waiting_Time=total_Waiting_Time/n;
    total_turnaround_Time=total_turnaround_Time/n;
    z=total_Waiting_Time;
    printf("\nThe Average Waiting Time : %.5f \n",total_Waiting_Time);
    printf("\nThe Average Turnaround Time : %.5f \n",total_turnaround_Time);
    minimum(z,2);    // // Average waiting time is passed with an index 2 assigned to it for Round Robin
    return z;

}
int minimum(int value,int position)
{
        float min=array[0];   // minimum is initially assigned to the 0 indexed average time
        array[position]=value;   // the average waiting times of FCFS, SJF, RR are assigned to their index values 0,1,2
        for (position = 0; position <3 ; position++)
            {
                if (array[position]<min)
                    min=array[position];
            }

        return min;

}





