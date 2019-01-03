#include<stdio.h>
#include<stdlib.h>

//FOR STACK 
int k=0;
//FOR PREFIX_EXP
int j=0; 

void pop(char *stack,char *exp) {
//	check_stack(stack);
	if(k!=0) {
		char c = stack[k-1];
		stack[k-1] = '\0';
		k--;
	
//INSERTING INTO POSTFIX EXP
		if(c != '(' && c!= ')') {
			exp[j] = c;
			j++;
		}
	}
}

void check_stack(char *stack,char c,char *exp) {
	if(c == '+' || c == '-') {
		for(int i=k-1;i>=0;i--) {
			if(stack[i] == '(') {
				break;
			}
			switch(stack[i]) {
				case '+' : pop(stack,exp); break;
				case '-' : pop(stack,exp); break;
				case '*' : pop(stack,exp); break;
				case '/' : pop(stack,exp); break;
				case '^' : pop(stack,exp); break;
			}
		}
	}
	else if(c == '*' || c == '/') {
		for(int i=k-1;i>=0;i--) {
			if(stack[i] == '(') {
				break;
			}
			switch(stack[i]){
				case '*' : pop(stack,exp); break;
				case '/' : pop(stack,exp); break;
				case '^' : pop(stack,exp); break;
			}
		}
	}
	else if(c == '^') {
		for(int i=k-1;i>=0;--i) {
			if(stack[i] == '(') {
				break;
			}
			switch(stack[i]) {
				case '^' : pop(stack,exp);
			}
		}
	}
	else if(c == ')') {
		int i = k-1;
		while(stack[i] != '(') {
			pop(stack,exp);
			i--;
		}
		pop(stack,exp);
		//printf("\n%s",stack);
	}
}
void push(char c,char *stack,char *exp) {
	check_stack(stack,c,exp);
	if(c != ')') {
		stack[k] = c;
		stack[k+1] = '\0';
		k++;
	}
}

void infixToPostfix(char* exp,FILE *fp) {
	
	char postfix_exp[100]="",stack[20];
	
	for(int i=0;exp[i]!='\0';++i) {
		//checking for operand
		if((exp[i]>=65 && exp[i]<=90) || (exp[i]>=97 && exp[i]<=122)) {
			postfix_exp[j]=exp[i];
			j++;
		}
		else {
			push(exp[i],stack,postfix_exp);
		}		
		//printf("\nSTACK = %s",stack);
	}
	while(k!=0) {
		pop(stack,postfix_exp);
	}
	postfix_exp[j] = '\0';
	fprintf(fp,"%s\n",postfix_exp);
}
#define infile stdin
void main() {
	
	char infix_exp[1000];
	FILE *fp,*f_out;
	fp = fopen("input.txt","r");
	f_out = fopen("ouput.txt","w");
	/*printf("\nEnter the infix expression :");
	scanf("%s",infix_exp);*/
	
	while(1) {

		fscanf(fp,"%s",infix_exp);
		//printf("%s\n",infix_exp);
		if(feof(fp)) {
			break;
		}
		printf("\n%s",infix_exp);
		//converting infix to postfix expression
		infixToPostfix(infix_exp,f_out);
		k=0;j=0;
	}
	fclose(fp);
	fclose(f_out);
}
