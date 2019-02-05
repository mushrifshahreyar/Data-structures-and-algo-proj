#include<stdio.h>
#include<stdlib.h>

typedef struct Hash_table{
    int array[1000][2];
    int count;
}*Hash_table;

    Hash_table create_hash(Hash_table hash_table,int size) {
    hash_table = (Hash_table)malloc(sizeof(struct Hash_table));
    hash_table->count = size;
    for(int i=0;i<size;++i) {
        hash_table->array[i][0] = -1020;
    }
    return hash_table;
}

int funct_k_mod_m(Hash_table hash_table, int element) {
    return (element % hash_table->count);
}
int function_linear(int position,int i,int size) {
    int j;
    j = position+i;
    return (j%size);
}
int search(Hash_table hash_table, int element) {
    int i=0;
    int position,j;
    
    while(i < hash_table->count) {
        
        position = funct_k_mod_m(hash_table,element);
        j = function_linear(position,i,hash_table->count);
               
        if(hash_table->array[j][0] == element) {
            return j;
        }
        else{
            i = i+1;
        }
        if(hash_table->array[j][0] == -1020) {
            break;
        }
    }
    return -1;
}
void push_into_hash(Hash_table hash_table,int key,int element,FILE *f_out) {
    int i=0;
    int position,j;
    while(i<hash_table->count) {
        position = funct_k_mod_m(hash_table,key);
        j = function_linear(position,i,hash_table->count);

        int result = search(hash_table,element);
        if(result != -1) {
            if(hash_table->array[result][1] == key) {
                fprintf(f_out,"(%d,%d)\n",element,key);
                return;
            }
        }
        if(hash_table->array[j][0] == -1020) {
            hash_table->array[j][0] = key;
            hash_table->array[j][1] = element;
            return;
        }
        else {
            i = i+1;
        }
    }
}



int main() {
    int array[1000][2];
    Hash_table hash_table;
    char option;
    int count = 0;
    FILE *f_in,*f_out;
    f_in = fopen("input.txt","r");
    f_out = fopen("output.txt","w");
    while(1){
        //printf("\nEnter the option :");
        fscanf(f_in,"%c",&option);
        
        if(option == 's') {
            //printf("\nEnter two numbers :");
            fscanf(f_in," (%d,%d)",&array[count][0],&array[count][1]);
            count++; 
            
        }
        else if(option == 'p') {
            //printf("\n%c",option);
            
            hash_table = create_hash(hash_table,count);
            //printf("%d ",count);
            
            for(int i=0;i<count;++i) {
                 int key = array[i][0];
                 int element = array[i][1];
                 if(key == element) {
                     fprintf(f_out,"(%d,%d)\n",key,element);
                     continue;
                 }
                 push_into_hash(hash_table,key,element,f_out);
            }  
        }
        else if(option == 'e') {
            exit(0);
        }
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}
