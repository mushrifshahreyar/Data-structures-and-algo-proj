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

node create(node head,FILE *fp) {
	int n,val;
	node array;
	/*printf("\nEnter the total number: ");
	scanf("%d",&n);*/
	fscanf(fp,"%d",&n);
	for(int i=0;i<n;++i) {
		fscanf(fp,"%d",&val);
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
void print(node head,FILE *fp) {
	if(head == NULL) {
		fprintf(fp,"\nEmpty List");
		return;
	}
	fprintf(fp,"\n");
	while(head!= NULL) {
		fprintf(fp,"%d ",head->data);
		head = head->next;
	}
}

void h_occur(node head,FILE *fp) {
	node array = head;
	int arr[100],n=0;
	int count=0,maxcount=0,res;
	while(array != NULL) {
		arr[n]=array->data;
		array = array->next;
		n++;
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			if(arr[i] == arr[j]) {
				count++;
			}
		}
		if(count>maxcount) {
			maxcount=count;
			res = arr[i];
		}
		count=0;
	}
	fprintf(fp,"\n%d ",res);
}

node add_node(node head,FILE *fp) {
	int val;
	node array;
	/*printf("\nEnter the element :");
	scanf("%d",&val);*/
	fscanf(fp,"%d",&val);
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
	int count_create=0;
	FILE *f_input,*f_output;
	f_output = fopen("output.txt","w");
	f_input = fopen("input.txt","r");
	while(1) {
		/*printf("\nEnter the option :");
		
		scanf(" %c",&option);*/
		int r = fscanf(f_input," %c",&option);
		if(feof(f_input)) {
			break;
		}
		//printf("\noption : %c\n%d",option,r);	
		switch(option) {
			case 'c': if(count_create > 1) {
						  head = NULL;
					  }
					  head = create(head,f_input);
					  count_create++;
		              break;
			
			case 'p': print(head,f_output); 
					  break;
			
			case 'a': head = add_node(head,f_input);
					  break;
			
			case 'h': h_occur(head,f_output);
					  break;

			case 's': printf("\nThank You for using the program\n");
					  exit(0);
					  break; 
	
			default : printf("\nPlease enter a valid option");
		}
	}
	fprintf(f_output,"\n");
	fclose(f_input);
	fclose(f_output);
}
