// Completed till double hashing function

/*
    left :- 
            just option D left;
            */
#include<stdio.h>
#include<stdlib.h>

typedef struct Hash_table{
    int array[1000];
    int size;
}*Hash_table;

Hash_table Create_Hash_Table(Hash_table hash_table,int size) {
    hash_table = (Hash_table)malloc(sizeof(struct Hash_table));
	hash_table->size = size;
    for(int i=0;i<size;++i) {
        hash_table->array[i] = -1020;
    }
    return hash_table;
}


//---------FUNCTION k mod m------------//
int function_k_mod_m(Hash_table hash_table, int element) {
    return (element % hash_table->size);
}

// int function_R_mod_k_m(Hash_table hash_table, int element) {

// }

//---------Hash Function for Linear Probing--//
int function_linear(int position,int i,int size) {
    int j;
    j = position+i;
    return (j%size);
}

//--------Hash function for Quadratic Probing-----//
int function_quad(int position,int i,int size,int c1,int c2) {
    int j;
    j = (position + (c1*i) + (c2*i*i));
    return j%size;
}

//--------Hash function for Double Hashing---------//
int function_k_mod_m_h2(int R,int element){
    return (R - (element % R));
}
int function_double_hash(int position,int position2,int i,int size) {
    int j;
    j = (position + (i * position2));
    return j%size;
}

int prime_checker(int number) {
    for (int j = 2; j <= number / 2; j++)
    {
        if ((number % j) == 0)
        {
            return -1;
        }
    }
    return 1;
}
int find_R(int size) {
    for(int i = size-1; i>=0;--i) {
        if(prime_checker(i) == 1) {
            return i;
        }
    }
    return 2;
}
//=======================================//
//---------Table Operations--------------//

void insert_into_table(Hash_table hash_table,int element,int option,int c1,int c2) {
    int i = 0;
    int position,j;
    int position2,R; 
    while(i < hash_table->size) {
        switch(option) {
            case 1: position = function_k_mod_m(hash_table,element);
                    j = function_linear(position,i,hash_table->size);
                    break;

            case 2: position = function_k_mod_m(hash_table,element);
                    j = function_quad(position,i,hash_table->size,c1,c2);
                    break;

            case 3: position = function_k_mod_m(hash_table,element);
                    R = find_R(hash_table->size);
                    position2 = function_k_mod_m_h2(R,element); 
                    j = function_double_hash(position,position2,i,hash_table->size);
                    break;
        }
        if(hash_table->array[j]== -1020 || hash_table->array[j] == -1021) {
            hash_table->array[j] = element;
            return;
        }
        else {
            i = i+1;
        }
    }
}
void print_table(Hash_table hash_table,FILE *f_out) {
    for(int i=0;i<hash_table->size;++i) {
        if(hash_table->array[i] != -1020 && hash_table->array[i] != -1021) {
            fprintf(f_out,"%d (%d)\n",i,hash_table->array[i]);
        }
        else {
            fprintf(f_out,"%d ()\n",i);    
        }
    }
}

int search(Hash_table hash_table, int element,int option,int c1,int c2) {
    int i=0;
    int position,j;
    int position2,R;
    while(i < hash_table->size) {
        switch(option) {
            case 1: position = function_k_mod_m(hash_table,element);
                    j = function_linear(position,i,hash_table->size);
                    break;
            case 2: position = function_k_mod_m(hash_table,element);
                    j = function_quad(position,i,hash_table->size,c1,c2);
                    break;
            case 3: position = function_k_mod_m(hash_table,element);
                    R = find_R(hash_table->size);
                    position2 = function_k_mod_m_h2(R,element); 
                    j = function_double_hash(position,position2,i,hash_table->size);
                    break;
        }
        
        if(hash_table->array[j] == element) {
            return j;
        }
        else{
            i = i+1;
        }
        if(hash_table->array[j] == -1020) {
            break;
        }
    }
    return -1;
}

void delete(Hash_table hash_table,int element,int option,int c1,int c2,FILE *f_out) {
    int position = search(hash_table,element,option,c1,c2);
    if(position != -1) {
        hash_table->array[position] = -1021;
        
    }
    else {
        fprintf(f_out,"-1\n");
    }
}
//====================================================================//

