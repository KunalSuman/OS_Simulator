#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <string.h>
int main(int argc , char* argv[]){
    FILE* system_u  ptime_info;
    // FILE* no_of_users;
    int no_of_users;
    int system_uptime ;
    printf("\n users \n" );system("users | wc -l");
    system_uptime_info = fopen("/proc/uptime","r");
    // no_of_users = fopen("/run/utmp","r");
    fscanf(system_uptime_info , "%d" , &system_uptime);
    int hh = system_uptime/3600;
    int mm = (system_uptime - hh*3600)/60;
    int ss = (system_uptime - hh*3600 -mm*60);
    printf("%d:%d:%d up",hh,mm,ss);
}
