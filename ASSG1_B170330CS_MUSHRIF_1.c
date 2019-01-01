#include<stdio.h>
#include<stdlib.h>

struct Linked_List {
	int data;
	struct Linked_List *next;
};

typedef struct Linked_List *node;

node Create_node() {
	node temp;
	temp = (node) malloc(sizeof(struct Linked_List));
	if(temp == NULL) {
		printf("\nMemory not alloted");
		exit(0);
	}
	temp->next = NULL;
	return temp;
}

node create(node head) {
	int n,val;
	node array;
	printf("\nEnter the total number: ");
	scanf("%d",&n);
	for(int i=0;i<n;++i) {
		scanf("%d",&val);
		if(head == NULL) {
			head=Create_node();
			array = head;
			array->data = val;
		}
		else {
			array->next = Create_node();
			array=array->next;
			array->data = val;
		}
	}
	return head;
}
void print(node head) {
	if(head == NULL) {
		printf("\nEmpty List\n");
		return;
	}
	while(head!= NULL) {
		printf("%d ",head->data);
		head = head->next;
	}
}

int partition(int arr[],int first,int last) {
	int x = arr[last];
	int i = first-1;
	for(int j = first; j < last; j++) {
		if(arr[j] <= x) {
			i = i+1;
			int swap = arr[i];
			arr[i] = arr[j];
			arr[j] = swap;
		}
	}
	int swap = arr[i+1];
	arr[i+1] = arr[last];
	arr[last] = swap;
	return i+1;
}
void quick_sort(int arr[],int first,int last) {
	if(first < last) {
		int p = partition(arr,first,last);
		quick_sort(arr,first,p-1);
		quick_sort(arr,p+1,last);
	}
}
void h_occur(node head) {
	node array = head;
	int arr[100],n=0;
	while(array != NULL) {
		arr[n]=array->data;
		array = array->next;
		n++;
	}
	//sorting
	quick_sort(arr,0,n-1);
	
	//counting frequency

	int max_count = 1, ele = arr[0], cur_count = 1;
	for(int i=1;i<n;++i) {
		if(arr[i] == arr[i-1]) {
			cur_count++;
		}
		else {
			if(cur_count > max_count) {
				max_count = cur_count;
				ele = arr[i-1];
			}	
			cur_count=1;
		}
	}
	printf("%d ",ele);
}
node add_node(node head) {
	int val;
	node array;
	printf("\nEnter the element :");
	scanf("%d",&val);
	if(head == NULL) {
		head = Create_node();
		array = head;
		array->data = val;
	}
	else {
		array = head;
		while(array->next != NULL) {
			array=array->next;
		}
		array->next = Create_node();
		array = array->next;
		array->data = val;
	}
	return head;
} 
void main() {
	char option;
	node head=NULL;
	while(1) {
		printf("\nEnter the option :");
		
		scanf(" %c",&option);
		
		switch(option) {
			case 'c': head = create(head); 
		              break;
			
			case 'p': print(head); 
					  break;
			
			case 'a': head = add_node(head);
					  break;
			
			case 'h': h_occur(head);
					  break;

			case 's': printf("\nThank You for using the program\n");
					  exit(0);
					  break; 
	
			default : printf("\nPlease enter a valid option");
		}
	}
}
