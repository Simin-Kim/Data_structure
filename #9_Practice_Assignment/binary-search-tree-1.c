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
	printf("[----- [��ù�] [2016039081] -----]\n");
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



void inorderTraversal(Node* ptr)			 //LVR ���
{
	if (ptr != NULL)						 //ptr�� NULL�� �ƴϸ�
	{
		inorderTraversal(ptr->left);		 //reculsive call left child node
		printf("[%d]", ptr->key);			 //parent node ���
		inorderTraversal(ptr->right);		 //reculsive call right child node 
	}
}

void preorderTraversal(Node* ptr)			 //VLR���
{
	if (ptr != NULL)
	{
		printf("[%d]", ptr->key);			 //parent node ���
		preorderTraversal(ptr->left);		 //reculsive call left child node
		preorderTraversal(ptr->right);		 //reculsive call right child node
	}
}

void postorderTraversal(Node* ptr)			 //LRV���
{
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);		 //reculsive call left child node
		postorderTraversal(ptr->right);		 //reculsive call right child node
		printf("[%d]",ptr->key);			 //parent node ���
	}
}


int insert(Node* head, int key)
{
	Node* node = (Node*)malloc(sizeof(Node));		  //���ο� ��� �޸��Ҵ�
	node->key = key;								  //��尪 set
	node->left = NULL;
	node->right = NULL;

	Node* root = head->left;						  //root node

	if (root == NULL)								  //root node�� ���� �� ���ο� ��� root node�� �ϰ� �Լ�����
	{
		head->left = node;
		return 1;
	}

	Node* p = root;									  //parent node point�� pointer
	while (root != NULL)							  //leaf node ���ö����� �ݺ�
	{			 
		p = root;

		if (root->key == key)						  //insert�� key���� node�� key�� ������ �Լ� ����
			return 0;
		else if (root->key > key)					  //node�� key���� insert�� key������ ũ�� left child node��
			root = root->left;
		else										  //node�� key���� insert�� key������ ũ�� right child node��
			root = root->right;
	}
	
	if (p->key > key)								  //parent node�� key���� �� �� left or right child node�� insert
		p->left = node;
	else
		p->right = node;
	
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node* leaf = head->left;

	if (leaf == NULL)									  //root node���� �� �����޽��� ��� �� �Լ�����
	{
		printf("\n Cannot find the node [%d]\n",key);
		return 0;
	}

	Node* p = leaf;										  //parent node point
	Node* anc = NULL;								      //p�� parent node
	while (leaf != NULL)								  //leaf node���ö����� �ݺ�
	{
		anc = p;
		p = leaf;
		if (leaf->key == key)							  //�����Ϸ��� key�� �߰� �� �ݺ��� Ż��
			break;
		else if (leaf->key > key)						  //�����Ϸ��� key���� ���� ��� left child node��
			leaf = leaf->left;
		else if (leaf->key < key)						  //�����Ϸ��� key���� ���� ��� right child node��
			leaf = leaf->right;
	}
	if (leaf == NULL)									  //�����Ϸ��� key�� ���� node ���� �� �����޽��� ��� �� �Լ� ����
	{
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}

	if (leaf->left == NULL && leaf->right == NULL)		  //leaf node���� ���ǹ����� Ȯ��  
	{
		if (anc->left == leaf)							  //left childe node�� �޸����� �� left point �� NULL�� ����
		{
			free(leaf);
			anc->left = NULL;
		}
		else if (anc->right == leaf)					  //right childe node�� �޸����� �� right point �� NULL�� ����
		{
			free(leaf);
			anc->right == NULL;
		}
		return 0;
	}
	else												  //leaf node�� �ƴҽ� �����޽��� ��� �� �Լ� ����
	{
		printf("\nthe node [%d] is not a leaf\n", key);
		return 0;
	}
}

Node* searchRecursive(Node* ptr, int key)		    
{
	if (ptr == NULL)							   //ptr NULL�̸� NULL�� ��ȯ
		return NULL;
																									
	if (ptr->key == key)						   //ptr�� key���� ã������ key�� ������ �� node�� �ּ��� ptr ��ȯ
		return ptr;
	else if (ptr->key > key)					   //ptr�� key������ ���� ��� left child node�� reculsive call
		return searchRecursive(ptr->left, key);
	else										   //ptr�� key������ Ŭ ��� right child node�� reculsive call
		return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)		   
{
	Node* root = head->left;
	
	while (root != NULL)						   //leaf node ���ö����� �ݺ�
	{
		if (root->key == key)					   //root�� key���� ã������ key�� ������ �� node�� �ּ��� root ��ȯ
			return root;
		else if (root->key > key)				   //root�� key�� ���� ���� ��� left child node�� ������
			root = root->left;
		else									   //root�� key�� ���� Ŭ ��� right child node�� ������
			root = root->right;
	}
	return NULL;								   //ã������ key�� ���� ��� NULL ��ȯ
}


int freeBST(Node* head)
{					
	Node* root = head->left;
	Node* p = NULL;						   //parent node�� ����Ű�� ������

	while (root != NULL) 				   
	{
		if (root->left != NULL) 		   //left child node�� NULL�� �ƴҶ�
		{
			Node* left = root->left;	   //letf child node ����Ű�� ������
			root->left = p;				   //left child node�� p�� ����
			p = root;					   //p�� parent node�� point
			root = left;				   //parent node�� left child node��
		}
		else if (root->right != NULL) 	   //right child node�� NULL�� �ƴҶ�
		{
			Node* right = root->right;	   //right child node ����Ű�� ������
			root->left = p;				   
			root->right = NULL;			   //right child node�� NULL��
			p = root;					   //p�� parent node point
			root = right;				   //parent node�� right child node��
		}
		else 							   
		{
			if (p == NULL) 				   //root�� leaf
			{
				free(root);				   //root �޸�����
				root = NULL;			   //NULL������ ä��
			}
			while (p != NULL) 			   //root�� non leaf
			{
				free(root);				   //root �޸�����
				if (p->right != NULL) 	   //right child node�� ������
				{
					root = p->right;	   //parent node�� right child node�� �ٲٰ�
					p->right = NULL;	   //right child node�� NULL�� ä��
					break;
				}
				else 
				{						   //right childe node ������
					root = p;			   //parent node�� p�� point
					p = p->left;		   //p�� left child node point
				}
			}
		}
	}

	free(head);							   //head node �޸�����
	return 0;
}