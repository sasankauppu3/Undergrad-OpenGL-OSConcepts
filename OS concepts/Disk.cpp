#include <iostream>
#include<math.h>
using namespace std;
void fcfs(int cur,int * pos,int n);
void sstf(int cur,int * pos,int n);
void scan(int num,int * pos,int cur,int n);
void cscan(int num,int * pos,int cur,int n);
int minimum(int * pos,int n,int cur);
void look(int num,int * pos,int cur,int n);
void clook(int num,int * pos,int cur,int n);
void sort(int a[],int n);

int main()
{
    int cur,n,num;
    cout<<"Enter the no of cylinders:";
    cin>>num;
    cout<<"Enter the current positon:";
    cin>>cur;
    cout<<"Enter the number of pending requests: ";
    cin>>n;
    int * pos=new int[n];
    cout<<"Enter the requests:";
    for(int i=0;i<n;i++)
        cin>>pos[i];

    int * temp=new int[n];
    for(int i=0;i<n;i++)
        temp[i]=pos[i];

    cout<<"FCFS:-\n";
    fcfs(cur,pos,n);
    cout<<"\nSSTF:-\n";
    sstf(cur,pos,n);
    cout<<"\nSCAN:-\n";
    scan(num,temp,cur,n);
    cout<<"\nC-SCAN:-";
    cscan(num,temp,cur,n);
    cout<<"\nLOOK:-\n";
    look(num,temp,cur,n);
    cout<<"\nCLOOK:-\n";
    clook(num,temp,cur,n);
    return 0;
}
void fcfs(int cur,int * pos,int n)
{
    cout<<cur<<"->";
    int count=fabs(pos[0]-cur);
    for(int i=1;i<n;i++)
    {
        cout<<pos[i-1]<<"->";
        count+=fabs(pos[i]-pos[i-1]);
    }
    cout<<pos[n-1]<<"\nCount="<<count<<endl;
}
void sstf(int cur,int * pos,int n)
{
    int count=0;
    cout<<cur<<"->";
    for(int i=0;i<n;i++)
    {
        int min=minimum(pos,n,cur);
        cout<<pos[min]<<"->";
        count+=fabs(cur-pos[min]);
        cur=pos[min];
        pos[min]=-1;
    }
    cout<<"count="<<count;
}
void scan(int num,int * pos,int cur,int n)
{
    int count=0;
    int * lesser=new int[n];
    int * greater1=new int[n];
    int c1=0,c2=0;
    for(int i=0;i<n;i++)
    {
        if(pos[i]<cur)
            lesser[c1++]=pos[i];
        if(pos[i]>cur)
            greater1[c2++]=pos[i];
    }
    cout<<endl;
    sort(greater1,c2);
    sort(lesser,c1);
    char dir='l';
    cout<<"Enter the direction:(r/l)";
    cin>>dir;

    if(dir=='r')
    {
        for(int i=0;i<c2;i++)
        {
            count+=fabs(cur-greater1[i]);
            cout<<greater1[i]<<"->";
            cur=greater1[i];
        }
        count+=fabs(greater1[c2-1]-num+1);
        count+=fabs(num-1-lesser[c1-1]);
        cur=lesser[c1-1];
        cout<<num-1<<"->";
        cout<<"\n"<<count;
        for(int i=c1-1;i>=0;i--)
        {
            count+=fabs(cur-lesser[i]);
            cout<<lesser[i]<<"->";
            cur=lesser[i];
        }
    }

    if(dir=='l')
    {
        for(int i=c1-1;i>=0;i--)
        {
            count+=fabs(cur-lesser[i]);
            cout<<lesser[i]<<"->";
            cur=lesser[i];
        }
        count+=fabs(lesser[0]-0);
        count+=fabs(0-greater1[0]);
        cur=greater1[0];
        cout<<"0->";
        for(int i=0;i<c2;i++)
        {
            count+=fabs(cur-greater1[i]);
            cout<<greater1[i]<<"->";
            cur=greater1[i];
        }

    }
    cout<<"\nCount="<<count;
}
void cscan(int num,int * pos,int cur,int n)
{
    int count=0;
    int * lesser=new int[n];
    int * greater1=new int[n];
    int c1=0,c2=0;
    for(int i=0;i<n;i++)
    {
        if(pos[i]<cur)
            lesser[c1++]=pos[i];
        if(pos[i]>cur)
            greater1[c2++]=pos[i];
    }
    cout<<endl;
    sort(greater1,c2);
    sort(lesser,c1);
    for(int i=0;i<c2;i++)
    {
        count+=fabs(cur-greater1[i]);
        cout<<greater1[i]<<"->";
        cur=greater1[i];
    }
    count+=fabs(greater1[c2-1]-num+1);
    count+=1;
    cur=0;
    cout<<num-1<<"->"<<"0"<<"->";

    for(int i=0;i<c1;i++)
    {
            count+=fabs(cur-lesser[i]);
            cout<<lesser[i]<<"->";
            cur=lesser[i];
    }

    cout<<"\nCount="<<count;
}
void look(int num,int * pos,int cur,int n)
{
    int count=0;
    int * lesser=new int[n];
    int * greater1=new int[n];
    int c1=0,c2=0;
    for(int i=0;i<n;i++)
    {
        if(pos[i]<cur)
            lesser[c1++]=pos[i];
        if(pos[i]>cur)
            greater1[c2++]=pos[i];
    }
    cout<<endl;
    sort(greater1,c2);
    sort(lesser,c1);
    char dir='l';
    cout<<"Enter the direction:(r/l)";
    cin>>dir;

    if(dir=='r')
    {
        for(int i=0;i<c2;i++)
        {
            count+=fabs(cur-greater1[i]);
            cout<<greater1[i]<<"->";
            cur=greater1[i];
        }
        cout<<"\n"<<count;
        count+=fabs(greater1[c2-1]-lesser[c1-1]);
        cur=lesser[c1-1];
        cout<<"\n"<<count;
        for(int i=c1-1;i>=0;i--)
        {
            count+=fabs(cur-lesser[i]);
            cout<<lesser[i]<<"->";
            cur=lesser[i];
        }
    }

    if(dir=='l')
    {
        for(int i=c1-1;i>=0;i--)
        {
            count+=fabs(cur-lesser[i]);
            cout<<lesser[i]<<"->";
            cur=lesser[i];
        }
        count+=fabs(lesser[0]-greater1[0]);
        cur=greater1[0];
        for(int i=0;i<c2;i++)
        {
            count+=fabs(cur-greater1[i]);
            cout<<greater1[i]<<"->";
            cur=greater1[i];
        }

    }
    cout<<"\nCount="<<count;
}
void clook(int num,int * pos,int cur,int n)
{
    int count=0;
    int * lesser=new int[n];
    int * greater1=new int[n];
    int c1=0,c2=0;
    for(int i=0;i<n;i++)
    {
        if(pos[i]<cur)
            lesser[c1++]=pos[i];
        if(pos[i]>cur)
            greater1[c2++]=pos[i];
    }
    cout<<endl;
    sort(greater1,c2);
    sort(lesser,c1);
    for(int i=0;i<c2;i++)
    {
        count+=fabs(cur-greater1[i]);
        cout<<greater1[i]<<"->";
        cur=greater1[i];
    }
    count+=1;
    cur=lesser[0];

    for(int i=0;i<c1;i++)
    {
            count+=fabs(cur-lesser[i]);
            cout<<lesser[i]<<"->";
            cur=lesser[i];
    }

    cout<<"\nCount="<<count;
}
void sort(int * a,int n)
{

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				int temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;

			}
		}
	}
}
int minimum(int * pos,int n,int cur)
{
    int res=fabs(cur-pos[0]);
    int k=0;
    while(pos[k]==-1)
    {
        res=fabs(cur-pos[k]);
        k++;
    }
    for(int i=0;i<n;i++)
    {
        if(pos[i]==-1)
            continue;
        if(fabs(cur-pos[i])<res)
        {
            res=fabs(cur-pos[i]);
            k=i;
        }
    }
    return k;
}
