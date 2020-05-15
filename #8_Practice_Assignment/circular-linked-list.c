/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);
inline int EmptyNode(listNode* h);

void printList(listNode* h);



int main()
{
	
	char command;
	int key;
	listNode* headnode = NULL;
	printf("[----- [김시민] [2016039081] -----]\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
	
	listNode* p = h->rlink;				//첫번째 node point
	listNode* trail = NULL;				//삭제할 node point

	while (p != h)						//headNode 나올때까지 반복
	{
		trail = p;						//p, trail이 point하는 node 변경
		p = p->rlink;					
		free(trail);					//trail이 point하는 node 메모리해제
	}

	free(h);							//headNode 메모리해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));	  //메모리할당하여 node point
	node->key = key;										  //새로운 node에 key값 대입
	node->rlink = NULL;										  //새로운 node link 초기화
	node->llink = NULL;

	if (h->rlink == h)										  //headNode만 있을때
	{
		h->rlink = node;									  //headNode의 link들 node를 point
		h->llink = node;									  
		node->rlink = h;									  //node의 link들 headNode point
		node->llink = h;

		return 0;											  
	}
															  //headNode를 제외한 node 있을때
	h->llink->rlink = node;									  //headNode의 rlink인 node가 새로운 node point 
	node->llink = h->llink;									  //node의 llink가 headNode의 llink인 node point
	h->llink = node;										  //headNode의 llink가 node를 point
	node->rlink = h;										  //node의 rlink가 headNode를 point


	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if (h->rlink == h)										  //headNode만 있을때 에러메시지 출력 후 함수종료
	{
		printf("삭제할 node가 없습니다.\n");				      
		return 0;
	}

	listNode* n = h->llink;									  //마지막 node point
	h->llink = n->llink;									  //headNode의 llink가 마지막 node의 llink인 node point
	n->llink->rlink = h;									  //마지막 node의 llink인 node의 rlink가 headNode point
	
	free(n);
															  //마지막 node 메모리 해제
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));	  //메모리 할당하여 node point
	node->key = key;										  //새로운 node에 key값 대입
	node->llink = NULL;										  //새로운 node link 초기화
	node->rlink = NULL;

	h->rlink->llink = node;									  //headNode의 rlink인 node의 llink가 새로운 node point
	node->rlink = h->rlink;									  //새로운 node의 rlink가 headNode의 rlink인 node point
	node->llink = h;										  //새로운 node의 llink가 headNode point
	h->rlink = node;										  //headNode의 rlink가 새로운 node point


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	
	if (h->rlink == h)										  //headNode만 있을때 에러메시지 출력 후 함수종료
	{
		printf("삭제할 node가 없습니다.\n");
		return 0;
	}

	listNode* n = h->rlink;									  //첫번째 node point
	n->rlink->llink = h;									  //첫번째 node의 rlink인 node의 llink가 headNode point
	h->rlink = n->rlink;									  //headNode의 rlink가 첫번째 node의 rlink인 node point

	free(n);												  //첫번째 node 메모리해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	if (h->rlink == h)										  //headNode만 있을때 함수종료
		return 0;
	
	listNode* lead = h->rlink;
	listNode* middle = NULL;
	listNode* trail = NULL;

	while (middle != h)										  //middle node가 headNode일때까지만 진행
	{
		trail = middle;										  //각 node가 Successor node 포인트
		middle = lead;
		lead = lead->rlink;

		middle->rlink = trail;								  //middle node의 rlink, llink swap
		middle->llink = lead;
	}
	h->llink->rlink = h;									  //headNode의 rlink, llink swap


	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));		   //메모리할당하여 node point
	node->key = key;										       //새로운 node에 key값 대입
	node->rlink = NULL;											   //새로운 node link 초기화
	node->llink = NULL;

	if (h->rlink == h)											   //headNode만 존재할때 headNode의 link들과 
	{															   //새로운 node의 link들 서로 point하고 함수종료
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
		return 0;
	}

	listNode* n = h->rlink;										   //headNode의 rlink인 node point

	while (n != h)												   //n이 headNode를 point할때까지 loop
	{
		if (n->key >= key)										   //n의 key가 입력받은 key 보다 크거나 같을때
		{														   //n의 link들과 새로운 node의 link들 수정 후 함수종료
			n->llink->rlink = node;
			node->llink = n->llink;
			n->llink = node;
			node->rlink = n;
			return 0;
		}
		else													   //n의 key가 더 작을때
			n = n->rlink;										   //Successor node point
	}
																   //입력받은 key가 기존 node들의 key 중 제일 클때
	h->llink->rlink = node;										   //가장 마지막 노드로 삽입
	node->llink = h->llink;
	h->llink = node;
	node->rlink = h;

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	if (h->rlink == h)										  //headNode만 있을때 에러메시지 출력 후 함수종료
	{
		printf("삭제할 node가 없습니다.\n");
		return 0;
	}

	listNode* n = h->rlink;									  //headNode의 rlink인 node point

	while (n != h)											  //point하는 node가 headNode가 될때까지 loop
	{
		if (n->key == key)									  //point하는 node의 key값이 입력받은 key값과 같을 때
		{
			n->rlink->llink = n->llink;						  //해당 node의 양 옆의 link들 서로 point
			n->llink->rlink = n->rlink;
			free(n);										  //해당 node의 메모리해제
			return 0;
		}
		else												  //point하는 node의 key값이 입력받은 key값과 다를 때
			n = n->rlink;									  //Successor node point
	}
	
	printf("해당 key에 대한 node가 없습니다.\n");				  //입력받은 key값을 가진 node가 없을 때 메시지 출력 후 함수 종료

	return 0;
}
