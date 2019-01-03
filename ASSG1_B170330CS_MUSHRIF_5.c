#include<stdio.h>
#include<stdlib.h>
struct Binary_tree {
	int data;
	struct Binary_tree *left;
	struct Binary_tree *right;
};

typedef struct Binary_tree *node;

node Create_node(int a) {
	node temp;
	temp = (node) malloc(sizeof(struct Binary_tree));
	if(temp == NULL) {
		printf("\nMemory not alloted");
		exit(0);
	}
	temp->data = a;
	temp->left = temp->right = NULL;
	return temp;
}
int partition(int *a,int first,int last) {
	int key = a[first],point;
	for(int i=first+1;i<=last;i++) {
		if(a[i]>key){
			point = i-1;
			break;
		}
	}
	return point;
}
//KEEPING TRACK OF CREATE_NODE IN BINARY TREE
int node_count=0;
node create_binary_tree(int *a,int first,int last,int size) {
	if(first<=last && first < size) {
		if(node_count >= size) {
			return NULL;
		}
		node root = Create_node(a[first]);
		node_count++;

		if(first == last) {
			printf("FIRST IF first - %d\t last - %d\n",first,last);
			return root;
		}
		int p = partition(a,first,last);
		printf("ELSE IF  first - %d\t last - %d\n",first,last);
		root->left = create_binary_tree(a,first+1,p,size);
		root->right = create_binary_tree(a,p+1,last,size);
		return root;
	}
	else {
		printf("ELSE     first - %d\t last - %d\n",first,last);		
		return NULL;
	}
}
void print_inorder(node root) {
	if(root != NULL) {
		print_inorder(root->left);
		printf("%d ",root->data);
		print_inorder(root->right);
	}
}
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

void main() {
	int a[100];
	int n;
	printf("\nEnter the total no. of elements in the array :");
	scanf("%d",&n);
	for(int i=0;i<n;++i) {
		scanf("%d",&a[i]);
	}	
	/*
	printf("-- ");
	for(int i=0;i<n;++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
	*/
	node root = create_binary_tree(a,0,n-1,n);
	print_inorder(root);
	printf("\n");
	print_tree(root);
	printf("\n");
}
