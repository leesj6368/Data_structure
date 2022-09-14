#include<stdio.h>
#include<stdlib.h>
typedef struct Node {//노드 구조체 선언
	int key;
	struct Node* link;
} listNode;

typedef struct Head {//헤드 구조체 선언
	struct Node* first;
}headNode;


//함수 선언
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);//first 삽입함수
int insertNode(headNode* h, int key);//hear 삽입함수
int insertLast(headNode* h, int key);//last 삽입함수

int deleteFirst(headNode* h);//first 삭제 함수
int deleteNode(headNode* h, int key);//node 삭제 함수
int deleteLast(headNode* h);//last 삭제 함수
int invertList(headNode* h);//리스트를 거꾸로

void printList(headNode* h);//list 출력 함수

int main()
{
    printf("[----- [leeseonjue] [2021041042] -----]");

	char command;
	int key;
	headNode* headnode=NULL;//hear node 초기화

	do{//메뉴출력
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);//헤드 초기화
			break;
		case 'p': case 'P':
			printList(headnode);//헤드노드 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);//헤드노드에 키 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);//노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);//last 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);//last 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);//first 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);//헤드노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);//리스트 거꾸로 
			break;
		case 'q': case 'Q':
			freeList(headnode);//리스트 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//리스트 해제가 아닌동안에

	return 1;
}

headNode* initialize(headNode* h) {//헤드노드 초기화

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;//초기화
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {//NULL이 아닌 동안
		prev = p;
		p = p->link;//연결리스트
		free(prev);//해제
	}
	free(h);//해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {//노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 동적메모리 할당
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)//first가 비었을때
	{
		h->first = node;//노드생성
		return 0;
	}

	listNode* n = h->first;//리스트노드
	listNode* trail = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {//last 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));//동적메모리할당
	node->key = key;//노드에 키
	node->link = NULL;//초기화

	if (h->first == NULL)
	{
		h->first = node;//first 노드
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {//NULL이 아니면
		n = n->link;
	}
	n->link = node;
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {//FIRST 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));//동적메모리할당
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {//노드 삭제

	if (h->first == NULL)//비었다면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;//h는 FIRST를 가리키고
	listNode* trail = NULL;//trail은 비었다

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {//last 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);//해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n);

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {//first 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;
	free(n);//해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {//거꾸로


	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;//중간 값 NULL로

	while(n != NULL){
		trail = middle;//꼬리와 중간은 같게
		middle = n;//중간을 n으로
		n = n->link;//n이 link 가리키고
		middle->link = trail;//꼬리를 가리키고
	}

	h->first = middle;//처음이 가리키는것은 중간

	return 0;
}


void printList(headNode* h) {//리스트 출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
