#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 


//declare stack type
struct Stack 
{ 
	int top; 
	unsigned capacity; 
	int* array; 
}; 

//stack creation
struct Stack* createStack( unsigned capacity ) 
{ 
	struct Stack* stack = (struct Stack*) 
		malloc(sizeof(struct Stack)); 

	if (!stack) 
		return NULL; 

	stack->top = -1; 
	stack->capacity = capacity; 

	stack->array = (int*) malloc(stack->capacity * 
								sizeof(int)); 

	return stack; 
} 
int isEmpty(struct Stack* stack) 
{ 
	return stack->top == -1 ; 
} 
char peek(struct Stack* stack) 
{ 
	return stack->array[stack->top]; 
} 
char pop(struct Stack* stack) 
{ 
	if (!isEmpty(stack)) 
		return stack->array[stack->top--] ; 
	return '$'; 
} 
void push(struct Stack* stack, char op) 
{ 
	stack->array[++stack->top] = op; 
} 


//scanned character is operand
int operand_true(char ch) 
{ 
	return (ch >= 'a' && ch <= 'z') || 
		(ch >= 'A' && ch <= 'Z'); 
} 

//return precedence
int precedence(char ch) 
{ 
	switch (ch) 
	{ 
	case '+': 
	case '-': 
		return 1; 

	case '*': 
	case '/': 
		return 2; 

	case '^': 
		return 3; 
	} 
	return -1; 
} 


//conversion functions
int InfixPostfix(char* expression) 
{ 
	int i, k; 

	struct Stack* stack = createStack(strlen(expression)); 
	//check if stack is created
	if(!stack) 
		return -1 ; 

	for (i = 0, k = -1; expression[i]; ++i) 
	{ 
		
		//add it to output if the scanned character is an operand 
		if (operand_true(expression[i])) 
			expression[++k] = expression[i]; 
		
		//push it to the stack if character is '(' 
		else if (expression[i] == '(') 
			push(stack, expression[i]); 
		
		// if character is ‘)’, pop and output from the stack until found ‘(‘ . 
		else if (expression[i] == ')') 
		{ 
			while (!isEmpty(stack) && peek(stack) != '(') 
				expression[++k] = pop(stack); 
			if (!isEmpty(stack) && peek(stack) != '(') 
				return -1; 
				// expression is invalid			 
			else
				pop(stack); 
		} 
		// character is operator
		else 
		{ 
			while (!isEmpty(stack) && 
				precedence(expression[i]) <= precedence(peek(stack))) 
				expression[++k] = pop(stack); 
			push(stack, expression[i]); 
		} 

	} 

	// pop all the operators from the stack 
	while (!isEmpty(stack)) 
		expression[++k] = pop(stack ); 

	expression[++k] = '\0'; 
	printf( "%s", expression ); 
} 

// Main Function
int main() 
{ 	
	int i;
	char expression[25];

	printf("Enter Infix expression: ");

	scanf("%s", &expression[i]);
 
	InfixPostfix(expression); 
	return 0; 
} 
