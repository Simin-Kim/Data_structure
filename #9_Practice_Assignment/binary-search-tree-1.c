/*
* Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	printf("[----- [김시민] [2016039081] -----]\n");
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}



void inorderTraversal(Node* ptr)			 //LVR 방식
{
	if (ptr != NULL)						 //ptr이 NULL이 아니면
	{
		inorderTraversal(ptr->left);		 //reculsive call left child node
		printf("[%d]", ptr->key);			 //parent node 출력
		inorderTraversal(ptr->right);		 //reculsive call right child node 
	}
}

void preorderTraversal(Node* ptr)			 //VLR방식
{
	if (ptr != NULL)
	{
		printf("[%d]", ptr->key);			 //parent node 출력
		preorderTraversal(ptr->left);		 //reculsive call left child node
		preorderTraversal(ptr->right);		 //reculsive call right child node
	}
}

void postorderTraversal(Node* ptr)			 //LRV방식
{
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);		 //reculsive call left child node
		postorderTraversal(ptr->right);		 //reculsive call right child node
		printf("[%d]",ptr->key);			 //parent node 출력
	}
}


int insert(Node* head, int key)
{
	Node* node = (Node*)malloc(sizeof(Node));		  //새로운 노드 메모리할당
	node->key = key;								  //노드값 set
	node->left = NULL;
	node->right = NULL;

	Node* root = head->left;						  //root node

	if (root == NULL)								  //root node가 없을 시 새로운 노드 root node로 하고 함수종료
	{
		head->left = node;
		return 1;
	}

	Node* p = root;									  //parent node point할 pointer
	while (root != NULL)							  //leaf node 나올때까지 반복
	{			 
		p = root;

		if (root->key == key)						  //insert할 key값과 node의 key값 같으면 함수 종료
			return 0;
		else if (root->key > key)					  //node의 key값이 insert할 key값보다 크면 left child node로
			root = root->left;
		else										  //node의 key값이 insert할 key값보다 크면 right child node로
			root = root->right;
	}
	
	if (p->key > key)								  //parent node의 key값과 비교 후 left or right child node로 insert
		p->left = node;
	else
		p->right = node;
	
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node* leaf = head->left;

	if (leaf == NULL)									  //root node없을 시 에러메시지 출력 후 함수종료
	{
		printf("\n Cannot find the node [%d]\n",key);
		return 0;
	}

	Node* p = leaf;										  //parent node point
	Node* anc = NULL;								      //p의 parent node
	while (leaf != NULL)								  //leaf node나올때까지 반복
	{
		anc = p;
		p = leaf;
		if (leaf->key == key)							  //삭제하려는 key값 발견 시 반복문 탈출
			break;
		else if (leaf->key > key)						  //삭제하려는 key값이 작을 경우 left child node로
			leaf = leaf->left;
		else if (leaf->key < key)						  //삭제하려는 key값이 작을 경우 right child node로
			leaf = leaf->right;
	}
	if (leaf == NULL)									  //삭제하려는 key값 가진 node 없을 시 에러메시지 출력 후 함수 종료
	{
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}

	if (leaf->left == NULL && leaf->right == NULL)		  //leaf node인지 조건문으로 확인  
	{
		if (anc->left == leaf)							  //left childe node면 메모리해제 및 left point 값 NULL로 수정
		{
			free(leaf);
			anc->left = NULL;
		}
		else if (anc->right == leaf)					  //right childe node면 메모리해제 및 right point 값 NULL로 수정
		{
			free(leaf);
			anc->right == NULL;
		}
		return 0;
	}
	else												  //leaf node가 아닐시 에러메시지 출력 후 함수 종료
	{
		printf("\nthe node [%d] is not a leaf\n", key);
		return 0;
	}
}

Node* searchRecursive(Node* ptr, int key)		    
{
	if (ptr == NULL)							   //ptr NULL이면 NULL값 반환
		return NULL;
																									
	if (ptr->key == key)						   //ptr의 key값과 찾으려는 key값 같으면 그 node의 주소인 ptr 반환
		return ptr;
	else if (ptr->key > key)					   //ptr의 key값보다 작을 경우 left child node로 reculsive call
		return searchRecursive(ptr->left, key);
	else										   //ptr의 key값보다 클 경우 right child node로 reculsive call
		return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)		   
{
	Node* root = head->left;
	
	while (root != NULL)						   //leaf node 나올때까지 반복
	{
		if (root->key == key)					   //root의 key값과 찾으려는 key값 같으면 그 node의 주소인 root 반환
			return root;
		else if (root->key > key)				   //root의 key값 보다 작을 경우 left child node로 내려감
			root = root->left;
		else									   //root의 key값 보다 클 경우 right child node로 내려감
			root = root->right;
	}
	return NULL;								   //찾으려는 key값 없을 경우 NULL 반환
}


int freeBST(Node* head)
{					
	Node* root = head->left;
	Node* p = NULL;						   //parent node를 가리키는 포인터

	while (root != NULL) 				   
	{
		if (root->left != NULL) 		   //left child node가 NULL이 아닐때
		{
			Node* left = root->left;	   //letf child node 가리키는 포인터
			root->left = p;				   //left child node에 p값 대입
			p = root;					   //p가 parent node를 point
			root = left;				   //parent node를 left child node로
		}
		else if (root->right != NULL) 	   //right child node가 NULL이 아닐때
		{
			Node* right = root->right;	   //right child node 가리키는 포인터
			root->left = p;				   
			root->right = NULL;			   //right child node를 NULL로
			p = root;					   //p가 parent node point
			root = right;				   //parent node를 right child node로
		}
		else 							   
		{
			if (p == NULL) 				   //root가 leaf
			{
				free(root);				   //root 메모리해제
				root = NULL;			   //NULL값으로 채움
			}
			while (p != NULL) 			   //root가 non leaf
			{
				free(root);				   //root 메모리해제
				if (p->right != NULL) 	   //right child node가 있으면
				{
					root = p->right;	   //parent node를 right child node로 바꾸고
					p->right = NULL;	   //right child node에 NULL값 채움
					break;
				}
				else 
				{						   //right childe node 없으면
					root = p;			   //parent node가 p값 point
					p = p->left;		   //p는 left child node point
				}
			}
		}
	}

	free(head);							   //head node 메모리해제
	return 0;
}