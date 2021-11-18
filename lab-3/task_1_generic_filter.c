#include <stdio.h>
#include <stdlib.h>

#define FILTER_ORDER 3

void filter(double *X, double *Y, int index){
    float A[FILTER_ORDER+1] = {1,-2.381248152097108,1.939698524314131,-0.535986990176121};
    float B[FILTER_ORDER+1] = {0.002807922755113,0.008423768265338,0.008423768265338,0.002807922755113};
    int i;
    Y[index] += B[0]*X[index];
    if(index<FILTER_ORDER+1){
        for(i=1; i<index+1; i++){
            Y[index] += B[i]*X[index-i];
            Y[index] -= A[i]*Y[index-i];
        }
    }
    else{
        for(i=1; i<FILTER_ORDER+1; i++){
            Y[index] += B[i]*X[index-i];
            Y[index] -= A[i]*Y[index-i];
        }
    }
}

int main(){

    double X[301];
    double Y[301] = {0};

    // read the signal_combined.csv file and store the data to X[]
    FILE* fp = fopen("signal_combined.csv", "at+");
    if(fp == NULL){
        printf("Fail to open the file !!");
        return -1;
    }

    // read the signal_combined.csv file and store the data to X[]
	char *line,*record;
	char buffer[16];
    fseek(fp, 0L, SEEK_SET);
    int index = 0;
    while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)
    {
        record = strtok(line, "\n");
        X[index] = atof(record);
        // printf("%lf\n", X[index]);
        index++;
    }
    fclose(fp);

    // process the data using filter()
    int length = index;
    for(index=0; index<length; index++){
        filter(X, Y, index);
    }

    // print the result Y[]
    for(index=0; index<length+1; index++){
        printf("%lf\n", Y[index]);
    }

    // export Y[] as "signal_new.csv"
    fp = fopen("signal_new.csv", "w");
    for(index=0; index<length; index++)
        fprintf(fp, "%f\n", Y[index]);
    fclose(fp);

    return 0;
}