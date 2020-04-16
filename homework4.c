#include <stdio.h> 
#include <stdlib.h> //malloc함수를 사용하기 위한 헤더파일포함
#include <time.h> //time()함수를 사용하기 위한 헤더파일 포함
#define _CRT_SECURE_NO_WARNINGS

int row, col; //행과 열을 저장할 변수
int** matrix; //행렬을 만들때 주소값을 할당받을 이중 포인터변수
int** A, ** B, ** RESULT, ** T; //함수 안에서 사용될 행렬을 저장할 변수(계살할 행렬 AB,결과 RESULT, 전치행렬 T)

int** create_matrix(int row, int col); //행렬을 생성할 메모리를 할당받는 함수
int free_matrix(int** matrix, int row, int col); //행렬을 저장하기 위해 할당받았던 메모리를 해제하는 함수
void print_matrix(int** matrix, int row, int col); //행렬의 값을 출력하는 함수
int fill_data(int** matrix, int row, int col); //행렬을 랜덤값으로 초기화하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //전치행렬을 구하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col); //두 행렬의 합을 구하여 결과를 반환하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col); //두 행렬의 차를 구하여 결과를 반환하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col); //행렬 A과 그의 전치행렬과 곱을 구하여 결과를 반환하는 함수


int main()
{

	printf("----------[이하은]     [2019038037]----------\n\n");

	printf("행을 입력하세요. : "); //사용자가 행과 열의 수를 입력
	scanf("%d", &row);
	printf("열을 입력하세요. : ");
	scanf("%d", &col);

	srand((unsigned)time(NULL)); //시드값을 초기화

	printf("\n     두 행렬의 합\n");
	printf("---------------------------------------------\n");
	addition_matrix(A, B, RESULT, row, col); //두 행렬을 더하는 함수 호출
	printf("-\n\n");
	printf("     두 행렬의 차\n");
	printf("---------------------------------------------\n");
	subtraction_matrix(A, B, RESULT, row, col); //두 행렬의 차를 구하는 함수 호출
	printf("\n\n"); 
	printf("     전치 행렬 T\n");
	printf("---------------------------------------------\n");
	transpose_matrix(A, T, row, col); //전치행렬 구하는 함수 호출
	printf("\n\n");
	printf("     두 행렬의 곱\n");
	printf("---------------------------------------------\n");
	multiply_matrix(A, T, RESULT, row, col); //행렬 A와 그 행렬의 전치행렬의 곱을 구하는 함수

	return 0;
}

int** create_matrix(int row, int col) //행렬을 저장할 메모리를 할당받는 함수
{
	int i; // 반복문을 위한 변수 i

	if (row <= 0 || col <= 0)  // 전처리 검사(행과 열의 값이 음수이면 NULL반환)
	{
		printf("Check the sizes of row and col!\n");
		return NULL;
	}

	matrix = (int**)malloc(row * sizeof(int*)); //행의 크기 * 포인터변수의 크기 만큼 할당받음
	for (i = 0; i < row; i++)
	{
		*(matrix + i) = (int*)malloc(col * sizeof(int)); //각 행에 열의수 * int 형의 크기 만큼 메모리 할당 받음
	}

	if (matrix == NULL) 
		/*후처리 검사 & 정상종료 검사(matrix에 메모리가 할당 되지 않았으면NULL 반환)
		                               메모리가 제대로 할당 되었으면 메모리의 주소 반환*/
	{
		printf("메모리 할당에 실패했습니다.\n");
		return NULL;
	}
	else //정상적으로 종료되었을 때
		return matrix;
}

int free_matrix(int** matrix, int row, int col) //메모리를 해제한는 함수
{
	int i;  // 반복문을 위한 변수 i

	if (row <= 0 || col <= 0)  // 전처리 검사(행과 열의 값이 음수이면 -1반환)
	{
		printf("Check the sizes of row and col!\n");
		return -1;
	}


	for (i = 0; i < row; i++) //각 행이 가리키고 있는 열의 값을 저장하고 있는 메모리 해제
	{
		free(matrix[i]);
	}
	free(matrix); //행을 가리키고 있던 이중포인터 메모리 해제

	
	if (i != row)  // 후처리 검사(for문을 실행하는데 문제가 생겼으면 에러처리)
	{
		printf("메모리 해제에 실패했습니다.\n");
		return -1;
	}


	return 1; //정상적으로 종료 되었을 경우 1반환
}

void print_matrix(int** matrix, int row, int col) //행렬의 값을 출력하는 함수
{
	int i, j;  // 반복문을 위한 변수 i,j

	if (row <= 0 || col <= 0)  // 전처리 검사(행과 열의 값이 음수이면 에러처리)
	{
		printf("Check the sizes of row and col!\n");
	}

	printf("------------------------------\n");
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%5d", *(*(matrix + i) + j));

		}
		printf("\n");
	}
	printf("------------------------------\n\n");

	if (i!=row && j!=col)  // 후처리 검사(for문을 실행하는데 문제가 생겼으면 에러처리)
	{
		printf("행렬을 출력하는데 문제가 발생했습니다.\n");
	}

}

