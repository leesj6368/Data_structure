#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 10
#define MAX_QUEUE_SIZE 100 
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct GraphNode // 연결리스트이므로 노드 생성을 위한 구조체
{
	int vertex; //정점=데이터필드
	struct GraphNode* link; //링크필드
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES]; //헤드 포인터들을 저장할 배열, 헤드 포인터 수 = 정점 수
} GraphType;

typedef int element;
typedef struct {
	element  queue[MAX_QUEUE_SIZE]; //bfs 구현을 위한 큐 구조체
	int  front, rear;
} QueueType;

///////////함수선언//////////////////

//DFS//
void graph_init(GraphType* g); //그래프 초기화
void insert_vertex(GraphType* g, int v); //정점 삽입
void insert_edge(GraphType* g, int u, int v); //간선 삽입
void dfs_list(GraphType* g, int v);// 깊이우선탐색
//BFS//
void init(QueueType* q); //큐 초기화
int is_empty(QueueType* q); //비었는지 확인
int is_full(QueueType* q); // 찼는지 확인
void enqueue(QueueType* q, element item); //큐에 데이터 입력
element dequeue(QueueType* q); //큐에서 삭제
element peek(QueueType* q);//큐에서 삭제
void bfs_list(GraphType* g, int v); //너비우선탐색

void Print_Graph();
void error(char* message) //에러 메시지 출력
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void graph_init(GraphType* g) // 그래프 초기화 
{
	int v;
	g->n = 0;//그래프의 정점을 0으로 하고
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;//v를 최대 정점의 수까지 반복하면서 그래프를 NULL로 초기화한다.
}

void insert_vertex(GraphType* g, int v) // 정점 삽입 연산
{
	if (((g->n) + 1) > MAX_VERTICES) { //정점을 삽입할때 최대 정점수 보다 많으면 삽입을 취소
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;//최대 정점수보다 많지 않으면 정점수를 +1 한다.
}
void insert_edge(GraphType* g, int u, int v) // 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
{
	GraphNode* node;
	if (u >= g->n || v >= g->n) {//출발점이나 도착점이 현재 정점 n번 보다 크거나 같다면(간선을 이을 수 없는상태)
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));//노드에 동적메모리를 할당하고
	node->vertex = v;
	node->link = g->adj_list[u]; //간선을 삽입하고 노드를 해당 헤드 포인터 리스트에 연결시킨다.
	g->adj_list[u] = node;
}

void init(QueueType* q) {//큐 초기화
	q->front = q->rear = 0;
}
int is_empty(QueueType* q) { //큐의 공백상태 확인
	return (q->front == q->rear);
}
int is_full(QueueType* q) { // 큐가 다 찼는지 아닌지 확인
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {//큐 삽입
	if (is_full(q))
		printf("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;//q->rear = (q->rear + 1) % MAX_QUEUE_SIZE 위치로 이동하고 이동한 자리에 삽입할 item을 넣어준다.
	q->queue[q->rear] = item;
}
element dequeue(QueueType* q) {//큐 삭제
	if (is_empty(q))
		printf("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;//front를 다음 자리로 넘겨주고 그 자리에 있던 원소를 반환해 삭제
	return q->queue[q->front];
}
element peek(QueueType* q) {//큐 삭제 함수
	if (is_empty(q))
		printf("큐가 공백상태입니다");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}

void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE; // 정점 v 방문 표시 
	printf("%d ", v);
	for (w = g->adj_list[v]; w; w = w->link)// 인접 정점 탐색 
		if (!visited[w->vertex])//// 미방문 정점 탐색 
			dfs_list(g, w->vertex); //정점 w에서 DFS 새로시작
}

void bfs_list(GraphType* g, int v)
{
	GraphNode* w;
	QueueType q;
	init(&q);   // 큐 초기 화 
	visited[v] = TRUE;  // 정점 v 방문 표시 
	printf("%d ", v);  // 방문한 정점 출력 
	enqueue(&q, v); // 시작정점을 큐에 저장 
	while (!is_empty(&q)) {
		v = dequeue(&q);// 큐에 저장된 정점 선택 
		for (w = g->adj_list[v]; w; w = w->link) //인접 정점 탐색
			if (!visited[w->vertex]) {	// 미방문 정점 탐색 
				visited[w->vertex] = TRUE;   // 방문 표시
				printf("%d ", w->vertex);
				enqueue(&q, w->vertex);	//정점을 큐에 삽입
			}
	}
}


///////////////////////////////
int main()
{

	GraphType* g = NULL;
	int u, v;
	char command;
	int key;
	printf("[----- [leeseonjue] [2021041042] -----]");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("Graph Searches \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph = z                                      \n");
		printf(" Insert Vertex = v             Insert Edge = e              \n");
		printf(" Depth First Search = d        Breath First Search = b \n");
		printf(" Print Graph = p              Quit = q \n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);
		switch (command) {
		case 'z': case 'Z':
			graph_init(g);
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &v);
			insert_vertex(g, v);
			break;
		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &u);
			scanf("%d", &v);
			insert_edge(g, u, v);
			break;
		case 'd': case 'D':
			dfs_list(g, v); 
			break;
		case 'b': case 'B':
			bfs_list(g, v);
			break;
		case 'p': case 'P':
			Print_Graph();
			break;
		}
	} while (command != 'q' && command != 'Q');
	return 1;
}