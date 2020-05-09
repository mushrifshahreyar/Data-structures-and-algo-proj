#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define d 256
void rabin_karb_algorithm(char text[],char pattern[],int prime,FILE *f_out,int count) {
    int pattern_length = strlen(pattern);
    int text_length = strlen(text);
    int hash_pattern = 0;
    int hash_text = 0;
    int temp = 1;
    if(count != 0) {
        fprintf(f_out,"\n");
    }
    for(int i=0;i<pattern_length-1;++i) {
        temp = (temp * d) % prime;
    }

    for(int i=0;i<pattern_length;++i) {
        hash_pattern = (d * hash_pattern + pattern[i]) % prime;
        hash_text = (d * hash_text + text[i]) %prime;
    }
    int i=0,j=0;
     
    for(i=0;i <= text_length-pattern_length;++i) {
        if(hash_pattern == hash_text) {
            for(j=0; j < pattern_length; ++j) {
                if(text[i+j] != pattern[j]){
                    break;
                }
            }
            if(j == pattern_length) {
                fprintf(f_out,"%d ",i);

            }
        }

        if(i < text_length-pattern_length) {
            hash_text = (d * (hash_text - text[i] * temp) + text[i+pattern_length]) % prime;
            if(hash_text < 0) {
                hash_text = hash_text + prime;
            }
        }
    }
}
void copy_text(char text[],char text_new[]) {
    int k=0;
    int n = strlen(text);
    for(int i=0;i < n;++i) {
        if(i==0) {
            if(text[i] == ' ') {
                continue;
            }
        }
        if(text[i] != '"') {
            text_new[k] = text[i];
            k++;
        }
    }
    text_new[k] = '\0';
}
void main() {
    char text[1000],text_new[1000];
    char pattern[100],pattern_new[1000];
    char ch;
    int j=0;
    FILE *f_in,*f_out;
    f_in = fopen("input.txt","r");
    f_out = fopen("output.txt","w");
    while(1) {
        if(feof(f_in)) {
            break;
        }
        fscanf(f_in,"%c",&ch);
        if(ch == 't') {
            fscanf(f_in,"%[^\n]s",text);
            copy_text(text,text_new);
            //printf("\n%s",text_new);
        }
        //printf("\nEnter the string :");
        //scanf("%[^\n]s",text);
        //printf("\nEnter the pattern :");
        else if(ch == 'p') {
            ch = getc(f_in);
            if(ch == 'r') {
                rabin_karb_algorithm(text_new,pattern_new,101,f_out,j);
                j++;
            }
            else {
                fscanf(f_in,"%s",pattern);
                copy_text(pattern,pattern_new);
                //printf("\n%s",pattern_new);
            }
        }
        else if(ch == 'e') {
            break;
        }
    }
    fclose(f_in);
    fclose(f_out);
}