int fill_data(int** matrix, int row, int col) //행렬에 난수를 채워넣는 함수 
{
	int i, j;  // 반복문을 위한 변수 i,j

	if (row <= 0 || col <= 0)  // 전처리 검사(행과 열의 값이 음수이면 -1반환)
	{
		printf("Check the sizes of row and col!\n");
		return -1;
	}

	for (i = 0; i < row; i++) //for문을 통해 row * col 행렬에 0~19 사이의 값을 저장
	{
		for (j = 0; j < col; j++)
		{
			*(*(matrix + i) + j) = (rand() % 20);
		}
	}

	if (i != row && j != col)  // 후처리 검사(for문을 실행하는데 문제가 생겼으면 에러처리)
	{
		printf("원소의 값을 생성하는데 문제가 발생했습니다.\n");
		return -1;
	}

	return 1; //정상종료시 1반환
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col) //전치행렬을 구하는 함수
//원래의 행렬과 전치된 행렬을 저장할 이중포인터 두개와 행,열을 저장할 변수를 매개변수로 가짐
{
	int i, j;  // 반복문을 위한 변수 i,j

	if (row <= 0 || col <= 0)  // 전처리 검사(행과 열의 값이 음수이면 -1반환)
	{
		printf("Check the sizes of row and col!\n");
		return -1;
	}

	matrix = create_matrix(row, col); //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음
	fill_data(matrix, row, col); //만들어진 메모리에 값을 채워넣는 함수 호출(메모리의 시작주소와 행,열의 값을 인자로 줌)
	matrix_t = create_matrix(col, row);//전치된 행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환 받음


	printf("     행렬 A\n");
	print_matrix(matrix, row, col); //원래의 행렬 출력하는 함수 호출

	for (i = 0; i < row; i++) //이중 for문을 통해 (T)ij 성분에 (A)ji 성분을 저장
	{
		for (j = 0; j < col; j++)
		{
			*(*(matrix_t + j) + i) = *(*(matrix + i) + j);
		}
	}

	printf("     행렬 T\n");
	print_matrix(matrix_t, col, row); //전치행렬을 출력하는 함수 호출(메모리의 시작주소와 행,열의 값을 인자로 전달)

	//동적메모리들을 해제
	free_matrix(matrix, row, col);
	free_matrix(matrix_t, col, row);

	if (i != row && j != col)  // 후처리 검사(for문을 실행하는데 문제가 생겼으면 에러처리)
	{
		printf("전치 행렬을 생성하는데 문제가 발생했습니다.\n");
		return -1;
	}

	return 1; //정상종료시 1반환
}

int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col)
//두 행렬을 생성하여 더한후 값을 출력하는 함수
{
	int i, j;  // 반복문을 위한 변수 i,j

	if (row <= 0 || col <= 0)  // 전처리 검사(행과 열의 값이 음수이면 -1반환)
	{
		printf("Check the sizes of row and col!\n");
		return -1;
	}

	matrix_a = create_matrix(row, col);  //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음
	fill_data(matrix_a, row, col); //만들어진 메모리에 값을 채워넣는 함수 호출(메모리의 시작주소와 행,열의 값을 인자로 줌)
	matrix_b = create_matrix(row, col);  //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음
	fill_data(matrix_b, row, col); //만들어진 메모리에 값을 채워넣는 함수 호출(메모리의 시작주소와 행,열의 값을 인자로 줌)
	matrix_sum = create_matrix(row, col);  //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음

	printf("     행렬 A\n");
	print_matrix(matrix_a, row, col); //행렬A를 출력하는 함수 호출
	printf("     행렬 B\n");
	print_matrix(matrix_b, row, col); //행렬B를 출력하는 함수 호출

	for (i = 0; i < row; i++) //이중 for문을 통해 두 행렬의 값을 더하여 sum행렬에 저장
	{
		for (j = 0; j < col; j++)
		{
			*(*(matrix_sum + i) + j) = *(*(matrix_a + i) + j) + *(*(matrix_b + i) + j);
		}
	}

	printf("     A+B\n");
	print_matrix(matrix_sum, row, col); //행렬의 합을 저장한 행렬을 출력하는 함수를 호출

	//동적메모리들을 해제
	free_matrix(matrix_a, row, col);
	free_matrix(matrix_b, row, col);
	free_matrix(matrix_sum, row, col);

	if (i != row && j != col)  // 후처리 검사(for문을 실행하는데 문제가 생겼으면 에러처리)
	{
		printf("행렬의 합을 계산하는데 문제가 발생했습니다.\n");
		return -1;
	}

	return 1; //정상종료시 1반환

}

