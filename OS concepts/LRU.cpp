#include<stdlib.h>
#include<stdio.h>
#include<iostream>

using namespace std;


int main(){

    int sequenceSize, frameSize;
    int sequence[15], frame[3], age[3];
    int hits = 0, fault = 0, oldest;

    frameSize = 3;

    cout<<"Enter the length of the sequnce : ";
    cin>>sequenceSize;
    cout<<"\nEnter the sequence : ";

    int i, j, flag;
    for(i = 0 ; i < sequenceSize ; i ++)
        cin>>sequence[i];

    for(i = 0 ; i < 3 ; i ++){
        frame[i] = -1;
        age[i] = -1;
    }

    ////////////////////////////////////////////
    //FIIIIIIIIIFOOOOOOOOOOOOOOO
    ////////////////////////////////////////////

    for(i = 0 ; i < sequenceSize ; i ++){

        flag = 0;
        for(j = 0 ; j < frameSize ; j ++){

            if(frame[j] == -1){
                frame[j] = sequence[i];
                break;
            }
            if(frame[j] == sequence[i]){

                flag = 1;
                age[j]++;
            }
        }

        if(flag == 1)
            hits++;
        else{

            oldest = age[0];
            for(j = 0 ; j < 3 ; j ++){
                if(age[j] > oldest)
                    oldest = age[j];
            }
            fault++;
            frame[oldest] = sequence[i];
            age[oldest] = 0;
        }

        //SHOW FRAME
        cout<<"\nFRAME : ";
        for(int k = 0 ; k < 3 ; k ++)
            cout<<frame[k]<<"|";

    }
}
