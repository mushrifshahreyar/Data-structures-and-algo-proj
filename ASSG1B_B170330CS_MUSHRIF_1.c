//Creating Huffman tree

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct String {
    int freq;
    char ch;
    struct String *left,*right;
}string;

typedef struct Queue {
    int size;
    string* (array[1000]);

}*queue;

queue Create_queue(int n) {
    queue temp;
    temp = (queue)malloc(sizeof(struct Queue));
    for(int i=0;i<n;++i) {
        temp->array[i] = (string*)malloc(sizeof(string));
    }
    temp->size = -1;
    return temp;
}

int check_queue(queue q, string *a) {
    string *s;
    for(int i=0; i <= q->size; ++i) {
        s = q->array[i];
        if(s->ch == a->ch) {
            return 1;
        }    
    }
    return 0;
}

int get_position(queue q, string a) {
    int i;
    for(i=0;i<=q->size;++i) {
        string *s = q->array[i];
        //printf("\ns ; %c %d",s.ch,s.freq);

        if(a.freq >= s->freq) {
            continue;
        } 
        else {
            return i;
        }
    }
    return i;
}
void push_queue(queue queue,string *a){
    if(queue->size == -1) {
        queue->size++;
        queue->array[queue->size] = a;
    }
    else {
        int checker;
        if(a->ch == '$') {
            checker = 0;
        }
        else {
            checker = check_queue(queue,a);
        }
        if(checker == 0) {
            int position = get_position(queue,*a);
            if(position == queue->size+1) {
                queue->size++;
                queue->array[position] = a;
            }
            else{
                for(int i = queue->size; i>=position; --i) {
                    queue->array[i+1] = queue->array[i];
                }
                queue->array[position] = a;
                queue->size++;
            }
        }
    }
}

string* pop_queue(queue q) {
    string *s;
    s = q->array[0];
    for(int i=0;i<=q->size-1;++i) {
        q->array[i] = q->array[i+1];
    }
    q->size--;
    return s;
}

void find_count(char *s,queue Queue) {
    int freq = 0;
    
    for(int i=0;s[i] != '\0'; ++i) {
        string *array = (string *)malloc(sizeof(struct String));
        for(int j=0;s[j] != '\0'; ++j) {
            if(s[i] == s[j]) {
                freq++;
            }
        }      
        array->freq = freq;
        array->ch = s[i];
        //Pushing into queue
        push_queue(Queue,array);
        freq = 0; 
    }
}



void print_arr(char ch,int arr[],int n) {
    printf("\n%c :",ch);
    for(int i=0;i<n;++i) {
        printf("%d",arr[i]);
    }
}

void initialize(string *s) {
    s->right = NULL;
    s->left = NULL;
   
}

