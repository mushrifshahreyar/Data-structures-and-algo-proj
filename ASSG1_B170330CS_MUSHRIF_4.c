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
node insert(node head,FILE *fp) {
	int val;
	//printf("\nEnter the value :");
	fscanf(fp,"%d",&val);
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
		printf("\nNIL");
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
		printf("\nNIL");
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
		printf("\nNot found");
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
	FILE *fp;
	fp = fopen("input.txt","r");
	int val;
	node head = NULL;
	node x;	
	while(1) {
		fscanf(fp,"%s",option);
		printf("\nOption - %s",option);
		if(feof(fp)) {
			break;
		}
		if(strcmp(option,"insr") == 0) {
			head = insert(head,fp);
		}
		else if(strcmp(option,"minm") == 0) {
			if(head == NULL) {
				printf("NIL");
			}
			else {
				node x = minimum(head);
				printf("\n%d",x->data);
			}
		}
		else if(strcmp(option,"maxm") == 0) {
			if(head == NULL) {
				printf("\nNIL");
			}
			else {
				node x = maximum(head);
				printf("\n%d",x->data);
			}
		}
		else if(strcmp(option,"inor") == 0) {
			printf("\n");
			inorder_tree(head);
		}
		else if(strcmp(option,"prer") == 0) {
			printf("\n");
			preorder_tree(head);
		}
		else if(strcmp(option,"post") == 0) {
			printf("\n");
			postorder_tree(head);
		}
		else if(strcmp(option,"srch") == 0) {
			//printf("\nEnter the key :");
			int val;
			fscanf(fp,"%d",&val);
			tree_search(head,val);
		}
		else if(strcmp(option,"succ") == 0) {
			//printf("\nEnter the element :");
			fscanf(fp,"%d",&val);
			x = successor(head,val);
			if(x != NULL)
				printf("\nSuccessor is : %d",x->data);
		}
		else if(strcmp(option,"pred") == 0) {
			//printf("\nEnter the element :");
			fscanf(fp,"%d",&val);
			x = predessor(head,val);
			if(x != NULL) 
				printf("\nPredessor is : %d",x->data);
		}
		else if(strcmp(option,"delt") == 0) {
			//printf("\nEnter the element :");
			fscanf(fp,"%d",&val);
			head = delete(head,val);
		}
		else if(strcmp(option,"stop") == 0) {
			break;
		}
		
	}
}	
