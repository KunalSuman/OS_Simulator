#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc , char* argv[]){
      char *day_set[] ={"Mon" ,"Tue" ,"Wed" ,"Thus" ,"Fri" ,"Sat ","Sun"};

      FILE* system_time_file;
      system_time_file = fopen("/proc/driver/rtc","r");
      char *system_date = NULL ;
      int yy , mm , dd ;
      char read_line[200];
      while(fgets(read_line,200,system_time_file)){
            int check_date = strncmp(read_line,"rtc_date",8);
            if(check_date==0){
                  system_date = strchr(read_line,':') +2;
                  sscanf(system_date, "%d-%d-%d" , &yy ,&mm , &dd);
        }
      }
      int month ;
      int year ;

      int month_array[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
      if (year %4 ==0){
        month_array[1] =29;
      }
      if(argc == 3){
          month = atoi(argv[1]) -1;
          year = atoi(argv[2]);
      }
      else{
          month  = mm;
          year = yy;
      }

      int date = 1 + 4%7;
      if(argc > 3){
          date = atoi(argv[3]);
      }
      if(month == 1){
          month = 13;
          year = year-1;
      }
      if(month == 2){
          month = 14;
          year = year-1;
      }
      int day = date + (13*(month+1))/5 +  (year%100)/4 + (year/100)/4 + (5*year/100) +year%100;
      day = day%7;
      if(argc == 4){
          printf("\n");
      }
      else{
          for(int i = 0 ; i < 7 ; i++){
              printf("%s ",day_set[i]);
          }
      }
      printf("\n");
      int mm_fromaary = month_array[mm] + day;
      int dates_array[mm_fromaary];
      int check_zeros = day ;
      if(check_zeros<8){
          for(int j = 0 ; j < check_zeros ; j++){
              dates_array[j] = -1 ;
          }
          for(int i = 1 ; i < month_array[mm]; i++){
              dates_array[check_zeros] = i ;
              check_zeros ++ ;
          }
      }
      if(argc == 4){
          printf("%s",day_set[day]);
      }
      else{

          for(int i = 0 ; i < mm_fromaary-1 ; i++){
                  if(i%7 == 0){
                      printf("\n");
                  }
                  printf(" %d  " , dates_array[i]);

          }
      printf("\n");
      }
}
