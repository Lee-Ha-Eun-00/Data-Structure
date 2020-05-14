/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {  //key값과 오른쪽, 왼쪽 링크를 가지고 있는 노드
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h); //리스트를 초기화 하는 함수
int freeList(listNode* h); //리스트를 해제시키는 함수
int insertLast(listNode* h, int key); //list에 key에 대한 노드하나를 마지막에 추가하는 함수
int deleteLast(listNode* h); //list의 마지막 노드 삭제하는 함수
int insertFirst(listNode* h, int key); //ㅣist 처음에 key에 대한 노드하나를 추가하는 함수
int deleteFirst(listNode* h); //list의 첫번째 노드 삭제하는 함수
int invertList(listNode* h); //리스트의 링크를 역순으로 재배치하는 함수

int insertNode(listNode* h, int key);  // 리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입하는 함수
int deleteNode(listNode* h, int key);  //list에서 key에 대한 노드 삭제하는 함수

void printList(listNode* h);  //리스트를 출력하는 함수



int main()
{
	char command; //사용자에게 입력받은 메뉴의 값을 저장할 변수
	int key; //사용자가 입력한 값을 저장할 변수
	listNode* headnode = NULL; //리스트의 처음을 가리킬 노드

	printf("----------[이하은]     [2019038037]----------\n");

	do { //메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		// 사용자에게 입력 받아서 command에 저장
		printf("Command = ");
		scanf(" %c", &command);

		switch (command) { //command의 값에 따라 코드 실행
		case 'z': case 'Z':
			initialize(&headnode);  //리스트를 초기화 하는 함수 호출
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


int initialize(listNode** h) { //리스트를 초기화 하는 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {

	if (h == NULL) {  //노드가 없을 때 
		printf("Nothing to free....\n");
		return 0;
	}

	if ((h->rlink == h) && (h->llink == h))//headnode의 오른쪽 왼쪽이 자기 자신을 가리키면 headnode 메모리 해제하고 끝냄
	{
		free(h);
		return 0;
	}

	listNode* pev; //메모리를 해제할 주소를 저장할 포인터 변수
	listNode* p = h->rlink; //해제할 노드의 그 다음 노드를 가리키는 포인터 변수
	while (p != h) //p가 headnode를 가리키기 전까지 반복
	{
		pev = p; //p의 주소를 저장
		p = p->rlink; //p에는 그 다음 노드의 주소를 저장
		free(pev); //pev메모리 해제
	}
	free(h); //headnode의 메모리도 해제

	return 0;
}



void printList(listNode* h) { //리스트를 출력하는 함수
	int i = 0; //노드의 갯수를 세기 위한 변수
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {  //노드가 없을 때 
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //head노드가 가리키는 값을 저장

	while (p != NULL && p != h) { //p가 NULL이 아니거나 헤더노드를 가리키고 있지 않을때반복
		printf("[ [%d]=%d ] ", i, p->key);  //노드의 key값 출력
		p = p->rlink; //p가 오른쪽 노드를 가리키게 함 
		i++;
	}
	printf("  items = %d\n", i); //노드의 개수 출력

	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0; //i초기화
	p = h->rlink; //head노드가 가리키는 값을 저장
	while (p != NULL && p != h) { //p가 NULL이 아니거나 헤더노드를 가리키고 있지 않을때반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //key값과 link가 가리키는 주소, rlink가 가리키는 주소 출력
		p = p->rlink;  //p가 오른쪽 노드를 가리키게 함 
		i++;
	}
}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) //headnode가 아직 초기화 되지 않았다면 종료
	{
		printf("Initialize first!\n");
		return 0;
	}

	if (h->rlink == h) //리스트가 비어 있다면 첫번째에 노드추가
	{
		insertFirst(h, key);
		return 0;
	}
	
	//초기화되고 리스트가 비어있지 않은 경우
	listNode* p = h->llink; //head가 가리키는 마지막노드를 가리키게 함
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //새로만든 노드의 key값에 외부에서 받아온 값 저장

	
	//마지막에 노드 삽입
	p->rlink = node; //마지막 노드의 오른쪽이 node를 가리키게 함
	node->llink = p; //node의 왼쪽이 마지막 노드를 가리키게 함
	node->rlink = h; //node의 외른쪽이 head를 가리키게함
	h->llink = node; //head의 왼쪽이 node를 가리키게 함

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if ((h == NULL)||(h->rlink == h)) //headnode가 아직 초기화 되지 않았거나 리스트가 비어있다면 종료
	{
		printf("There is nothing to delete!\n");
		return 0;
	}

	listNode* p = h->llink; //head가 가리키는 마지막노드를 가리키게 함
	listNode* trail = p->llink; //trail이 마지막 이전 노드를 가리키게 함

	trail->rlink = p->rlink; //마지막 이전 노드의 오른쪽이 마지막 노드가 가리키던 오른쪽을 가리키게 함
	h->llink = trail; //head노드의 왼쪽이 trail을 가리키게 함
	free (p); //삭제한 노드의 메모리 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	if (h == NULL) //headnode가 아직 초기화 되지 않았다면 종료
	{
		printf("Initialize first!\n");
		return 0;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //새로만든 노드의 key값에 외부에서 받아온 값 저장

	if (h->rlink == h) //비어있는 리스트에 첫번째 값 삽입
	{
		h->rlink = node; //head의 오른쪽이 node가리킴
		h->llink = node;  //head의 왼쪽이 node가리킴
		node->llink = h; //node의 왼쪽이 head가리킴
		node->rlink = h; //node의 오른쪽이 head가리킴
		return 0;
	}
	
	else 
	{
		listNode* next = h->rlink; //첫번째 노드를 가리킬 포인터
		h->rlink = node; //head의 오른쪽이 node가리킴
		node->llink = h; //node의 왼쪽이 head가리킴
		node->rlink = next;  //node의 오른쪽이 next가리킴
		next->llink = node; //next의 왼쪽이 node가리킴
	}

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if ((h == NULL) || (h->rlink == h)) //headnode가 아직 초기화 되지 않았거나 리스트가 비어있다면 종료
	{
		printf("There is nothing to delete!\n");
		return 0;
	}

	listNode* p = h->rlink; //head가 가리키는 첫번째 노드를 가리키게 함
	listNode* next = p->rlink; //첫번째 노드의 오른쪽 노드를 가리킬 포인터
	h->rlink = next; //head의 오른쪽이 next를 가리키게 함
	next->llink = h; //next의 왼쪽이 head를 가리키게 함

	free(p); //삭제한 노드 메모리 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	if ((h == NULL) || (h->rlink == h)) //headnode가 아직 초기화 되지 않았거나 리스트가 비어있다면 종료
	{
		printf("There is nothing to inverse!\n");
		return 0;
	}
	
	listNode* temp = h->rlink; //temp가 첫번째 노드를 가리키게 함
	listNode* mid = temp; //mid가 temp가 가리키는 노드를 가리키게 함
	listNode* trail = h; //mid전 노드를 가리킬 포인터


	h->rlink = h->llink; //head의 오른쪽이 맨 마지막 노드를 가리키게 함
	h->llink = temp; //head의 왼쪽이 첫번째 노드를 가리키게 함

	while (temp != h) //temp가 head를 가리키기 전까지 반복
	{
		temp = temp->rlink; //temp가 오른쪽 노드 가리키게 함
		mid->llink = temp; //mid의 왼쪽이 temp가 가리키는 노드 가리키게 함
		mid->rlink = trail; //mid의 오른쪽이 trail이 가리키는 노드 가리키게 함
		
		trail = mid; //trail이 mid가 가리키는 노드 가리키게 함
		mid = temp; //mid가 temp가 가리키는 노드 가리키게 함
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if (h == NULL) //headnode가 아직 초기화 되지 않았다면 종료
	{
		printf("Initialize first!\n");
		return 0;
	}

	listNode* p = h->rlink; //head가 가리키는 첫번째 노드를 가리키게 함
	listNode* trail = p->llink; //trail이 p이전 노드를 가리키게 함

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //새로만든 노드의 key값에 외부에서 받아온 값 저장
	
	if (p == h) //리스트가 비어있으면 첫번째에 노드 삽입하고 종료
	{
		insertFirst(h, key);
		return 0;
	}

	while (p != h) //p가 headnode이기 전까지 반복
	{

		if (key <= (p->key)) //key보다 큰값이 나오는 노드 앞에 node삽입
		{
			if (trail == h) //노드를 첫번째에 삽입해야 하는 경우
			{
				insertFirst(h, key);
				return 0;
			}
			node->llink = trail; //node의 왼쪽이 trail을 가리키게 함
			trail->rlink = node; //trail의 오른쪽이 node를 가리키게 함
			node->rlink = p; //node의 오른쪽이 p를 가리키게 함
			p->llink = node; //p의 왼쪽이 node를 가리키게 함
			return 0;
		}
		
		//trail과 p가 각각 오른쪽 노드를 가리키게 함
		trail = p;
		p = p->rlink;
	}
	//삽입해야 하는 key값이 가장 클때 가장 마지막에 삽입
	insertLast(h, key);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if ((h == NULL) || (h->rlink == h)) //headnode가 아직 초기화 되지 않았거나 리스트가 비어있다면 종료
	{
		printf("There is nothing to delete!\n");
		return 0;
	}

	listNode* p = h->rlink; //head가 가리키는 첫번째 노드를 가리키게 함
	listNode* trail = p->llink; //trail이 p이전 노드를 가리키게 함
	listNode* next = p->rlink; //삭제할 노드의 오른쪽 노드를 가리킬 포인터

	while (p != h) //p가 headnode이기 전까지 반복
	{

		if (key == (p->key)) //입력한 key값이 p가 가리키는 key값과 같을 때
		{
			if (trail == h) //삭제해야 하는 노드가 첫번째 노드일 경우
			{
				deleteFirst(h);
				return 0;
			}

			//해당 노드 삭제
			trail->rlink = p->rlink; //이전 노드의 오른쪽이 그 다음 노드 가리키게 함
			next->llink = trail; //삭제할 다음노드의 왼쪽이 삭제할 노드 이전노드를 가리키게 함
			free(p); //삭제할 노드 메모리 해제
			return 0;
		}
		//trail과 p가 각각 오른쪽 노드를 가리키게 함
		trail = p;
		p = p->rlink;
		next = p->rlink;
	}
	
	//입력한 값이 리스트에 없을 때
	printf("The value does not exist!\n");

	return 0;
}