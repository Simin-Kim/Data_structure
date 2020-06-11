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

 /* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int** a);									
int freeArray(int* a);
void printArray(int* a);

int selectionSort(int* a);
int insertionSort(int* a);
int bubbleSort(int* a);
int shellSort(int* a);
/* recursive function���� ���� */
int quickSort(int* a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int* a, int** ht);

/* hash table���� key�� ã�� hash table�� index return */
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

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if (*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	}
	else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int* a)
{
	/* array�� NULL�� �ƴ� ��� �޸� ���� */
	if (a != NULL)
		free(a);
	return 0;
}

void printArray(int* a)
{
	/* array�� NULL�� ��� �����޽��� ��� */
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	/* ������� �迭�� �ε��� ������Ű�鼭 �迭�� �� ��� */
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
	/* ���� �迭�� �ε��� ������� array ����ϱ� ���� printArray ȣ�� */
	printArray(a);
	/* MAX_ARRAY_SIZE��ŭ for�� �ݺ��Ͽ� �ּڰ��� ã�� ������������ ���� */
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;				/* minindex�� ���� �ε����� ���� */
		min = a[i];					/* min�� ���� �ε����� ���� �迭�� �� ���� */
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)   /* i�� ���� �ε������� MAX_ARRAY_SIZE���� �ݺ� */
		{
			/* �ε����� j�� �迭�� ���� min���� ������� �� �迭�� �� min�� �����ϰ� 
			  �� �迭�� �ε����� minindex�� ���� */
			if (min > a[j])				   
			{
				min = a[j];
				minindex = j;
			}
		}
		/* min�� ����� �ּڰ��� �ε����� �迭�� �ε����� i�� �迭�� ���� ����, 
		    �ε����� i�� �迭�� min�� ����� �ּڰ����� ����.
			�̷ν� �ּڰ��� ��ġ�� ��ü�Ǿ� ���ĵ�. */
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	/* Selection Sort�� array ��� */
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
		/* t�� �ε����� i�� �迭�� �� ����, j�� i�� ���� */
		t = a[i];
		j = i;
		/* i�� �ٷ� �� �迭�� ������ �񱳽���. t�� j-1�� ������ ���� �� 
		  j-1�� ���� j�� �ڸ��� �����ϰ� �ε��� j�� ���������ν� �� ���� �迭�� ��.
		  �ε��� ���� 0���� �۾����ų� t���� ������ ���ԵǸ� while�� �ߴ�*/
		while (a[j - 1] > t&& j > 0)
		{
			a[j] = a[j - 1];
			j--;
		}
		/* while���� ����Ǳ� ������ a[i]���� �۾Ҵ� �迭�� ��ġ�� t�� ���� */
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	/* Insertion Sort�� array ��� */
	printArray(a);

	return 0;
}

int bubbleSort(int* a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	/* �� for�� ��� MAX_ARRAY_SIZE��ŭ �ݺ� */
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			/* j�� j-1(���� ����)�� �迭�� �� ���Ͽ� j�� ���� ������ ���� swap
			   �׷��� ������ j�� ���� �������Ѱ��鼭 ���� ������ �迭�� �� �� ��ȯ�س��� */
			if (a[j - 1] > a[j])
			{
				t = a[j - 1];
				a[j - 1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	/* Bubble Sort�� array ��� */
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
	   ������ �ʱⰪ�� MAX_ARRAY_SIZE/2 �� ����, 
	   for���� �ѹ� �������� ������ ������ ����, 
	   ������ 1�� �ɶ����� for�� �ݺ� 
	*/
	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)
	{
		/* ������ ũ�⸸ŭ for�� �ݺ� */
		for (i = 0; i < h; i++)
		{
			/* 
				a[j(=k)](=v) : ����(h)��ŭ ������ ��� 
				a[k-h] : ���� ���
				������ �տ� �ִ� ��Ұ� �ڿ� �ִ� ��Һ��� �� ũ�� 
				������ ������ �ε����� ����-1 ���� Ŭ��
				������ ��,�� ��Ҹ� swap
				�� ������ ������ �������� �Ǵ� ��ұ��� �ݺ�
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
	/* Shell Sort�� array ��� */
	printArray(a);

	return 0;
}

int quickSort(int* a, int n)
{
	int v, t;
	int i, j;

	/* array�� ũ�Ⱑ 1�� �ɶ����� �ݺ� */
	if (n > 1)
	{
		/*
		  v : �Ǻ�
		  i : ���� ���
		  j : ������ ���

		*/
		v = a[n - 1];
		i = -1;
		j = n - 1;

		while (1)
		{
			/* 
			  �Ǻ����� ���� key ã��(���� => ������)
			  �Ǻ����� ū key ã��(������ => ����)
			*/
			while (a[++i] < v);
			while (a[--j] > v);

			/*
			  �����ʰ� ���� �� swap  
			*/
			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		/* �Ǻ��� ���� j ��ġ�� �̵� */
		t = a[i];
		a[i] = a[n - 1];
		a[n - 1] = t;

		/* 
		  ���ο� �Ǻ��� ��ġ�� �߽����� ����, ������ ���� 
		  reculsive call�� ���� �ݺ�
		*/
		quickSort(a, i);
		quickSort(a + i + 1, n - i - 1);
	}

	return 0;
}

int hashCode(int key) {
	/* 
	  key���� �ε����� i�� �迭�� ��Ұ� �ǹ��ϰ� 
	  �� ���� ������ ������ ���������� ��ȯ�Ͽ� hashcode�� ��ȯ��
	*/
	return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int* a, int** ht)
{
	int* hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	}
	else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	/* hash table�� ��ҵ��� -1�� ä�� */
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
		  key : �迭 ��� ��
		  hashcode : key�� ������ ��ȯ
		*/
		key = a[i];
		hashcode = hashCode(key);
		
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/

		/* 
		  key ���� hashtable ���� ��Ŷ���� mapping
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} 
		/* 
		  �浹 �߻� => �� ���̺� ��Ŷ�� key�� mapping ���Ѿ���
		  index�� �̿��Ͽ� ��� Ž��, �װ��� key�� mapping
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
	  ã������ key���� ��ġ�ϴ� hash table �߽߰� �� �ε��� ��ȯ
	*/
	if (ht[index] == key)
		return index;

	/*
	  �ε��� �������Ѱ��� Ž��, ������ �ε��� ��ȯ
	*/
	while (ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}