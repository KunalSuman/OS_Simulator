#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hex_2_binary.h"
int main(int argc , char* argv[]){
    int loop = 1 ;
    char input[16];
    int counter_loop = 0 ;
    char vpn_tbl[4][5] ={"0000","0001","0010","0011"};
    int pfn_tbl[4] ={0,1,2,3};
    char vpn_table[16][5] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    int pfn_table[16] = {15,2,3,12,8,9,14,1,4,7,11,10,13,5,6,16};
    while (loop){
        scanf("%s",input);
        if(strcmp(input,"1")==0){
            break ;
        }
        char* binary_value = hex_2_binary(input,16);

        int pfn_value = 0;
        char virtual_page_number[5];
        char offset_of_address[13] ;

        for(int i = 0 ; i < 4 ; i++){
        virtual_page_number[i] = binary_value[i];
        }
        int j = 0;
        for(int i = 4 ; i < 16 ; i++){
            offset_of_address[j] = binary_value[i];
            j++ ;
        }
        for(int i = 0 ; i < 16 ; i++){
            if(strcmp(virtual_page_number ,vpn_table[i])==0){
                pfn_value = pfn_table[i];
                break ;
            }
        }
        int offset = strtol(offset_of_address , NULL ,2);
        // USING PFN_Addr = (PFN << 12 )|offset
        int pfn_addr = ( pfn_value << 12 )|offset;
        printf("PFN Addr is %x ",pfn_addr);

        int checker = 0 ;
        for(int i = 0 ; i < 4 ; i++){
            if(strcmp(virtual_page_number , vpn_tbl[i])==0){
                printf("TLB HIT \n");
                checker=1 ;
            }
        }

        if(checker == 0){
            if(counter_loop > 3){
                counter_loop = 0 ;
            }
            if(counter_loop < 4){

                printf("TLB MISS ");
                strncpy(vpn_tbl[counter_loop],virtual_page_number,5) ;
                vpn_tbl[counter_loop][4] = '\0';
                pfn_tbl[counter_loop] = pfn_value ;
                counter_loop ++;
                printf("\n");
                for(int i = 0 ; i < 4 ; i ++){
                    printf("vpn is %s " , vpn_tbl[i]);
                    printf("pfn is %d " , pfn_tbl[i]);
                    printf("\n");
                }
            }
        }
    }
}
