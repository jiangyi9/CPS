#include <stdio.h>

void encode(const char *original, char *encoded){
    int index_ori = 0, index_en = 0;
    int size = 1;

    while(original[index_ori] != '\0'){
        if(original[index_ori] == original[index_ori+1]){
            size++;
            index_ori++;
        }
        else{
            if( size>=2 && size<=9 ){
                encoded[index_en++] = size + '0';
            }
            else if( size>=10 ){
                encoded[index_en++] = size/10 + '0';
                encoded[index_en++] = size%10 + '0';
            }
            size = 1;
            encoded[index_en++] = original[index_ori++];
        }
    }
}

void decode(const char *encoded, char *decoded){
    int index_en = 0, index_de = 0;
    int index_num = 0, index_char = 0;
    int num_array[100] = {0}; 
    char char_array[100];

    for(; encoded[index_en] != '\0'; index_en++){
        if(encoded[index_en] <= '9'){
            if(encoded[index_en+1] <= '9'){
                num_array[index_num] = 10 * (encoded[index_en] - '0') + (encoded[index_en+1] - '0');
                index_en++;
                index_num++;
            }
            else{
                num_array[index_num++] =  encoded[index_en] - '0';
            }
        }
        else{
            if(index_en == 0 || encoded[index_en-1] > '9'){
                num_array[index_num++] =  1;
            }
            char_array[index_char++] = encoded[index_en];
        }
    }

    int length = index_num;
    index_num = 0;
    index_char = 0;
    
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