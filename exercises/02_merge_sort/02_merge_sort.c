#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge(int left, int mid, int right){
    int seg1_cur = left;
    int seg1_end = mid;
    int seg2_cur = mid+1;
    int seg2_end = right;
    
    int temp_idx = 0;
    while(seg1_cur<=seg1_end && seg2_cur<=seg2_end){
        if(students[seg1_cur]>students[seg2_cur]){
            temp[temp_idx] = students[seg1_cur];
            seg1_cur++;
        }else{
            temp[temp_idx] = students[seg2_cur];
            seg2_cur++;
        }
        temp_idx++;
    }

    while (seg1_cur<=seg1_end){
        temp[temp_idx] = students[seg1_cur];
        seg1_cur++;
        temp_idx++;
    }
    while (seg2_cur<=seg2_end){
        temp[temp_idx] = students[seg2_cur];
        seg2_cur++;
        temp_idx++;
    }

    for(int i = 0;i < right - left ; i++){
        students[left + i] = temp[i];
    }
}

void merge_sort(int left, int right) {
    if(left>=right){
        return;
    }
    int mid = left+(right-left)/2;
    merge_sort(left,mid);
    merge_sort(mid+1,right);
    merge(left,mid,right);
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}