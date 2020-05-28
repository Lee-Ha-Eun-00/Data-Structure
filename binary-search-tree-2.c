/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node { //트리의 노드 key값과 왼쪽자식을 가리킬 포인터, 오른쪽 자식을 가리킬 포인터로 구성
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE	20
Node * stack[MAX_STACK_SIZE]; //node를 가리키는 포인터배열
int top = -1; //스택의 top

Node* pop(); //스택에서 삭제하는 함수
void push(Node* aNode); //스택에 삽입하는 함수

/* for queue */
#define MAX_QUEUE_SIZE	20
Node * queue[MAX_QUEUE_SIZE]; //node를 가리키는 포인터배열
int front = -1; //처음을 가리키는 변수
int rear = -1; //맨끝을 가리키는 변수

Node* deQueue(); //큐에서 삭제하는 함수
void enQueue(Node* aNode); //큐에 삽입하는 함수


int initializeBST(Node** h); //트리를 초기화하는 함수

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */


int main()
{
	char command; //사용자에게 입력받은 메뉴를 저장할 변수
	int key; //사용자에게 받은 노드의 값을 저장할 변수
	Node* head = NULL; //root를 가리킬 노드

	printf("----------[이하은]     [2019038037]----------\n");

	do {  //메뉴출력
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialitze BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) { //command의 값에 따라 코드 실행
		case 'z': case 'Z':
			initializeBST(&head); //트리를 초기화 하는 함수
			break;
		case 'q': case 'Q':
			freeBST(head); //트리의 메모리를 해제하는 함수
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); //노드를 추가하는 함수
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key); //입력한 key값을 갖는 노드를 삭제하는 함수
			break;

		case 'r': case 'R':
			recursiveInorder(head->left); //재귀적으로 중위순회하는 함수
			break;
		case 't': case 'T':
			iterativeInorder(head->left); //반복적으로 중위순회하는 함수
			break;

		case 'l': case 'L':
			levelOrder(head->left); //레벨순서 순회하는 함수
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q'); //q 또는 Q가 입력될때까지 반복

	return 1;
}

