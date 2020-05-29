/*
* Binary Search Tree #2
*
* Data Structures
*
* Department of Computer Science
* at Chungbuk National University
*
*/

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;					   

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
Node* maxKey(Node* ptr);			  /* find maximum value node in subtree */


int main()
{
	printf("[----- [김시민] [2016039081] -----]\n");

	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head->left, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}
								
void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	Node* ptr; 
	/* topt 초기값 설정*/
	top = -1; 
	ptr = node;

	/* break 나올때까지 반복 */
	while (1) 
	{ 
		/* node가 없을때까지 반복 */
		while (node != NULL)
		{ 
			/* push하고 왼쪽 자식노드로 이동*/
			push(node);
			node = node->left;
		} 
		
		/* pop의 리턴값 node에 대입 */
		node = pop();
		/* node가 없으면 반복문 탈출 */
		if (node == NULL)
			break; 
		/* node의 key값 출력하고 오른쪽 자식노드로 이동 */
		printf(" [%d] ", node->key);
		node = node->right;
	}
}

Node* pop()
{							
	Node* node = NULL; 

	/* empty면 종료 */
	if (top == -1)
		return 0;
	
	/* top에 위치한 스택 반환하고 top 감소 */
	node = stack[top]; 
	top -= 1; 
	
	return node;
}

void push(Node* aNode)
{
	/* full이면 종료 */
	if (top >= MAX_STACK_SIZE - 1) 
		return 0;

	/* top 증가하고 스택에 적재 */
	top += 1; 
	stack[top] = aNode;
}
																									
/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	
	if (ptr == NULL)
		return 0;
	/* 큐에 ptr 추가 */
	enQueue(ptr);

	while (1)
	{ 
		/* 큐에 있는 값 반환 */
		ptr = deQueue();
		/* 더이상 노드 없을 시 종료 */
		if (ptr == NULL)
		{
			break;
		}
		printf(" [%d] ", ptr->key);
		
		/* 왼쪽 자식노드 있을경우 왼쪽 자식노드값 큐에 추가 */
		if (ptr->left != NULL)
			enQueue(ptr->left);

		/* 오른쪽 자식노드 있을경우 오른쪽 자식노드값 큐에 추가 */
		if (ptr->right != NULL)
			enQueue(ptr->right);
	}

}

Node* deQueue()
{
	Node* node = NULL; 
	
	/* 공백상태시 종료 */
	if (front == rear)
		return 0;

	/* front 증가하고 front에 위치한 큐 반환 */
	front += 1; 
	node = queue[front];

	return node;

}

void enQueue(Node* aNode)
{
	/* 포화상태시 종료 */
	if (rear == MAX_QUEUE_SIZE - 1)
		return 0;
	/* rear 증가하고 aNode 큐에 추가 */
	rear += 1; 
	queue[rear] = aNode;
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* root=head;
	
	if (root == NULL)
	{
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}

	/* 키값이 루트노드보다 작을경우 왼쪽 서브트리로 순환 */
	if (root->key > key)
		deleteNode(root->left, key);
		/* 키값이 루트노드보다 클경우 오른쪽 서브트리로 순환 */
	else if (root->key < key)
		deleteNode(root->right, key);

	else
	{
		/* case 1 */
		if (root->left = NULL && root->right == NULL)
		{
			free(root);
			root = NULL;
		}

		/* case 3 */
		else if (root->left != NULL && root->right != NULL)
		{
			Node* temp = maxKey(root->left);

			root->key = temp->key;
			deleteNode(root->left, temp->key);
		}

		/* case 2 */
		else
		{
			Node* child = (root->left) ? root->left : root->right;
			Node* cur = root;

			root = child;
			free(cur);
			cur = NULL;
		}
	}
	return root;
}

Node* maxKey(Node* ptr)
{
	Node* cur = ptr;
	/* 오른쪽 자식노드가 없을때까지 오른쪽 자식노드로 이동 */
	while (cur->right != NULL)
	{
		cur = cur->right;
	}
	return cur;
}

void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}