/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType* createQueue();
int isEmpty(QueueType* cQ);
int isFull(QueueType* cQ);
void enQueue(QueueType* cQ, element item);
void deQueue(QueueType* cQ, element* item);
void printQ(QueueType* cQ);
void debugQ(QueueType* cQ);

element getElement();


int main(void)
{
	QueueType* cQ = createQueue();
	element data;

	char command;

	printf("[�̸�] : ��ù�\t[�й�] : 2016039081\n");

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}


QueueType* createQueue()
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType* cQ)				/* ť ���� �˻� �Լ� */
{
	return (cQ->front == cQ->rear);		/* ť�� front�� rear�� �������(=ť�� �����ϰ��) True�� ��ȯ */
}

/* complete the function */
int isFull(QueueType* cQ)									/* ť ��ȭ �˻� �Լ� */
{
	return ((cQ->rear+1)%MAX_QUEUE_SIZE == cQ->front);		/* ť�� front�� (rear+1)%MAX_QUEUE_SIZE ���� �������(=ť�� ��ȭ�ϰ��) True�� ��ȯ */
}


/* complete the function */
void enQueue(QueueType* cQ, element item)					/* ť�� ��Ұ� �߰� �Լ�*/ 
{
	if (isFull(cQ))											/* isFull�˻� �� ���̸�(=ť�� ��ȭ�ϰ��) ��ȭ �޽��� ��� */
	{
		printf("Circular Queue is full!\n");				
	}
	else													/* ��ȭ �ƴҰ�� rear�� �����Ű�� ����� rear �ڸ��� ���ο� ��� ���� */
	{	
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;			
		cQ->queue[cQ->rear] = item;
	}
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)			/* ť���� ��Ұ� �ϳ� ���� �Լ�*/
{
	if (isEmpty(cQ))								/* isFull�˻� �� ���̸�(=ť�� �����ϰ��) ���� �޽��� ��� */
	{
		printf("Circular Queue is empty!\n");				
	}
	else										/* ��ȭ �ƴҰ�� front�� �����Ű�� ����� front �ڸ��� '?'�����Ͽ� ������ ���ڸ��� ������� */
	{											
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->front] = '?';				/* '?' �������� ������� queue�� ������ delete �����ʰ� enQueue, deQueue�� �ݺ��ϴ� ���� �ᱹ �ٽ� ť�� ���� �Ǵ� ���� �߻� */
	}
}


void printQ(QueueType* cQ)					  //���� ť�� ���� ���
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ)					   //ť���� ���� ������
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
