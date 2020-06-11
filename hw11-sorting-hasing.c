/*
* hw5-sorting.c
*
*  Created on: May 22, 2019
*
*  Homework 5: Sorting & Hashing
*  Department of Computer Science at Chungbuk National University
*
*/

#include <stdio.h> //표준입출력을 위한 헤더추가
#include <stdlib.h> //동적 메모리할당을 위한 헤더추가
#include <time.h>  //time함수를 사용하기 위한 헤더추가

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE //해시테이블의 크기

/* 필요에 따라 함수 추가 가능 */
int initialize(int** a); //초기화함수
int freeArray(int* a); //메모리를 해제하는 함수
void printArray(int* a); //배열을 출력하는 함수

int selectionSort(int* a); //선택정렬함수
int insertionSort(int* a); //삽입정렬함수
int bubbleSort(int* a); //버블정렬함수
int shellSort(int* a); //셸정렬함수
/* recursive function으로 구현 */
int quickSort(int* a, int n); //퀵정렬을 위한 함수


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int* a, int** ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int* ht, int key);


int main()
{
	char command; //사용자가 입력한 메뉴를 저장할변수
	int* array = NULL; //배열의 주소를 저장할 포인터 NULL로 초기화
	int* hashtable = NULL; //hashtable의 주소를 저장할 포인터 NULL로 초기화
	int key = -1; //사용자가 입력한 key값을 저장할 변수
	int index = -1; //반환된 값을 저장할 변수

	srand(time(NULL)); //시드값을 초기화

	do {
		//메뉴출력
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자가 입력한값 받아서 command에 저장

		switch (command) { //command값에 따라 함수 실행
		case 'z': case 'Z':
			initialize(&array); //초기화함수
			break;
		case 'q': case 'Q':
			freeArray(array); //메모리를 해제하는 함수
			break;
		case 's': case 'S':
			selectionSort(array); //선택정렬함수
			break;
		case 'i': case 'I': 
			insertionSort(array); //삽입정렬함수
			break;
		case 'b': case 'B':
			bubbleSort(array);  //버블정렬함수
			break;
		case 'l': case 'L':
			shellSort(array); //셸정렬함수
			break;
		case 'k': case 'K': //퀵정렬
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열출력함수
			quickSort(array, MAX_ARRAY_SIZE); //퀵정렬함수
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열출력함수

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열출력함수
			hashing(array, &hashtable); //해시테이블을 만드는 함수
			printArray(hashtable); //해시테이블의 값을 출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); //사용자가 입력한 값을 key에 저장
			printArray(hashtable); //해시테이블의 값을 출력
			index = search(hashtable, key); //해시테이블에서 key값을 탐색하여 해당 인덱스번호를 반환
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); //key값, 해당 index값, hashtable의 값출력
			break;

		case 'p': case 'P':
			printArray(array); //배열을 출력하는 함수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q'); //q또는 Q가 입력되면 반복종료

	return 1;
}

int initialize(int** a) //초기화함수
{
	int* temp = NULL; 

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int* a) //메모리를 해제하는 함수
{
	if (a != NULL) //a가 NULL이 아닐때까지
		free(a); //a가 가리키고 있는 메모리 해제
	return 0;
}

void printArray(int* a) //배열을 출력하는 함수
{
	if (a == NULL) { //배열이 초기화가 안되었을 경우 
		printf("nothing to print.\n");
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 인덱스 번호 출력
		printf("a[%02d] ", i);
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) //인덱스에 저장된 값 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int* a) //선택정렬 함수
{
	int min; //최솟값을 저장할변수
	int minindex; //최솟값이 있는 인덱스의 번호를 저장할 변수
	int i, j; //반복을 위한 변수

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //처음 배열의 상태 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //배열 크기만큼 반복
	{
		minindex = i; //최솟값이 있는 인덱스의 번호를 i라고 설정
		min = a[i]; //최솟값은 a[i]

		//i의 값을 그 다음부터 배열의 끝에 있는 값까지 비교
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++) 
		{
			if (min > a[j]) //원래 min의 값보다 비교할 값이 더 작으면
			{
				min = a[j]; //min의 값 변경
				minindex = j; //minindex의 값도 변경
			}
		}

		/*
		i번째 인덱스에 있는 값을 최종 minindex에 있던 값에 넣고
		i번째 인덱스에 최솟값을 넣음
		*/
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬된 값을 출력
	return 0;
}

int insertionSort(int* a) //삽입정렬함수
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬이전 배열의 값 출력

	//배열의 값을 하나씩 옮기면서 i번째 인덱스의 값을 정렬
	for (i = 1; i < MAX_ARRAY_SIZE; i++) //배열의 크기만큼 반복
	{
		t = a[i]; //t에 i번째 인덱스의 값 저장
		j = i; //j에 i의 값을 저장
		//j의 값을 줄이며 이전 인덱스의 값을 그 다음 인덱스에 대입
		while (a[j - 1] > t && j > 0) //a[j-1]이 t보다 크고 j의 값이 0보다 클때 반복
		{
			a[j] = a[j - 1]; //j번째 인덱스에 j-1번째 인덱스에 있던 값을 대입
			j--;//j의 값을 1줄임
		}
		a[j] = t; //j번째 인덱스에 i번째 인덱스에 있던값을 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬후 배열의 값을 출력

	return 0;
}
 
int bubbleSort(int* a) //버블정렬함수
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열의 값을 출력

	/* 배열의 j번째와 j-1번째 값을 비교하여 정렬해나감
	   j를 1씩 증가시켜 배열의 마지막 까지 대강 정렬한후 
	   j=1부터 시작하여 j와 j-1번째 값을 비교한다
	   배열이 완전히 정렬될때까지 반복(이 코드에서는 배열의 크기만큼 반복)  */
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j - 1] > a[j]) //j번째 인덱스에 있는 값이 j-1번째 인덱스에 있는 값보다 작을 떄
			{
				t = a[j - 1]; //t에 a[j-1]을 저장
				a[j - 1] = a[j]; //a[j-1]에 a[j]를 대입
				a[j] = t;//a[j]에 t를 대입
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬된 후 배열의 값 출력

	return 0;
}

