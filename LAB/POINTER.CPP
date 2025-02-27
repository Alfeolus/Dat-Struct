#include <stdio.h>
#include <stdlib.h>

struct Student{
    int age;
    int height;
}arrStudent[5];

int main() {

    Student ppti;


    //akses anggota struct
    ppti.age = 20;
    ppti.height = 170;
    // int a = 10;
    // int* ptr = &a;

    // printf("memory dari ptr: %d\n", &ptr);
    // printf("Value dari ptr: %d\n",ptr);
    // printf("value dari memory yang disimpan: %d\n",*ptr);

    // *ptr = 20;

    // printf("nilai a sekarang : %d\n",a);

    //memory allocation example
    int* ptr = (int *)malloc(sizeof(int));

    *ptr = 20;

    printf("alamat baru: %d, value dari alamat: %d\n",ptr,*ptr);

    // Alokasi memori untuk struct
    Student* ptr2 = (Student*)malloc(sizeof(struct Student));

    // Akses anggota dari struct pointer
    ptr2->age = 21;
    ptr2->height = 175;

    printf("age: %d, height: %d\n",ptr2->age, ptr2->height);

    // melepaskan alokasi memori
    free(ptr2);

    // akses anggota dari array of struct
    arrStudent[0].age = 20;
    arrStudent[1].age = 12;
}