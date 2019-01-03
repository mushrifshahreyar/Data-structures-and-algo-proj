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
void preorder(node root) {
	if(root != NULL) {
		printf("%d ",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

int get_height(node head) {
	if(head == NULL) {
		return 0;
	}
	else {
		int left_height = 0;
		int right_height = 0;
		int maximum = 0;
		left_height = get_height(head->left);
		right_height = get_height(head->right);

		if(right_height > left_height) {
			maximum = right_height;
		}
		else {
			maximum = left_height;
		}
		return maximum+1;
	}
}

int get_diameter(node head) {
	int left_height = get_height(head->left);
	int right_height = get_height(head->right);
	return left_height+right_height+1;
}
int get_width(node root,int level) {
	if(root == NULL) {
		return 0;
	}
	if(level == 1) {
		return 1;
	}
	if(level>1) {
		return get_width(root->left,level-1) + get_width(root->right,level-1);
	}
}
int get_max_width(node root){
	int max_width=0;
	int height = get_height(root);
	for(int i=1;i<=height;i++) {
		if(max_width < get_width(root,i)) {
			max_width = get_width(root,i);
		}
	}
	return max_width;
}
void main() {
	FILE *fp;
	fp = fopen("input.txt","r");
	while(1) {
		char s[100];
		node root = NULL;
		stack stack_new = stack_create();
		fscanf(fp,"%s",s);
		//printf("%s",s);
		int length = strlen(s);
		root = create_binary_tree(stack_new,s,1,length-2);
		printf("\n");
		preorder(root);
		int height = get_height(root);
		printf("\nHeight = %d",height-1);
		
		int d = get_diameter(root);
		printf("\nDiameter = %d",d);

		int width = get_max_width(root);
		printf("\nWidth = %d",width);

		if(feof(fp)) {
			break;
		}
	}
}