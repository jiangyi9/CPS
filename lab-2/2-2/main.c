#include <stdio.h>

// define a new datatype "Grade_info"
typedef struct{
    char first_name[15];
    char last_name[15];
    int assignment_1;
    int assignment_2;
    int assignment_3;
    int assignment_4;
    char email_address[30];
    int score;
    float grade;
}Grade_info;

// transfer score to grade
float transfer(int score){
    float grade;
    if(score < 50) grade = 5.0;
    else if(score >= 50 && score < 55.5) grade = 4.0;
    else if(score >= 55.5 && score < 60.5) grade = 3.7;
    else if(score >= 60.5 && score < 65.5) grade = 3.3;
    else if(score >= 65.5 && score < 70.5) grade = 3.0;
    else if(score >= 70.5 && score < 75.5) grade = 2.7;
    else if(score >= 75.5 && score < 81) grade = 2.3;
    else if(score >= 81 && score < 86) grade = 2.0;
    else if(score >= 86 && score < 91) grade = 1.7;
    else if(score >= 91 && score < 96) grade = 1.3;
    else if(score >= 96) grade = 1.0;
    return grade;
}

int main(){

    Grade_info student[100];
    int num = 0;

    //open input.txt
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL){
        printf("Fail to open the file !!");
        return -1;
    }

    //read file and store data to student[num]
    while(!feof(fp)){
        fscanf(fp, "%[^,],%[^,],%d,%d,%d,%d,%s\n", student[num].first_name, student[num].last_name
        , &student[num].assignment_1, &student[num].assignment_2, &student[num].assignment_3
        , &student[num].assignment_4, student[num].email_address);
        student[num].score = student[num].assignment_1 + student[num].assignment_2 
        + student[num].assignment_3 + student[num].assignment_4;
        student[num].grade = transfer(student[num].score);
        num++;
    }
    fclose(fp);

    //"total" is the total number of students, e.g. 2
    int total = num;

    //write data to output.txt
    fp = fopen("output.txt", "w");
    for(num=0; num<total; num++){
        fprintf(fp, "%s %s <%s>: %.1f\n", student[num].first_name, student[num].last_name, student[num].email_address
        , student[num].grade);
    }
    fclose(fp);

    return 0;
}