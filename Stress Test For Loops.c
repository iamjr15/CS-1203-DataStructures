

#include<stdio.h>
#include<stdlib.h>


int main(int argc, char** argv){

    float i;
    float incrementation = 0.000000001;    
    float x = 0.00000001; 
    int count = 1;

    for (i=0.0; i<x; i+=incrementation) {
        printf("Loop Number: %d\n", count);
        count++;
    }

    return 0;
}