#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//---------BINARY TREE------------//
typedef struct Binary_Tree {
	int data;
	struct Binary_Tree *left,*right;
}*node;

//----------STACK CREATED---------//
typedef struct Stack {
	char array[100];
	int top;
}*stack;

//---------Function for Create stack -------//
stack stack_create() {
	stack temp = (stack)malloc(sizeof(struct Stack));
	temp->top = -1;
	return temp;
}

//---------Push Stack Function -------------//
void stack_push(stack x,char ch) {
	x->top++;
	x->array[x->top] = ch;
}	

//---------Checking whether the stack is empty or not ----------//
int stack_isEmpty(stack x) {
	return x->top == -1;
}

//---------POP stack  function --------------//
char stack_pop(stack x) {
	if(!stack_isEmpty(x)) {
		char ch = x->array[x->top];
		x->top--;
		return ch;
	}
	printf("Underflow!\n");
	return 0;
}

//------Creating node for binary tree-----------//
node Create_node(int ele) {
	node temp = (node)malloc(sizeof(struct Binary_Tree));
	if(temp == NULL) {
		printf("\nMemory not alloted");
		exit(0);
	}
	temp->data = ele;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

int find_index(stack x,char *s,int first,int last) {
	if(first>last) {
		return -1;
	}
	for(int i=first;i<=last;i++) {
		if(s[i] == '(') {
			stack_push(x,s[i]);
		}
		if(s[i] == ')') {
			if(x->array[x->top] == '(') {
				stack_pop(x);
			}
		}
		if(stack_isEmpty(x)) {
			return i;
		}
		
	}
	return -1;
}

//--------------------------Creating Binary Tree----------------------------//
node create_binary_tree(stack stack_new,char *s,int first,int last) {
	if(first > last) {
		return NULL;
	}
	node root = NULL;
	int index = -1;
	if(isdigit(s[first])) {
		int number=0;
		while( isdigit(s[first]) ) {
			number = (number*10) + (s[first]-'0');
			if(s[first+1]=='('||s[first+1]==')' || ((first+1) >last) ) {
				break;
			}
			first++;
			
		}
		//printf("\nnumber - %d",number);
		root = Create_node(number);
	}
	if(s[first+1] == '(' && (first+1)<=last ) {
		index = find_index(stack_new,s,first+1,last);
	}
	if(index != -1) {
		root->left = create_binary_tree(stack_new,s,first+2,index-1);

		root->right = create_binary_tree(stack_new,s,index+2,last);
	}
	return root;
}

//-----------PREORDER Traversal--------//
void print_tree(node root) {
	if(root!=NULL) {
		printf("(%d",root->data);

		print_tree(root->left);

		if(root->left == NULL) {
			printf("()");
		}

		print_tree(root->right);

		if(root->right == NULL) {
			printf("()");
		}
		printf(")");
	}
}
void swap(node root) {
	node swap = NULL;
	swap = root->left;
	root->left = root->right;
	root->right = swap; 
}
void mirror(node root) {
    if(root != NULL) {
		swap(root);
		mirror(root->left);
		mirror(root->right);		
	}
}
void main() {
    char option;
    node root = NULL;
    stack stack_new = stack_create(); 
    while(1) {
        printf("\nEnter the option :");
        scanf(" %c",&option);
		char s[100];
		int length = 0;
        switch(option) {
            case 'c' : printf("\nEnter the string :");
                       scanf("%s",s);
                       length = strlen(s);
                       root = create_binary_tree(stack_new,s,1,length-2); 
					   break;
            case 'p' : if(root == NULL) {
                            printf("()");   
                       }
                       else {
                           print_tree(root);
                       }
					   break;
            case 'm' : mirror(root);
					   print_tree(root);
					   break;
			case 's' : exit(0);
        }
    }
}
		