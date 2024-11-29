#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int FIFO(int total_processes , int burst_time[] , int pid[] ,int arrival_time[]){
    for(int i = 0 ; i < total_processes-1 ; i++){
        for(int j = 0 ; j < total_processes-i-1 ; j++){
            if(arrival_time[j] > arrival_time[j+1]){
                int temp1 = arrival_time[j];
                arrival_time[j] = arrival_time[j+1];
                arrival_time[j+1] = temp1;

                int temp2 = burst_time[j];
                burst_time[j] = burst_time[j+1];
                burst_time[j+1] = temp2;

                int temp3 = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp3;

            }
        }
    }

    float total_time = 0 ;
    float turnaround_time = 0 ;
    float total_turnaround_time = 0 ;
    float start_time = 0;
    float response_time = 0 ;
    float total_response_time = 0 ;
    float average_turnaround ;
    float average_response ;
    for(int i = 0 ; i < total_processes;i++){
          total_time = burst_time[i] + total_time ;
          turnaround_time = (total_time - arrival_time[i]);
          total_turnaround_time = total_turnaround_time + turnaround_time ;
    }
    total_time = 0 ;
    for(int i = 0 ; i < total_processes ; i++){
          total_time = total_time + burst_time[i];
          start_time = total_time - burst_time[i];
          response_time = start_time - arrival_time[i];
          total_response_time = total_response_time + response_time ;
     }
    for(int i = 0 ; i< total_processes ;i++){
        printf("Pid -> %d ",pid[i]);
    }
    average_turnaround = total_turnaround_time/total_processes ;
    average_response = total_response_time/total_processes;
    printf("\nATT is %.2f and RT is %.2f \n",average_turnaround,average_response);
}


int SJF(int total_processes,int burst_time[] ,int pid[], int arrival_time[]){
    float total_time = 0 ;
    float turnaround_time = 0 ;
    float total_turnaround_time = 0 ;
    float start_time = 0;
    float response_time = 0 ;
    float total_response_time = 0 ;
    float average_turnaround ;
    float average_response ;
    for(int i = 0 ; i < total_processes-1 ; i++){
        for(int j = 0 ; j < total_processes-i-1 ; j++){
            if(arrival_time[j] > arrival_time[j+1]){
                int temp1 = arrival_time[j];
                arrival_time[j] = arrival_time[j+1];
                arrival_time[j+1] = temp1;

                int temp2 = burst_time[j];
                burst_time[j] = burst_time[j+1];
                burst_time[j+1] = temp2;

                int temp3 = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp3;
            }
            if(arrival_time[j] == arrival_time[j+1]){
                if(burst_time[j]>burst_time[j+1]){
                        int temp1 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1]=temp1;

                        int temp2 = pid[j];
                        pid[j] = pid[j+1];
                        pid[j+1]=temp2;

                        int temp3 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1]=temp3;
                    }
            }
        }
    }
    int First_process_end = burst_time[0];
    int totalspent_time= burst_time[0];
    int First_process_pid = pid[0];
    for(int i = 1 ; i < total_processes;i++){
        if(arrival_time[i]<totalspent_time){
                for(int j = 1 ; j < total_processes-i;j++){
                    if(burst_time[j]>burst_time[j+1]){
                        int temp1 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1]=temp1;

                        int temp2 = pid[j];
                        pid[j] = pid[j+1];
                        pid[j+1]=temp2;

                        int temp3 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1]=temp3;
                    }
            }
        }
        if(arrival_time[i] > totalspent_time){
            for(int i = 0 ; i < total_processes-1 ; i++){
                for(int j = 0 ; j < total_processes-i-1 ; j++){
                    if(arrival_time[j] > arrival_time[j+1]){
                        int temp1 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1] = temp1;

                        int temp2 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1] = temp2;

                        int temp3 = pid[j];
                        pid[j] = pid[j+1];
                        pid[j+1] = temp3;
                    }
                }
            }
            printf("%d \n" , pid[i]);
        }
        totalspent_time = totalspent_time + burst_time[i];
    }
       for(int i = 0 ; i < total_processes;i++){
          total_time = burst_time[i] + total_time ;
          turnaround_time = (total_time - arrival_time[i]);
          total_turnaround_time = total_turnaround_time + turnaround_time ;
    }
    total_time = 0;
    for(int i = 0 ; i < total_processes ; i++){
          total_time = total_time + burst_time[i];
          start_time = total_time - burst_time[i];
          response_time = start_time - arrival_time[i];
          total_response_time = total_response_time + response_time ;
     }
    for(int i = 0 ; i< total_processes ;i++){
        printf("pid -> %d ",pid[i]);
    }
    average_turnaround = total_turnaround_time/total_processes ;
    average_response = total_response_time/total_processes;
    printf("\nATT is %.2f and RT is %.2f \n",average_turnaround,average_response);
}