int initializeBST(Node** h) { //트리를 초기화 하는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}

void recursiveInorder(Node* ptr) //재귀적으로 중위순회하는 함수
{
	if (ptr) { //root가 NULL이 아니면
		recursiveInorder(ptr->left); //왼쪽 자식노드를 인자로 하는 inorder Traversal 함수 호출
		printf(" [%d] ", ptr->key);  //노드의 값 출력
		recursiveInorder(ptr->right); //오른쪽 자식노드를 인자로 하는 inorder Traversal 함수 호출
	} 
}

void iterativeInorder(Node* node) //반복적으로 중위순회하는 함수
{
	for (;;)
	{
		for (; node; node = node->left)
		{
			push(node); //스택에 삽입
		}
		node = pop(); //스택에서 삭제
		if (!node) break; //node가 NULL이면 반복분 탈출
		printf(" [%d] ", node->key); //key값 출력
		node = node->right; //노드가 오른쪽 노드 가리키게 함
	}
}

void levelOrder(Node* ptr) //레벨순서 순회하는 함수
{
	if (!ptr) return; //트리가 비어 있을때

	enQueue(ptr);//root노드 큐에 삽입
	for (;;)
	{
		ptr = deQueue(); //노드 큐에서 삭제
		if (ptr) //ptr이 NULL이 아니면
		{
			printf(" [%d] ", ptr->key); //key값 출력
			if (ptr->left) //ptr의 왼쪽자식이 NULL이 아니면
				enQueue(ptr->left); //큐 삽입
			if (ptr->right) //ptr의 오른쪽자식이 NULL이 아니면
				enQueue(ptr->right); //큐 삽입
		}
		else //ptr이 NULL이면 반복 종료
			break;
	}

}


int insert(Node* head, int key) //노드를 추가하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) { //트리가 비어 있으면
		head->left = newNode; //root가 newNode가리키게 함
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key) //입력한 key값을 갖는 노드를 삭제하는 함수
{
	if (head == NULL) //Tree가 생성되지 않았을때 예외처리
	{
		printf("initialize first!\n");
		return 0;
	}

	Node* temp = head->left;//삭제할 노드를 가리킬 포인터
	Node* pre = head;//삭제할 노드 이전 노드를 가리킬 포인터
	Node* leaf=NULL;//삭제할 노드의 오른쪽 서브트리에서 가장 작은 원소 가리킬 포인터
	Node* pre_leaf=NULL;//삭제할 노드 이전 노드를 가리킬 포인터(삭제할 노드가 leaf노드일때)

	if (temp == NULL) //Tree가 비어있을 때
	{
		printf("Tree is empty!\n");
		return 0;
	}

	while (temp != NULL)
	{
		if (temp->key == key) //key값이 일치할때
		{
			if ((temp->left == NULL) && (temp->right == NULL)) //삭제할 노드가 leaf노드 일때
			{
				if (pre->key > temp->key)//temp가 pre의 왼쪽 노드라면
				{
					pre->left = NULL; //pre의 왼쪽 자식 노드를 NULL로 바꿈
					free(temp);//temp의 메모리 해제
					return 1;
				}
				pre->right = NULL; //pre의 오른쪽 자식 노드를 NULL로 바꿈
				free(temp);//temp의 메모리 해제
				return 1;
			}
			else if ((temp->left != NULL) && (temp->right == NULL)) //삭제할 노드의 왼쪽 서브트리만 있는 경우
			{
				if (pre->key > temp->key) //삭제할 노드가 이전 노드의 왼쪽 노드이면
				{
					pre->left = temp->left; //temp의 왼쪽 자식이 이전 노드의 왼쪽 자식이 되게 함
					free(temp); //temp 메모리 해제
					return 1;
				}
				//삭제할 노드가 이전 노드의 오른쪽 노드이면
				pre->right = temp->left; //temp의 왼쪽 자식이 이전 노드의 오른쪽 자식이 되게 함
				free(temp); //temp 메모리 해제
				return 1;		
			}

			//오른쪽 서브트리의 가장 작은 값을 올리기
			leaf = temp->right; //leaf가 temp가 가리키는 노드의 오른쪽 자식 노드 가리키게 함
			pre_leaf = temp;//leaf이전 노드 가리키는 포인터가 temp가리키게 함
			while(leaf->left!=NULL) //leaf노드보다 작은 노드가 없을 때까지 반복
			{
				pre_leaf = leaf;//leaf가 가리키는 노드 가리킴
				leaf = leaf->left;//leaf가 왼쪽 자식 노드 가리킴
			}
			if (leaf->right != NULL) //leaf의 오른쪽 자식 노드가 NULL이 아니면
			{
				if (pre_leaf == temp) //leaf가 temp의 오른쪽 자식이면
				{
					temp->key = leaf->key; //temp의 key값을 바꿈
					pre_leaf->right = leaf->right; //tmep의 오른쪽 자식 노드가 leaf의 오른쪽 자식노드 가리키게 함
					free(leaf);//leaf의 메모리 해제
					return 1;
				}
				temp->key = leaf->key; //leaf의 key값을 temp에 넣음
				pre_leaf->left = leaf->right; //leaf이전 노드의 왼쪽이 leaf의 오른쪽 자식 노드 가리키게 함
				free(leaf); //leaf의 메모리 해제
				return 1;
			}
			//leaf의 오른쪽 자식 노드가 비어 있으면
			temp->key = leaf->key; //leaf의 key값을 temp에 넣음
			free(leaf); //leaf의 메모리 해제
			if (pre_leaf == temp) //leaf가 temp의 오른쪽 자식이면
			{
				pre_leaf->right = NULL; //pre_leaf의 오른쪽 자식 노드가 NULL이 되게 함
				return 1;
			}
			pre_leaf->left = NULL;//pre_leaf의 왼쪽 자식 노드가 NULL이 되게 함
			return 1;
		}

		else if (temp->key > key) //key값이 temp의 key값보다 작으면
		{
			pre = temp; //pre가 temp를 가리키게 함
			temp = temp->left; //temp가 왼쪽 자식노드를 가리키게 함
		}
		else //key값이 temp의 key값보다 크면
		{
			pre = temp; //pre가 temp를 가리키게 함
			temp = temp->right; //temp가 오른쪽 자식노드를 가리키게 함
		}
	}
	//key값이 tree에 존재하지 않을 때
	printf("the node [%d] is not a leaf.\n", key);
	return 0;
}


void freeNode(Node* ptr) //노드의 메모리를 해제하는 함수
{
	if (ptr) {
		freeNode(ptr->left); //왼쪽 자식 노드의 메모리 해제
		freeNode(ptr->right); //오른쪽 자식 노드의 메모리 해제
		free(ptr); //노드의 메모리 해제
	}
}

int freeBST(Node* head) //트리의 메모리를 해제하는 함수
{

	if (head->left == head) //트리가 비어있으면
	{
		free(head); //head 해제하고 종료
		return 1;
	}

	Node* p = head->left; //p가 root가리키게 함

	freeNode(p); //노드들 해제하는 함수 호출

	free(head); //head의 메모리 해제
	return 1;
}

Node* pop() //스택에서 삭제하는 함수
{
	if (top == -1) //스택에 비어 있으면
	{
		return NULL; //NULL반환
	}
	
	return stack[top--]; //현재 top이 가리키고 있는 곳의 데이터 반환 후 top의 값 1감소
}

void push(Node* aNode) //스택에 삽입하는 함수
{
	if (top == (MAX_STACK_SIZE - 1)) //스택이 꽉차 있을 때
	{
		printf("stack is full!\n"); //에러 메세지 출력하고 종료
		return;
	}

	top++; //top의 위치를 바꿈
	stack[top] = aNode; //스택에 노드의 주소 저장
}

Node* deQueue() //큐에서 삭제하는 함수
{
	if (front == rear) //queue가 비어있을때 NULL반환
	{
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //queue삭제할 위치를 front에 저장
	return queue[front];//queue에 저장된 값 리턴
}

void enQueue(Node* aNode) //큐에 삽입하는 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //queue에 저장할 위치를 rear에 저장 
	if (((rear == MAX_QUEUE_SIZE - 1) && (front == -1)) || (rear == front)) //queue가 꽉차있을 때
	{
		printf("queue is full!\n");//에러 메세지 출력 후 종료
		return;
	}
	
	queue[rear] = aNode; //queue에 주소 저장
}