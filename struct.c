#include <stdio.h>

struct student1 { // student1 구조체 테이터 타입 생성
    char lastName; //문자형 lastName ,학생의 이름 마지막글자저장
    int studentId; //int형 studentId ,학번저장
    char grade; //문자형 grade ,학점저장
};

typedef struct { //typedef를 사용하여 student2구조체 테이터 타입 생성
    char lastName; //문자형 lastName ,학생의 이름 마지막글자저장
    int studentId; //int형 studentId ,학번저장
    char grade; //문자형 grade ,학점저장
} student2;

int main()
{
    printf("----------[이하은]     [2019038037]----------\n");
 
    struct student1 st1 = {'A', 100, 'A'}; //student1 타입의 구조체 변수 st1 생성과 초기화 (typedef로 정의 하지 않아서 struct 키워드 사용)

    printf("st1.lastName = %c\n", st1.lastName); //st1.lastName의 값 출력
    printf("st1.sutdentId = %d\n", st1.studentId); //st1.studentId의 값 출력
    printf("st1.grade = %c\n", st1.grade); //st1.grade의 값 출력

    student2 st2 = {'B', 200, 'B'}; //student2타입의 구조체 변수 st2 생성과 초기화

    printf("\nst2.lastName = %c\n", st2.lastName); //st2.lastName의 값 출력
    printf("st2.studentId = %d\n", st2.studentId); //st2.studentId의 값 출력
    printf("st2.grade = %c\n", st2.grade); //st2.grade의 값 출력
    
    student2 st3; //student2타입의 구조체 변수 st3 생성

    st3 = st2; //st3에 st2의 값을 대입(구조치환)

    printf("\nst3.lastName = %c\n", st3.lastName); //st3.lastName의 값 출력
    printf("st3.studentId = %d\n", st3.studentId); //st3.studentId의 값 출력
    printf("st3.grade = %c\n", st3.grade); //st3.grade의 값 출력
    //st2와 동일한값

    /*
    if(st3==st2) //st3와 st2가 같은지 비교 (불가능)
    {
        printf("equal\n"); //참일 때 equal출력
    }
    else //그렇지 않으면 not equal출력
    {
        printf("not equal\n");
    }
       */

    return 0;
}