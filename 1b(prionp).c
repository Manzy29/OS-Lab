#include<stdio.h>
#include<stdlib.h>
typedef struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tt;
    int wt;
    int rt;
    int fin;
    int pri;
}pro;
void prionp(pro[],int);
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
        printf("Enter priority: ");
        scanf("%d",&p[i].pri);
        p[i].fin=0;
        p[i].pid=i+1;
    }
    prionp(p,n);
}
void prionp(pro p[],int n)
{
    int ttt=0,twt=0,trt=0;
    float att=0,art=0,awt=0;
    int el=0,exec=-1;
    int rempro=n;
    printf("Gantt chart\n");
    while(rempro)
    {
        exec=-1;
        int lpv=9999;
        for(int i=0;i<n;i++)
        {
            if(p[i].at<=el && !p[i].fin)
            {
                if(p[i].pri<lpv)
                {
                    exec=i;
                    lpv=p[i].pri;
                }
            }
        }
        if(exec==-1)
        {
            printf("|%d***%d",el,el+1);
            el++;
        }
        else
        {
            int temp=el;
            p[exec].rt=el-p[exec].at;
            el+=p[exec].bt;
            p[exec].ct=el;
            p[exec].fin=1;
            rempro--;
            p[exec].tt=p[exec].ct-p[exec].at;
            p[exec].wt=p[exec].tt-p[exec].bt;
            printf("|%d p%d %d",temp,p[exec].pid,el);
        }
    }
    printf("Observation table\nPid\tPri\ttAT\tBT\tCT\tTT\tRT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].pri,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].rt,p[i].wt);
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
