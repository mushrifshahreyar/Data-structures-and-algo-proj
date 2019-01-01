#include<stdio.h>
#include<stdlib.h>

char* PUSH(int k,char set[100]) {
	char s;
	
	printf("\nEnter the character to be pushed :");
	scanf(" %c",&s);
	set[k] = s;
	return set;
}

char* POP(int k,char set[100]) {
	if(k!=0) {
		set[k-1]='\0';
	}
	else {
		printf("\nEMPTY");
	}
	return set;
}

void print(char* set) {
	for(int i=0; set[i] != '\0'; ++i) {
		printf("%c",set[i]);
	}
	printf("\n");
}
	
	
void main() {
	char pushed[100];
	int option,i=0;
	while(1) {
		printf("\nPUSH\nPULL\nPRINT\nEXIT\n");
		printf("\nEnter the option: ");
		scanf("%d",&option);
		switch(option) {
			case 1: *pushed = PUSH(i,pushed); i++; break;
			case 2: *pushed = POP(i,pushed); break;
			case 3: print(pushed); break;
			case 4: exit(0); break;
			default : printf("\nPlease enter the valid option\n");
		}
	}
}
