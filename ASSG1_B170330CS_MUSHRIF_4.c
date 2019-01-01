#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Linked_List {
	int data;
	struct Linked_List *left,*right,*parent;
};
	
typedef struct Linked_List *node;

node Create_node() {
	node temp;
	temp = (node)malloc(sizeof(struct Linked_List));
	if(temp == NULL) {
		printf("\nmemory not alloted\n");
		exit(0);
	}
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	return temp;
}
//INSERTING AN ELEMENT IN THE TREE
node insert(node head) {
	int val;
	printf("\nEnter the value :");
	scanf("%d",&val);
	node z = Create_node();
	z->data = val;
	node y,x;
	y = NULL;
	x = head;
	while(x != NULL) {
		y=x;
		if(z->data < x->data) {
			x = x->left;
		}
		else {
			x = x->right;	
		}
	}
	z->parent = y;
	if( y == NULL) {
		head = z;
	}
	else if(z->data < y->data) {
		y->left = z;
	}
	else {
		y->right = z;
	}
	return head;
} 
//INORDER TREE WALK
void inorder_tree(node head) {
	if(head != NULL) {
		inorder_tree(head->left);
		printf("%d ",head->data);
		inorder_tree(head->right);
	}
}
//PREORDER TREE WALK
void preorder_tree(node head) {
	if(head != NULL) {
		printf("%d ",head->data);
		preorder_tree(head->left);
		preorder_tree(head->right);
	}
}
//POSTORDER TREE WALK
void postorder_tree(node head) {
	if(head != NULL) {
		postorder_tree(head->left);
		postorder_tree(head->right);
		printf("%d ",head->data);
	}
}
//MINIMUM TREE
node minimum(node x) {
	while(x->left != NULL) {
		x = x->left;
	}
	return x;
}
//MAXIMUM TREE
node maximum(node x) {
	while(x->right != NULL) {
		x = x->right;
	}
	return x;
}
//SEARCH
node tree_search(node head,int key) {
	node array=head;
	int found = 0; 
	while(array != NULL) {
		if(key < array->data) {
			array = array->left;
		}
		else if(key > array->data) {
			array = array->right;
		}
		else { 
			if(array->data == key) {
				found = 1;
				break;
			}
		}
	}
	if(found == 1) {
		printf("\nFOUND");
	}
	else {
		printf("\nNOT FOUND");
	}
	if(found == 1) {
		return array;
	}
	else {
		return NULL;
	}
}

//SUCCESSOR 
node successor(node head,int val) {
	node x;
	x = tree_search(head,val);
	if(x == NULL) {
		printf("\nNo such element found");
		return NULL;
	}
	if(x->right != NULL) {
		return minimum(x->right);
	}
	node y = x->parent;
	while(y != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}
//PREDESSOR
node predessor(node head,int val) {
	node x;
	x = tree_search(head,val);
	if(x == NULL) {
		printf("\nNo such element found:");
		return head;
	}
	if(x ->left != NULL) {
		return maximum(x->left);
	}
	node y = x->parent;
	while(y != NULL && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

node delete(node head,int ele) {
	node z = tree_search(head,ele);
	node y=NULL,x=NULL;
	if(z == NULL) {
		printf("\nElement not found\n");
		return NULL;
	}
	if(z->left == NULL || z->right == NULL) {
		y=z;
	}
	else {
		y = successor(head,ele);
	}
	if(y->left != NULL) {
		x = y->left;
	}
	else {
		x = y->right;
	}
	if(x != NULL) {
		x->parent = y->parent;
	}
	if(y->parent == NULL) {
		head = x;
	}
	else if(y == y->parent->left) {
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}
	if(y != z) {
		z->data = y->data;
	}
	return head;
}
void main() {
	
	char option[10];
	int val;
	node head = NULL;
	node x;	
	while(1) {
		printf("\nEnter the option :");
		scanf("%s",option);
		
		if(strcmp(option,"insr") == 0) {
			head = insert(head);
		}
		else if(strcmp(option,"inorder") == 0) {
			inorder_tree(head);
		}
		else if(strcmp(option,"preorder") == 0) {
			preorder_tree(head);
		}
		else if(strcmp(option,"postorder") == 0) {
			postorder_tree(head);
		}
		else if(strcmp(option,"search") == 0) {
			printf("\nEnter the key :");
			int val;
			scanf("%d",&val);
			tree_search(head,val);
		}
		else if(strcmp(option,"successor") == 0) {
			printf("\nEnter the element :");
			scanf("%d",&val);
			x = successor(head,val);
			if(x != NULL)
				printf("\nSuccessor is : %d",x->data);
		}
		else if(strcmp(option,"predessor") == 0) {
			printf("\nEnter the element :");
			scanf("%d",&val);
			x = predessor(head,val);
			if(x != NULL) 
				printf("\nPredessor is : %d",x->data);
		}
		else if(strcmp(option,"delete") == 0) {
			printf("\nEnter the element :");
			scanf("%d",&val);
			head = delete(head,val);
		}
		
	}
}	