int shellSort(int* a) //셀정렬함수
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열의 값 출력


	//h만큼 떨어진 곳의 값과 비교하여 정렬
	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2) //h=6으로 시작하여 2로 나눠가며 0보다 클때동안 반복
	{
		for (i = 0; i < h; i++) //i가 h보다 작을때 동안 반복
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h) //j는 i와 h만큼 떨어진곳부터 마지막 인덱스보다 작을 동안 +h반복
			{
				v = a[j]; //v에 a[j]값 저장
				k = j; //k에 j값 저장
				while (k > h - 1 && a[k - h] > v) //k가 h-1보다 크고 a[k-h]의 값이 a[j]보다 크면
				{
					a[k] = a[k - h]; //k-h번째 인덱스에 있던 값을 k번째 인덱스에 대입
					k -= h; //k에서 h를 뺌
				}
				a[k] = v; //k번째 인덱스에 a[j]의 값 대입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열의 값 출력

	return 0;
}

int quickSort(int* a, int n) //퀵정렬 함수
{
	int v, t;
	int i, j;


	if (n > 1) //n이 1보다 크면
	{
		v = a[n - 1]; //배열의 마지막 인덱스에 있는 값을 피벗으로 정함
		i = -1; //i에는 -1저장
		j = n - 1; //j에는 n-1저장

		//피벗보다 작은 값을 피벗의 왼쪽에, 큰값을 오른쪽에 배치되도록함
		while (1)
		{
			while (a[++i] < v); //a[i+1]이 v보다 작을 동안 반복
			while (a[--j] > v); //a[j-1]이 v보다 클 동안 반복

			if (i >= j) break; //i가 j보다 크거나 같으면 반복문 탈출
			t = a[i]; //a[i]를 t에 저장
			a[i] = a[j]; //a[i]에 a[j]의 값을 대입
			a[j] = t; //a[j]에 t의 값을 대입
		}
		//i번째 인덱스에 있는 값과 n-1번째 인덱스에 있는 값을 바꿈(피벗과 자리바꿈)
		t = a[i];
		a[i] = a[n - 1];
		a[n - 1] = t;

		quickSort(a, i); //피벗의 왼쪽 퀵정렬
		quickSort(a + i + 1, n - i - 1); //피벗의 오른쪽 퀵정렬
	}


	return 0;
}

int hashCode(int key) //해시 테이블의 주소를 반환해 주는 함수
{
	//key값을 13으로 나눈 나머지의 값을 반환
	return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int* a, int** ht) //배열의 값을 hashtable에 
{
	int* hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++) //hashtable의 값을 -1로 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 크기만큼 반복
	{
		key = a[i]; //i번째 인덱스의 값을 key에 저장
		hashcode = hashCode(key); //hashCode 함수로 key 값에 해당하는 hashtable의 주소 반환
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //hashCode로 얻은 주소에 해당하는 table의 위치가 비어있으면
		{
			hashtable[hashcode] = key; //hashcode위치에 key값을 저장
		}
		else { //이미 값이 있으면 

			index = hashcode; //index에 hashcode를 저장

			
			//hashtable에 비어있는 곳을 찾을 때까지 index값을 증가시킴
			while (hashtable[index] != -1) 
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //비어있는 곳에 key값을 저장
		}
	}

	return 0;
}

int search(int* ht, int key) //hashtable에서 key값이 저장된 index의 값을 반환하는 함수
{
	int index = hashCode(key); //hash함수로 반환된 key값에 대한 주소를 index에 저장

	if (ht[index] == key) //반환된 주소에 있는 값이 key값과 같으면 index반환
		return index;

	while (ht[++index] != key) //같지 않으면 index의 값을 증가시키면서 index에 위치한 값이 key와 같은지 비교
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; //찾은 index의 값을 반환
}