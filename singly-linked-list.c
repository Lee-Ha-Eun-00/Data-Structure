/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* link;
} listNode; //일반 노드

typedef struct Head {
	struct Node* first;
}headNode; //첫번째 노드를 가리킬 헤더 노드


/* 함수 리스트 */
headNode* initialize(headNode* h); //첫번째 노드를 만들어 주소반환하는 함수
int freeList(headNode* h); //리스트를 해제 시키를 함수

int insertFirst(headNode* h, int key); //맨 앞에 노드를 추가시키는 함수
int insertNode(headNode* h, int key); //크기에 따라 노드를 추가시키는 함수
int insertLast(headNode* h, int key); //마지막에 노드를 추가시키는 ㅎ마수
  
int deleteFirst(headNode* h); //첫번째 노드를 삭제하는 함수
int deleteNode(headNode* h, int key); //입력한 값을 가지고 있는 노드를 삭제하는 함수
int deleteLast(headNode* h); //마지막 노드를 삭제하는 함수
int invertList(headNode* h); //리스트를 역순으로 배치하는 함수

void printList(headNode* h); //리스트를 출력하는 함수

int main()
{
	char command; //메뉴 저장할 변수
	int key; //사용자가 입력한 값 저장할 변수
	headNode* headnode = NULL; //헤더노드를 위한포인터

    printf("----------[이하은]     [2019038037]----------\n");

	do { //메뉴출력
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); //메뉴를 받음
		scanf(" %c", &command);

		switch (command) { //입력에 따라 함수 호출
		case 'z': case 'Z':
			headnode = initialize(headnode); //헤더노드로쓰일 구조체를 만들어서 주소 반환
			break;
		case 'p': case 'P':
			printList(headnode); //리스트출력하는 함수 호출
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //key값 리스트에 추가하는 함수 호출
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //입력한 값을 가지고 있는 노드 삭제하는 함수호출
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //마지막에 노드를 추가하는 함수 호출
			break;
		case 'e': case 'E':
			deleteLast(headnode); //마지막 노드를 삭제하는 함수 호출
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //첫번째에 노드를 추가하는 함수 호출
			break;
		case 't': case 'T':
			deleteFirst(headnode); //첫번째 노드를 삭제하는 함수 호출
			break;
		case 'r': case 'R':
			invertList(headnode); //리스트를 역순으로 만드는 함수 호출
			break;
		case 'q': case 'Q':
			freeList(headnode);// 리스트를 해제시키를 함수 호출
			break;
		default: //메뉴 외의 입력 처리
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적 메모리 할당으로 node를 생성
	node->key = key; //node에 key값을 입력

	node->link = h->first; //node가 NULL을 가리키게함
	h->first = node; //head노드

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = h->first; //동적 메모리 할당으로 node를 생성 후 head가 가리키는 값을 node에 저장
	listNode* temp = (listNode*)malloc(sizeof(listNode)); //동적 메모리 할당으로 temp를 생성
	temp->key = key; //temp에 key 값을 저장
	listNode* trail = NULL; //이전 노드를 가리킬 포인터

	if (trail == NULL) //temp가 맨 앞에 위치해야 할 경우
	{
		insertFirst(h, key); //맨 앞에 노드를 삽입하는 함수 호출
		return 0;
	}

	while (node->link != NULL) //node의 다음노드가 NULL이면 반복중지
	{
		if (node->key > key)
		{
			//temp를 node앞에 삽입
			temp->link = node;
			trail->link = temp;
			return 0;  
		}
		//trail과 node가 하나씩 앞에 있는 노드를 가리키게 함
		trail = node;
		node = node->link;
	}

	//temp가 가장 마지막에 삽입되어야 할때
	insertLast(h, key);

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* temp = (listNode*)malloc(sizeof(listNode)); //동적 메모리 할당으로 temp를 생성
	temp->key = key; //temp에 key값을 저장
	listNode* node = h->first; //node에 헤더노드 값을 저장
	while (node->link != NULL) //node의 다음노드가 NULL이면 반복중지
	{
		node = node->link; //node가 다음 노를 가리키게함
	}
	temp->link = node->link; //temp가 NULL을 가리키게 함
	node->link = temp; //node가 temp를 가리키게 함 

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* node = h->first; //첫번째 노드를 가리키게 함
	h->first = node->link; //헤더노드가 가리키는 값을 2번째 노드로 바꿈
	free(node); //첫번째 노드의 메모리를 해제시킴

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* node = h->first; //동적 메모리 할당으로 node를 생성 후 head가 가리키는 값을 node에 저장
	listNode* trail = NULL; //이전 노드를 가리킬 포인터

	while (node != NULL) //node가 NULL이면 반복중지
	{
		if (node->key == key) //node의 key값이 사용자가 입력한 값과 같을 때
		{
			if (trail == NULL) //삭제할 노드가 첫번째 노드일 때 
			{
				deleteFirst(h); //첫번째 노드를 삭제하는 함수 호출
				return 0;
			}
			else
			{
				trail->link = node->link; //이전 노드가 다음 노드를 가리키게 함
				free(node); //현재 node의 메모리를 해제시킴
				return 0;
			}
			
		}
		//trail과 node가 다음 노드를 가리키게 함
		trail = node;
		node = node->link;

	}

	//입력한 값이 list에 없을 때
	printf("입력한 값이 존재하지 않습니다.\n");

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* node = h->first; //node에 헤더노드 값을 저장
	listNode* trail = NULL;
	while (node->link != NULL) //node의 다음노드가 NULL이면 반복중지
	{
		trail = node; //trail이 현재 node가 가리키고 있는 값을 가리키게 함
		node = node->link; //node가 다음 노드를 가리키게함
	}

	//trail이 NULL을 가리키고 node의 메모리는 해제시킴
	trail->link = node->link;
	free(node);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* lead = h->first; //lead에 헤더노드가 가리키는 값을 저장
	listNode* middle;
	listNode* trail; //역순으로 배치하기 위한 포인터 생성
	middle = NULL;

	while (lead != NULL) //lead가 NULL이 아닐때까지 반복
	{
		//middle이 가리키는 노드는 trail의 노드를 가키게한다. 이것을 마지막 노드까지 반복
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}


//리스트를 출력
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) { //헤드노드가 널일때
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p가 헤더노드가 가리키를 값을 가리키게 함

	while (p != NULL) { //p의 값이 NULL이 아닐때까지 p의 key값 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link; //p가 그 다음 노드를 가리키게함
		i++;
	}

	printf("  items = %d\n", i);
}
