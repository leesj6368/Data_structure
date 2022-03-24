#include<stdio.h>
#include<stdlib.h>

void main(){
    int list[5]; //5개의 정수 배열
    int *plist[5]={NULL}; //정수에 대한 5개 포인터 초기화

    plist[0]=(int *)malloc(sizeof(int)); //동적 메모리 할당

    list[0]=1; //배열에 값 넣음
    list[1]=100;

    *plist[0]=200; //포인터가 가리키는 첫 주소의 값은 200
    printf("[----- [이선주] [2021041042] -----]\n");
    printf("value of list[0] = %d\n", list[0]); //배열의 첫번째 값 출력
    printf("address of list[0] = %p\n", &list[0]); //배열의 첫번째 주소 출력
    printf("value of list = %p\n", list); //list=list[0]=&list
    printf("address of list (&list) = %p\n", &list);
    printf("----------------------------------------\n\n");
    printf("value of list[1] = %d\n", list[1]); //배열 두번째 값 출력
    printf("address of list[1] = %p\n", &list[1]); //배열 두번째 주소 출력
    printf("value of *(list+1) = %d\n", *(list + 1)); //list[1]=*(list+1)
    printf("address of list+1 = %p\n", list+1); //list+1=&list[1]
    printf("----------------------------------------\n\n");
    printf("value of *plist[0] = %d\n", *plist[0]); //*plist[0]값 출력
    printf("&plist[0] = %p\n", &plist[0]); //plist[0]의 주소 출력
    printf("&plist = %p\n", &plist); 
    printf("plist = %p\n", plist); //plist=&plist=&plist[0]
    printf("plist[0] = %p\n", plist[0]); //plist 배열 주소 출력, 0~4
    printf("plist[1] = %p\n", plist[1]);
    printf("plist[2] = %p\n", plist[2]);
    printf("plist[3] = %p\n", plist[3]);
    printf("plist[4] = %p\n", plist[4]);
    free(plist[0]); //동적할당 해제
    
}

