#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "hex_2_binary.h"
    static int page_table_array[1024][1024] ;
    int page_directory_array[1024];
    static int physical_memorry[1024][1024];
    char input[33];
    int hit = 0 ;
    int miss = 0;
    int loop = 1;

void store(char* binary_value){
            char page_table_index[11] = "";
            char page_directory[11] ="";
            char offset_address[13] = "";

            int s = 0;
            for(int i = 10 ; i < 20 ; i++ ){
                page_table_index[s]= binary_value[i];
                s++ ;
            }
            page_table_index[s] = '\0';

            int k = 0;
            for(int i = 20 ; i < 32 ; i++){
                offset_address[k] = binary_value[i];
                k++;
            }
            offset_address[k] ='\0';

            int m =0;
            for(int i = 0 ; i< 10 ; i++){
                page_directory[i]=binary_value[i];
                m++;
            }
            page_directory[m] ='\0';

            int offset = strtol(offset_address , NULL ,2);
            int page_table_index_integer = strtol(page_table_index , NULL ,2);
            int page_directory_int = strtol(page_directory , NULL ,2);
            miss++;
            printf("Miss %d ",miss);
            page_directory_array[page_directory_int] = page_directory_int ;
            page_table_array[page_directory_int][page_table_index_integer] = page_directory_int*1000 + page_table_index_integer;
            physical_memorry[page_directory_int][page_table_index_integer] = page_directory_int*1000 + page_table_index_integer ;

            long long pfn_value = physical_memorry[page_directory_int][page_table_index_integer];
            long long pfn = (pfn_value*4096) + offset ;
            printf("PAddr updated @ %llx ",pfn);
            printf("Updated PD @ %d and PTE @ %d ",page_directory_int,physical_memorry[page_directory_int][page_table_index_integer]);
                uint8_t data = physical_memorry[pfn_value % 1024][offset % 1024];
                printf("%x", (uint8_t)data)  ;
}
uint8_t load(uint32_t val) {
        char binary_value[33];
        binary_value[32] ='\0';
        for(int i = 31 ; i >= 0 ; i--){
            if((val % 2) == 1){
                binary_value[i] = '1';
            }
            else{
                binary_value[i] = '0';
            }
            val = val/2 ;
        }
        printf("%s",binary_value);

        char page_table_index[11] = "";
        char page_directory[11] ="";
        char offset_address[13] = "";

        int s = 0;
        for(int i = 10 ; i < 20 ; i++ ){
            page_table_index[s]= binary_value[i];
            s++ ;
        }
        page_table_index[s] = '\0';

        int k = 0;
        for(int i = 20 ; i < 32 ; i++){
            offset_address[k] = binary_value[i];
            k++;
        }
        offset_address[k] ='\0';

        int m =0;
        for(int i = 0 ; i< 10 ; i++){
            page_directory[i]=binary_value[i];
            m++;
        }
        page_directory[m] ='\0';

        int offset = strtol(offset_address , NULL ,2);
        int page_table_index_integer = strtol(page_table_index , NULL ,2);
        int page_directory_int = strtol(page_directory , NULL ,2);


        int checker = 0 ;
        for(int i = 0 ; i < 1024 ; i++){
            if(page_directory_int == page_directory_array[i]){
                hit++;
                long long pfn_value = physical_memorry[page_directory_int][page_table_index_integer];
                long long pfn = (pfn_value*4096) + offset ;
                printf("HIT %d @ %llx \n return value of laod = ",hit,pfn);
                uint8_t data = physical_memorry[pfn_value % 1024][offset % 1024];
                printf("%x", (uint8_t)data)  ;
                checker = 1 ;
            }
        }
        if(checker == 0){
            store(binary_value);
        }
}

int main(int argc , char* argv[]){
        for(int i = 0 ; i < 1024; i++){
            if(i < 1000){
                page_directory_array[i] = i;
            }
            else{
                page_directory_array[i] = -1 ;
            }
        }
        for(int i = 0 ; i <1024 ; i++){
                if(i<1000){
                    for(int j = 0 ; j < 1024 ;j++){
                        page_table_array[i][j] = i*1000 + j ;
                        physical_memorry[i][j] = i*1000 + j ;
                    }
                }
                else{
                    for(int j = 0 ; j < 1024 ;j++){
                        page_table_array[i][j] = -1 ;
                        physical_memorry[i][j] = -1 ;
                    }
                }
        }
        while(loop){
            printf("\n");
            scanf("%s",input);
            if(strcmp(input,"1")==0){
                break ;
            }
            char* binary_value = hex_2_binary(input , 32);
            uint32_t val = strtoul(hex_2_binary(input ,32),NULL ,2);
            printf("%d ",(uint32_t) val);
            load(val);
        }
        int ratio = hit/miss;
        printf("ratio is %d ",ratio);
}
