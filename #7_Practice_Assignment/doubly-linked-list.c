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
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;

}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		 singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		 - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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

	printf("[----- [��ù�] [2016039081] -----]\n");
	
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

/* singly-linked-list.c ������ �޸� ���������ͷ� �Ű������� �޾ұ⶧���� 
  ���ϰ����� h�� �����ϴ°� �ƴ϶� ������ ���� h�� �ּҸ� �������ش�.*/
int initialize(headNode** h) {										 /* ���������͸� �Ű������� ���� */

	if (*h != NULL)					 								 /* headNode�� �ּҰ� ��� h�� ����Ʈ�Ͽ� NULL�� �ƴϸ� freeList ȣ���Ͽ� �޸����� */
		freeList(*h);

	/* headNode�� ���� �޸� �Ҵ��Ͽ� �� �ּ� h�� �־���*/
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;			

	/* headNode�� ����Ʈ�ϴ� h�� �ּڰ��� �����ϰ��� �ϱ⶧���� h�� ����Ʈ�Ͽ� temp�� �ּڰ����� ����. 
	   ������ ���� ���� �����Ϸ��� ���������͸� �̿��Ͽ� �� �����ͺ����� �ּڰ��� ��� �������ش�.*/
	*h = temp;														 
	return 1;														  
}

/* freeList�Լ������� �����ͺ��� h�� �ּҸ� �������� �ʿ䰡 ���⶧����
	initialize �Լ�ó�� ���������͸� �̿��� �ʿ䰡 ����.
	������ ���������͸� �̿��Ͽ� �Լ��� ������ �� �ֱ��ϴ�.*/
int freeList(headNode* h) {
	listNode* p = h->first;
	listNode* trail=NULL;

	while (p != NULL)
	{
		trail = p;
		p = p->rlink;						/* rlink�� ���� ��带 ����Ű�⶧���� rlink ��� */
		free(trail);						/* �� ����� trail �޸����� */
	}

	free(h);								/* ������ �޸����� */
	return 0;
}

/* ���������͸� �Ű������� �޾����� 
   ����Ϸ��� �Լ� ����ο� main()�Լ� initialize�Լ� ���κκе� ����������� */
/*
int freeList(headNode** h)					//���������ͷ� �Ű����� ������
{
	listNode* p = (*h)->first;				//headNode�� �ּҸ� ���� h�� �������ϴ� *h
	listNode* trail = NULL;

	while (p != NULL)
	{
		trail = p;
		p = p->rlink;
		free(trail);
	}

	free(*h);							   //free���� �޸����� �Ϸ��� ���� �ּҰ� ��ܾ� �ϱ⶧���� *h ���ڷ� �־���
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
		p = p->rlink;								 //���� ��带 ��Ÿ���� rlink
		i++;
	}

	printf("  items = %d\n", i);
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�					
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;										   // �¿� ��ũ ��� NULL������ �ʱ⼳��
	node->llink = NULL;
	
	if (h->first == NULL)									   // �߰��� ��尡 ù����϶�
	{
		h->first = node;
		return 0;
	}

	listNode* n = (listNode*)malloc(sizeof(listNode));
	n = h->first;

	node->rlink = n;										   // ����� rlink�� ���� ù ��忴�� n�� ����Ŵ
	n->llink = node;										   // n�� llink�� node�� ����Ŵ
	h->first = node;										   // ����� list ó�� ��ġ�� �� node�� ����Ŵ

	return 0;
}


/**
 * list�� key�� ���� ����ϳ��� �߰�
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

	while (n->rlink != NULL )									  // n�� ������ ��尡 �Ǹ� while�� Ż��
	{
		n = n->rlink;															
	}
	node->llink = n;											  // node llink�� �������� n�� ����Ŵ
	n->rlink = node;											  // n�� rlink�� �ļӳ���� node�� ����Ŵ

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
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
	listNode* trail = NULL;											//������ ���� trail

	while (n != NULL)
	{
		if (n->key >= key)											// �Է¹��� key������ ū key�� ���� ��� n
		{
			if (n == h->first)										// n�� ����� ����Ű�� ����϶�
			{
				node->rlink = n;									// node�� rlink�� �ļӳ���� n�� ����Ŵ
				n->llink = node;									// n�� llink�� �������� node�� ����Ŵ
				h->first = node;									// ����� node�� ����Ŵ
			}
			else													// �߰��̳� ������ ����϶�
			{
				node->rlink = n;									// node�� rlink,llink�� ���� �ļ�,�����带 ����Ŵ 
				node->llink = trail;								
				trail->rlink = node;								// node�� ���Եʿ� ���� ����,�ļ� ������ rlink, llink�� ����
				n->llink = node;
			}
			return 0;
		}
		trail = n;													// trail�� ������ n����
		n = n->rlink;												// n�� rlink�� ����Ű�� ������� 
	}

	node->llink = trail;											// �Է¹��� key���� ���� Ŭ���
	trail->rlink = node;											// ������ ���� ���Ե�  

	return 0;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	
	if (h->first == NULL)
	{
		printf("������ ��尡 �����ϴ�.\n");
		return 0;
	}

	listNode* n = h->first;										   
	listNode* trail = NULL;

	if (n->rlink == NULL)										   // ��尡 �ϳ��϶�
	{
		h->first = NULL;
		free(n);												   // ������ ��� �޸�����
		return 0;
	}

	while (n->rlink != NULL)									   // ��尡 �ϳ� �̻��϶� n�� ��������尡 �ɶ�����
	{
		trail = n;												   
		n = n->rlink;
	}
	trail->rlink = NULL;										   // ��������� n�� �������� trail�� ��������尡 �ǵ���
	free(n);													   // trail�� rlink�� NULL�� ����ϰ� n�� �޸����� 

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("������ ��尡 �����ϴ�.\n");
		return 0;
	}

	listNode* n = h->first;

	h->first = n->rlink;										 // ����� n�� �ļӳ�� ����Ŵ
	free(n);													 // n�� �޸�����


	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("������ ��尡 �����ϴ�.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	while (n != NULL)
	{
		if (n->key == key)
		{
			if (n == h->first && n->rlink != NULL)			 //�ļӳ�尡 �ִ� ù����϶�
			{
				h->first = n->rlink;						 //����� n�� �ļӳ�带 ����Ű����
				n->rlink->llink = NULL;						 //n�� ����Ű�� �ļӳ���� llink�� NULL������
			}
			else if (n == h->first && n->rlink == NULL)		 //�ļӳ�尡 ���� ù����϶�
			{
				h->first = n->rlink;						 //n�� �ļӳ�带 ����Ű����
			}
			else if (n != h->first && n->rlink == NULL)		 //�ļӳ�尡 ���� ���������(ù���� ����)
			{	
				trail->rlink = n->rlink;					 //�����尡 n�� rlink �� NULL�� ����Ŵ
			}
			else											 //�߰�����϶�
			{
				trail->rlink = n->rlink;					 //�������� rlink�� n�� �ļӳ�� ����Ŵ
				n->rlink->llink = trail;					 //n�� ����Ű�� �ļӳ���� llink�� n�� ������ ����Ŵ
			}
			free(n);
			return 0;
		}
		trail = n;
		n = n->rlink;
	}
	
	printf("�ش� Ű���� ���� ��尡 �����ϴ�.\n");
	return 1;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
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
		
		/* middle����� llink�� �ļӳ�� lead�� 
		rlink�� ������ trail�� ����Ű���Ͽ�	�������� ���ġ�� */
		middle->llink = lead;									 
		middle->rlink = trail;									 
	}															 
	h->first = middle;

	return 0;
}




