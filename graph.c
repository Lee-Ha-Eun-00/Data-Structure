#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20 

typedef struct Vertex {
	int num; /* vertex number */
	struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;

typedef struct VertexHead {
	Vertex* head; /* linked list of all adjacent vertices */
} VertexHead;

typedef struct Graph {
	VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;

int arr[MAX_VERTEX] = { 0 }; //그래프의 Vertex가 활성화 되었는지 확인하기 위한 배열

int createGraph(Graph** g, int n); /* empty graph creation */
int destroyGraph(Graph** g, int n); /* deallocating all allocated memory */
int insertVertex(Graph* g, int ver); /* vertex insertion */
int deleteVertex(Graph* g, int ver); /* vertex deletion */
int insertEdge(Graph* g, int ver1, int ver2); /* new edge creation between two vertices */
int deleteEdge(Graph* g, int ver1, int ver2); /* edge removal */
int depthFS(Graph* g, int key); /* depth firt search using stack */
int breadthFS(Graph* g, int key); /* breadth first search using queue */
int printGraph(Graph* g); /* printing graph with vertices and edges */
int freeList(Vertex* v); //인접 노드들의 메모리를 해제하는 함수
int visited[MAX_VERTEX] = { 0 }; //깊이 우선탐색, 너비우선 탐색, pintGraph에서 사용할 방문확인 배열

//stack을 위한 자료
int stack[MAX_VERTEX] = { 0 }; //깊이 우선 탐색에서 사용할 스택
int top = -1;
void push(int key);
int pop();

//queue를 위한 자료
int element[MAX_VERTEX]; //너비 우선 탐색에서 사용할 큐
int front = -1;
int rear = -1;
void addq(int val);
int deleteq();




int main()
{
	char command; //사용자에게 입력받은 메뉴의 값을 저장할 변수
	int key, key2; //사용자가 입력한 값을 저장할 변수
	Graph* Graph = NULL; //Graph가 NULL을 가리키게 함

	do
	{
		//메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" createGraph   = z           printGraph    = p \n");
		printf(" insertVertex  = i           deleteVertex  = d \n");
		printf(" insertEdge    = n           deleteEdge    = e\n");
		printf(" depthFS       = f           breadthFS     = t\n");
		printf(" Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		//사용자에게 입력 받아서 command에 저장
		printf("Command = ");
		scanf(" %c", &command);

		switch (command) { //command의 값에 따라 코드 실행
		case 'z': case 'Z':
			createGraph(&Graph, MAX_VERTEX); //그래프를 초기화 하는 함수 호출
			break;
		case 'p': case 'P':
			printGraph(Graph); //그래프를 출력하는 함수 호출
			break;
		case 'i': case 'I':
			//key값을 받아 vertext삽입
			printf("Your Key (0~19) = ");
			scanf("%d", &key);
			insertVertex(Graph, key);
			break;
		case 'd': case 'D':
			//key값을 받아 vertext삭제
			printf("Your Key (0~19) = ");
			scanf("%d", &key);
			deleteVertex(Graph, key);
			break;
		case 'n': case 'N':
			//key값을 받아 edge를 추가
			printf("Your Key1 (0~19) = ");
			scanf("%d", &key);
			printf("Your Key2 (0~19) = ");
			scanf("%d", &key2);
			insertEdge(Graph, key, key2);
			break;
		case 'e': case 'E':
			//key값을 받아 edge를 삭제
			printf("Your Key1 (0~19) = ");
			scanf("%d", &key);
			printf("Your Key2 (0~19) = ");
			scanf("%d", &key2);
			deleteEdge(Graph, key, key2);
			break;
		case 'f': case 'F':
			//key값을 입력 받고 깊이 우선탐색
			printf("Your Key = ");
			scanf("%d", &key);
			depthFS(Graph, key);
			break;
		case 't': case 'T':
			//key값을 입력 받고 너비 우선탐색
			printf("Your Key = ");
			scanf("%d", &key);
			breadthFS(Graph, key);
			break;
		case 'q': case 'Q':
			//그래프의 메모리를 해제시키는 함수 호출
			destroyGraph(&Graph, MAX_VERTEX);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int createGraph(Graph** g, int n) /* empty graph creation */
{
	//그래프가 비어있지 않으면 메모리해제
	if (*g != NULL) 
	{
		destroyGraph(g, n);
	}

	(*g) = (Graph*)malloc(sizeof(Graph)); //Grapg동적 메모리 할당
	(*g)->vlist = (VertexHead*)malloc(n * sizeof(VertexHead)); //vlist에 MAX_VERTEX크기 만큼의 동적 메모리 할당을 한다.
	
	//VertexHead의 값 NULL로 초기화
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		(((*g)->vlist) + i)->head = NULL;
	}

	return 1;
}

int destroyGraph(Graph** g, int n)  /* deallocating all allocated memory */
{
	//그래프가 아직 만들어지지 않았을 경우 에러 메세지 출력 후 종료
	if ((*g) == NULL)
	{
		printf("createGraqh first!\n");
		return 0;
	}

	//각각의 VertexHead가 가리키고 있는 인접 리스트를 메모리 해제 후 VertexHead의 메모리도 해제
	for (int i = 0; i < n; i++)
	{
		if (((((*g)->vlist) + i)->head) != NULL) //인접노드가 있을 때
		{
			freeList(((((*g)->vlist) + i)->head));
		}
		free((((*g)->vlist) + i)); //VertexHead 메모리 해제
	}

	//그래프의 메모리 해제후 NULL가리키게함
	free(*g);
	*g = NULL;

	return 1;
}

int insertVertex(Graph* g, int ver)/* vertex insertion */
{
	//그래프가 아직 만들어지지 않았을 경우 에러 메세지 출력 후 종료
	if (g == NULL)
	{
		printf("createGraqh first!\n");
		return 0;
	}

	/*올바른 vertex의 값을 입력했는지 확인 후 올바른 값을 입력할 때까지 key값을 받음
	  값을 입력 받은 후 vertex가 존재함을 arr배열을 통해 체크
	  인접리스트의 head
	*/
	if (ver > 19 || ver < 0)
	{
		while (ver < 20 && ver >= 0)
		{
			printf("Please enter a valid value.\n");
			printf("Your Key (0~19) = ");
			scanf("%d", ver);
		}
	}
	arr[ver] = 1;

	return 1;
}

int deleteVertex(Graph* g, int ver) /* vertex deletion */
{
	Vertex* temp;
	Vertex* trail;

	//그래프가 아직 만들어지지 않았을 경우 에러 메세지 출력 후 종료
	if (g == NULL)
	{
		printf("createGraqh first!\n");
		return 0;
	}

	//올바른 범위의 vertex의 값을 입력했는지 확인 후 올바른 값을 입력할 때까지 key값을 받음
	if (ver > 19 || ver < 0)
	{
		while (ver < 20 && ver >= 0)
		{
			printf("Please enter a valid value.\n");
			printf("Your Key (0~19) = ");
			scanf("%d", ver);
		}
	}

	//존재하는 vertex의 값을 입력했는지 확인후 그렇지 않으면 에러 메세지 출력 후 종료
	if (arr[ver] == 0)
	{
		printf("[ %d ]vertex does not exist\n", ver);
		return 0;
	}

	/*
		ver를 인접 노드로 가지로 있는 리스트에서 ver제거후 사용자가 입력한 vertex 삭제 
	*/
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		temp = ((g->vlist) + i)->head;
		trail = temp;
		while (temp != NULL)
		{
			if (temp->num == ver)
			{
				trail = temp->link;
				free(temp);
			}
			else
			{
				temp = temp->link;
				trail = temp;
			}
		}
	}
	//ver 삭제(메모리 해제, arr의 해당 인덱스값 0으로바꿈)
	freeList(((g->vlist) + ver)->head);
	((g->vlist) + ver)->head = NULL;
	arr[ver] = 0;
	return 1;
}

int insertEdge(Graph* g, int ver1, int ver2) /* new edge creation between two vertices */
{
	Vertex* temp; //추가할 vertex를 가리킬포인터
	Vertex* trail=NULL; //추가할 위치 이전의 vertex를 가리킬 포인터
	VertexHead* first;

	//그래프가 아직 만들어지지 않았을 경우 에러 메세지 출력 후 종료
	if (g == NULL)
	{
		printf("createGraqh first!\n");
		return 0;
	}

	//입력한 첫번 째 값이 범위에 맞는지 확인후 알맞은 값 입력하게함
	if (ver1 > 19 || ver1 < 0)
	{
		while (ver1 < 20 && ver1 >= 0)
		{
			printf("Please enter a valid value.\n");
			printf("Your Key1 (0~19) = ");
			scanf("%d", ver1);
		}
	}

	//입력한 두번 째 값이 범위에 맞는지 확인후 알맞은 값 입력하게함
	if (ver2 > 19 || ver2 < 0)
	{
		while (ver2 < 20 && ver2 >= 0)
		{
			printf("Please enter a valid value.\n");
			printf("Your Key2 (0~19) = ");
			scanf("%d", ver2);
		}
	}

	//입력한 값들이 존재하는 값인지 확인
	if ((arr[ver1] == 0) || (arr[ver2] == 0))
	{
		printf("vertex does not exist\n");
		return 0;
	}


	//ver1의 리스트에 ver2의 값 추가
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	first = (g->vlist) + ver1;
	temp = ((g->vlist) + ver1)->head;
	if (temp == NULL) //리스트가 비어있을때
	{
		vertex->num = ver2;
		vertex->link = NULL;
		first->head = vertex;
	}
	else
	{
		while (temp != NULL) 
		{
			trail = temp;
			temp = temp->link;
		}
		vertex->num = ver2;
		vertex->link = NULL;
		trail->link = vertex;
	}


	//ver2의 리스트에 ver1의 값 추가
	first = (g->vlist) + ver2;
	temp = ((g->vlist) + ver2)->head;
	if (temp == NULL) //리스트가 비어있을 때
	{
		vertex->num = ver1;
		vertex->link = NULL;
		first->head = vertex;
	}
	else
	{
		while (temp != NULL)
		{
			trail = temp;
			temp = temp->link;
		}
		vertex->num = ver1;
		vertex->link = NULL;
		trail->link = vertex;
	}

	return 1;
}

int deleteEdge(Graph* g, int ver1, int ver2) /* edge removal */
{
	Vertex* temp = NULL;
	Vertex* trail;
	VertexHead* first;

	//그래프가 아직 만들어지지 않았을 경우 에러 메세지 출력 후 종료
	if (g == NULL)
	{
		printf("createGraqh first!\n");
		return 0;
	}

	//입력한 첫번 째 값이 범위에 맞는지 확인후 알맞은 값 입력하게함
	if (ver1 > 19 || ver1 < 0)
	{
		while (ver1 < 20 && ver1 >= 0)
		{
			printf("Please enter a valid value.\n");
			printf("Your Key1 (0~19) = ");
			scanf("%d", ver1);
		}
	}

	//입력한 두번 째 값이 범위에 맞는지 확인후 알맞은 값 입력하게함
	if (ver2 > 19 || ver2 < 0)
	{
		while (ver2 < 20 && ver2 >= 0)
		{
			printf("Please enter a valid value.\n");
			printf("Your Key2 (0~19) = ");
			scanf("%d", ver2);
		}
	}

	//입력한 값들이 존재하는 값인지 확인
	if ((arr[ver1] == 0) || (arr[ver2] == 0))
	{
		printf("vertex does not exist\n");
		return 0;
	}

	//ver1의 리스트에서 ver2삭제
	first = (g->vlist) + ver1;
	trail = NULL;
	temp = ((g->vlist) + ver1)->head;
	while (temp != NULL) 
	{
		if (temp->num == ver2)
		{
			if (trail == NULL) //ver2가 첫번째 값일때
			{
				first->head = temp->link;
				free(temp);
				break;
			}
			else
			{
				trail->link = temp->link;
				free(temp);
				break;
			}
		}
		trail = temp;
		temp = temp->link;
	}
	if (temp == NULL) //예외처리
	{
		printf("There is no edge between two vertex.\n");
		return 0;
	}

	//ver2의 리스트에서 ver1삭제
	first = (g->vlist) + ver2;
	temp = ((g->vlist) + ver2)->head;
	while (temp != NULL)
	{
		if (temp->num == ver1)
		{
			if (trail == NULL) //ver1이 첫번째에 있을 때
			{
				first->head = temp->link;
				free(temp);
				break;
			}
			else
			{
				trail->link = temp->link;
				free(temp);
				break;
			}
		}
		trail = temp;
		temp = temp->link;
	}
	if (temp == NULL) //예외처리
	{
		printf("There is no edge between two vertex.\n");
		return 0;
	}

	return 1;
}

int depthFS(Graph* g, int key) /* depth firt search using stack */
{
	Vertex* temp; //pop한 vertex의 인접리스트 가리킬 포인터
	int n, val; //pop한 값을 저장할 n, push할 값을 저장할 val
	top = -1; //스택의 top값 초기화

	//그래프가 아직 만들어지지 않았을 경우 에러 메세지 출력 후 종료
	if (g == NULL)
	{
		printf("createGraqh first!\n");
		return 0;
	}

	/*vertex의 값의 법위체크, 입력한 vertex의 값이 존재하는지 체크
	  올바른 값을 입력할 때까지 while문 반복
	*/
	if ((key > 19 || key < 0) && arr[key] == 0)
	{
		while ((key < 20 && key >= 0) && arr[key] == 1)
		{
			printf("Please enter a valid value.\n");
			printf("Your Key (0~19) = ");
			scanf("%d", key);
		}
	}

	//visited 배열 초기화한 후 사용
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		visited[i] = 0;
	}

	push(key); //첫번째 vertex스택에 넣음
	temp = ((g->vlist) + key)->head; //key번째 headvertex가 가리키고 있는 값

	while (top != -1) //스택에 vertex가 있을 동안 반복
	{
		while (temp != NULL)
		{
			if (visited[temp->num] == 0) //방문하지 않은 vertex이면
			{
				visited[temp->num] = 1; //방문했다고 표시
				printf(" [%d] ", temp->num); //vertex프린트
				push(temp->num); //스택에 num값 저장
			}
			else //방문한 vertex라면
			{
				temp = temp->link; //다른 인접한vertex를 가리키게함
				if (temp == NULL) //다른 vertex가 없다면
				{
					pop(); //직전 넣었던 값 pop
					n = pop(); //이전에 넣었던 값 pop
					temp = ((g->vlist) + n)->head; //이전 노드를 가리키게 함
					break;
				}
			}
			temp = temp->link; //다음 vertex가리키게 함
			if (temp == NULL) //다음 vertex가 없을 때
			{
				pop(); //직전 넣었던 값 pop
				n = pop(); //이전에 넣었던 값 pop
				temp = ((g->vlist) + n)->head; //이전 노드를 가리키게 함
				break;
			}
		}
	}

	printf("\n\n");

	return 1;
}

int breadthFS(Graph* g, int key) /* breadth first search using queue */
{
	front = rear = NULL; //queue값 초기화
	int num; //deleteq한 vertex값 저장할 변수
	int val;//addq에 사용할 변수
	Vertex* temp; //deleteq한 vertex의 인접리스트 가리킬 포인터

	//그래프가 아직 만들어지지 않았을 경우 에러 메세지 출력 후 종료
	if (g == NULL)
	{
		printf("createGraqh first!\n");
		return 0;
	}

	/*vertex의 값의 법위체크, 입력한 vertex의 값이 존재하는지 체크
	 올바른 값을 입력할 때까지 while문 반복
	 */
	if ((key > 19 || key < 0) && arr[key] == 0)
	{
		while ((key < 20 && key >= 0) && arr[key] == 1)
		{
			printf("Please enter a valid value.\n");
			printf("Your Key (0~19) = ");
			scanf("%d", key);
		}
	}

	//visited 배열 초기화한 후 사용
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		visited[i] = 0;
	}

	addq(key); //key값 큐에 입력
	visited[key] = 1; //key값 방문했음
	while (front != rear) //queue가 비어있지 않을 동안 반복
	{
		num = deleteq(); // 방문할 vertex 정보꺼냄
		printf("  [%d]  ", num);
		temp = ((g->vlist) + num)->head; //num번째 headvertex가 가리키고 있는 값
		while (temp != NULL) //temp가 NULL이면 반복종료
		{
			//인접 vertex들을 큐에 넣음
			val = temp->num; //vertex의 값
			if (visited[val] != 1) //방문한 vertex이면 큐에 넣지 않음
			{
				addq(val);
				visited[val] = 1;
			}
			temp = temp->link; //리스트의 그다음 vertex
		}
	}

	return 1;
}

int printGraph(Graph* g) /* printing graph with vertices and edges */
{
	int i = 0; //반복문을 위한 변수
	Vertex* temp; //인접리스트 가리킬 포인터

	//그래프가 아직 만들어지지 않았을 경우 에러 메세지 출력 후 종료
	if (g == NULL)
	{
		printf("createGraqh first!\n");
		return 0;
	}

	//visited 배열 초기화한 후 사용
	for (i = 0; i < MAX_VERTEX; i++)
	{
		visited[i] = 0;
	}

	//vertex print
	printf("=========================================\n");
	printf("Vertex\n");
	for (i = 0; i < MAX_VERTEX; i++)
	{
		if (arr[i] == 1)
		{
			printf("  [%d]  ", i);
		}
	}
	printf("\n\n");

	//edge print (vertex가 존재하면 해당 vertex의 인접리스트 모두 출력)
	printf("Edge\n");
	for (i = 0; i < MAX_VERTEX; i++)
	{
		if (arr[i] == 1)
		{
			temp = ((g->vlist) + i)->head;
			while (temp != NULL)
			{
				printf("  (%d,%d)  ", i, temp->num);
				temp = temp->link;
			}
		}
	}
	printf("\n");
	printf("=========================================\n");

	return 1;
}

int freeList(Vertex* v) //인접 노드들의 메모리를 해제하는 함수
{
	Vertex* next; //다음 vertex를 가리킬 포인터

	while (v != NULL) //인접 vertex가 없을 때까지 반복
	{
		next = v->link; //메모리 해제할 vertex의 다음 vertex를 가리킴
		free(v); //v의 메모리 해제
		v = next; //next가 가리키는 값 가리키게함
	}

	return 1;
}

void push(int key) //스택에 삽입하는 함수
{
	top++; //top의 위치를 바꿈
	stack[top] = key; //stack에 vertex의 값 저장

    return ;
}

int pop() //스택에 있는 값을 반환하는 함수
{
	return stack[top--]; //top 위치에 있는 값을 리턴
}

void addq(int val)
{
	rear = (rear + 1) % MAX_VERTEX; //queue에 저장할 위치
	if (((rear == MAX_VERTEX - 1) && (front == -1)) || (rear == front)) //queue가 꽉차있을 때
	{
		printf("queue is full!\n");//에러 메세지 출력 후 종료
		return;
	}
	element[rear] = val; //queue에 저장

    return ;
}

int deleteq()
{
	if (front == rear) //queue가 비어있을때 NULL반환
	{
		return -1;
	}

	front = (front + 1) % MAX_VERTEX; //queue삭제할 위치를 front에 저장

	return element[front];//queue에 저장된 값 리턴
}
