#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int target ;
    int index = -1;
    int argv[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    printf("Array:");
    for(int i = 0 ; i < 16 ; i++ ){
          printf(" %d " , argv[i]);
    }
    printf("\n");
    printf("Enter a target value : ");
    scanf("%d", &target);
    int binary_array[16];
    for(int i = 0 ; i < 16 ; i++){
        binary_array[i] = argv[i];
    }

    int low = 0 ;
    int high = sizeof(binary_array)/(sizeof(binary_array[0]));

    while(low <= high){
        int mid = low + (high-low)/2 ;

        if(binary_array[mid] == target){
              index = mid ;
        }
        int rc = fork();
        if(rc==0){
              if (binary_array[mid] < target){
                    low = mid+1;
              }
              else{
                  high = mid -1 ;
              }
              printf("Pid of child is : %d \n",getpid());
        }
        else{
              wait(NULL);
              exit(0);
    }
  }
    printf("Target value's index : %d", index);
}
