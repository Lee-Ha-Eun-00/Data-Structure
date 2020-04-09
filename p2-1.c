#include <stdio.h>

#define MAX_SIZE 100 // MAX_SIZE를 100으로 정의

float sum(float [], int); //float형 배열과 int형 변수를 인자로 받고 float형을 리턴해 주는 함수의 함수원형
float input[MAX_SIZE], answer; //100개의 원소를 가진 float형 input배열과 float형 변수 answer 선언
int i;  //반복문에 사용할 변수

int main()
{
    printf("----------[이하은]     [2019038037]----------\n");

    for(i=0 ; i<MAX_SIZE ; i++) //100번 반복
    {
        input[i] = i; //i번째 원소에 i를 대입
    }

    printf("address of input = %p\n", input); //배열의 주소 출력

    answer =sum(input, MAX_SIZE); //sum 함수에 input의 주소와 100을 인자로 주고 리턴값은 answer에 저장
    printf("The sum is : %f\n", answer); 

    return 0;
}

float sum(float list[], int n) //float형 list배열과, int형 변수 n을 매개변수로 사용하는 함수
{
    printf("value of list = %p\n", list); //list의 값 출력 = input의 주소
    printf("address of list = %p\n\n", &list); //list의 주소 출력 !=list (&list는 list의 위치, list는 input의 주소)

    int i; //반복문에 사용할 변수
    float tempsum =0; //배열의 값을 더한 값을 저장할 변수
    for( i = 0; i < n; i++) //n번 반복(100번)
    {
       tempsum += list[i]; //tempsum에 list[i]의 값을 더해줌
    }
    
    return tempsum; //tempsum 리턴
} 