#include <stdio.h>
int main()
{
    int i, *p; //���� ����i�� �����ͺ��� p ����
    i = 10; //i�� 10���� �ʱ�ȭ
    printf("value of i = %d\n", i); //i ���� 10���� ���·� ���
    printf("address of i = %p\n", &i); //i�� �ּҰ� ���
    printf("value of p = %p\n", p); //p�� �� ���
    printf("address of p = %p\n", &p); //p�� �ּҰ� ���
    p = &i; //���� i�� �ּҸ� p�� ����
    printf("\n\n----- after p = &i ------------\n\n"); //�������
    printf("value of p = %p\n", p); // p�� ���
    printf("address of p = %p\n", &p); //p�� �ּҰ� ���
    printf("dereferencing *p = %d\n", *p); //p�� ������ ���
    printf("�ȳ��ϼ���");
    return 0;
}
