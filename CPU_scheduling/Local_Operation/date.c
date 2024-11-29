#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main(int argc , char *argv[]){
    FILE* system_time_file;
    system_time_file = fopen("/proc/driver/rtc","r");
    char read_line[200];
    char *system_date = NULL ;
    char *system_time = NULL ;
    int yy , mm , dd ;
    int hh , mn , ss;
    char *month_set[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    while(fgets(read_line , 200 , system_time_file)){
        int check_time = strncmp(read_line,"rtc_time",8);
        int check_date = strncmp(read_line,"rtc_date",8);
        if(check_time==0){
            system_time = strchr(read_line,':') + 2;
            sscanf(system_time, "%d:%d:%d" , &hh , &mn ,&ss);
    }
        if(check_date==0){
            system_date = strchr(read_line,':') +2;
            sscanf(system_date, "%d-%d-%d" , &yy ,&mm , &dd);
        }
    }
    if(argc > 1 ){
        int check_UTF = strncmp(argv[1],"-u",2);
        int check_RTF = strncmp(argv[1],"-r",2);
        if(check_UTF == 0){
             system("./cal mm yy dd");
             printf(" %s %d %d:%d:%d UTC %d",month_set[mm-1],dd,hh,mn,ss,yy);

        }
        if(check_RTF == 0){
            system("./cal mm yy dd");

            printf(" %d %s %d %d:%d:%d +0530",dd,month_set[mm-1],yy,hh,mn,ss);
        }
    }
    else{
        system("./cal mm yy dd");
        int new_min = mn +30 ;
        int new_hh = hh + 5;
        if(new_min > 59){
            new_min = new_min - 60;
            new_hh = new_hh + 1;
        }
        printf(" %s %d %d:%d:%d IST %d",month_set[mm-1],dd,new_hh,new_min,ss,yy);
    }
}
