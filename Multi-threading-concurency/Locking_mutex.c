#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
pthread_mutex_t mutex;
int c[3]={0};
char* c1[3] = {"T1","T2","T3"};
void* lockA(void* args){

    pthread_mutex_lock(&mutex);
    char* val = (char*) args ;
    if(strcmp(val,"T1") == 0){
        c[0] =1 ;
    }
    if(strcmp(val,"T2") == 0){
        c[1] =1 ;
    }
    if(strcmp(val,"T3") == 0){
        c[2] =1 ;
    }

    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex);
    for(int i = 0 ; i < 3 ;i++){
        if(c[i] == 1){
            printf("%s is Running A \n",(char*)args);
        }
        else{
            printf("%s is waitng A \n",c1[i]);
        }
    }
    for(int i = 0 ; i < 3 ; i++){
        c[i] = 0 ;
    }
    pthread_mutex_unlock(&mutex);

    return NULL ;
}
void* lockB(void* args){


    pthread_mutex_lock(&mutex);
    char* val = (char*) args ;
    if(strcmp(val,"T1") == 0){
        c[0] =1 ;
    }
    if(strcmp(val,"T2") == 0){
        c[1] =1 ;
    }
    if(strcmp(val,"T3") == 0){
        c[2] =1 ;
    }
    pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    for(int i = 0 ; i < 3 ;i++){
        if(c[i] == 1){
            printf("%s is Running B \n",(char*)args);
        }
        else{
            printf("%s is waitng B \n",c1[i]);
        }
    }
    for(int i = 0 ; i < 3 ; i++){
        c[i] = 0 ;
    }
    pthread_mutex_unlock(&mutex);

    return NULL ;
}

int main(){
	pthread_t T1 , T2 , T3;
    pthread_mutex_init(&mutex,NULL);
    for(int i = 0 ; i <3 ;i++){
        pthread_create(&T1 , NULL ,&lockA, "T1");
        pthread_create(&T2 , NULL ,&lockA, "T2");
        pthread_create(&T3 , NULL ,&lockA, "T3");

        pthread_join(T1 ,NULL);
        pthread_join(T2,NULL);
        pthread_join(T3 , NULL);


        pthread_create(&T1 , NULL ,&lockB, "T1");
        pthread_create(&T2 , NULL ,&lockB, "T2");
        pthread_create(&T3 , NULL ,&lockB, "T3");

        pthread_join(T1 ,NULL);
        pthread_join(T2,NULL);
        pthread_join(T3 , NULL);
    }
}
