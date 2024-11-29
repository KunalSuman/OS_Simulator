#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

sem_t sema ;
pthread_t truck[128] , warehouse[128] ;
pthread_t truck_deliveries[128]={0};
pthread_cond_t is_full ,is_empty;
pthread_mutex_t mutex ;
int max_deliveries = 20;
int deliveries_done = 0;
int total_items = 0 ;
int total_items_dublicate = 0 ;
int counter_delivery = 0 ;
int dublicate = 0;
int items_capacity[5]={0,0,0,0,0};
int process =0 ;
int truck_inputs ;
void* Truck( void* item){
    int items = rand()%10 +1 ;
    printf("itms PS %d \n",items);
        pthread_mutex_lock(&mutex);
        counter_delivery = counter_delivery + items ;
        printf("Items : %d \n",total_items);
        if(total_items + items > 20){
            pthread_mutex_unlock(&mutex);
            return NULL  ;
        }
        total_items = total_items + items ;
        dublicate = total_items ;
        for(int i = 0 ; i < items ; i++){
            if( max_deliveries == 0 ||dublicate == 0){
                printf("STORAGE IS FULL");
                pthread_cond_broadcast(&is_empty);
                return NULL ;
            }
            while(process==5){
                    printf("buffer is full \n");
                    pthread_cond_wait(&is_full,&mutex);
            }
            process++ ;
            deliveries_done++ ;
            if(i < 5){
                items_capacity[i] = 1 ;
            }
            printf("Items in cart P : %d \n",process);
            pthread_cond_signal(&is_empty);
        }
    pthread_mutex_unlock(&mutex);
    sleep(1);
    return NULL ;
}

void* Warehouse(void* item){
    while(max_deliveries>0 && dublicate>0){
        pthread_mutex_lock(&mutex);
        int items = rand()%10 + 1;
        printf("itms  C %d \n",items);
        for(int i = 0 ; i < items ; i++){
            while(process==0){
                if(dublicate == 0 || max_deliveries == 0){
                    pthread_cond_broadcast(&is_full);
                    return NULL ;
                }
                printf("buffer is empty \n");
                pthread_cond_wait(&is_empty,&mutex);
            }
            process--;
            max_deliveries--;
            dublicate--;
            if(i<5){
                    items_capacity[i] = 0 ;
            }
            printf("Items in cart C : %d \n",process);
            printf("Storage Left %d\n",max_deliveries);

            pthread_cond_signal(&is_full);
            pthread_mutex_unlock(&mutex);
            sleep(1);
            }

    }
    printf("ALL ITEMS STORED \n");
    return NULL ;
}

void launch(int truck_inputs , int warehouse_inputs){

    for(int i = 0 ; i < truck_inputs ;i++){
        pthread_mutex_lock(&mutex);
        pthread_create(&truck[i],NULL,&Truck,NULL);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    for(int i = 0 ; i < warehouse_inputs ;i++){
            pthread_mutex_lock(&mutex);
            pthread_create(&warehouse[i],NULL,&Warehouse,NULL);
            pthread_mutex_unlock(&mutex);
            sleep(1);
    }


    // for(int i = 0 ; i < truck_inputs ; i++){
    //     printf("%d ",truck_deliveries[i]);
    // }
    for(int i = 0 ; i < truck_inputs ;i++){
        pthread_join(truck[i],NULL);
    }

    for(int i = 0 ; i < warehouse_inputs ;i++){
        pthread_join(warehouse[i],NULL);
    }
    printf("Total deliveries tried %d \n",counter_delivery);
    if(counter_delivery > 20){
        printf("Deliveries Rejected %d",counter_delivery-20);
    }
}

int main(int argc , char* argv[]){
    sem_init(&sema,0,2);
    srand(time(NULL));
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&is_full,NULL);
    pthread_cond_init(&is_empty,NULL);
    truck_inputs =  atoi(argv[1]);
    int warehouse_inputs = atoi(argv[2]);
    launch(truck_inputs , warehouse_inputs);

    return 0;
}
