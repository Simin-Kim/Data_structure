/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;

}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	printf("[----- [김시민] [2016039081] -----]\n");
	
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

/* singly-linked-list.c 에서와 달리 이중포인터로 매개변수를 받았기때문에 
  리턴값으로 h를 변경하는게 아니라 참조로 직접 h의 주소를 변경해준다.*/
int initialize(headNode** h) {										 /* 이중포인터를 매개변수로 받음 */

	if (*h != NULL)					 								 /* headNode의 주소가 담긴 h를 포인트하여 NULL이 아니면 freeList 호출하여 메모리해제 */
		freeList(*h);

	/* headNode에 대한 메모리 할당하여 그 주소 h에 넣어줌*/
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;			

	/* headNode를 포인트하는 h의 주솟값을 변경하고자 하기때문에 h를 포인트하여 temp의 주솟값으로 변경. 
	   포인터 변수 값을 변경하려면 이중포인터를 이용하여 그 포인터변수의 주솟값을 담아 변경해준다.*/
	*h = temp;														 
	return 1;														  
}

/* freeList함수에서는 포인터변수 h의 주소를 변경해줄 필요가 없기때문에
	initialize 함수처럼 이중포인터를 이용할 필요가 없다.
	하지만 이중포인터를 이용하여 함수를 구현할 수 있긴하다.*/
int freeList(headNode* h) {
	listNode* p = h->first;
	listNode* trail=NULL;

	while (p != NULL)
	{
		trail = p;
		p = p->rlink;						/* rlink가 다음 노드를 가리키기때문에 rlink 사용 */
		free(trail);						/* 앞 노드인 trail 메모리해제 */
	}

	free(h);								/* 헤더노드 메모리해제 */
	return 0;
}

/* 이중포인터를 매개변수로 받았을때 
   사용하려면 함수 선언부와 main()함수 initialize함수 내부부분도 수정해줘야함 */
/*
int freeList(headNode** h)					//이중포인터로 매개변수 받을때
{
	listNode* p = (*h)->first;				//headNode의 주소를 담은 h를 포인터하는 *h
	listNode* trail = NULL;

	while (p != NULL)
	{
		trail = p;
		p = p->rlink;
		free(trail);
	}

	free(*h);							   //free에는 메모리해제 하려는 곳의 주소가 담겨야 하기때문에 *h 인자로 넣어줌
	return 0;
}
*/

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;								 //다음 노드를 나타내는 rlink
		i++;
	}

	printf("  items = %d\n", i);
}


/**
 * list 처음에 key에 대한 노드하나를 추가					
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;										   // 좌우 링크 모두 NULL값으로 초기설정
	node->llink = NULL;
	
	if (h->first == NULL)									   // 추가할 노드가 첫노드일때
	{
		h->first = node;
		return 0;
	}

	listNode* n = (listNode*)malloc(sizeof(listNode));
	n = h->first;

	node->rlink = n;										   // 노드의 rlink가 원래 첫 노드였던 n을 가리킴
	n->llink = node;										   // n의 llink는 node를 가리킴
	h->first = node;										   // 헤더가 list 처음 위치가 된 node를 가리킴

	return 0;
}


/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;
	
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	while (n->rlink != NULL )									  // n이 마지막 노드가 되면 while문 탈출
	{
		n = n->rlink;															
	}
	node->llink = n;											  // node llink가 선행노드인 n을 가리킴
	n->rlink = node;											  // n의 rlink가 후속노드인 node를 가리킴

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL) 
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;											//선행노드 역할 trail

	while (n != NULL)
	{
		if (n->key >= key)											// 입력받은 key값보다 큰 key를 가진 노드 n
		{
			if (n == h->first)										// n이 헤더가 가리키는 노드일때
			{
				node->rlink = n;									// node의 rlink가 후속노드인 n을 가리킴
				n->llink = node;									// n의 llink가 선행노드인 node를 가리킴
				h->first = node;									// 헤더가 node를 가리킴
			}
			else													// 중간이나 마지막 노드일때
			{
				node->rlink = n;									// node의 rlink,llink가 각각 후속,선행노드를 가리킴 
				node->llink = trail;								
				trail->rlink = node;								// node가 삽입됨에 따라 선행,후속 노드들의 rlink, llink가 변함
				n->llink = node;
			}
			return 0;
		}
		trail = n;													// trail이 선행노드 n으로
		n = n->rlink;												// n이 rlink가 가리키는 선행노드로 
	}

	node->llink = trail;											// 입력받은 key값이 가장 클경우
	trail->rlink = node;											// 마지막 노드로 삽입됨  

	return 0;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	
	if (h->first == NULL)
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}

	listNode* n = h->first;										   
	listNode* trail = NULL;

	if (n->rlink == NULL)										   // 노드가 하나일때
	{
		h->first = NULL;
		free(n);												   // 유일한 노드 메모리해제
		return 0;
	}

	while (n->rlink != NULL)									   // 노드가 하나 이상일때 n이 마지막노드가 될때까지
	{
		trail = n;												   
		n = n->rlink;
	}
	trail->rlink = NULL;										   // 마지막노드 n의 선행노드인 trail의 마지막노드가 되도록
	free(n);													   // trail의 rlink가 NULL을 담게하고 n의 메모리해제 

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}

	listNode* n = h->first;

	h->first = n->rlink;										 // 헤더가 n의 후속노드 가리킴
	free(n);													 // n의 메모리해제


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	while (n != NULL)
	{
		if (n->key == key)
		{
			if (n == h->first && n->rlink != NULL)			 //후속노드가 있는 첫노드일때
			{
				h->first = n->rlink;						 //헤더가 n의 후속노드를 가리키게함
				n->rlink->llink = NULL;						 //n을 가리키는 후속노드의 llink를 NULL값으로
			}
			else if (n == h->first && n->rlink == NULL)		 //후속노드가 없는 첫노드일때
			{
				h->first = n->rlink;						 //n의 후속노드를 가리키게함
			}
			else if (n != h->first && n->rlink == NULL)		 //후속노드가 없는 마지막노드(첫노드와 구분)
			{	
				trail->rlink = n->rlink;					 //선행노드가 n의 rlink 즉 NULL을 가리킴
			}
			else											 //중간노드일때
			{
				trail->rlink = n->rlink;					 //선행노드의 rlink가 n의 후속노드 가리킴
				n->rlink->llink = trail;					 //n을 가리키는 후속노드의 llink가 n의 선행노드 가리킴
			}
			free(n);
			return 0;
		}
		trail = n;
		n = n->rlink;
	}
	
	printf("해당 키값에 대한 노드가 없습니다.\n");
	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	
	
	listNode* lead = h->first;									
	listNode* middle = NULL;
	listNode* trail;

	while (lead != NULL)
	{
		trail = middle;
		middle = lead;
		lead = lead->rlink;
		
		/* middle노드의 llink가 후속노드 lead를 
		rlink가 선행노드 trail을 가리키게하여	역순으로 재배치됨 */
		middle->llink = lead;									 
		middle->rlink = trail;									 
	}															 
	h->first = middle;

	return 0;
}




