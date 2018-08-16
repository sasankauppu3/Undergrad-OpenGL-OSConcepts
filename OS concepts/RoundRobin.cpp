#include<stdio.h>
#include<iostream>
using namespace std;
struct node
{
    char name[8];
    int at,st,pt,ft,tat,wt,priority,remain,flag;
}p[20],temp;


void rr();

int main()
{
   rr();
}
void rr()
{
    int no,i,j,interval;
    float fcnt=0,scnt=0;
    cout<<"Enter no of processes : ";
    cin>>no;
    for(i=0;i<no;i++)
    {
        cout<<"\nEnter process name : ";
        cin>>p[i].name;
        cout<<"\nEnter Burst time : ";
        cin>>p[i].pt;
        p[i].remain=p[i].pt;
        p[i].flag=0;
    }
    cout<<"\nEnter interval  : ";
    cin>>interval;

    cout<<"\nGhant Chart : \n\t\t";

    i=0;
    while(1)
    {
        for(i=0;i<no;i++)
        {
        if(p[i].flag==0)
        {
            if(p[i].remain<=interval)
            {
                cout<<"--  "<<p[i].name<<"(C)--";
                scnt+=p[i].remain;
                p[i].wt=scnt-p[i].pt;
                p[i].tat=scnt;
                p[i].flag=1;
                fcnt++;
            }
            else
            {
                cout<<"--"<<p[i].name<<" --";
                p[i].remain-=interval;
                scnt+=interval;
            }
        }
        }
        if(fcnt==no)
            break;
    }

    cout<<"Finish";
    fcnt=0,scnt=0;
    cout<<"\n\tProcess \t burst time \t waiting time \t turn around time";
    for(i=0;i<no;i++)
    {
        cout<<"\n";
        cout<<"\t"<<p[i].name<<"\t\t"<<p[i].pt<<"\t\t"<<p[i].wt<<"\t\t"<<p[i].tat;
        fcnt+=p[i].wt;
        scnt+=p[i].tat;
    }

    cout<<"\n Average wt: "<<fcnt/no<<"Average tat: "<<scnt/no;
}

