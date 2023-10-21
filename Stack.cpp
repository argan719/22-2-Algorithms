

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "Stack.h"

// 스택 초기화
void init(StackType *s)
{
	s->top = -1;
}

// 공백 상태 검출 
int is_empty(StackType *s)
{
	return (s->top == -1);
}

// 포화 상태 검출 
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(StackType *s, element item)
{
	if (is_full(s)) {
		printf("스택 포화 에러\n");				
		return;
	}
	else s->stack[++(s->top)] = item;
}

// 삭제 함수(삭제 후 반환)
element pop(StackType *s)
{
	if (is_empty(s)) {
		printf("스택 공백 에러\n");				
		exit(1);
	}
	else return s->stack[(s->top)--];
}
