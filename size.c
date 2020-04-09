#include <stdio.h>
#include <stdlib.h> //malloc() 함수를 쓰기위한 헤더파일 포함

int main()
{
    printf("----------[이하은]     [2019038037]----------\n");
 
    int **x; //int를 가리키는 이중포인터변수 x 선언

    printf("sizeof(x)   = %lu\n", sizeof(x)); //*x의 주소를 가지고 있는 변수이기 때문에 8byte
    printf("sizeof(*x)  = %lu\n", sizeof(*x)); //**x의 주소를 가지고 있는 변수이기 때문에 8byte
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //int형의 값을 저장하는 변수 이기 때문에 4byte

    return 0;
}