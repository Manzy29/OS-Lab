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
    int remtime;
}pro;
int tp[100],pt[100],j=-1,k=-1;
void sjfpre(pro[],int);
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
        p[i].remtime=p[i].bt;
        p[i].pid=i+1;
    }
    sjfpre(p,n);
}
void sjfpre(pro p[],int n)
{
    int ttt=0,twt=0,trt=0;
    float att=0,art=0,awt=0;
    int el=0,exec=-1;
    int rempro=n;
    tp[++j]=0;
    while(rempro)
    {
        exec=-1;
        int sbt=9999;
        for(int i=0;i<n;i++)
        {
            if(p[i].at<=el && p[i].remtime>0)
            {
                if(p[i].remtime<sbt)
                {
                    exec=i;
                    sbt=p[i].remtime;
                }
            }
        }
        if(exec==-1)
        {
            pt[++k]=0;
            el++;
            tp[++j]=el;
            continue;
        }
        if(p[exec].remtime==p[exec].bt)
         p[exec].rt=el-p[exec].at;
        p[exec].remtime--;
        el++;
        pt[++k]=p[exec].pid;
        tp[++j]=el;
        if(p[exec].remtime==0)
        {
            p[exec].ct=el;
            p[exec].tt=p[exec].ct-p[exec].at;
            p[exec].wt=p[exec].tt-p[exec].bt;
            rempro--;
            ttt+=p[exec].tt;
            twt+=p[exec].wt;
            trt+=p[exec].rt;
        }
    }
    printf("Observation table\nPid\tAT\tBT\tCT\tTT\tRT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].rt,p[i].wt);
    }
    printf("\nGantt chart\n");
    for(int i=0;i<=k;i++)
     printf("| P%d\t ",pt[i]);
    printf("|\n");
    for(int i=0;i<=j;i++)
     printf("%d\t",tp[i]);
    printf("\n");
    att=(float)ttt/n;
    awt=(float)twt/n;
    art=(float)trt/n;
    printf("Avg TT: %.2f\n",att);
    printf("Avg RT: %.2f\n",art);
    printf("Avg WT: %.2f\n",awt);  
}
