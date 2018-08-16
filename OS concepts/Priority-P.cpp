#include<iostream>
#include<stdlib.h>
using namespace std;

struct node{
	signed int pid,arrTime,burstTime,waitTime,TAT,priority,remain; //remain-> remaining Time
	struct 	node* right;

};

typedef struct node* NODE;
typedef struct node nodeSize;
NODE curProcess=NULL;
void sort(NODE);
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
	cout<<"enter the priority of the process";
	cin>>temp->priority;
	temp->remain=temp->burstTime;

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
	cout<<"clock =>"<<clock<<endl;
	
	sort(head);
	if(curProcess!=NULL ){	
		if(curProcess->remain==0){
			curProcess->waitTime=(clock - curProcess->arrTime) - curProcess->burstTime;
			curProcess->TAT=clock - curProcess->arrTime;
		}
	}
	if(curProcess!=head->right){
		curProcess=head->right;
		while(curProcess->remain==0 ){
			curProcess=curProcess->right;
			if(curProcess==NULL){
				cout<<"queue empty";
				return;
			}	
		}
			
		
		curProcess->remain --;
		cout<<"remaining time "<<curProcess->remain;		
	} 
	else if(curProcess->remain >0) { //stopped here
		curProcess->remain --;
		cout<<"remaining time "<<curProcess->remain;
	}
	else if(curProcess->remain ==0){
		cout<<"here\n";		
		curProcess->waitTime=clock - curProcess->arrTime - curProcess->burstTime;
		curProcess->TAT=clock - curProcess->arrTime;
		curProcess=curProcess->right;
		if(curProcess!=NULL){
			cout<<"DD";	
			curProcess->remain--;
		}
		else{
			cout<<"queue empty";
			return;
		}
		cout<<"remaining time "<<curProcess->remain;
	}
	cout<<"\ncurrent running process "<<curProcess->pid<<endl;
	cout<<"current process's priority: "<<curProcess->priority<<endl;
	return;

}



void display(NODE head){
	int avgWait=0,avgTAT=0,n=0;	
	NODE cur;
	cur=head->right;
	cout<<"PID\t|"<<"priority\t|"<<"arrTIME\t|"<<"burstTime\t|"<<"waitTime\t|"<<"TAT"<<endl;
	while(cur!=NULL){
		cout<<cur->pid<<"\t|";
		cout<<cur->priority<<"\t\t|";
		
		cout<<cur->arrTime<<"\t\t|";
		cout<<cur->burstTime<<"\t\t|";
		cout<<cur->waitTime<<"\t\t|";
		//cout<<cur->remain<<"\t|";
		cout<<cur->TAT<<"\t\t";
		cur=cur->right;
		cout<<endl;
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
	//cout<<numNode<<endl;
	NODE cur,next,temp,prev;
	
	for(int i=0;i<=numNode-2;i++){
		cur=head->right;prev=head;		
		for(int j=0;j<numNode-1-i;j++){
			if(cur->right!=NULL){
				next=cur->right;	
				if(cur->priority > next->priority ){
					prev->right=next;
					cur->right=next->right;
					next->right=cur;
					//for next iteration  move previous further and cur already went to next position
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
		cout<<"\n1:insert processes \t 2:run processes \t 3:display \t4:sort\n9:EXIT\n ";
		cout<<"current clock:"<<clock<<endl;
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