int SRTF(int total_processes,int burst_time[] ,int pid[], int arrival_time[]){
    float total_time = 0 ;
    float turnaround_time = 0 ;
    float total_turnaround_time = 0 ;
    float start_time = 0;
    float response_time = 0 ;
    float total_response_time = 0 ;
    float average_turnaround ;
    float average_response ;
    float current_time = 0 ;
    float timer = 0;
    int process_status[total_processes];
    int copy_total_process = total_processes ;
    for(int i = 0 ; i < total_processes ; i++){
        process_status[i] = 0;
    }
    int copy_bust[total_processes];
    int copy_pid[total_processes];
    int copy_arrival[total_processes];
    int response_times[total_processes];
    for(int i =0 ; i < total_processes ; i++){
        copy_bust[i] = burst_time[i];
        copy_arrival[i] = arrival_time[i];
        copy_pid[i] = pid[i];
        response_times[i] = -1 ;
    }
    for(int i = 0 ; i < total_processes ; i++){
        for(int j = 0 ; j < total_processes-i-1;j++){
            if(arrival_time[j] > arrival_time[j+1]){
                int temp1 = arrival_time[j];
                arrival_time[j] = arrival_time[j+1];
                arrival_time[j+1] = temp1;

                int temp2 = burst_time[j];
                burst_time[j] = burst_time[j+1];
                burst_time[j+1] = temp2;

                int temp3 = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp3;
            }
            if(arrival_time[j] == arrival_time[j+1]){
                if(burst_time[j]>burst_time[j+1]){
                        int temp1 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1]=temp1;

                        int temp2 = pid[j];
                        pid[j] = pid[j+1];
                        pid[j+1]=temp2;

                        int temp3 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1]=temp3;
                    }
            }
        }
    }
    current_time = 0 ;

    int current_process = 0;
    float completed = 0 ;
    float shortest = 0 ;
    float First_process_end = burst_time[0];
    float totalspent_time= burst_time[0];
    float First_process_pid = pid[0];
    for(int i = 0 ; i < total_processes;i++){
        current_process++ ;
        if(arrival_time[i]<totalspent_time){
                for(int j = 0 ; j < total_processes-i-1;j++){
                    if(burst_time[current_process]>burst_time[current_process+1]){
                        int temp1 = burst_time[current_process];
                        burst_time[current_process] = burst_time[current_process+1];
                        burst_time[current_process+1]=temp1;

                        int temp2 = pid[j];
                        pid[j] = pid[j+1];
                        pid[j+1]=temp2;

                        int temp3 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1]=temp3;
                    }
            }
        }
        if(arrival_time[i] > totalspent_time){
            for(int i = 0 ; i < total_processes ; i++){
                for(int j = 0 ; j < total_processes-i-1 ; j++){
                    if(arrival_time[j] > arrival_time[j+1]){
                        int temp1 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1] = temp1;

                        int temp2 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1] = temp2;

                        int temp3 = pid[j];
                        pid[j] = pid[j+1];
                        pid[j+1] = temp3;
                    }
                }
            }
        }
        totalspent_time = totalspent_time + burst_time[i];
    }
    for(int i = 0 ; i< total_processes ;i++){
        printf("pid ->%d",pid[i]);
    }
    for(int i = 0 ; i < total_processes ; i++){
        turnaround_time = burst_time[i] - arrival_time[i];
        total_turnaround_time = total_turnaround_time + turnaround_time;
        response_time = copy_bust[i] - arrival_time[i];
        total_response_time  = total_response_time + response_time ;
    }
    for(int i = 0 ; i < total_processes;i++){
          total_time = burst_time[i] + total_time ;
          turnaround_time = (total_time - arrival_time[i]);
          total_turnaround_time = total_turnaround_time + turnaround_time ;
    }
    total_time = 0;
    for(int i = 0 ; i < total_processes ; i++){
          total_time = total_time + burst_time[i];
          start_time = total_time - burst_time[i];
          response_time = start_time - arrival_time[i];
          total_response_time = total_response_time + response_time ;
     }
    average_turnaround = total_turnaround_time/total_processes ;
    average_response = total_response_time/total_processes;
    printf("ATT is %.2f and RT is%.2f",average_turnaround,totalspent_time/total_processes);
    // while(completed < total_processes){
    //     for(int i = 0 ; i < total_processes-1 ; i++){
    //             for(int j = 0 ; j < total_processes-i-1 ; j++){
    //                  if(burst_time[j]<burst_time[j+1]){
    //                     int temp1 = burst_time[j];
    //                     burst_time[j] = burst_time[j+1];
    //                     burst_time[j+1]=temp1;

    //                     int temp2 = pid[j];
    //                     pid[j] = pid[j+1];
    //                     pid[j+1]=temp2;

    //                     int temp3 = arrival_time[j];
    //                     arrival_time[j] = arrival_time[j+1];
    //                     arrival_time[j+1]=temp3;
    //                 }
    //             }
    //         break;
    //         }
        // for(int i =0 ; i < total_processes ; i++){
        //     if(arrival_time[i]  < current_time ){
        //         if(copy_bust[i] > copy_bust[shortest]){
        //             shortest = i ;
        //         }
            }

            // if(response_times[shortest] == -1){
            //     response_times[shortest] == current_time - copy_arrival[shortest];
            // }
            // copy_bust[shortest] = copy_bust[shortest] - 1 ;
            // current_time++;
            // if(copy_bust[shortest] == 0 ){
            //     printf("%d ",copy_pid[shortest]);
            //     completed ++ ;
            //     turnaround_time = current_time - copy_arrival[shortest];
            //     total_turnaround_time = total_turnaround_time + turnaround_time;
            // }

    // }
    // for(int  j = 0 ; j < total_processes ; j++){
    //     for(int i = 0 ;i < total_processes ; i++){
    //         copy_bust[j] = copy_bust[j] - 1 ;
    //         current_time ++ ;
    //         if(copy_arrival[i]< current_time){
    //             if(copy_bust[current_time]>copy_bust[i]){

    //             }
    //         }
            //printf("%d " , pid[i]);
    //         printf("%d || arrivaltime is  %d \n",current_time,copy_arrival[i]);
    //         printf(" %d== copy_burst\n",copy_bust[j]);
    //         if(current_time == copy_arrival[i]){
    //             if(copy_bust[current_time] < copy_bust[i]){
    //                 printf("%d %d",pid[i],current_time);
    //             }
    //         }
    //     }
    //     current_time ++ ;
    // }


