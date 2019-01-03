#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

//STACK LENGTH
int st_length=0;
void push_stack(int *stack,int k) {
	stack[st_length] = k;
	st_length++;
}

int pop(int *stack) {
	if(st_length != 0) {
		int k=stack[st_length-1];
		st_length--;
		return k;
	}
	else {
		printf("ERR: st_length is 0\n");
	}
}
void evaluate(char *s,int length) {
	int number=-1;
	int stack[100];
	printf("eval: %s\n", s);
	for(int i=0;i<length;++i) {
		if(isdigit(s[i])) {
			if(number == -1) {
				number = 0;
			}
			number = (number*10)+(s[i]-'0');
			continue;
		}

		if(number != -1) {
			push_stack(stack,number);
			number=-1;
		}

		if(s[i] == '+' ||s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'){

			int n1=pop(stack);
			int n2=pop(stack);
			int k;
			switch(s[i]) {
				case '+' : push_stack(stack,n1+n2);
						   break;
				case '-' : push_stack(stack,n2-n1);
						   break;
				case '*' : push_stack(stack,n2*n1);
						   break;
				case '/' : if(n1 != 0) {
							   push_stack(stack,n2/n1);
						   }
						   break;
				case '^' : k = pow(n2,n1);
						   push_stack(stack,k);
						   break;

			}
		}
	}
	int answer = pop(stack);
	printf("\nANSWER = %d",answer);
}	


void main() {
	char s[100];
	int i=0;
	FILE *fp;
	fp = fopen("input.txt","r");
	while(1) {
		char ch = fgetc(fp);
		if(feof(fp)) {
			break;
		}
		if(ch == '\n') {
			s[i] = '\0';
			evaluate(s,i);
		}
		//READING IN A STRING
		s[i] = ch;
		i++;
	}
	s[i] = '\0';
}

