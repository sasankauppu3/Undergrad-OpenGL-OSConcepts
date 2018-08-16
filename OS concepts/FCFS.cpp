#include<stdio.h>
#include<iostream>
using namespace std;
struct templet
{
    char name[8];
    int at,st,pt,ft,tat,wt,priority,remain,flag;
}p[20],temp;

void fcfs();

int main()
{
    fcfs();
}
void fcfs()
{
    int no,i,j,fcnt=0,scnt=0;
    cout<<"\n\tEnter no of processes : ";
    cin>>no;
    for(i=0;i<no;i++)
    {
        cout<<"\n\tEnter process name : ";
        cin>>p[i].name;
        cout<<"\n\tEnter Burst time : ";
        cin>>p[i].pt;
    }
    cout<<"\n\t Grant Chart : \n\t\t";
    for(i=0;i<no;i++)
    {
        p[i].st=fcnt;
        fcnt+=p[i].pt;
        p[i].wt=fcnt-p[i].pt;
        p[i].tat=fcnt;
        cout<<"%s -->"<<p[i].name;
    }
    cout<<"Finish";
    fcnt=0;
    cout<<"\n\tProcess \t burst time \t waiting time \t turn around time";
    for(i=0;i<no;i++)
    {
        cout<<"\n\t\t\t\t\t\t\t \t"<<p[i].name<<p[i].pt<<p[i].wt<<p[i].tat;
        fcnt+=p[i].wt;
        scnt+=p[i].tat;
    }
    cout<<"\n\n\t\t\t\tAverage : \t \t   \t"<<fcnt/no<<scnt/no;
}

