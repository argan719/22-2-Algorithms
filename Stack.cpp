

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "Stack.h"

// ���� �ʱ�ȭ
void init(StackType *s)
{
	s->top = -1;
}

// ���� ���� ���� 
int is_empty(StackType *s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� 
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// ���� �Լ�
void push(StackType *s, element item)
{
	if (is_full(s)) {
		printf("���� ��ȭ ����\n");				
		return;
	}
	else s->stack[++(s->top)] = item;
}

// ���� �Լ�(���� �� ��ȯ)
element pop(StackType *s)
{
	if (is_empty(s)) {
		printf("���� ���� ����\n");				
		exit(1);
	}
	else return s->stack[(s->top)--];
}