int isleaf(string *node) {
    if(node->left == NULL && node->right == NULL) {
        return 1;
    }
    else return 0;
}
string* Create_tree(queue Queue) {
    while(Queue->size != 0) {
        string *s1 = (string*)malloc(sizeof(string));
        s1 = pop_queue(Queue);
        string *s2 = (string*)malloc(sizeof(string)); 
        s2 = pop_queue(Queue);
        string *s3 = (string*)malloc(sizeof(string));
        s3->ch = '$';
        s3->freq = s1->freq+s2->freq;

        if(s1->freq == s2->freq) {
            if(isleaf(s1) == 1 && isleaf(s2) == 0) {
                s3->left = s1;
                s3->right = s2;
            }
            else if(isleaf(s1) == 0 && isleaf(s2) == 1) {
                s3->left = s2;
                s3->right = s1;
            }
            else if(isleaf(s1) == 0 && isleaf(s2) == 0) {
                s3->left = s1;
                s3->right = s2;
            }
            else if(isleaf(s1) == 1 && isleaf(s2) == 1) {
                if(s1->ch < s2->ch) {
                    s3->left = s1;
                    s3->right = s2;
                }
                else {
                    s3->left = s2;
                    s3->right = s1;
                }
            }
            else {
                s3->left = s1;
                s3->right = s2;
            }
        }
        else {
            s3->left = s1;
            s3->right = s2;
        }
        

        push_queue(Queue,s3);  
        // for(int i=0;i<=Queue->size;++i) {
        //     printf("\n[%c | %d]",Queue->array[i]->ch,Queue->array[i]->freq);
        // }
        printf("\n\n");
    }
    
    return (Queue->array[0]);
}
// //void print(string *head) {
// if(head != NULL) {
//     print(head->left);
//     printf("\n{%c,%d} ",head->ch,head->freq);
//     print(head->right);
// }
// }
// void get_huff_code(string *head,char ch,FILE *f_out) {
//     if(head != NULL) {
//         string *array = head;
//         while(array->left != NULL && array->right != NULL) {
//             if(array->left->ch == ch) {
//                 fprintf(f_out,"0");
//                 return;
//             }
//             else if(array->right->ch == ch) {
//                 fprintf(f_out,"1");
//                 return;
//             }
//             else {
//                 assert(0);
//                 // if(array->left->ch == '$') {
//                 //     fprintf(f_out,"0");
//                 //     array = array->left;
//                 // }
//                 // else if(array->right->ch == '$') {
//                 //     fprintf(f_out,"1");
//                 //     array= array->right;
//                 // }
//                 // else {
//                 //     return;
//                 // }
//             }
//         }
//     }
// }

void get_huff_code(string *head,char ch,FILE *f_out,char str[],int index) {
    if(head == NULL) {
        return;
    }
    if(head->ch == ch) {
        fprintf(f_out,"%s",str);
        return;
    }
    else {
        char str_1[100] = "";
        char str_2[100] = "";
        strcpy(str_1,str);
        strcpy(str_2,str);
        strcat(str_1,"0");
        strcat(str_2,"1");
        get_huff_code(head->left,ch,f_out,str_1,index+1);
        get_huff_code(head->right,ch,f_out,str_2,index+1);
    }
}


void sort(queue Queue) {
    string *temp;
    for(int i=0;i<=Queue->size;++i) {
        for(int j=0;j<=Queue->size;++j) {
            if(i == j) {
                continue;
            }
            if(Queue->array[i]->freq == Queue->array[j]->freq) {
                if(i<j) {
                if(Queue->array[i]->ch > Queue->array[j]->ch) {
                    temp = Queue->array[i];
                    Queue->array[i] = Queue->array[j];
                    Queue->array[j] = temp;
                }
            }
            }
        }   
    }
}
int main() {
    char s[1000];
    FILE *f_in,*f_out;
    f_in = fopen("input.txt","r");
    f_out = fopen("output.txt","w");
    //string string_array;
    while(1) {
        
        //printf("\nEnter the string :");
        fscanf(f_in,"%s",s);
        if(feof(f_in)){
            break;
        }
        //printf("\n%s\n",s);
        queue Queue = Create_queue(strlen(s));
        find_count(s,Queue);
        for(int i=0;i<=Queue->size;++i) {
            initialize(Queue->array[i]);
        }
        for(int i=0;i<=Queue->size;++i) {
            printf("\n[%c | %d]",Queue->array[i]->ch,Queue->array[i]->freq);
        }
        printf("\n");
        //for(int i=0;i<=Queue->size;++i) {
         //   printf("\n%c %d",Queue->array[i]->ch,Queue->array[i]->freq);
        //}
        sort(Queue);
        for(int i=0;i<=Queue->size;++i) {
            printf("\n[%c | %d]",Queue->array[i]->ch,Queue->array[i]->freq);
        }
        string *head = Create_tree(Queue);
        // print(head);   
        
        for(int i=0;s[i] != '\0';++i) {
            char str[100];
            strcpy(str,"");
            get_huff_code(head,s[i],f_out,str,0);
            fprintf(f_out," ");
        }
        fprintf(f_out,"\n");  
        
    }
    fclose(f_in);
    fclose(f_out);
   
}
