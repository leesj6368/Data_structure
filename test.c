#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList { //����ü ����
    int data;
    struct LinkedList* next;
}List;        

List* make_node() {        // ����� ����� �Լ�
    List* newnode = (List*)malloc(sizeof(List));
    newnode->next = NULL;        // ���� �����Ǵ� ����Ʈ�� next�� �׻� NULL
    return newnode;                // ���� �����Ǵ� ����Ʈ(���)�� ��ȯ
}

void add_node(List* head, int value) {        //���Լ��� ������� ����Ʈ�� �߰����ִ� �Լ�
    List* newnode = (List*)malloc(sizeof(List));    // ���ο� ����Ʈ�� �Ҵ�
    List* cur = head;                    // �ݺ��� ���� �����ͺ���
    while (cur != NULL) {            // ������� �����ؼ�
        if (cur->next == NULL) {    // next�� NULL�� ����� 
            cur->next = newnode;    // next ���� ���� ������ ����Ʈ�� ����
            newnode->next = NULL;    // ���� �����Ǵ� ����Ʈ�� next�� �׻� NULL
            newnode->data = value;    // ���� �����Ǵ� ����Ʈ�� ���� �־���
        }
        cur = cur->next;    //if ���� �����ϸ� cur�� next�� NULL�̱� ������ �ݺ����� ��������� �����
    }
}

// ����ü �����ͺ��� h�� NULL�� ����
void free_list(List* head) {        // �Ҵ���� �޸𸮸� ��� �ݳ����ִ� �Լ�
    List* h = head->next;
    while (h->next != NULL) {    // h�� ����Ʈ�� ���� ������ ������ �ݺ�
        List* next = h->next;        // ���� �ٿ��� h������ �Ҵ�� �޸𸮰� ������Ƿ� h�� ������带 next������ ����
        free(h);                // h(���Ḯ��Ʈ) �޸� ���� 
        h = next;                // �����Ǳ��� h�� ���� ��带 �����ߴ� next�� h�� �ٽ� �ҷ���
    }
}

int main() {
    List* head = NULL;        // head�� �ʱⰪ�� NULL�� ����
    if (head == NULL) {        // head�� NULL�� ��� head�� ���ʷ� �����Ǵ� ����Ʈ�� ����Ŵ
        head = make_node();    //    (head�� ����Ʈ�� �̸��̶�� ������ ���� ���� �� ����)
    }
    int n;
    printf("������ ����Ʈ�� ���� �Է�: ");
    scanf("%d", &n);
    for (int i = 1; i < n + 1; i++) {
        add_node(head, i);        //head ����Ʈ�� ���� �Էµ� ���� ���� �������� ��带 �߰��ϴ� �Լ� ����
    }
    List* a = head->next;
    while (a != NULL) {        //����Ʈ�� ������ �Էµ� ������� �����
        printf("%d", a->data);
        a = a->next;
    }
    free_list(head);    // head ����Ʈ���� ���� �����ϴ� ������ �޸� ����
    free(head);            // head�� ��� �޸� ����

    return 0;
}