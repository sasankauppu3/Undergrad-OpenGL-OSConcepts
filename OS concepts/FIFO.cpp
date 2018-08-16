#include<stdlib.h>
#include<stdio.h>
#include<iostream>

using namespace std;


int main(){

    int sequenceSize, frameSize;
    int sequence[15], frame[3];
    int hits = 0, fault = 0;

    frameSize = 3;

    cout<<"Enter the length of the sequnce : ";
    cin>>sequenceSize;
    cout<<"\nEnter the sequence : ";

    int i, j, flag, index = 0;
    for(i = 0 ; i < sequenceSize ; i ++)
        cin>>sequence[i];

    sequence[i] = -1;

    for(i = 0 ; i < 3 ; i ++)
        frame[i] = -1;

    ////////////////////////////////////////////
    //FIIIIIIIIIFOOOOOOOOOOOOOOO
    ////////////////////////////////////////////

    for(i = 0 ; i < sequenceSize ; i ++){
        flag = 0;

        for(j = 0 ; j < frameSize ; j ++){

            if(frame[j] == sequence[i]){

                flag = 1;
                break;
            }
        }

        if(flag == 1)
            hits++;
        else{
            fault++;
            frame[index] = sequence[i];
        }
        index++;
        if(index == 3)
            index=0;

        //SHOW FRAME
        cout<<"\nFRAME : ";
        for(int k = 0 ; k < 3 ; k ++)
            cout<<frame[k]<<"|";

    }
}
