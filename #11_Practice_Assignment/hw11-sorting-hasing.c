/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

 /* 필요에 따라 함수 추가 가능 */
int initialize(int** a);									
int freeArray(int* a);
void printArray(int* a);

int selectionSort(int* a);
int insertionSort(int* a);
int bubbleSort(int* a);
int shellSort(int* a);
/* recursive function으로 구현 */
int quickSort(int* a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int* a, int** ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int* ht, int key);


int main()
{
	char command;
	int* array = NULL;
	int* hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do {
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
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
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

int freeArray(int* a)
{
	/* array가 NULL이 아닐 경우 메모리 해제 */
	if (a != NULL)
		free(a);
	return 0;
}

void printArray(int* a)
{
	/* array가 NULL인 경우 에러메시지 출력 */
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	/* 순차대로 배열의 인덱스 증가시키면서 배열의 값 출력 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int* a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	/* 먼저 배열의 인덱스 순서대로 array 출력하기 위해 printArray 호출 */
	printArray(a);
	/* MAX_ARRAY_SIZE만큼 for문 반복하여 최솟값을 찾아 오름차순으로 정렬 */
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;				/* minindex에 현재 인덱스값 저장 */
		min = a[i];					/* min에 현재 인덱스에 따른 배열의 값 저장 */
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)   /* i의 다음 인덱스부터 MAX_ARRAY_SIZE까지 반복 */
		{
			/* 인덱스가 j인 배열의 값이 min보다 작을경우 그 배열의 값 min에 저장하고 
			  그 배열의 인덱스값 minindex에 저장 */
			if (min > a[j])				   
			{
				min = a[j];
				minindex = j;
			}
		}
		/* min에 저장된 최솟값의 인덱스인 배열에 인덱스가 i인 배열의 값을 저장, 
		    인덱스가 i인 배열은 min에 저장된 최솟값으로 저장.
			이로써 최솟값과 위치가 교체되어 정렬됨. */
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	/* Selection Sort된 array 출력 */
	printArray(a);
	return 0;
}

int insertionSort(int* a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		/* t에 인덱스가 i인 배열의 값 저장, j에 i값 대입 */
		t = a[i];
		j = i;
		/* i의 바로 앞 배열의 값부터 비교시작. t가 j-1의 값보다 작을 시 
		  j-1의 값을 j의 자리에 대입하고 인덱스 j를 감소함으로써 더 앞의 배열과 비교.
		  인덱스 값이 0보다 작아지거나 t보다 작은값 없게되면 while문 중단*/
		while (a[j - 1] > t&& j > 0)
		{
			a[j] = a[j - 1];
			j--;
		}
		/* while문이 종료되기 직전에 a[i]보다 작았던 배열의 위치에 t값 저장 */
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	/* Insertion Sort된 array 출력 */
	printArray(a);

	return 0;
}

int bubbleSort(int* a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	/* 두 for문 모두 MAX_ARRAY_SIZE만큼 반복 */
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			/* j와 j-1(서로 인접)의 배열의 값 비교하여 j의 값이 작으면 서로 swap
			   그렇지 않으면 j의 값을 증가시켜가면서 서로 인접한 배열의 값 비교 교환해나감 */
			if (a[j - 1] > a[j])
			{
				t = a[j - 1];
				a[j - 1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	/* Bubble Sort된 array 출력 */
	printArray(a);

	return 0;
}

int shellSort(int* a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	/* 
	   간격의 초기값을 MAX_ARRAY_SIZE/2 로 설정, 
	   for문이 한번 돌때마다 간격을 반으로 감소, 
	   간격이 1이 될때까지 for문 반복 
	*/
	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)
	{
		/* 간격의 크기만큼 for문 반복 */
		for (i = 0; i < h; i++)
		{
			/* 
				a[j(=k)](=v) : 간격(h)만큼 떨어진 요소 
				a[k-h] : 앞의 요소
				간격의 앞에 있는 요소가 뒤에 있는 요소보다 더 크고 
				간격의 뒤쪽의 인덱스가 간격-1 보다 클때
				간격의 앞,뒤 요소를 swap
				이 과정을 간격의 마지막이 되는 요소까지 반복
			*/
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h - 1 && a[k - h] > v)
				{
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	/* Shell Sort된 array 출력 */
	printArray(a);

	return 0;
}

int quickSort(int* a, int n)
{
	int v, t;
	int i, j;

	/* array의 크기가 1이 될때까지 반복 */
	if (n > 1)
	{
		/*
		  v : 피봇
		  i : 왼쪽 요소
		  j : 오른쪽 요소

		*/
		v = a[n - 1];
		i = -1;
		j = n - 1;

		while (1)
		{
			/* 
			  피봇보다 작은 key 찾기(왼쪽 => 오른쪽)
			  피봇보다 큰 key 찾기(오른쪽 => 왼쪽)
			*/
			while (a[++i] < v);
			while (a[--j] > v);

			/*
			  오른쪽과 왼쪽 값 swap  
			*/
			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		/* 피봇의 값을 j 위치로 이동 */
		t = a[i];
		a[i] = a[n - 1];
		a[n - 1] = t;

		/* 
		  새로운 피봇의 위치를 중심으로 왼쪽, 오른쪽 구분 
		  reculsive call로 정렬 반복
		*/
		quickSort(a, i);
		quickSort(a + i + 1, n - i - 1);
	}

	return 0;
}

int hashCode(int key) {
	/* 
	  key값이 인덱스가 i인 배열의 요소값 의미하고 
	  그 값을 연산이 가능한 정수형으로 변환하여 hashcode로 반환함
	*/
	return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int* a, int** ht)
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

	/* hash table의 요소들을 -1로 채움 */
	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;
	
	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/						   

	int key = -1;
	int hashcode = -1;
	int index = -1;				
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		/* 
		  key : 배열 요소 값
		  hashcode : key값 정수로 변환
		*/
		key = a[i];
		hashcode = hashCode(key);
		
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/

		/* 
		  key 값을 hashtable 내의 버킷으로 mapping
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} 
		/* 
		  충돌 발생 => 빈 테이블 버킷에 key를 mapping 시켜야함
		  index를 이용하여 빈곳 탐색, 그곳에 key값 mapping
		*/
		else {

			index = hashcode;

			while (hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int* ht, int key)
{
	int index = hashCode(key);

	/*
	  찾으려는 key값과 일치하는 hash table 발견시 그 인덱스 반환
	*/
	if (ht[index] == key)
		return index;

	/*
	  인덱스 증가시켜가며 탐색, 성공시 인덱스 반환
	*/
	while (ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}