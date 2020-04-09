#include <stdio.h>

void print1(int *ptr, int rows); ///포인터와 int형 rows를 매개변수로 하는 함수의 함수원형

int main()
{
    printf("----------[이하은]     [2019038037]----------\n");

    int one[] = {0, 1, 2, 3, 4}; //원소가 5개인 int형 배열 선언과 초기화

    //one=&one=one[0]
    printf("one     = %p\n", one); //one의 값 출력
    printf("&one    = %p\n", &one); //one의 주소출력
    printf("&one[0] = %p\n", &one[0]); //one[0]의 주소출력
    printf("\n"); 

    print1(&one[0], 5); //print1함수에인자로 one[0]의 주소와 5를 넘겨줌

    return 0;
}

void print1 (int *ptr, int rows) ///포인터와 int형 rows를 매개변수로 하는 함수
{
    int i; //반목문에 쓸 변수

    printf("Address \t Contents\n");
    for ( i = 0; i < rows; i++) //5번 반복
    {
        printf("%p \t %5d\n", ptr+i, *(ptr+i)); //ptr(one)+i 의 값과 ptr+i가 가리키는 곳의 값 출력
        //포인터가 one의 주소를 받아 one에 접근 후 각 원소의 값을 출력함
    }
     printf("\n");
}
