/*
compile command:
gcc -o Single_EXP Single_EXP.c
run command:
./Single_EXP <seed_num>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARTICLES_NUM 10000
#define RIGHT_PROB 65
#define LEFT_PROB 5
#define UP_PROB 15
#define DOWN_PROB 15
#define ONE_HUNDRED_PERCENT 100


/*
RandDirection is a function that return int between 0-3
the distribution is as stated in the defines:
0 if we get "LEFT"
1 if we get "RIGHT"
2 if we get "UP"
3 if we get "DOWN"
*/
int RandDirection(){
    int randVar = rand() % ONE_HUNDRED_PERCENT;
    if (randVar < RIGHT_PROB){
        return 0;
    }
    randVar -= RIGHT_PROB;
    if (randVar < LEFT_PROB){
        return 1;
    }
    randVar -= LEFT_PROB;
    if (randVar < UP_PROB){
        return 2;
    }
    return 3;

}
/*
SimulateParticle is a function that return a float that represent the posotion y that the particle reached when finish
the function is running on a particle until he reaches x=1.
jumps of 0.1.
it randoms a direction with the apropriate distribution and act accordinaly
*/
float SimulateParticle(){
    int notFinish = 1;
    float x = 0;
    float y = 0;
    while (notFinish){
        int deriction = RandDirection(); //0 right, 1 left , 2 up, 3 down
        if (deriction == 0){
            x += 0.1;
            if (x>=1) notFinish=0;
        }
        else if (deriction==1){
            if (x==0) x=0.1;
            else x -= 0.1;
        }
        else if (deriction==2){
            if (y==0.5) y=0.4;
            else y += 0.1;
        }
        else { //derection ==3
            if (y==-0.5) y=-0.4;
            else y -= 0.1;
        }
    }
    return y;
}

int main (int argc, char **argv){
    int seed = atoi(argv[1]); //We assume that we send an argument otherwize the program cracshes
    srand(seed); //set seed for the job randoms to be unique for each job
    for (int i = 0;i<PARTICLES_NUM;i++){
        printf("%f\n" , SimulateParticle() ) ; //print result to output file
    }
    return 0;
}