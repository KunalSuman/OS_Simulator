#include<stdio.h>
#include<string.h>


int binaryToInt(const char *binaryStr) {
    int num = 0;
    int len = strlen(binaryStr);
    for(int i = 0; i < len; i++) {
        if(binaryStr[i] == '1') {
            num = (num << 1) | 1;
        }
        else {
            num = num << 1;
        }
    }
    return num;
}

void hexToBinary(const char *hexStr, char *binaryStr) {
    binaryStr[0] = '\0'; // Start with an empty string

    for(int i = 0; i < 4; i++) {
        switch(hexStr[i]) {
            case '0': strcat(binaryStr, "0000"); break;
            case '1': strcat(binaryStr, "0001"); break;
            case '2': strcat(binaryStr, "0010"); break;
            case '3': strcat(binaryStr, "0011"); break;
            case '4': strcat(binaryStr, "0100"); break;
            case '5': strcat(binaryStr, "0101"); break;
            case '6': strcat(binaryStr, "0110"); break;
            case '7': strcat(binaryStr, "0111"); break;
            case '8': strcat(binaryStr, "1000"); break;
            case '9': strcat(binaryStr, "1001"); break;
            case 'A': strcat(binaryStr, "1010"); break;
            case 'B': strcat(binaryStr, "1011"); break;
            case 'C': strcat(binaryStr, "1100"); break;
            case 'D': strcat(binaryStr, "1101"); break;
            case 'E': strcat(binaryStr, "1110"); break;
            case 'F': strcat(binaryStr, "1111"); break;

            // default: printf("Invalid hex digit %c\n", hexStr[i]);
        }
    }
}

int main(){

    //               CODE,  HEAP, STACK
    int base[3] =  {32768, 34816, 28672 };
    int bounds[3] = {2048,  3072,  2048 };
    //                2Kb,   3Kb,   2Kb


    printf("Enter the hexadecimal number: ");
    char VA_hex[4];
    gets(VA_hex);

    // printf("%c\n",VA_hex[0]);
    // char VA_bin[16];
    // hexToBinary(VA_hex, VA_bin );
    // for(int i=0; i<16; i++){
    //     printf("%c", VA_bin[i]);
    // }
    printf("\n");
    // printf("string length: %d\n",strlen(VA_hex));
    if(strlen(VA_hex)==4){

        char VA_bin[16];
        hexToBinary(VA_hex, VA_bin );
        printf("Input in Binary:");
        for(int i=0; i<16; i++){
            if(i%4==0){
                printf(" ");
            }
            printf("%c", VA_bin[i]);
        }

        printf("\n\n");

        int VA_int = binaryToInt(VA_bin);
        // printf("VA int: %d\n ", VA_int);

        int segment = (VA_int & 49152) >> 14 ;
        // printf("\nSegment in int: %d\n", segment);
        int offset = (VA_int & 16383);               //! checking last 14 bits
        // printf("OFFSET in int: %d\n", offset);

        if(segment >= 3 || segment < 0 ){
            printf("Segmentation Fault: Invalid Segment");
            return 0;
        }
        if (offset >= bounds[segment]){
            printf("Segmentation Fault: Out of Bounds\n");
            return 0;
        }
        else{
            // printf("BASE[%d] = %d\n", segment, base[segment]);

            char hex_addrs[4];
            if(segment == 2){
                // printf("[2] phy addrs: %d\n", base[segment] - offset );
                sprintf(hex_addrs, "%X", base[segment] - offset);
            }
            else{
                // printf("phy addrs: %d\n", base[segment] + offset );
                sprintf(hex_addrs, "%X", base[segment] + offset);
            }
            printf("Hexadecimal physical address: 0x%c%c%c%c\n", hex_addrs[0], hex_addrs[1], hex_addrs[2], hex_addrs[3] );

        }
    }
    else{
        printf("Segmentation Fault: String length != 4");
    }
    return 0;
}
