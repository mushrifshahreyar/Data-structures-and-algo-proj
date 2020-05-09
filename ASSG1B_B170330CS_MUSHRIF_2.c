#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct Linked_List {
	int data;
	struct Linked_List *left;
	struct Linked_List *right;
	struct Linked_List *parent;
}*node;

node create_node() {
	node temp;
	temp = (node) malloc(sizeof(struct Linked_List));
	temp->left = NULL;
	temp->parent = NULL;
	temp->right = NULL;
	return temp;
}
int find_minimum(int a, int b){
	if(a<b) {
		return a;
	}
	else {
		return b;
	}
}
void string_to_array(char *arr_char,int *arr_int,int *n) {
	int k=0;
	int number = -1;
	for(int i=0;;++i) {
		if(isdigit(arr_char[i])) {
			if(number == -1) {
				number = 0;
			}
			number = (number*10)+(arr_char[i]-'0');
			continue;
		}
		if(number != -1) {
			arr_int[k] = number;
			k++;
			number = -1;
		}
		if(arr_char[i] == '\0' || arr_char[i] == '\n') {
			*n = k;
			break;

		}
	}

}
void print(node head,FILE *f_out) {
	node array = head;
	if(head->left->data == head->data) {
		array = array->left;
	}
	else {
		array = array->right;
	}
	if(array->left->data == array->data) {
		//printf("\n%d",array->right->data);
		fprintf(f_out,"%d\n",array->right->data);
		
	}
	else
	{
		//printf("\n%d",array->left->data);
		fprintf(f_out,"%d\n",array->left->data);
	}
}

void store_in_nodearray(node temp,node array[],int i,int min_value,int main_count) {
	temp->data = min_value;
	temp->left = array[i];
	temp->right = array[i+1];
	array[i]->parent = temp;
	array[i+1]->parent = temp;
	array[main_count] = temp;
}
void create_tree(char *str,FILE *f_out) {
	node node_array[200];
	
	int arr_int[1000];
	int n=0;
	string_to_array(str,arr_int,&n);
	//printf("\n");
	// for(int i=0;i<n;++i) {
	// 	printf("%d ",arr_int[i]);
	// }
	for(int i=0;i<n;++i){
		node_array[i] = create_node();
		node_array[i]->data = arr_int[i];
	}
	int main_count = 0;
	int temp_int = n;
	while(temp_int != 1) {
		main_count = 0;
		for(int i=0;i<temp_int;i+=2) {
			node temp = create_node();
			int a = node_array[i]->data;
			int b = node_array[i+1]->data;
			int min_value = find_minimum(a,b);
			store_in_nodearray(temp,node_array,i,min_value,main_count);
			
			main_count++;
		}
		temp_int = main_count;
	}
	node head = node_array[0];
	print(head,f_out);
}
int main() {
	char arr[1000];
	//int n;
	FILE *f_in,*f_out;
	f_in = fopen("input.txt","r");
	f_out = fopen("output.txt","w");
	while(fgets(arr,1000,f_in) != NULL) {
		
		create_tree(arr,f_out);
	}
	fclose(f_in);
	fclose(f_out);
}
