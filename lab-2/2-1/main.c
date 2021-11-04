#include <stdio.h>
#include <ctype.h>

void encode(const char *original, char *encoded){
    int index_ori = 0, index_en = 0;
    int size = 1; // there are "size" consecutive same letters

    //traversal original[]
    while(original[index_ori] != '\0'){

        //(case 1) when the currect and the next letters are the same
        if(original[index_ori] == original[index_ori+1]){
            size++; 
            index_ori++;
        }
        else{//(case 2) when the currect and the next letters are different
            if( size>=2 && size<=9 ){              /* (case 2.1) if the former 1 to 8 letters and the current letter are the same, */
                encoded[index_en++] = size + '0';  /* corevrt (int)size to (char)size, and store it to encoded[index_en]           */
            }
            else if( size>=10 ){
                encoded[index_en++] = size/10 + '0'; /* (case 2.2) if the former >=9 letters and the current letter are the same, */
                encoded[index_en++] = size%10 + '0'; /* corevrt (int)size to (char)size, and store it to encoded[index_en] and    */
            }                                        /* encoded[index_en+1]                                                       */
            size = 1;
            encoded[index_en++] = original[index_ori++]; /* store the corresponding letter of original[index_ori] to encoded[index_en] */
        }
    }
}

void decode(const char *encoded, char *decoded){
    int index_en = 0, index_de = 0;
    int index_num = 0, index_char = 0;
    int num_array[100] = {0}; // num_array[] is an array to store all numbers of encoded[]
    char char_array[100]; // char_array[] is an array to store all letters of encoded[]

    for(; encoded[index_en] != '\0'; index_en++){
        if(isdigit(encoded[index_en])){ //case 1: when encoded[index_en] is a number
            if(isdigit(encoded[index_en+1])){ // case 1.1: when encoded[index_en+1] is also a number
                num_array[index_num] = 10 * (encoded[index_en] - '0') + (encoded[index_en+1] - '0'); /* let these 2 numbers be a   */
                index_en++;                                                                          /* 2-digit number, and store  */
                index_num++;                                                                         /* it to num_array[index_num] */
            }
            else{ // case 1.2: when encoded[index_en+1] is not a number
                num_array[index_num++] =  encoded[index_en] - '0'; // simply store this 1-digit number to num_array[index_num]
            }
        }
        else{// case 2: when encoded[index_en] is a letter
            if(index_en == 0 || encoded[index_en-1] > '9'){ // case 2.1: if this letter is at encoded[0], or both this element and its former element are letters
                num_array[index_num++] =  1; // store number "1" to num_array[index_num]
            }
            // case 2.2 (other cases): nothings happens here
            
            // when encoded[index_en] is a letter
            char_array[index_char++] = encoded[index_en]; // store this letter to char_array[index_char]
        }
    }

    int length = index_num;
    index_num = 0;
    index_char = 0;
    
    // compute decoded[] by adding "num_array[index_num]" number of "char_array[index_num]" letters in order
    while(index_num <= length){
        for(int i=0; i<num_array[index_num]; i++){
            decoded[index_de] = char_array[index_num];
            index_de++;
        }
    index_num++;
    }
}

int main(){
    const char original[100] = "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB";
    char encoded[100];
    char decoded[100];
    printf("Original: %s\n", original);
    encode(original, encoded);
    printf("Encoded: %s\n", encoded);
    decode(encoded, decoded);
    printf("Decoded: %s\n", decoded);
    return 0;
}