#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

struct page {
    int16_t page_number;
    bool reference_bit;
    bool dirty_bit;
};

int page_scan( struct page memory[], int num_of_pages, int16_t page_number){
    for(int i=0; i<num_of_pages; i++){
        // printf("%d\n", memory[i].page_number);
        if(memory[i].page_number == page_number){
            // printf("page found\n");
            return i;
        }
    }
    // printf("page not found\n");
    return -1;
}


bool dirty_bit_scan( struct page memory[], int num_of_pages){
    for(int i=0; i<num_of_pages; i++){
        if(memory[i].dirty_bit == false){
            return false;       //* atleast 1 page is NOT dirty
        }
    }
    //* all pages are dirty
    return true;
}


int main(){
    int MAX_frames = 100;
    int num_of_pages;
    int q;
    int page_requested;
    // printf("enter max_frames: ");
    // scanf("%d", &MAX_frames);
    printf("enter num of pages: ");
    scanf("%d", &num_of_pages);
    printf("enter num of page request Queries: ");
    scanf("%d", &q);
    struct page memory[MAX_frames];

    printf("Page num\t| Refernce bit\t| Dirty bit  \n");
    for(int i=0; i<num_of_pages; i++){
        memory[i].page_number = -1;
        memory[i].reference_bit =  false;
        memory[i].dirty_bit = false;
        printf("\t%d\t\t%d\t\t%d\n",memory[i].page_number,memory[i].reference_bit,memory[i].dirty_bit);
    }

    int fault = 0;
    int hit = 0;

    while(q--){

        printf("Enter Requested page: ");
        scanf("%d", &page_requested);
        printf("Requested page: %d\n", page_requested);
        printf("Initially taken as Dirty bit? (1/0): ");
        int dirty_bit_inp;
        scanf("%d", &dirty_bit_inp);

        int page_idx = page_scan(memory, num_of_pages, page_requested);

        if(page_idx == -1){
            printf("Page wasnt found\n");
            fault++;
            int ptr = 0;

            if(dirty_bit_scan(memory, num_of_pages) == false){
                while( !(memory[ptr].reference_bit == false && memory[ptr].dirty_bit == false) ){
                    // printf("refernce bit: %d\n", memory[ptr].reference_bit);
                    memory[ptr].reference_bit = false;
                    ptr = (ptr+1) % num_of_pages;
                }
                printf("Replacing %d with %d.\n", memory[ptr].page_number, page_requested);

                memory[ptr].page_number = page_requested;
                memory[ptr].reference_bit = true;       //? whenever used their refernce bit is made 1
                if(dirty_bit_inp == 1){
                    memory[ptr].dirty_bit = true;
                }
                else{
                    memory[ptr].dirty_bit = false;
                }
            }
            else{
                printf("ALL pages are dirty\nWriting page: %d to memory, and then replacing it.\n", memory[ptr].page_number);
                memory[ptr].page_number = page_requested;
                memory[ptr].reference_bit = true;       //? whenever used their refernce bit is made 1
                if(dirty_bit_inp == 1){
                    memory[ptr].dirty_bit = true;
                }
                else{
                    memory[ptr].dirty_bit = false;
                }
            }


        }

        else{
            printf("Page Found\n");
            memory[page_idx].reference_bit = true;

            if(dirty_bit_inp == 1){
                memory[page_idx].dirty_bit = true;
            }
            else{
                memory[page_idx].dirty_bit = false;
            }

            hit++;
        }
        
        printf("Page num\t| Refernce bit\t| Dirty bit  \n");
        for(int i=0; i<num_of_pages; i++){
            printf("\t%d\t\t%d\t\t%d\n",memory[i].page_number,memory[i].reference_bit,memory[i].dirty_bit);
        }

    }

    printf("hits: %d\n", hit);
    printf("fault: %d\n", fault);
    float hit_rate = (float)((hit))/(float)(hit+fault) * 100 ;
    printf("hit rate: %.2f %% \n", hit_rate);

    // for(int i=0; i<num_of_pages; i++){
    //     printf("%d\t%d\t%d\n",memory[i].page_number,memory[i].reference_bit,memory[i].dirty_bit);
    //}
}
