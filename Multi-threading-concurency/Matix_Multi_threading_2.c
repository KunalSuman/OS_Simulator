#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
int m , p ,n1 ,n2 ;
int MatrixA[512][512];
int MatrixB[512][512];
int MatrixC[512][512]={0};
pthread_mutex_t mutex ;
void* matrix_mul(void *arg){
    int* temp = (int*) arg ;
    int s = temp[0];
    int x = s%12;
    for(int i = x ; i < m ; i+=12){
        for(int j = 0 ; j < p ; j++){
            for(int k= 0 ; k < n1 ; k++){
                MatrixC[i][j] = MatrixC[i][j] + MatrixA[i][k]*MatrixB[k][j];
            }
        }
    }
    return NULL ;
}
void* matrix_mul2(void *arg){
    int* temp = (int*) arg ;
    int i = temp[0] ;
    int j = temp[1];
    for(int k = 0 ; k < n1 ; k++){
        MatrixC[i][j]=MatrixC[i][j] + MatrixA[i][k]* MatrixB[k][j];
    }
    return NULL ;
}

int main(int argc , char* argv[]){
    m  = atoi(argv[1]);
    n1 = atoi(argv[2]);
    p  = atoi(argv[3]);
    pthread_t mul[12] ;
    pthread_t mul1[m][p] ;
    int counter = 4 ;
    for(int i = 0 ; i < m ; i++){
        for(int j =0 ; j < n1 ; j++){
            MatrixA[i][j] = atoi(argv[counter]);
            counter++ ;
        }
    }
    for(int i =0 ; i < n1 ; i++){
        for(int j =  0 ; j < p ; j++){
            MatrixB[i][j] = atoi(argv[counter]);
            counter++ ;
        }
    }
    clock_t c1 = clock();
    for(int j = 0 ; j  < 12 ; j++){
        int* arg = malloc(2 * sizeof(int));
        arg[0] = j ;
        pthread_create(&mul[j],NULL,&matrix_mul,arg);
    }
    for(int j = 0 ; j  < 12 ; j++){
        pthread_join(mul[j],NULL);
    }
    clock_t c2 = clock();
    long double time_taken = (long double)((c2-c1));
     for (int i = 0; i < m ; i++) {
        for (int j = 0; j < p ; j++) {
            printf("%d ", MatrixC[i][j]);
        }
        printf("\n");
    }
    printf("Time taken by 12 thread %Lf \n",time_taken);
    for(int i = 0 ; i < m ; i++){
        for(int j = 0 ; j < p ; j ++){
            MatrixC[i][j] = 0;
        }
    }
    clock_t c3 = clock();
    for(int i = 0 ; i < m ; i++){
        for(int j = 0 ; j < p ; j++){
            for(int k= 0 ; k < n1 ; k++){
                MatrixC[i][j] = MatrixC[i][j] + MatrixA[i][k]*MatrixB[k][j];
            }
        }
    }
    clock_t c4 = clock() ;
    long double time_taken2 = (long double)((c4-c3));
    clock_t c5 = clock();
    for(int i = 0 ; i < m ; i++){
        for(int j = 0 ; j  < p ; j++){
            int* arg = malloc(2 * sizeof(int));
            arg[0] = i ;
            arg[1] = j ;
            pthread_create(&mul1[i][j],NULL,&matrix_mul2,arg);
        }
    }
    for(int i = 0 ; i < m ; i++){
        for(int j = 0 ; j  < p ; j++){
            pthread_join(mul1[i][j],NULL);
        }
    }
    clock_t c6 = clock();
    long double time_taken3 = (long double)((c6-c5));
    printf("Time taken by sequential version %Lf \n",time_taken2);
    printf("Time taken by multiple threads %Lf \n",time_taken3);
    printf("Speedup og %Lf \n",time_taken2/time_taken);
    printf("Speedup new %LF \n",time_taken2/time_taken3);
}
