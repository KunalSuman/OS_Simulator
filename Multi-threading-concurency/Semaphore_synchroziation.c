#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<string.h>

int connections[5]={0,0,0,0,0};
pthread_mutex_t mutex;
sem_t servers[5] ;
pthread_t server1 , server2 , server3 , server4 , server5 ;

void *server(void* args){
    if(strcmp((char *) args,"server1")==0){
        sem_wait(&servers[0]);
        sem_wait(&servers[1]);
            printf("%s is running \n",(char *)args);
            pthread_mutex_lock(&mutex);
             connections[0] =1 ;
             for(int i = 0 ; i < 5 ; i++){
                if(connections[i]==0){
                    printf("server%d is waiting \n",i+1);
                }
            }
            for(int i = 0 ; i < 5 ; i++){
                if(connections[i]==1){
                    connections[i]=0;
                }
            }
            pthread_mutex_unlock(&mutex);
        sem_post(&servers[0]);
        sem_post(&servers[1]);
    }
    if(strcmp((char *) args,"server2")==0){
        sem_wait(&servers[1]);
        sem_wait(&servers[2]);
             printf("%s is running \n",(char *)args);
             pthread_mutex_lock(&mutex);
             connections[1] =1 ;
             for(int i = 0 ; i < 5 ; i++){
                if(connections[i]==0){
                    printf("server%d is waiting \n",i+1);
                }
            }
            for(int i = 0 ; i < 5 ; i++){
                if(connections[i]==1){
                    connections[i]=0;
                }
            }
             pthread_mutex_unlock(&mutex);
        sem_post(&servers[1]);
        sem_post(&servers[2]);
    }
    if(strcmp((char *) args,"server3")==0){
        sem_wait(&servers[2]);
        sem_wait(&servers[3]);
            printf("%s is running \n",(char *)args);
            pthread_mutex_lock(&mutex);
             connections[2] =1 ;
             for(int i = 0 ; i < 5 ; i++){
                if(connections[i]==0){
                    printf("server%d is waiting \n",i+1);
                }
            }
            for(int i = 0 ; i < 5 ; i++){
                if(connections[i]==1){
                    connections[i]=0;
                }
            }
             pthread_mutex_unlock(&mutex);
        sem_post(&servers[2]);
        sem_post(&servers[3]);
    }
    if(strcmp((char *) args,"server4")==0){
        sem_wait(&servers[3]);
        sem_wait(&servers[4]);
        printf("%s is running \n",(char *)args);
        pthread_mutex_lock(&mutex);
        connections[3] =1 ;
        for(int i = 0 ; i < 5 ; i++){
            if(connections[i]==0){
                printf("server%d is waiting \n",i+1);
            }
        }
        for(int i = 0 ; i < 5 ; i++){
            if(connections[i]==1){
                connections[i]=0;
            }
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&servers[3]);
        sem_post(&servers[4]);
    }
    if(strcmp((char *) args,"server5")==0){
        sem_wait(&servers[4]);
        sem_wait(&servers[0]);
        printf("%s is running \n",(char *)args);
        pthread_mutex_lock(&mutex);
        connections[4] =1 ;
        for(int i = 0 ; i < 5 ; i++){
            if(connections[i]==0){
            printf("server%d is waiting \n",i+1);
            }
        }
        for(int i = 0 ; i < 5 ; i++){
            if(connections[i]==1){
                connections[i]=0;
            }
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&servers[4]);
        sem_post(&servers[0]);
    }
    // pthread_mutex_lock(&mutex);
    // for(int i = 0 ; i < 5 ; i++){
    //     if(connections[i]==0){
    //         printf("server%d is waiting \n",i+1);
    //     }
    // }

    return NULL ;
}

void run(){

    for(int i = 0 ; i <3 ; i ++){
        pthread_create(&server1,NULL,&server,"server1");
        pthread_create(&server2,NULL,&server,"server2");
        pthread_create(&server3,NULL,&server,"server3");
        pthread_create(&server4,NULL,&server,"server4");
        pthread_create(&server5,NULL,&server,"server5");

        pthread_join(server1,NULL);
        pthread_join(server2,NULL);
        pthread_join(server3,NULL);
        pthread_join(server4,NULL);
        pthread_join(server5,NULL);

    }

}

int main(){
    sem_init(&servers[0],0,1);
    sem_init(&servers[1],0,1);
    sem_init(&servers[2],0,1);
    sem_init(&servers[3],0,1);
    sem_init(&servers[4],0,1);
    run();
}
