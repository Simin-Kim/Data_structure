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
 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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
	printf("[----- [��ù�] [2016039081] -----]\n");

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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h) {
	
	listNode* p = h->rlink;				//ù��° node point
	listNode* trail = NULL;				//������ node point

	while (p != h)						//headNode ���ö����� �ݺ�
	{
		trail = p;						//p, trail�� point�ϴ� node ����
		p = p->rlink;					
		free(trail);					//trail�� point�ϴ� node �޸�����
	}

	free(h);							//headNode �޸�����
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));	  //�޸��Ҵ��Ͽ� node point
	node->key = key;										  //���ο� node�� key�� ����
	node->rlink = NULL;										  //���ο� node link �ʱ�ȭ
	node->llink = NULL;

	if (h->rlink == h)										  //headNode�� ������
	{
		h->rlink = node;									  //headNode�� link�� node�� point
		h->llink = node;									  
		node->rlink = h;									  //node�� link�� headNode point
		node->llink = h;

		return 0;											  
	}
															  //headNode�� ������ node ������
	h->llink->rlink = node;									  //headNode�� rlink�� node�� ���ο� node point 
	node->llink = h->llink;									  //node�� llink�� headNode�� llink�� node point
	h->llink = node;										  //headNode�� llink�� node�� point
	node->rlink = h;										  //node�� rlink�� headNode�� point


	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
	if (h->rlink == h)										  //headNode�� ������ �����޽��� ��� �� �Լ�����
	{
		printf("������ node�� �����ϴ�.\n");				      
		return 0;
	}

	listNode* n = h->llink;									  //������ node point
	h->llink = n->llink;									  //headNode�� llink�� ������ node�� llink�� node point
	n->llink->rlink = h;									  //������ node�� llink�� node�� rlink�� headNode point
	
	free(n);
															  //������ node �޸� ����
	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));	  //�޸� �Ҵ��Ͽ� node point
	node->key = key;										  //���ο� node�� key�� ����
	node->llink = NULL;										  //���ο� node link �ʱ�ȭ
	node->rlink = NULL;

	h->rlink->llink = node;									  //headNode�� rlink�� node�� llink�� ���ο� node point
	node->rlink = h->rlink;									  //���ο� node�� rlink�� headNode�� rlink�� node point
	node->llink = h;										  //���ο� node�� llink�� headNode point
	h->rlink = node;										  //headNode�� rlink�� ���ο� node point


	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
	
	if (h->rlink == h)										  //headNode�� ������ �����޽��� ��� �� �Լ�����
	{
		printf("������ node�� �����ϴ�.\n");
		return 0;
	}

	listNode* n = h->rlink;									  //ù��° node point
	n->rlink->llink = h;									  //ù��° node�� rlink�� node�� llink�� headNode point
	h->rlink = n->rlink;									  //headNode�� rlink�� ù��° node�� rlink�� node point

	free(n);												  //ù��° node �޸�����

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	if (h->rlink == h)										  //headNode�� ������ �Լ�����
		return 0;
	
	listNode* lead = h->rlink;
	listNode* middle = NULL;
	listNode* trail = NULL;

	while (middle != h)										  //middle node�� headNode�϶������� ����
	{
		trail = middle;										  //�� node�� Successor node ����Ʈ
		middle = lead;
		lead = lead->rlink;

		middle->rlink = trail;								  //middle node�� rlink, llink swap
		middle->llink = lead;
	}
	h->llink->rlink = h;									  //headNode�� rlink, llink swap


	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));		   //�޸��Ҵ��Ͽ� node point
	node->key = key;										       //���ο� node�� key�� ����
	node->rlink = NULL;											   //���ο� node link �ʱ�ȭ
	node->llink = NULL;

	if (h->rlink == h)											   //headNode�� �����Ҷ� headNode�� link��� 
	{															   //���ο� node�� link�� ���� point�ϰ� �Լ�����
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
		return 0;
	}

	listNode* n = h->rlink;										   //headNode�� rlink�� node point

	while (n != h)												   //n�� headNode�� point�Ҷ����� loop
	{
		if (n->key >= key)										   //n�� key�� �Է¹��� key ���� ũ�ų� ������
		{														   //n�� link��� ���ο� node�� link�� ���� �� �Լ�����
			n->llink->rlink = node;
			node->llink = n->llink;
			n->llink = node;
			node->rlink = n;
			return 0;
		}
		else													   //n�� key�� �� ������
			n = n->rlink;										   //Successor node point
	}
																   //�Է¹��� key�� ���� node���� key �� ���� Ŭ��
	h->llink->rlink = node;										   //���� ������ ���� ����
	node->llink = h->llink;
	h->llink = node;
	node->rlink = h;

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	if (h->rlink == h)										  //headNode�� ������ �����޽��� ��� �� �Լ�����
	{
		printf("������ node�� �����ϴ�.\n");
		return 0;
	}

	listNode* n = h->rlink;									  //headNode�� rlink�� node point

	while (n != h)											  //point�ϴ� node�� headNode�� �ɶ����� loop
	{
		if (n->key == key)									  //point�ϴ� node�� key���� �Է¹��� key���� ���� ��
		{
			n->rlink->llink = n->llink;						  //�ش� node�� �� ���� link�� ���� point
			n->llink->rlink = n->rlink;
			free(n);										  //�ش� node�� �޸�����
			return 0;
		}
		else												  //point�ϴ� node�� key���� �Է¹��� key���� �ٸ� ��
			n = n->rlink;									  //Successor node point
	}
	
	printf("�ش� key�� ���� node�� �����ϴ�.\n");				  //�Է¹��� key���� ���� node�� ���� �� �޽��� ��� �� �Լ� ����

	return 0;
}