int RR(int total_processes,int burst_time[] ,int pid[], int arrival_time[], int time_quantom){
    float turnaround_time = 0 ;
    float total_turnaround_time = 0 ;
    float start_time = 0;
    float response_time = 0 ;
    float total_response_time = 0 ;
    float average_turnaround ;
    float average_response ;
    for(int i = 0 ; i < total_processes-1 ; i++){
        for(int j = 0 ; j < total_processes-i-1 ; j++){
            if(arrival_time[j] > arrival_time[j+1]){
                int temp1 = arrival_time[j];
                arrival_time[j] = arrival_time[j+1];
                arrival_time[j+1] = temp1;

                int temp2 = burst_time[j];
                burst_time[j] = burst_time[j+1];
                burst_time[j+1] = temp2;

                int temp3 = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp3;
            }
            if(arrival_time[j] == arrival_time[j+1]){
                if(burst_time[j]>burst_time[j+1]){
                        int temp1 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1]=temp1;

                        int temp2 = pid[j];
                        pid[j] = pid[j+1];
                        pid[j+1]=temp2;

                        int temp3 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1]=temp3;
                    }
                }
            }
    }
    int copy_burst[total_processes];
    int total_time = 0;
    for(int i = 0 ; i < total_processes ; i++){
        copy_burst[i] = burst_time[i];
        total_time = total_time+copy_burst[i];
    }
    int current_time = 0 ;
    int start_counter[total_processes];
    int program_holder[total_processes];
    int completed[total_processes];
    for(int i =0 ; i < total_processes ; i++){
        program_holder[i] = 0 ;
        completed[i] = 0 ;
        start_counter[i] = 0
;    }
    int copy_zero[total_processes];
    int start_times[total_processes];

    // while(current_time <= total_time){
    for(int j = 0 ; j < total_processes ;j++){
        for(int i = 0 ; i < total_processes ;i++){
            if(copy_burst[i] >= time_quantom) {
                printf("pid ->%d  ",pid[i]);
                copy_burst[i] = copy_burst[i] - time_quantom;
                if(copy_burst[i] != burst_time[i] && start_counter[i] == 0){
                    start_times[i] = current_time;
                    start_counter[i] = 1;
                }
                current_time = current_time + time_quantom ;


                if(copy_burst[i] == 0){
                    program_holder[i] = current_time ;
                }
            }
            else if(copy_burst[i] == 0){
                copy_zero[i] = current_time;
                continue;
            }

            else{
                printf("pid ->%d ",pid[i]);
                int x = time_quantom - copy_burst[i];
                copy_burst[i] = copy_burst[i] - x ;
                current_time = current_time + x  ;
                completed[i] =1 ;
                program_holder[i] = current_time;
            }
        }
    }
    for(int i = 0 ; i < total_processes ; i++){
        turnaround_time = program_holder[i] - arrival_time[i];
        total_turnaround_time = total_turnaround_time + turnaround_time;
        response_time = start_times[i] - arrival_time[i];
        total_response_time  = total_response_time + response_time ;
    }
    average_turnaround = total_turnaround_time/total_processes ;
    average_response = total_response_time/total_processes;
    printf("\nATT is %.2f and RT is %.2f \n",average_turnaround,average_response);
    }
    // for(int i = 0 ; i < total_processes ; i++){
    //     printf("%dpid %darival %dburst \n",pid[i],arrival_time[i],copy_burst[i]);
    // }


int main(int argc , char *argv[]){
    int total_processes ;
    printf("Enter the total number of processes ");
    scanf("%d" , &total_processes);
    int process[4];
    int burst_time[total_processes];
    int arrival_time[total_processes];
    int pid[total_processes];
    for(int i = 0 ; i < total_processes ; i++ ){
        scanf("%d %d %d" , &pid[i] , &arrival_time[i] ,&burst_time[i]);
    }
    int time_quantom ;
    printf("Enter the time_quantom ");
    scanf("%d" , &time_quantom);
    printf("FIFO => \n");
    FIFO(total_processes,burst_time,pid,arrival_time);
    printf("SJF => \n");
    SJF(total_processes,burst_time,pid,arrival_time);
    printf("RR => \n");
    RR(total_processes,burst_time,pid,arrival_time,time_quantom);
    printf("SRTF => \n");
    SRTF(total_processes,burst_time,pid,arrival_time);

}
