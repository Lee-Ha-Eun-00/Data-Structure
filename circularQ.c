/*
 * circularQ.c
 *
 */

#include <stdio.h> 
#include <stdlib.h>  //malloc함수를 사용하기 위한 헤더파일포함

#define MAX_QUEUE_SIZE 4 //큐원소의 갯수+1

typedef char element; //문자형 변수를 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; //원소의 데이터와 원소의 맨앞과 끝을 알려주는 변수를 포함하는 구조체변수 선언


QueueType *createQueue(); //큐를 생성하는 함수
int isEmpty(QueueType *cQ); //큐가 비어있을때 실행하는 함수
int isFull(QueueType *cQ); //큐가 꽉차있을 때 실행하는 함수
void enQueue(QueueType *cQ, element item); //원소를 삽입하는 함수
void deQueue(QueueType *cQ, element* item);//원소를 삭제하는 함수
void printQ(QueueType *cQ); //큐에 있는 원소의 값을 출력하는 함수
void debugQ(QueueType *cQ); //원소의값과 fornt,rear의 값을 출력하는 함수
element getElement(); //사용자에게 원소의 값을 입력 받는 함수

int freeQueue(QueueType *cQ) //동적메모리를 해제하는 함수, 큐의 주소를 넘겨받음
{
	if(cQ == NULL) return 1; //cQ가 비어있으면 1을반환
	free(cQ); //그렇지 않으면 cQ의 메모리를 해제
	return 1;
}
int main(void)
{
	QueueType *cQ = createQueue(); //큐를 생성하여 cQ에 저장
	element data; //사용자에게 받은 원소의 값을 저장할 변수

	char command; //사용자에게 입력받은 메뉴를 저장할 변수

	printf("----------[이하은]     [2019038037]----------\n");

	do{
		//메뉴 출력
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자에게 입력받은 값을 command에 저장

		switch(command) {
		case 'i': case 'I': //command가 i or I일때
			data = getElement(); //사용자에게 원소의 값을 입력받는 함수 실행하여 data에 저장
			enQueue(cQ, data); //원소의 값을 큐에 저장하는 함수 호출
			break;
		case 'd': case 'D': //command가 d or D일때
			deQueue(cQ,&data); //원소의 값을 삭제하는 함수 호출
			break;
		case 'p': case 'P': //command가 p or P일때
			printQ(cQ); //원소의 값을 출력하는 함수 호출
			break;
		case 'b': case 'B': //command가 b or B일때
			debugQ(cQ); //원소의 값과 front, rear의 값을 출력하는 함수 호출
			break;
		case 'q': case 'Q': //command가 q or Q일때
			freeQueue(cQ); //cQ의 메모리를 해제하는 함수호출
			break;
		default: //메뉴에 없는 값을 입력했을 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //먼저 실행한후 q나Q의 값이 입력될때까지 반복


	return 1;
}


QueueType *createQueue() //큐를 생성하는 함수
{
	QueueType *cQ; //QueueType형을 가리키는 cQ변수 생성
	cQ = (QueueType *)malloc(sizeof(QueueType)); //QueueType크기의 동적메모리 할당
	cQ->front = 0;//front의 값 초기화
	cQ->rear = 0;//rear의 값 초기화
	return cQ; //cQ의 주소 반환
}

element getElement() //사용자에게 원소의 값을 입력 받는 함수
{
	element item; //원소의 값을 저장할 변수
	printf("Input element = ");
	scanf(" %c", &item); //사용자에게 입력받음
	return item; //원소의 값을 반환
}


int isEmpty(QueueType *cQ)  //큐가 비어있을때 실행하는 함수 큐의주소를 매개변수로 받음
{
    printf("circular Queue is empty!\n");  //큐가 비어있음을 알림
    return 0;
}

int isFull(QueueType *cQ) //큐가 꽉차있을 때 실행하는 함수 큐의주소를 매개변수로 받음
{
    printf("Circulat Queue is full!\n");  //큐가 꽉차있음을 알림

     //원소의 값을 저장하기 위해 ++해줬던 rear의 값을 원래대로 만들어줌
    if(cQ->rear==0) //rear의 값이 0일때
    {
        cQ->rear=MAX_QUEUE_SIZE-1; //이전의 값이었던 마지막 인덱스의 번호로 바꿔줌
    }
    else
    {
        cQ->rear--; //-1한 값으로 바꿔줌

    }
    
   return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item) //원소를 삽입하는 함수 큐의 주소와 사용자가 입력한 원소의 값을 전달받음
{
    cQ->rear=((cQ->rear+1)%MAX_QUEUE_SIZE); //rear의 값을 +1 해줌 마지막 원소라면 0을 입력함
    if(cQ->front==cQ->rear) //front와 rear의 값이 같다면
    {
        isFull(cQ); //큐가 꽉차있때 실행하는 함수 호출
    }
    else
    {
        cQ->queue[cQ->rear]=item; //큐에 원소를 저장

    }
    
	//return 0;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) //원소를 삭제하는 함수 큐의 주소와 사용자가 입력한 원소의 값을 전달받음
{
    if(cQ->front==cQ->rear) //front와 rear의 값이 같다면
    {
        isEmpty(cQ); //큐가 비어 있때 실행하는 함수 호출
    }
    else 
    {
        cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE; //fornt의 값을 +1 해줌 마지막 원소라면 0을 입력함
        cQ->queue[cQ->front]='\0'; //현재 front번째 있는 원소의 값을 삭제해줌
    }
   //return 0;
}


void printQ(QueueType *cQ) //큐에 있는 원소의 값을 출력하는 함수 큐의주소를 매개변수로 받음
{
	int i, first, last; 

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // first에 front다음 수를 입력 마지막 인덱스의 번호이면 0을 입력
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // last에 rear다음 수를 입력 마지막 인덱스의 번호이면 0을 입력

	printf("Circular Queue : [");
	//first 부터 last전까지 출력
	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]); //i번째 인덱스에 있는 큐의 값 출력
		i = (i+1)%MAX_QUEUE_SIZE; //i의 값 증가 마지막 인덱스의 번호와 동일하면 0으로

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //원소의값과 fornt,rear의 값을 출력하는 함수 큐의주소를 매개변수로 받음
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)  //원소의 개수+1만큼복
	{
		if(i == cQ->front) { //i가 front의 값과 같으면 front라고 출력
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //i번째 원소의 값을 출력 

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front의 값과 reqr의 값출력
}

