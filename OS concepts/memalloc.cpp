#include<iostream>
using namespace std;
typedef struct NODE
{
    int base,s;
    struct NODE *next;
}node;
node *head;
void firstFit(int psize)
{
    node *minm=head;
    node* temp=head->next;
    while(temp!=NULL)
    {
        if(minm->base>temp->base)
            minm=temp;
        temp=temp->next;
    }
    minm->base=minm->base+psize;
    minm->s=minm->s-psize;
}
void bestFit(int psize)
{
    node *minm=new node();
    node *todel=minm;
    minm->s=psize;
    minm->base=head->base;
    node* temp=head;
    while(temp!=NULL)
    {
        if((minm->base>=temp->base)&&(minm->s<=temp->s))
            minm=temp;
        temp=temp->next;
    }
    if(todel==minm)
    {
        cout<<"Not enough space\n";
        delete todel;
        return;
    }
    minm->base=minm->base+psize;
    minm->s=minm->s-psize;
    delete todel;
}
void worstFit(int psize)
{}
int main()
{
    head=NULL;
    //Base address
    //netsize
    //where the holes are
    //Begin entering the processes. See by best fit, first fit and worst fit as to which hole the process goes
    //and the what the hole size becomes.
    int base,sizem,choice;
    cout<<"Enter the base address";
    cin>>base;
    cout<<"Enter the size of the memory block";
    cin>>sizem;
    cout<<"Enter your choice:\n1:First fit\n2:Best Fit\n3:Worst fit";
    cin>>choice;

    int d=1,e=0,c=1;
    while(e!=2)
    {
        while(c==1)
        {
            cout<<"Do you want to enter any hole?(1/0)";
            cin>>c;
            if(c)
            {
                e=0;
                int hbase,hsize;
                cout<<"Enter the base address of the hole:";
                cin>>hbase;
                cout<<"Enter the size of the hole:";
                cin>>hsize;
                node *temp=new node();
                temp->base=hbase;
                temp->s=hsize;
                temp->next=NULL;
                node *temp2=head;
                if(head==NULL)
                    head=temp;
                else
                {
                    while(temp2->next!=NULL)
                        temp2=temp2->next;
                    temp2->next=temp;
                }
            }
        }
        e++;
        if(e==2)
            break;
        //Entered the holes
        while (d==1)
        {
            cout<<"Do you want to enter any process?(1/0)";
            cin>>d;
            if(d)
            {
                e=0;
                int psize;
                cout<<"Enter the process size:";
                cin>>psize;
                if(head==NULL)
                {
                    cout<<"Cannot allocate:";
                    break;
                }
                switch(choice)
                {
                    case 1:
                            firstFit(psize);
                            break;
                    case 2:
                            bestFit(psize);
                            break;
                    case 3:
                            worstFit(psize);
                }
            }
        }
        e++;
    }
}
