#include "hex_2_binary.h"
#include <string.h>
char* hex_2_binary(char* input , int binary_length){
    static char binary_value[128] = "";
    binary_value[0] ='\0';
    for(int i = 0 ; i < strlen(input) ; i++){
        input[i] == '0' ? strcat(binary_value,"0000") :
        input[i] == '1' ? strcat(binary_value,"0001") :
        input[i] == '2' ? strcat(binary_value,"0010") :
        input[i] == '3' ? strcat(binary_value,"0011") :
        input[i] == '4' ? strcat(binary_value,"0100") :
        input[i] == '5' ? strcat(binary_value,"0101") :
        input[i] == '6' ? strcat(binary_value,"0110") :
        input[i] == '7' ? strcat(binary_value,"0111") :
        input[i] == '8' ? strcat(binary_value,"1000") :
        input[i] == '9' ? strcat(binary_value,"1001") :
        input[i] == 'A' || input[i] == 'a' ? strcat(binary_value,"1010") :
        input[i] == 'B' || input[i] == 'b' ? strcat(binary_value,"1011") :
        input[i] == 'C' || input[i] == 'c' ? strcat(binary_value,"1100") :
        input[i] == 'D' || input[i] == 'd' ? strcat(binary_value,"1101") :
        input[i] == 'E' || input[i] == 'e' ? strcat(binary_value,"1110") :
        input[i] == 'F' || input[i] == 'f' ? strcat(binary_value,"1111") : "" ;
    }
    return binary_value ;
}
