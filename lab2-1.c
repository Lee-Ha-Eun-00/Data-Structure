#include <stdio.h>

int main()
{
    char charType; //문자형 변수 charType 선언
    int integerType; //정수형 변수 integerType 선언
    float floatType; //실수형 변수 floatType선언
    double doubleType; //실수형 변수 doubleType선언

    printf("Size of char : %ld byte\n",sizeof(charType)); //변수 charType의 크기 출력
    printf("Size of int : %ld bytes\n",sizeof(integerType)); //변수 intgerType의 크기 출력
    printf("Size of float : %ld bytes\n",sizeof(floatType)); //변수 floatType의 크기 출력
    printf("Size of double : %ld bytes\n",sizeof(doubleType)); //변수 doubleType의 크기 출력

    printf("----------------------------------------------\n"); 

    printf("Size of char : %ld byte\n",sizeof(char)); //자료형 char의 크기를 출력
    printf("Size of int : %ld bytes\n",sizeof(int)); //자료형 int의 크기를 출력
    printf("Size of float : %ld bytes\n",sizeof(float)); //자료형 float의 크기를 출력
    printf("Size of double : %ld bytes\n",sizeof(double)); //자료형 double의 크기를 출력

    printf("----------------------------------------------\n");

    printf("Size of char* : %ld byte\n",sizeof(char*)); //char형 포인터변수의 크기를 출력
    printf("Size of int* : %ld bytes\n",sizeof(int*)); //int형 포인터변수의 크기를 출력
    printf("Size of float* : %ld bytes\n",sizeof(float*)); //float형 포인터변수의 크기를 출력
    printf("Size of double* : %ld bytes\n",sizeof(double*)); //double형 포인터변수의 크기를 출력

    printf("----------[이하은]     [2019038037]----------");

/*일반변수는 자료형에 따라 저장공간의 크기가 달라지지만 포인터 변수는 자료형이 달라도 크기가 같다. 
 그 이유는 포인터 변수는 주소를 저장하는 저장공간으로 모두  8byte 이기 때문이다.*/

    return 0;
}