#include <stdio.h>
#include <stdlib.h> //malloc() 함수를 쓰기위한 헤더파일 포함

int main()
{
    printf("----------[이하은]     [2019038037]----------\n");
    
    int list[5]; //int형 배열 선언
    int *plist[5]; //int형을 가리킬 포인터배열 선언

    list[0] = 10; //list[0]에 10저장
    list[1] = 11; //list[0]에 11저장

    plist[0] =  (int*)malloc(sizeof(int)); //plist 첫번째 원소에 할당받은 동적 메모리 주소를 저장 

    printf("list[0] \t = %d\n", list[0]); //list[0]의 값 출력 (초기화 하지 않았으므로 쓰레기값 있음)
    printf("addressof list \t = %p\n", list); //list의 주소 출력
    printf("addressof list[0] \t = %p\n", &list[0]); //list[0]의 주소출력 = &list[0]
    printf("addressof list+0 \t = %p\n", list +0); //list + 0의 주소출력  =&list[0] +4byte
    printf("addressof list+1 \t = %p\n", list +1); //list + 1의 주소출력
    printf("addressof list+2 \t = %p\n", list +2); //list + 2의 주소출력
    printf("addressof list+3 \t = %p\n", list +3); //list + 3의 주소출력
    printf("addressof list+4 \t = %p\n", list +4); //list + 4의 주소출력
    printf("addressof list[4] \t = %p\n", &list[4]); //list[4]의 주소출력

    free(plist[0]); //할당해줬던 동적 메모리 해지

    return 0;
}