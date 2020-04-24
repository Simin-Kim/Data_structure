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

	printf("[이름] : 김시민\t[학번] : 2016039081\n");

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
int isEmpty(QueueType* cQ)				/* 큐 공백 검사 함수 */
{
	return (cQ->front == cQ->rear);		/* 큐의 front와 rear가 같을경우(=큐가 공백일경우) True값 반환 */
}

/* complete the function */
int isFull(QueueType* cQ)									/* 큐 포화 검사 함수 */
{
	return ((cQ->rear+1)%MAX_QUEUE_SIZE == cQ->front);		/* 큐의 front와 (rear+1)%MAX_QUEUE_SIZE 값이 같을경우(=큐가 포화일경우) True값 반환 */
}


/* complete the function */
void enQueue(QueueType* cQ, element item)					/* 큐에 요소값 추가 함수*/ 
{
	if (isFull(cQ))											/* isFull검사 후 참이면(=큐가 포화일경우) 포화 메시지 출력 */
	{
		printf("Circular Queue is full!\n");				
	}
	else													/* 포화 아닐경우 rear값 변경시키고 변경된 rear 자리에 새로운 요소 삽입 */
	{	
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;			
		cQ->queue[cQ->rear] = item;
	}
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)			/* 큐에서 요소값 하나 제거 함수*/
{
	if (isEmpty(cQ))								/* isFull검사 후 참이면(=큐가 공백일경우) 공백 메시지 출력 */
	{
		printf("Circular Queue is empty!\n");				
	}
	else										/* 포화 아닐경우 front값 변경시키고 변경된 front 자리에 '?'삽입하여 완전히 빈자리로 만들어줌 */
	{											
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->front] = '?';				/* '?' 삽입하지 않을경우 queue가 완전히 delete 되지않고 enQueue, deQueue를 반복하다 보면 결국 다시 큐에 남게 되는 에러 발생 */
	}
}


void printQ(QueueType* cQ)					  //현재 큐의 상태 출력
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


void debugQ(QueueType* cQ)					   //큐안의 값들 보여줌
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
