#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int score;
} Student;

int find_max(Student students[], int start_idx, int n){
    int max_goal = 0;
    int idx = 0;
    int cur_score = 0;
    for (int i=start_idx;i<n;i++){
        cur_score = students[i].score;
        if (cur_score > max_goal){
            idx = i;
            max_goal = cur_score;
        }
    }
    return idx;
}

void swap(Student students[], int idx_a,int idx_b){
    Student temp = students[idx_a];
    students[idx_a]=students[idx_b];
    students[idx_b]=temp;
}

void insertion_sort(Student students[], int n) {
    int sorted_idx = 0;
    for(int i = 0; i<n; i++){
        int cur_max=find_max(students, sorted_idx, n);
        swap(students, cur_max, sorted_idx);
        sorted_idx++;
    }
}

int main(void) {
    FILE *file;
    Student students[50];
    int n = 0;
    
    // 打开文件（从命令行参数获取文件名）
    file = fopen("01_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 01_students.txt\n");
        return 1;
    }
    
    // 从文件读取学生信息
    while (n < 50 && fscanf(file, "%s %d", students[n].name, &students[n].score) == 2) {
        n++;
    }
    fclose(file);
    
    if (n == 0) {
        printf("文件中没有学生信息\n");
        return 1;
    }
    
    insertion_sort(students, n);
    
    printf("\n按成绩从高到低排序后的学生信息:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }
    
    return 0;
}

