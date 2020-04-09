#include <stdio.h>
#include <stdlib.h> //malloc() 함수를 쓰기위한 헤더파일 포함

int main()
{
    printf("----------[이하은]     [2019038037]----------\n");

    int list[5]; //int형 배열 선언
    int *plist[5]={NULL,}; //int형을 가리킬 포인터배열 선언 후 NULL로 초기화
    
    plist[0] = (int*)malloc(sizeof(int)); //plist 첫번째 원소에 할당받은 동적 메모리 주소를 저장 

    list[0] = 1; //list[0]에 1대입
    list[1] = 100; //list[1]에 100대입

    *plist[0] = 200; //plist[0]이 가리키는 메모리에 200대입

    printf("value of list[0]         = %d\n", list[0]); //list[0]값 출력
    printf("address of list[0]       = %p\n", &list[0]); //list[0]의 주소출력
    printf("value of list            = %p\n", list); //list의 값 출력
    printf("address of list (&list)  = %p\n", &list); //list의 주소출력
    //배열의 이름은 배열의 처음 시작의 주소라서 &list[0]=list=&list

    printf("--------------------------------------------\n\n");
    printf("value of list[1]   = %d\n", list[1]); //list[1]의 값 출력
    printf("address of list[1] = %p\n", &list[1]); //list[1]의 주소 출력
    printf("value of *(list+1) = %d\n", *(list+1)); //*(list+1)의 값 출력 =list[1]
    printf("address of list+1  = %p\n", list+1); //list+1의 주소 출력
    //list+1=&list[1]

    printf("----------------------------------------------\n\n");

    //(plist=&plist[0])
    printf("value of *plist[0] = %d\n", *plist[0]); //*plist[0]의 값 출력
    printf("&plist[0]          = %p\n", &plist[0]); //plist[0]의 주소 출력  
    printf("&plist             = %p\n", &plist); //plist의 주소출력 
    printf("plist              = %p\n", plist); //plist의 값 출력
    printf("plist[0]           = %p\n", plist[0]); //plist[0]의 값 출력 = 200을 저장하고 있는 메모리의 주소
    printf("plist[1]           = %p\n", plist[1]); //plist[1]의 값 출력
    printf("plist[2]           = %p\n", plist[2]); //plist[2]의 값 출력
    printf("plist[3]           = %p\n", plist[3]); //plist[3]의 값 출력
    printf("plist[4]           = %p\n", plist[4]); //plist[4]의 값 출력
 
    free(plist[0]); //할당해줬던 동적 메모리 해지

    return 0;

}