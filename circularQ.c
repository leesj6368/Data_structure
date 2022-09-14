#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {//구조체 선언
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();//큐 생성
int freeQueue(QueueType *cQ);//해제
int isEmpty(QueueType *cQ);//empty 상태 함수
int isFull(QueueType *cQ);//full 상태 함수
void enQueue(QueueType *cQ, element item);//원소 넣기
void deQueue(QueueType *cQ, element* item);//원소 삭제
void printQ(QueueType *cQ);//원소 출력
void debugQ(QueueType *cQ);//디버그
element getElement();


int main(void)
{
    printf("[----- [leeseonjue][2021041042] -----]");
	QueueType *cQ = createQueue();//포인터 변수에 큐 생성 함수 대입
	element data;

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();//ㅇ데이터 변수에 원소 넣기
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);//지우기
			break;
		case 'p': case 'P':
			printQ(cQ);//출력
			break;
		case 'b': case 'B':
			debugQ(cQ);//디버그
			break;
		case 'q': case 'Q':
			break;//탈출
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));//동적메모리할당
	cQ->front = 0;//초기화
	cQ->rear = 0;//초기화
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);//동적 메모리 해제
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){//front와 rear이 같다면 빈 상태
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {//큐 full 상태
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;// (cQ->rear + 1)를 MAX_QUEUE_SIZE로 나눈 나머지를 rear에
		cQ->queue[cQ->rear] = item;
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;//(cQ->front + 1)를 MAX_QUEUE_SIZE로 나눈 나머지를 front에 
		*item = cQ->queue[cQ->front];
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//처음
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//마지막

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);//마지막 원소가 아니라면
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);//i와 앞 원소가 같다면 계속 진행
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}