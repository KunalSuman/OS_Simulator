#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc , char *argv[]){
    srand(getpid());
    // int random1;
    // int random2;
    // int random3;
    // int random4;

    float mean;

    char *meanlist[7];
    for(int i = 0 ; i < 7 ; i++){
        int rc  = fork();
        if(rc == 0) {
            int random1 = rand() %100 + 1;
            int random2 = rand() %100 + 1;
            int random3 = rand() %100 + 1;
            int random4 = rand() %100 + 1;

            mean = (random1 + random2 +random3 +random4)/4 ;
            printf("child's mean %.2f and pid:%d\n",mean,getpid());

        }
        else{
             int wc = wait(NULL);
             exit(0);
        }
    }
}
