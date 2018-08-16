#include<iostream>

using namespace std;

int main(){

int m,n;
int avail[5];

	int alloc[10][10];
	int need[10][10];
	int max[10][10];
	int i,j;
	int req[10],pid;

	cout<<"Enter the number of processes."<<endl;
	cin>>n;
	cout<<"Enter the number of resources."<<endl;
	cin>>m;
	cout<<"Enter the available resources."<<endl;

	for( i=0;i<m;i++)
		cin>>avail[i];

	cout<<"Enter the allocated resources and max resources for each process."<<endl;
	for( i=0;i<n;i++)
	{	cout<<"Process "<<i<<"."<<endl;
		for( j=0;j<m;j++)
			cin>>alloc[i][j];
		for( j=0;j<m;j++)
			cin>>max[i][j];
		for( j=0;j<m;j++)
			need[i][j]=max[i][j]-alloc[i][j];
	}

	cout<<"\nEnter the process number and the request\n";

	cin>>pid;
	for(i=0;i<m;i++)
		cin>>req[i];
	for(i=0;i<m;i++){
        if(req[i]>alloc[pid][i] || (alloc[pid][i]+req[i])>max[pid][i]){

			cout<<"Invalid Input\nCauses Deadlock";
return 1;
		}
    }

	for(i=0;i<m;i++)
		{
			alloc[pid][i]+=req[i];
			avail[i]-=req[i];
		}
		int complete[n];
	for(int i=0;i<n;i++)
		complete[i]=0;
	int check,x=0;
	cout<<"Order:"<<endl;
	while(x!=n)
	{	check=1;
		if(complete[x]==1)
			x++;
		else
		{	for(int j=0;j<m;j++)
				if(avail[j]<need[x][j])
					check=0;
			if(check==0)
				x++;
			else
			{	complete[x]=1;
				for(int j=0;j<m;j++)
				{	avail[j]+=alloc[x][j];
					need[x][j]=0;
					alloc[x][j]=0;
				}
				cout<<"P"<<x<<" ";
				x=0;
			}
		}
	}
	check=1;
	for(int j=0;j<n;j++)
		if(complete[j]==0)
			check=0;
	if(check==0)
		cout<<endl<<"Deadlock state."<<endl;
	else
		cout<<endl<<"Safe state."<<endl;

	return 0;
}
