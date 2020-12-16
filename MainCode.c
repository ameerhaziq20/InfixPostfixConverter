// C program to convert infix expressionression to postfix 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

// Declare the stack type 
struct Stack 
{ 
	int top; 
	unsigned capacity; 
	int* array; 
}; 

// Stack creation
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


//check if operand
int isOperand(char ch) 
{ 
	return (ch >= 'a' && ch <= 'z') || 
		(ch >= 'A' && ch <= 'Z'); 
} 

//return precedence
int Precedence(char ch) 
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

	// Create a stack of capacity equal to expressionression size 
	struct Stack* stack = createStack(strlen(expression)); 
	//check if stack is created
	if(!stack) 
		return -1 ; 

	for (i = 0, k = -1; expression[i]; ++i) 
	{ 
		
		// If the scanned character is 
		// an operand, add it to output. 
		if (isOperand(expression[i])) 
			expression[++k] = expression[i]; 
		
		// If the scanned character is an 
		// ‘(‘, push it to the stack. 
		else if (expression[i] == '(') 
			push(stack, expression[i]); 
		
		// If the scanned character is an ‘)’, 
		// pop and output from the stack 
		// until an ‘(‘ is encountered. 
		else if (expression[i] == ')') 
		{ 
			while (!isEmpty(stack) && peek(stack) != '(') 
				expression[++k] = pop(stack); 
			if (!isEmpty(stack) && peek(stack) != '(') 
				return -1; // invalid expressionression			 
			else
				pop(stack); 
		} 
		else // an operator is encountered 
		{ 
			while (!isEmpty(stack) && 
				Precedence(expression[i]) <= Precedence(peek(stack))) 
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
