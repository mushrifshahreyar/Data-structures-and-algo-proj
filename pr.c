#include<stdio.h>
#include<stdlib.h>
void main() {
	char s[100];	
	int val[100];
	int k=0;
	scanf("%s",s);
	
	for(int i=0; s[i] != '\0';++i) {
		if(s[i]<=57 &&s[i]>=48) {
			val[k] = atol(s[i]);
			k++;
		}
	}
	for(int i=0;i<k;++i) {
		printf("%d ",val[k]);
	}
}
