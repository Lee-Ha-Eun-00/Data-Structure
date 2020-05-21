#include <stdio.h>
#include <stdlib.h>

typedef struct node { //트리의 노드 key값과 왼쪽자식을 가리킬 포인터, 오른쪽 자식을 가리킬 포인터로 구성
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; //사용자에게 입력받은 메뉴를 저장할 변수
	int key; //사용자에게 받은 노드의 값을 저장할 변수
	Node* head = NULL; //root를 가리킬 노드
	Node* ptr = NULL;	/* temp */

	printf("----------[이하은]     [2019038037]----------\n");

	do { //메뉴출력
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); 
			insert(head, key); //노드를 추가하는 함수
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key); //key값을 가지는 leaf노드를 삭제하는 함수
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); //반복적탐색으로 노드를 탐색하는 함수
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); //재귀적으로 노드를 탐색하는 함수
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			if (head != NULL)
			{
				inorderTraversal(head->left); //중위순회하는 함수
			}
			else
				printf("initialize first!\n");
			
			break;
		case 'p': case 'P':
			if (head != NULL)
			{
				preorderTraversal(head->left); //전위순회하는 함수
			}
			else
				printf("initialize first!\n");
			
			break;
		case 't': case 'T':
			if (head != NULL)
			{
				postorderTraversal(head->left); //후위순회하는 함수
			}
			else
				printf("initialize first!\n");
			
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
	return 1;
}

void inorderTraversal(Node* ptr) //중위순회를 위한 재귀함수
{
	if (ptr) //root가 NULL이 아니면
	{
		inorderTraversal(ptr->left); //왼쪽 자식노드를 인자로 하는 inorder Traversal 함수 호출
		printf("[%d]  ", ptr->key); //노드의 값 출력
		inorderTraversal(ptr->right); //오른쪽 자식노드를 인자로 하는 inorder Traversal 함수 호출
	}
}

void preorderTraversal(Node* ptr) //전위 순회를 위한 재귀함수
{
	if (ptr)
	{
		printf("[%d]  ", ptr->key); //노드의 값 출력
		preorderTraversal(ptr->left); //왼쪽 자식노드를 인자로 하는 preorder Traversal 함수 호출
		preorderTraversal(ptr->right); //오른쪽 자식노드를 인자로 하는 preorder Traversal 함수 호출
	}
}

void postorderTraversal(Node* ptr) //후위 순회를 위한 재귀함수
{
	if (ptr)
	{
		postorderTraversal(ptr->left); //왼쪽 자식노드를 인자로 하는 postorder Traversal 함수 호출
		postorderTraversal(ptr->right); //오른쪽 자식노드를 인자로 하는 postorder Traversal 함수 호출
		printf("[%d]  ", ptr->key); //노드의 값 출력
	}
}

int insert(Node* head, int key) //노드를 추가하는 함수
{
	Node* node = (Node*)malloc(sizeof(Node)); //새로 추가할 노드 생성
	node->key = key; //노드에 key값 저장
	node->left = NULL; //노드 왼쪽 자식에 NULL을 저장
	node->right = NULL; //노드 오른쪽 자식에 NULL을 저장

	if (head == NULL) //tree가 initialize되어 있지 않으면 예외처리
	{
		printf("initialize first!\n");
		return 0;
	}


	Node* temp = head->left;//노드를 추가할 위치를 가리킬 포인터
	Node* pre=NULL ;//노드를 추가할 위치의 이전 노드를 가리킬 포인터
	while (temp != NULL) //temp가 NULL이 아닐때까지 반복
	{
		pre = temp; //pre가 temp를 가리키게 함
		if (temp->key == key) //temp의 key값과 key값이 같으면 중지
			return 0;
		if (temp->key > key) //key값이 노드의 값보다 작으면
			temp = temp->left; //temp가 왼쪽 자식노드를 가리키게 함
		else //key값이 노드의 값보다 크면
			temp = temp->right; //temp가 오른쪽 자식노드를 가리키게 함
	}
	if (pre == NULL)
	{
		head->left = node;
		return 0;
	}
	if (node->key < pre->key) //마지막 노드보다 작으면
		pre->left = node; //왼쪽에 삽입
	else //마지막 노드보다 크면
		pre -> right = node; //오른쪽에 삽입

	return 1;
}

