#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _exam {
    char* exam_name;
    int  credits;
    int difficulty;
    int mark;
} exam;

exam* init_array(int num_exams);
int compare_1(const void* a, const void* b);
int compare_2(const void* a, const void* b);
void print_array(exam* exams, int num_exam);
void best_exams(exam* exams, int num_exam, int max_credits);

int main() {
    exam* exams;
    int num_ex;
    int max_credits;

    scanf("%d", &max_credits);
    scanf("%d", &num_ex);
    exams = init_array(num_ex);
    qsort(exams,num_ex,sizeof(exam),compare_1);
    //print_array(exams,num_ex);
    best_exams(exams,num_ex,max_credits);


    free(exams);
    return 0;
}

exam* init_array(int num_exams) {
    exam* exams = malloc(sizeof(exam)*num_exams);
    char* exam_name = malloc(sizeof(char)*101);


    for(int i = 0; i < num_exams; i++) {
        exams[i].mark = 0;
        scanf("%s", exam_name);
        exams[i].exam_name = malloc(sizeof(char) * (strlen(exam_name)+1));
        strcpy(exams[i].exam_name,exam_name);
        scanf("%d", &exams[i].credits);
        scanf("%d", &exams[i].difficulty);
    }
    return exams;
}

int compare_1(const void* a, const void* b) {
    if ((*(exam*)a).credits != ((*(exam*)b).credits))
        return -((*(exam*)a).credits - ((*(exam*)b).credits));
    if((*(exam*)a). difficulty != ((*(exam*)b).difficulty))
        return ((*(exam*)a).difficulty - ((*(exam*)b).difficulty));
    return strcmp((*(exam*)a).exam_name, (*(exam*)b).exam_name);
}

int compare_2(const void* a, const void* b){
    if((*(exam*)a).mark == 1 && ((*(exam*)b).mark) != 1)
        return -1;
    if((*(exam*)a).mark != 1 && ((*(exam*)b).mark) == 1)
        return 1;
    if((*(exam*)a).mark == 0 && ((*(exam*)b).mark) == 0)
        return strcmp((*(exam*)a).exam_name, (*(exam*)b).exam_name);
    return strcmp((*(exam*)a).exam_name, (*(exam*)b).exam_name);
}

void print_array(exam* exams, int num_exam) {
    for(int i = 0; i < num_exam; i++)
        printf("%s ", exams[i].exam_name);
    printf("\n");
    return;
}

void best_exams(exam* exams, int num_exam, int max_credits){
    int sum = 0;
    for(int i = 0; i < num_exam; i++){
        sum += exams[i].credits;
        if(sum <=  max_credits)
            exams[i].mark = 1;
        if (sum > max_credits)
            sum -= exams[i].credits;
    }
    qsort(exams,num_exam,sizeof(exam),compare_2);
    for(int j = 0; j < num_exam; j++){
        if (exams[j].mark == 1)
            printf("%s\n", exams[j].exam_name);
    }
    return;
}