//====================================================================//
//---------Probing types--------------//
void linear_probing(Hash_table hash_table,FILE *f_in,FILE *f_out) {
    char option;
    int element;
    int insert_count = 0;
    do{
        //printf("\nEnter the option:");
        fscanf(f_in,"%c",&option);
        switch(option) {
            case 'i': //printf("\nEnter the number to be inserted :");
                      fscanf(f_in,"%d",&element);
                      if(insert_count < hash_table->size) {
                        insert_into_table(hash_table,element,1,0,0);
                      }
                      else {
                          //printf("\nOverfilled");
                      }
                      insert_count++;
                      break;

            case 'p': print_table(hash_table,f_out);
                      break;

            case 's': //printf("\nEnter the key to be searched :");
                      fscanf(f_in,"%d",&element);
                      int result = search(hash_table,element,1,0,0);
                      if(result != -1) {
                        fprintf(f_out,"1\n");
                      }
                      else {
                          fprintf(f_out,"%d\n",result);
                      }
                      break;

            case 'd': //printf("\nEnter the element to be deleted :");
                      fscanf(f_in,"%d",&element);
                      delete(hash_table,element,1,0,0,f_out);
                      break;

            case 't': //printf("\nThank you for using the program");
                      exit(0);
                      break;

            //default : //printf("\nPlease enter valic option");
                      
        }
    }while(option != 't');
}

void quadratic_probing(Hash_table hash_table,int c1,int c2,FILE *f_in,FILE *f_out) {
    char option;
    int element;
    int insert_count = 0;
    do{
        //printf("\nEnter the option:");
        fscanf(f_in,"%c",&option);
        switch(option) {
            case 'i': //printf("\nEnter the number to be inserted :");
                      fscanf(f_in,"%d",&element);
                      if(insert_count < hash_table->size) {
                        insert_into_table(hash_table,element,2,c1,c2);
                      }
                      else {
                          //printf("\nOverfilled");
                      }
                      insert_count++;
                      break;

            case 'p': print_table(hash_table,f_out);
                      break;

            case 's': //printf("\nEnter the key to be searched :");
                      fscanf(f_in,"%d",&element);
                      int result = search(hash_table,element,2,c1,c2);
                      if(result != -1) {
                        fprintf(f_out,"1\n");
                      }
                      else {
                        fprintf(f_out,"%d\n",result);
                      }
                      break;

            case 'd': //printf("\nEnter the element to be deleted :");
                      fscanf(f_in,"%d",&element);
                      delete(hash_table,element,2,c1,c2,f_out);
                      break;

            case 't': //printf("\nThank you for using the program");
                      exit(0);
                      break;

            //default : //printf("\nPlease enter valid option");
                      
        }
    }while(option != 't');
}

void double_hashing(Hash_table hash_table,FILE *f_in,FILE *f_out) {
    char option;
    int element;
    int insert_count = 0;
    do{
        //printf("\nEnter the option:");
        fscanf(f_in,"%c",&option);
        switch(option) {
            case 'i': //printf("\nEnter the number to be inserted :");
                      fscanf(f_in,"%d",&element);
                      if(insert_count < hash_table->size) {
                        insert_into_table(hash_table,element,3,0,0);
                      }
                      else {
                          //printf("\nOverfilled");
                      }
                      insert_count++;
                      break;

            case 'p': print_table(hash_table,f_out);
                      break;

            case 's': //printf("\nEnter the key to be searched :");
                      fscanf(f_in,"%d",&element);
                      int result = search(hash_table,element,3,0,0);
                      if(result != -1) {
                        fprintf(f_out,"1\n");
                      }
                      else {
                        fprintf(f_out,"%d\n",result);
                      }
                      break;

            case 'd': //printf("\nEnter the element to be deleted :");
                      fscanf(f_in,"%d",&element);
                      delete(hash_table,element,3,0,0,f_out);
                      break;

            case 't': //printf("\nThank you for using the program");
                      exit(0);
                      break;

            //default : //printf("\nPlease enter valid option");
                      
        }
    }while(option != 't');
}

typedef struct Node{
    int data;
    struct Node *nxt;
}*Node;

typedef struct Hash_table_Chaining {
    Node list[100];
    int size;
}*Hash_table_Chaining;

Hash_table_Chaining Create_table_chaining(Hash_table_Chaining hash_table,int size) {
    hash_table = (Hash_table_Chaining)malloc(sizeof(struct Hash_table_Chaining));
    hash_table->size = size;
    for(int i=0;i<size;++i) {
        hash_table->list[i] = NULL;
    }
    return hash_table;
}
Node Create_node(int data) {
    Node node;
    node = (Node)malloc(sizeof(struct Node));
    node->data = data;
    node->nxt = NULL;
    return node;
}
int function_k_mod_m_chaining(Hash_table_Chaining hash_table,int ele) {
    return (ele % hash_table->size);
}
void insert_list(Hash_table_Chaining hash_table,Node ele) {
    int position = function_k_mod_m_chaining(hash_table,ele->data);
    if(hash_table->list[position] == NULL) {
        hash_table->list[position] = ele;
    }
    else {
        Node temp;
        temp = hash_table->list[position];
        hash_table->list[position] = ele;
        ele->nxt = temp;
        
        
    }
}
Node search_chaining(Hash_table_Chaining hash_table,int element) {
    int position = function_k_mod_m_chaining(hash_table,element);
    Node temp = hash_table->list[position];
    while(temp != NULL) {
        if(temp->data == element) {
            return temp;
        }
        temp = temp->nxt;
    }
    return NULL;
}

