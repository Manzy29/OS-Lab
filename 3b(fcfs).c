#include<stdio.h>
#include<stdlib.h>
typedef struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int tt;
    int wt;
    int rt;
}pro;
void fcfs(pro[],int);
void main()
{
    int n;
    printf("Enter no. of processes\n");
    scanf("%d",&n);
    pro p[n];
    for(int i=0;i<n;i++)
    {
        printf("Process %d\n",i+1);
        printf("Enter AT: ");
        scanf("%d",&p[i].at);
        printf("Enter BT: ");
        scanf("%d",&p[i].bt);
        p[i].pid=i+1;
    }
    printf("Sorting process based on arrival time\n");
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].at>p[j+1].at)
            {
                pro temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    fcfs(p,n);
}
void fcfs(pro p[],int n)
{
    int ttt=0,twt=0,trt=0,el=0;
    float att=0,art=0,awt=0;
    printf("Gantt chart\n");
    for(int i=0;i<n;i++)
    {
        if(p[i].at>el)
         el=el+(p[i].at-el);
        int temp=el;
        p[i].rt=el-p[i].at;
        el+=p[i].bt;
        p[i].ct=el;
        p[i].tt=p[i].ct-p[i].at;
        p[i].wt=p[i].tt-p[i].bt;
        printf("|%d P%d %d",temp,p[i].pid,el);
    }
     printf("Observation table\nPid\tPri\ttAT\tBT\tCT\tTT\tRT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].rt,p[i].wt);
         ttt+=p[i].tt;
         twt+=p[i].wt;
         trt+=p[i].rt;
    }
    att=(float)ttt/n;
    awt=(float)twt/n;
    art=(float)trt/n;
    printf("Avg TT: %.2f\n",att);
    printf("Avg RT: %.2f\n",art);
    printf("Avg WT: %.2f\n",awt); 
}
