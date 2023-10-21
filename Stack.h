

#ifndef STACK
# define STACK

# define MAX_STACK_SIZE 100

typedef struct {
	int xpos;
	int ypos;
}pos;

typedef pos element;				

typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

void init(StackType *s);
int is_empty(StackType *s);
int is_full(StackType *s);
void push(StackType *s, element item);
element pop(StackType *s);

#endif