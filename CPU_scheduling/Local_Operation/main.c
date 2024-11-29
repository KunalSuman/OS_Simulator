#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc , char* argv[]){
    int cal = fork();
    if(cal == 0){
      execl("./cal","cal",(char*)NULL);
    }
    wait(NULL) ;
    int date = fork();
    if(date == 0){
      execl("./date","date",(char*)NULL);
    }
    wait(NULL) ;
    int uptime = fork();
    if(uptime == 0){
      execl("./uptime","uptime",(char*)NULL);
    }
    
    wait(NULL) ;
}