int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col)
//두 행렬을 생성하여 한행렬에서 다른 행렬을 뺀 값을 출력하는 함수
{
	int i, j;  // 반복문을 위한 변수 i,j

	if (row <= 0 || col <= 0)  // 전처리 검사(행과 열의 값이 음수이면 -1반환)
	{
		printf("Check the sizes of row and col!\n");
		return -1;
	}

	matrix_a = create_matrix(row, col); //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음
	fill_data(matrix_a, row, col); //만들어진 메모리에 값을 채워넣는 함수 호출(메모리의 시작주소와 행,열의 값을 인자로 줌)
	matrix_b = create_matrix(row, col); //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음
	fill_data(matrix_b, row, col); //만들어진 메모리에 값을 채워넣는 함수 호출(메모리의 시작주소와 행,열의 값을 인자로 줌)
	matrix_sub = create_matrix(row, col); //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음

	printf("     행렬 A\n");
	print_matrix(matrix_a, row, col); //행렬A를 출력하는 함수 호출
	printf("     행렬 B\n");
	print_matrix(matrix_b, row, col); //행렬B를 출력하는 함수 호출

	for (i = 0; i < row; i++) //이중 for문을 통해 두 행렬의 값을 뺀후 sub행렬에 저장
	{
		for (j = 0; j < col; j++)
		{
			*(*(matrix_sub + i) + j) = *(*(matrix_a + i) + j) - *(*(matrix_b + i) + j);
		}
	}

	printf("     A-B\n");
	print_matrix(matrix_sub, row, col); //행렬의 차를 저장한 행렬을 출력하는 함수를 호출

	//동적메모리들을 해제
	free_matrix(matrix_a, row, col);
	free_matrix(matrix_b, row, col);
	free_matrix(matrix_sub, row, col);

	if (i != row && j != col)  // 후처리 검사(for문을 실행하는데 문제가 생겼으면 에러처리)
	{
		printf("행렬의 차를 계산하는데 문제가 발생했습니다.\n");
		return -1;
	}

	return 1; //정상종료시 1반환

}

int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col)
//원래의 행렬과 전치행렬생성하여 두 행렬의 곱을 구한후 출력하는 함수
{
	int i, j, k;  // 반복문을 위한 변수 i,j,k
	int sum = 0;

	if (row <= 0 || col <= 0)  // 전처리 검사(행과 열의 값이 음수이면 -1반환)
	{
		printf("Check the sizes of row and col!\n");
		return -1;
	}

	matrix_a = create_matrix(row, col); //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음
	fill_data(matrix_a, row, col);  //만들어진 메모리에 값을 채워넣는 함수 호출(메모리의 시작주소와 행,열의 값을 인자로 줌)
	matrix_t = create_matrix(col, row); //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음
	matrix_axt = create_matrix(row, row); //행렬을 저장할 메모리 생성하는 함수 호출하여 주소값 반환받음

	printf("       행렬 A\n");  
	print_matrix(matrix_a, row, col); //행렬A를 출력하는 함수 호출 

	for (i = 0; i < row; i++) //이중 for문을 통해 (matrix_t)ij 성분에 (matrix_a)ji 성분을 저장
	{
		for (j = 0; j < col; j++)
		{
			*(*(matrix_t + j) + i) = *(*(matrix_a + i) + j);
		}
	}

	printf("       행렬 T\n");
	print_matrix(matrix_t, col, row); //전치행렬T를 출력하는 함수 호출 

	for (i = 0; i < row; i++) //for문을 통해 원래 행렬의 row번째 행과 전치행렬의 col번째 열의 곱의 값을 구함
	{
		for (j = 0; j < col; j++) //row번째 행과 전치행렬의 col번째 열의 원소를 차례대로 곱하는 구문
		{
			sum = sum + ((*(*(matrix_a + i) + j)) * (*(*(matrix_t + j) + i)));
		}

		for (k = 0; k < row; k++) //행렬의 원소의 곱을 더함
		{
			*(*(matrix_axt + i) + k) = sum;
		}
		sum = 0; //sum을 초기화

	}

	printf("     A * T\n");
	print_matrix(matrix_axt, row, row); //두행렬의 곱의 결과를 출력하는 함수 호출 

	//동적메모리들을 해제
	free_matrix(matrix_a, row, col);
	free_matrix(matrix_t, col, row);
	free_matrix(matrix_axt, row, row);

	if (i != row && j != col)  // 후처리 검사(for문을 실행하는데 문제가 생겼으면 에러처리)
	{
		printf("행렬의 곱을 계산하는데 문제가 발생했습니다.\n");
		return -1;
	}

	return 1; //정상종료시 1반환
}
