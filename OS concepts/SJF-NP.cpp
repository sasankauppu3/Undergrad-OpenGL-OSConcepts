#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

struct node{
	int pid,arrTime,burstTime,waitTime,TAT;
	struct 	node* right;

};

typedef struct node* NODE;
typedef struct node nodeSize;
NODE curProcess=NULL;

void insert(NODE head,int clock){
	cout<<"insert";
	NODE temp=(NODE)malloc(sizeof(nodeSize));
	cout<<"\nenter the pid";
	cin>>temp->pid;
	cout<<"\nenter the burst time ";
	cin>>temp->burstTime;
	temp->arrTime=clock;
	temp->right=NULL;
	temp->waitTime=temp->TAT=0;

	NODE cur;
	if(head->right==NULL){
		head->right=temp;
		return;		

	}
	cur=head->right;
	while(cur->right!=NULL){
		cur=cur->right;
	}
	cur->right=temp;
	
	return;


}

void currentProcess(NODE head,int clock){
		cout<<"clock:"<<clock<<endl;
		static int tat;
		if(curProcess==NULL){
			if(head->right!=NULL){
				curProcess=head->right;
				tat= (clock - curProcess->arrTime)  + curProcess->burstTime; //wait + burst time
				cout<<tat;
				curProcess->TAT=tat;
			}
			else{
				cout<<"no process in queue\n";
				return;
			}
		}

		
		if(clock >= tat){
			if(curProcess->right!=NULL)
				curProcess=curProcess->right;  // insert more security here
			else {
				cout<<"no further process";
				return;
			}
			curProcess->waitTime=clock-curProcess->arrTime;
			tat=curProcess->waitTime+ curProcess->burstTime;
			curProcess->TAT=tat;
			cout<<"curProcess wait time "<<curProcess->waitTime<<endl;
		}
		cout<<"\ncurrent process"<<(curProcess->pid)<<endl;
		return;

}



void display(NODE head){
	int avgWait=0,avgTAT=0,n=0;	
	NODE cur;
	cur=head->right;
	while(cur!=NULL){
		cout<<"\npid"<<cur->pid;
		cout<<"\narrTime"<<cur->arrTime;
		cout<<"\nburstTime"<<cur->burstTime;
		cout<<"\nwaitTime"<<cur->waitTime;
		cout<<"\nTAT"<<cur->TAT;
		cur=cur->right;
	}
	
	cur=head->right;
	while(cur!=NULL){
		avgWait+=cur->waitTime;
		avgTAT+=cur->TAT;
		n++;
		cur=cur->right;
	}
	cout<<"average waiting time "<<(avgWait*1.0)/n<<endl;
	cout<<"average TAT"<<(avgTAT*1.0)/n<<endl;
	

}

int count(NODE head){
	int n=0;
	NODE cur;
	cur=head->right;
	while(cur!=NULL){
		n++;
		cur=cur->right;
	}
	return n;
		
}

void sort(NODE head){
	int numNode = count(head);
	cout<<numNode<<endl;
	NODE cur,next,temp,prev;
	
	for(int i=0;i<=numNode-2;i++){
		cur=head->right;prev=head;		
		for(int j=0;j<numNode-1-i;j++){
			if(cur->right!=NULL){
				next=cur->right;	
				if(cur->burstTime > next->burstTime ){
					prev->right=next;
					cur->right=next->right;
					next->right=cur;
					//for next iteration  move previous further
					prev=prev->right;
				}
				else{
					cur=cur->right;
					prev=prev->right;
				}
			}				
		}
	}
	
}

int main(){
	NODE head=(NODE)malloc(sizeof(nodeSize));
	head->right=NULL;
	//insert(head);

	int cpuTime=30,clock,input;
	for(clock=0;;){
		cout<<"\n1:insert processes\t 2:run processes \t 3:display \t4:sort\n9:EXIT\n ";
		cin>>input;
		switch(input){
			case 1:insert(head,clock);break;
			case 2:currentProcess(head,clock);clock++;break;
			case 3:display(head);break;
			case 4:sort(head);break;
			case 9:exit(1);
				
		}




	}
	cout<<"broken";

	display(head);



	return 0;

}
