#include<stdio.h>
#include<stdlib.h>
push_stack(int k) {
}

evaluate(char *s) {
	
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
			evaluate(s);
		}
		//READING IN A STRING
		s[i] = ch;
		i++;
	}
	s[i] = '\0';
	printf("%d\n",i);
	//for(int j=0; j<i; ++j)
	printf("%s",s);
}

