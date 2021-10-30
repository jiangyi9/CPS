#include <stdio.h>



//  This is the function to switch the the given number from decimal to binary, 
//and the binary result is stored in the array[] biy by bit.
void dec_to_bin(unsigned char number, int array[]){
    int step = 7;
    while(number != 0){
        array[step] = number % 2;
        step--;
        number /= 2;
    }
}



//this is the main() function
int main(){



    //define and initiate variables
    unsigned char number_dec, mask_dec, mask_hex;
    int number_array[8] = {}, mask_array[8] = {};
    int result = 0;



    //enter a number
    printf("Please enter a decimal number (0 - 255): ");
    scanf("%d", &number_dec);

    //switch the the given number from decimal to binary
    dec_to_bin(number_dec, number_array);



    //enter the mask
    printf("Please enter a hexadecimal mask (0x00 - 0xff): ");
    scanf("%x", &mask_hex);

    //switch the mask from hexadecimal to decimal
    mask_dec = (int) mask_hex;

    //switch the mask from decimal to binary
    dec_to_bin(mask_dec, mask_array);



    //compute the result by judging whether the last "the length of mask" unit is 1 bit by bit
    for(int i=0; i<8;i++){
        if(number_array[i] && mask_array[i]) result++;
    }



    //print the input number (binary)
    printf("The (binary) input number is: ");
    for(int i=0; i<8; i++){
        printf("%d", number_array[i]);
    }
    printf("\n");

    //print the mask number (binary)
    printf("The (binary) mask number is : ");
    for(int i=0; i<8; i++){
        printf("%d", mask_array[i]);
    }
    printf("\n");

    //print the final result
    printf("The result is: %d\n", result);



return 0;
}