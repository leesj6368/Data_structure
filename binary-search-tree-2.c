#include <stdio.h>
#include <stdlib.h>

typedef struct node {//노드 구조체
	int key;
	struct node *left;//왼쪽노드
	struct node *right;//오른쪽 노드
} Node;

#define MAX_STACK_SIZE	20 /* for stack *///스택을 위한 것
Node* stack[MAX_STACK_SIZE];//스택에 관한 노드 생성
int top = -1;

Node* pop();//팝
void push(Node* aNode);//푸쉬

#define MAX_QUEUE_SIZE	20 /* for queue *///큐를 위한 것
Node* queue[MAX_QUEUE_SIZE];//큐에 관한 노드 생성
int front = -1;//큐는 front와 rear이 필요함
int rear = -1;

Node* deQueue();//Dequeue(덱)은 양쪽에서 넣고 빼고가 가능한 특이한 큐
void enQueue(Node* aNode);

int initializeBST(Node** h);//이진탐색트리 초기화
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

void printStack();//스택 출력 함수
int main()
{
	char command;
	int key;
	Node* head = NULL;//head를 0으로 초기화

	printf("[----- [2021041042] [leeseonjue] -----]");
	do{
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

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);//이진탐색트리 초기화
			break;
		case 'q': case 'Q':
			freeBST(head);//이짐탐색트리 동적메모리 해제
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);//head에 key 값 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);//노드 삭제
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);//재귀순서
			break;
		case 't': case 'T':
			iterativeInorder(head->left);//반복순서
			break;

		case 'l': case 'L':
			levelOrder(head->left);//트리의 레벨 순서대로 순회
			break;

		case 'p': case 'P':
			printStack();//스택 출력
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {//이진탐색트리 초기화

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));//동적메모리로 헤드노드 생성
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;//헤드노드의 right가 헤드노드를 가리키도록
	(*h)->key = -9999;

	top = -1;//초기화
	front = rear = -1;

	return 1;
}

void recursiveInorder(Node* ptr)//중위탐색 순환
{
	if(ptr) {
		recursiveInorder(ptr->left);//ptr이 left를 가리킴
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);//ptr이 right를 가리킴
	}
}

void iterativeInorder(Node* node)//반복중위탐색 순환
{
	for(;;)
	{
		for(; node; node = node->left)
			push(node);//노드에 푸쉬
		node = pop();//노드에 팝

		if(!node) break;
		printf(" [%d] ", node->key);

		node = node->right;
	}
}

void levelOrder(Node* ptr)//트리의 레벨 순서대로 순회
{
	// int front = rear = -1;
	if(!ptr) return; /* empty tree */
	enQueue(ptr);

	for(;;)
	{
		ptr = deQueue();//Dequeue(덱)은 양쪽에서 넣고 빼고가 가능한 특이한 큐, 데이터를 출력하는 큐
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left)
				enQueue(ptr->left);//데이터를 입력하는 큐, ptr의 left에 데이터 입력
			if(ptr->right)
				enQueue(ptr->right);//데이터를 입력하는 큐, ptr의 right에 데이터 입력
		}
		else
			break;
	}
}

int insert(Node* head, int key)//노드의 헤더에 키 삽입
{
	Node* newNode = (Node*)malloc(sizeof(Node));//동적메모리로 새로운 노드 생성
	newNode->key = key;//노드에 키값 넣고
	newNode->left = NULL;//left, right 모두 null로 초기화
	newNode->right = NULL;

	if (head->left == NULL) {//헤드의 left가 비어있다면
		head->left = newNode;//left에 새로운 노드 삽입
		return 1;
	}
	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;//부모노드 초기화
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)//부모노드의 키값이 삽입된 값보다 크면
		parentNode->left = newNode;//부모노드의 left에 새로운 노드 삽입
	else
		parentNode->right = newNode;//부모노드의 right에 새로운 노드 삽입
	return 1;
}


int deleteNode(Node* head, int key)//노드 삭제
{
	if (head == NULL) {//비어있다면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left;
	Node* parent = NULL;//부모 null로 초기화
	Node* ptr = root;//ptr 노드가 root를 가리킴

	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;	/* save the parent */

			if(ptr->key > key)//key값이 크면
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}
	if(ptr->left == NULL && ptr->right == NULL)//ptr 노드의 left와 right가 비어있다면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)
				parent->left = NULL;//parent의 left를 초기화
			else
				parent->right = NULL;////parent의 right를 초기화
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;
		}
		free(ptr);//메모리 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))//ptr의 left와 right가 비어있다면
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;//child노드는 ptr의 left를 가리킴
		else
			child = ptr->right;//child 노드는 ptr의 right를 가리킴
		if(parent != NULL)//부모노드가 안비었으면
		{
			if(parent->left == ptr)
				parent->left = child;//부모노드의 left는 child 노드 가리킴
			else
				parent->right = child;////부모노드의 right는 child 노드 가리킴
		} else {
			root = child;//루트는 child 노드
		}
		free(ptr);
		return 1;
	}

	Node* candidate;//후보 노드 생성
	parent = ptr;
	candidate = ptr->right;
	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)//후보 노드의 left가 0이 아니면
	{
		parent = candidate;//parent노드는 후보 노드를 가리키고
		candidate = candidate->left;//후보노드는 후보노드의 left를 가리킴
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)//부모노드의 right와 후보노드가 같으면
		parent->right = candidate->right;//같음
	else
		parent->left = candidate->right;//같지 않으면 부모노드의 left가 후보노드의 right 가르킴

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;

	free(candidate);
	return 1;
}


void freeNode(Node* ptr)//노드의 동적메모리 할당을 해제
{
	if(ptr) {
		freeNode(ptr->left);//ptr의 left와 right를 freeNode 함수를 통해 노드를 해제함
		freeNode(ptr->right);
		free(ptr);//ptr 노드 해제
	}
}

int freeBST(Node* head)//이진탐색트리 해제
{

	if(head->left == head)//head노드의 left가 head를 가리키면
	{
		free(head);//헤드노드를 해제한다
		return 1;
	}
	Node* p = head->left;//p노드는 head의 left를 가리킨다

	freeNode(p);//해제
	free(head);//해제
	return 1;
}

Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--];
}

void push(Node* aNode)//aNode에 푸쉬
{
	stack[++top] = aNode;//stack의 top에 push
}


void printStack()//스택 출력
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

Node* deQueue()//양쪽에서 넣고 빼고가 가능한 특이한 큐
{
	if (front == rear) {//front와 rear이 같으면 null 리턴
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;//front에 값 삼입
	return queue[front];//큐의 front 리턴

}

void enQueue(Node* aNode)//큐 삽입함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;//rear에 값 삽입
	if (front == rear) {//front와 rear이 같으면 null 리턴
		// printf("\n....Now Queue is full!!\n");
		return;
	}
	queue[rear] = aNode;//queue의 rear에 aNode 대입
}
