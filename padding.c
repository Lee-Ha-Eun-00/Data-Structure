#include <stdio.h>

struct student{ // student1 구조체 테이터 타입 생성
    char lastName[13]; //문자열 lastName ,학생의 이름 저장 (1*13bytes)
    int studentId; //int형 studentId ,학번저장 (4bytes)
    short grade;  //short형 grade ,학점저장 (2bytes)
};

int main()
{
    printf("----------[이하은]     [2019038037]----------\n");
 
    struct student pst; //student 타입의 구조체 변수 pst 생성 (typedef로 정의 하지 않아서 struct 키워드 사용)

    printf("size of student = %ld\n",sizeof(struct student)); //student의 크기 출력
    printf("size of int = %ld\n",sizeof(int)); //int의 크기출력
    printf("size of short = %ld\n",sizeof(short)); //short의 크기출력

    /*student안에 있는 변수들의 byte수를 다 더하면 13+4+2=19
      즉 구조체의 크기가 19bytes여야 하는데 padding처리가 된다면 구조체의 크기가 더 커진다.  */

    return 0;
}