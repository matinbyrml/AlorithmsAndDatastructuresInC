#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_LEN 100+1

typedef struct _list{
    char *word;
    int occurences;
    struct _list *next;
}lists_;

void FreeMemory(lists_ *head);
lists_ *ReadFileTwo(lists_ *head, char* filename);
lists_ *ReadFileOne(lists_ *head, char* filename);
lists_ *CreateNewNode(lists_ *head, char *temp);
int SmartSearch(char *word1,char *word2);
void PrintResult(lists_ *head);


int main(int argc, char * argv[]){
    lists_  *head;
    head=NULL;
    int n;
    if(argc<3){
        printf("wrong number of input files");
        return EXIT_FAILURE;
    }
    head = ReadFileOne(head,argv[1]);
    head = ReadFileTwo(head,argv[2]);
    PrintResult(head);
    FreeMemory(head);
    return 1;
}

void FreeMemory(lists_ *head){
    lists_ *p, *temp;
    temp=head;

    while(temp!=NULL){
        p=temp->next;
        free(temp);
        temp=p;
    }
}


lists_ *ReadFileTwo(lists_ *head, char* filename){
    lists_ *p;
    p=head;
    FILE *fp;
    char temp[MAX_ROW_LEN];
    fp=fopen(filename, "r");
    if(fp== NULL){
        printf("file 1 can not be opened");
          return EXIT_FAILURE;
    }
    int flag =1;
    while(fscanf(fp."%s",temp) && flag){
        while(p!=NULL){
            if(SmartSearch(temp,p->word)){
                p->occurences++;
                flag=0;
            }
            else{
                p=p->next;
            }
        }

    }

    fclose(fp);
    return p;
}

lists_ *ReadFileOne(lists_ *head, char* filename){
    lists_ *p;
    p=head;
    FILE *fp;

    char temp[MAX_ROW_LEN];

    fp=fopen(filename, "r");
    if(fp== NULL){
        printf("file 1 can not be opened");
          return EXIT_FAILURE;
    }

    while(fscanf(fp,"%s",temp)){
            p=CreateNewNode(p,temp);

    }

    fclose(fp);
    return p;
}

lists_ *CreateNewNode(lists_ *head, char *temp){
    lists_ *p; *new;
    p=head;
    new= malloc(sizeof(lists_));
    if(new==NULL){
          printf("error on dynamic allocation of a new node");
          return EXIT_FAILURE;
    }
    new->word=strdup(temp);
    new->occurences=1;
    new->next=p;
    return (new);
}

int SmartSearch(char *word1,char *word2){
    if(strlen(word1)!=strlen(word2)){
        retrun 0;
    }
    for(int j=0;j<strlen(word1);j++){
        if(tolower[word1[j]]!=tolower[word2[j]]){
            return 0; // return 0 if they are not same word
        }
    }
    return 1; // return 1 if they are same
}

void PrintResult(lists_ *head){
    lists_ *p;
    p=head;
    while(p!=NULL){
        printf("%s  %d", p->word,p->occurences);
    }
    return;
}