int deleteLeafNode(Node* head, int key) //key값을 가지는 leaf노드를 삭제하는 함수
{
	if (head == NULL) //Tree가 생성되지 않았을때 예외처리
	{
		printf("initialize first!\n");
		return 0;
	}
	Node* temp = head->left;//삭제할 노드를 가리킬 포인터
	Node* pre = head;//삭제할 노드 이전 노드를 가리킬 포인터
	if (temp == NULL) //Tree가 비어있을 때
	{
		printf("Tree is empty!\n");
		return 0;
	}
	while (temp != NULL) //temp가 NULL이 아닐때 까지
	{
		if (temp->key == key) //temp의 key와 key가 동일할때
		{
			if ((temp->left != NULL) || (temp->right != NULL)) //temp가 leaf노드가 아니면 종료
			{
				printf("the node [%d] is not a leaf.\n", key);
				return 0;
			}
			if (pre == head) //삭제할 노드가 첫번째이면 head가 NULL가리키게 함
			{
				free(temp);
				pre->left = NULL;
				return 0;
			}
			if (pre->key > key) //temp가 이전노드보다 작으면 이전노드의 왼쪽을 NULL로 바꿈
			{
				free(temp);
				pre->left = NULL;
				return 0;
			}
			//temp가 이전노드보다 크면 이전노드의 오른쪽을 NULL로 바꿈
			free(temp);
			pre->right = NULL; 
			return 0;
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

Node* searchRecursive(Node* ptr, int key) //재귀적으로 노드를 탐색하는 함수
{
	if (ptr == NULL) //head가 NULL이면 key값이 tree에 존재하지 않으므로 NULL 반환
		return NULL;
	if (ptr->key == key) //key값을 가지고 있는 노드의 위치 반환
		return ptr;
	if (key < ptr->key) //현재 노드의 key값보다 key값이 작으면 왼쪽자식을 인자로 주는 함수 호출
		return searchRecursive(ptr->left, key);
	else//현재 노드의 key값보다 key값이 크면 오른쪽 자식을 인자로 주는 함수 호출
		return searchRecursive(ptr->right, key);


}

Node* searchIterative(Node* head, int key)  //반복적탐색으로 노드를 탐색하는 함수
{
	if (head == NULL) //Tree가 생성되지 않았을 때 NULL 반환
	{
		return NULL;
	}
	Node* temp = head->left;//탐색할 노드를 가리킬 포인터
	if (temp == NULL) //Tree가 비어있을 때 NULL반환
	{
		return NULL;
	}
	while (temp != NULL) //temp가 NULL이 아닐때까지
	{
		if (temp->key == key) //temp의 key와 key가 동일할 때
			return temp; //temp의 주소반환
		else if (temp->key > key) //temp의 key가 key보다 클 때
			temp = temp->left; //temp가 왼쪽 자식을 가리키게 함
		else //temp의 key가 key보다 작을 때
			temp = temp->right; //temp가 오른쪽 자식을 가리키게 함
	}
	//검색한key가 없을 때 NULL반환
	return temp;
}


int freeBST(Node* head) //Tree의 메모리를 해제하는 함수
{
	if (head != NULL) //head가 NULL아 아닐때
	{
		freeBST(head->left); //왼쪽자식을 인자로 하는 함수 호출
		if(head->right != head) //head가 자기자신을 가리키지 않을때만
			freeBST(head->right); //오른쪽 자식을 인자로 하는 함수 호출
	}
	free(head); //head의 메모리 해제
    return 0;
}