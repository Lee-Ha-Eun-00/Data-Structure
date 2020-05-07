/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>


typedef struct Node { //key값과 오른쪽, 왼쪽 링크를 가지고 있는 노드
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head { //첫번째 노드를 가리키는 헤드노드
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수르 받음
		 singly-linked-list의 initialize와 차이점을 이해할 것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
	    - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key); //노드를 삽입하는 함수
int insertLast(headNode* h, int key); //마지막에 노드를 삽입하는 함수
int insertFirst(headNode* h, int key); //첫번째에 노드를 삽입하는 함수
int deleteNode(headNode* h, int key); //노드를 삭제하는 함수
int deleteLast(headNode* h); //마지막 노드를 삭제하는 함수
int deleteFirst(headNode* h); //첫번째 노드를 삭제하는 함수
int invertList(headNode* h); //리스트를 역순으로 바꾸는 함수

void printList(headNode* h); //리스트를 출력하는 함수


int main()
{
	char command; //사용자에게 입력받은 메뉴의 값을 저장할 변수
	int key; //사용자가 입력한 값을 저장할 변수
	headNode* headnode = NULL; //헤드노드가 NULL을 가리키게 함

    printf("----------[이하은]     [2019038037]----------\n");

	do { //메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		//사용자에게 입력 받아서 command에 저장
		printf("Command = "); 
		scanf(" %c", &command);

		switch (command) { //command의 값에 따라 코드 실행
		case 'z': case 'Z':
			initialize(&headnode); //리스트를 초기화 하는 함수 호출
			break;
		case 'p': case 'P':
			printList(headnode); //리스트를 출력하는 함수 호출
			break;
		case 'i': case 'I':
			//key값을 받아 노드를 삽입하는 함수 호출
			printf("Your Key = "); 
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			//key값을 받아 key값을 가지고 있는 노드를 삭제하는 함수 호출
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			//key값을 입력 받아 마지막에 추가하는 함수 호출
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			//마지막 노드를 삭제하는 함수 호출
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			//key값을 입력 받아 첫번째에 삽입하는 함수 호출
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			//첫번째 노드를 삭제하는 함수 호출
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			//리스트를 역순으로 바꾸는 함수 호출
			invertList(headnode);
			break;
		case 'q': case 'Q':
			//리스트의 메모리를 해제시키는 함수 호출
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) //리스트를 초기화 하는 함수
{
	if (*h != NULL) //headNode가 다른 노드를 가리키고 있을 때 그 리스트를 해제시킴
		freeList(*h);

	(*h) = (headNode*)malloc(sizeof(headNode)); //h가 가리키고 있는 값을 변경(headNode만든 후 값 저장)
	(*h)->first = NULL; //headNode가 가리키는 값을 NULL로 초기화

	return 1;
}

int freeList(headNode* h) { //리스트를 해제시키는 함수
	if (h == NULL) //headnode가 NULL을 가리키고 있으면 끝냄
		return 0;

	listNode* pev; //메모리를 해제할 주소를 저장할 포인터 변수
	listNode* p = h->first; //해제할 노드의 그 다음 노드를 가리키는 포인터 변수
	while (p != NULL) //p가 NULL이 아닐때까지 반복
	{
		pev = p; //p의 주소를 저장
		p = p->rlink; //p에는 그 다음 노드의 주소를 저장
		free(pev); //pev메모리 해제
	}
	free(h); //headnode의 메모리도 해제

	return 0;
}


void printList(headNode* h) { //리스트를 출력하는 함수
	int i = 0; //노드의 갯수를 세기 위한 변수
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) { //노드가 없을 때
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //head노드가 가리키는 값을 저장

	while (p != NULL) { //p가 NULL이 아닐때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //노드의 key값 출력
		p = p->rlink; //p가 오른쪽 노드를 가리키게 함 
		i++;
	}

	printf("  items = %d\n", i); //노드의 개수 출력
}




/**
 * list에 key에 대한 노드하나를 마지막에 추가
 */
int insertLast(headNode* h, int key) {

	listNode* temp = h->first; //temp가 첫번째 노드가리키게함
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //새로만든 노드의 key값에 외부에서 받아온 값 저장

	while (temp->rlink != NULL) //temp가 마지막 노드일때까지 반복
	{
		temp = temp->rlink; //temp가 오른쪽 노드 가리키게 함
	}
	temp->rlink = node; //temp의 오른쪽이 node가리키게 함
	node->llink = temp; //node의 왼쪽이 temp가리키게 함
	node->rlink = NULL; //node의 오른쪽이 NULL가리키게 함
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* temp = h->first;//temp가 첫번째 노드를 가리키게 함
	listNode* trail = NULL; //temp이전 노드를 가리키게 할 포인터

	while (temp->rlink != NULL) //temp가 마지막 노드가 아닐때까지 반복
	{
		trail = temp; //trail이 temp가 가리기고 있는 노드를 가리키게 함
		temp = temp->rlink; //tmep가 오른쪽의 노드를 가리키게 함
	}
	trail->rlink = temp->rlink; //trail의 오른쪽이 temp가 가리키고 있던 NULL을 가리키게 함
	free(temp); //마지막 노드를 해제 시킴

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //노드에 key값 저장
	node->llink = NULL; //노드 왼쪽이 NULL가리키게 함

	if (h->first == NULL) //리스트가 비어있다면
	{ 
		h->first = node; //헤드노드가 node가리키게 함
		node->rlink = NULL;//node의 오른쪽이 NULL가리키게 함
	}
	else //리스트가 비어있지 않다면
	{
		listNode* temp = h->first; //temp가 첫번째 node를 가리키게 함
		h->first = node; //헤드노드가 node를 가리키게함
		node->rlink = temp; //node의 오른쪽이 temp가 가리키고 있던 값 가리키게함
		temp->llink = node; //이전의 첫번째 였던 노드의 왼쪽이 node를 가리키게 함
	}

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)//리스트가 비어있으면
	{
		return 0; //끝냄
	}
	//리스트가 비어있지 않으면
	listNode* temp = h->first; //temp가 첫번째 노드를 가리키게 함
	listNode* node = temp; //node가 temp가 가리키는 노드를 가리키게 함
	h->first = temp->rlink; //헤더노드가 temp오른쪽의 노드를 가리키게함
	temp = temp->rlink;//temp가 그 다음 노드를 가리키게함
	temp->llink = NULL; //temp의 왼쪽이 NULL을 가리키게 함

	free(node);//첫번째 노드 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* temp = h->first; //temp가 첫번째 노드를 가리키게 함
	listNode* mid = temp; //mid가 temp가 가리키는 노드를 가리키게 함
	listNode* trail = NULL; //mid전 노드를 가리킬 포인터

	while (temp != NULL) //temp가 NULL이 아닐때까지
	{
		temp = temp->rlink; //temp가 오른쪽 노드를 가리키게 함
		mid->rlink = trail; //mid의 오른쪽이 이전 노드를 가리키게 함
		mid->llink = temp; //mid의 왼쪽이 다음 노드를 가리키게 함
		trail = mid; //trail이 mid가 가리키는 값을 가리키게 함 
		mid = temp; //mid가 temp가 가리키는 값을 가리키게 함
	}
	h->first = trail; //헤더노트가 temp를 가리키게 함(역순으로 배치한 후 첫번째 노드)

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* temp = h->first; //temp가 첫번째 노드를 가리키게 함
	listNode* trail = NULL; //temp 이전의 노드를 가리킬 포인터
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드를 생성
	node->key = key; //key값을 저장

	if (h->first == NULL) //리스트가 비어있을때 첫번째 위치에 노드 삽입
	{
		insertFirst(h, key);
		return 0;
	}
	
	while (temp != NULL) //temp가 NULL이 될때까지 반복
	{
		if (node->key < temp->key) //temp의 key가 node의 key보다 클때
		{
			if (trail == NULL) //node의 key값이 첫번째 노드의 key값보다 작으면 첫번째 위치에 node를 삽입
			{
				insertFirst(h, key);
				return 0;
			}
			node->rlink = temp; //node의 오른쪽이 temp를 가리키게 함
			node->llink = trail; //node의 왼쪽이 trail을 가리키게 함
			trail->rlink = node; //trail의 오른쪽이 node를 가리키게 함
			temp->llink = node; //temp의 왼쪽이 node를 가리키게 함
			return 0;
		}
		trail = temp; //trail이 temp가 가리키고 있던 노드를 가리키게함
		temp = temp->rlink; //tmep가오른쪽의 노드를 가리키게 함
	}

	//node의 key값보다 큰값이 없을 때
	insertLast(h, key); //마지막에 node를 삽입

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* temp = h->first; //삭제할 노드를 저장할 포인터 첫번째 노드를 가리키게함
	listNode* trail = NULL; //삭제할 노드 전노드를 저장할 포인터
	listNode* prev = NULL; //삭제할 노드 다음 노드를 저장할 포인터

	if (h->first == NULL) //리스트가 비어있을 때 그냥 종료
		return 0;

	while (temp != NULL) //temp가 NULL이 될때까지 반복
	{
		if (temp->key == key) //temp의 key값이 사용자가 입력한 값과 같을때
		{
			if (trail == NULL) //삭제할 값이 첫번째 노드의 값이면
			{
				deleteFirst(h); //첫번째 노드 삭제하는 함수 호출 후 종료
				return 0;
			}

			prev = temp->rlink; //temp의 오른쪽의 값을 prev가 가리키게 함
			trail->rlink = prev; //temp이전의 노드의 오른쪽이 prev를 가리키게 함
			prev->llink = trail; //prev의 왼쪽이 tmep이전의 노드를 가리키게 함
			free(temp); //temp의 메모리를 해제 시킴
			return 0;
		}
		trail = temp; //trail이 temp가 가리키던 노드를 가리키게 함
		temp = temp->rlink; //temp가 오른쪽 노드를 가리키게 함
	}
	
	//사용자가 입력한 key값이 리스트에 없을 때 에러 출력
	printf("입력한 값이 없습니다.\n");

	return 1;
}