int delete_chaining(Hash_table_Chaining hash_table,int element) {
    Node temp = search_chaining(hash_table,element);
    int position = function_k_mod_m_chaining(hash_table,element);
    if(hash_table->list[position]->data == element) {
        hash_table->list[position] = hash_table->list[position]->nxt;
        return 0;
    }
    if(temp != NULL) {
        int position = function_k_mod_m_chaining(hash_table,element);
        Node array = hash_table->list[position];
        while(array->nxt != NULL) {
            if(array->nxt == temp) {
                array->nxt = temp->nxt;
                free(temp);
                return 0;
            }
            array = array->nxt;
        }  
	}
    return 0;
}
void print_table_chaining(Hash_table_Chaining hash_table,FILE *f_out) {
    for(int i=0;i<hash_table->size;++i) {
        if(hash_table->list[i] == NULL) {
            fprintf(f_out,"%d ()\n",i);
        }
        else {
            fprintf(f_out,"%d (",i);
            Node array = hash_table->list[i];
            while(array != NULL) {
                fprintf(f_out,"%d",array->data);
                if(array->nxt != NULL) {
                    fprintf(f_out," ");
                }
                array = array->nxt;
            }
            fprintf(f_out,")\n");

        }
    }
}
void chaining(Hash_table_Chaining hash_table,FILE *f_in,FILE *f_out) {
    char ch;
    int element;
    
    
    do {
    //printf("\nEnter the option :");
    fscanf(f_in,"%c",&ch);    
    switch(ch) {

        case 'i': //printf("\nEnter the number:");
                  fscanf(f_in,"%d",&element);
                  Node ele = Create_node(element);  
                  insert_list(hash_table,ele);
                  
				  break;

        case 's': //printf("\nEnter the element to be seatched:");
                  fscanf(f_in,"%d",&element);
                  Node temp = search_chaining(hash_table,element);
                  if(temp != NULL) {
                      fprintf(f_out,"1\n");
                  }
                  else {
                      fprintf(f_out,"-1\n");
                  }
                  break;

        case 'd': //printf("\nEnter the number to be deleted :");
                  fscanf(f_in,"%d",&element);
                  delete_chaining(hash_table,element);
                  //if(result != 100) {
                  //    fprintf(f_out,"\n-1");
                  //}
                  break;

        case 'p': print_table_chaining(hash_table,f_out);
                  break;

        case 't': exit(0);
    }
    }while(ch != 't');
    
}
int main() {
    Hash_table hash_table;
    Hash_table_Chaining hash_table_chaining;
    char hashtable_options; //a,b,c,d;
    int table_size = 0;
    FILE *f_in,*f_out;
    f_in = fopen("input.txt","r");
    f_out = fopen("output.txt","w");

    int c1,c2;
    while(1) {
        //printf("\nEnter the option for hash table :");
        fscanf(f_in,"%c",&hashtable_options);
    
        switch(hashtable_options) {
            case 'a': //printf("\nEnter the size of table :");
                      fscanf(f_in,"%d",&table_size);
                      hash_table = Create_Hash_Table(hash_table,table_size);
                      linear_probing(hash_table,f_in,f_out);
                      break;

            case 'b': //printf("\nEnter the size of table :");
                      fscanf(f_in,"%d",&table_size);
                      fscanf(f_in,"%d %d",&c1,&c2);
                      hash_table = Create_Hash_Table(hash_table,table_size);
                      quadratic_probing(hash_table,c1,c2,f_in,f_out);
                      break;

            case 'c': //printf("\nEnter the size of the table :");
                      fscanf(f_in,"%d",&table_size);
                      hash_table = Create_Hash_Table(hash_table,table_size);

                      double_hashing(hash_table,f_in,f_out);
                      break;

		    case 't': exit(0);

            case 'd': //printf("\nEnter the size of table :");
                      fscanf(f_in,"%d",&table_size);
                      hash_table_chaining = Create_table_chaining(hash_table_chaining,table_size);
                      chaining(hash_table_chaining,f_in,f_out);
                      break;

        //default : //printf("\nEnter the valid option\n");
                            
        }
    }   
}

