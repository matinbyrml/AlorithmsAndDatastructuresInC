#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN (50+1)
#define MAX_ID_LEN (16+1)
#define MAX_DATE_LEN (10+1)

typedef struct list_{
    char *name;
    char *id;
    int salary;
    char *hiring_date;
    struct list_ *right;
    struct list_ *left;
}_lists;
_lists *InsertNode(_lists *head,char *tempname, char *tempid,char *tempdate, int tempsalary);
_lists *ReadFile(_lists *head,char *filename);
void ReadCommand(_lists *head, char *name, char *command);
void PrintNode(_lists *node);
void CleanMemory(_lists *head);

int main(int argc, char *argv[]) {
    _lists *head;
    head=NULL;
    printf("Please enter input file name, name and surname as NAME_SURNAME  and + or - \n");
    if(argc<4){
        printf("wrong inputs \n");
        return(EXIT_FAILURE);
    }
    head= ReadFile(head, argv[1]);
    ReadCommand(head,argv[2],argv[3]);
    CleanMemory(head);

    return 0;
}
//clean memory
void CleanMemory(_lists *head){
    _lists *p, *q;
    p=head;
    while(p!=NULL){
        free(p->name);
        q=p->right;
        free(p);
        p=q;
    }
}


_lists* ReadFile(_lists *head,char *filename){
    char tempname[MAX_NAME_LEN];
    char tempid[MAX_ID_LEN];
    char tempdate[MAX_DATE_LEN];
    int tempsalary;




    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("File can not be opened \n ");
        return(EXIT_FAILURE);
    }

    while(fscanf(fp,"%s %s %s %d", tempname, tempid,tempdate, &tempsalary)!=EOF){
        if(strlen(tempid)!=17){
            printf("this %s person has error on his/her id", tempname);
                    }
        head=InsertNode(head,tempname,tempid,tempdate,tempsalary);
    }
    return head;
}

_lists *InsertNode(_lists *head,char *tempname, char *tempid,char *tempdate, int tempsalary){
   _lists *p, *q;
   p=head;
    if(p==NULL)
    {
        p= malloc(sizeof (_lists));
        if(p==NULL){
            printf("error on dynamic allocation");
        }
        p->hiring_date= strdup(tempdate);
        p->id = strdup(tempid);
        p->name= strdup(tempname);
        p->salary=tempsalary;
        p->right=NULL;
        p->left=NULL;
    }
    else{
        while(p->right==head){
            p=p->right;
        }
        q= malloc(sizeof (_lists));
        if(q==NULL){
            printf("error on dynamic allocation");
        }
        q->hiring_date= strdup(tempdate);
        q->id = strdup(tempid);
        q->name= strdup(tempname);
        q->salary=tempsalary;
        q->right=head;
        q->left=p;
    }
    return head;


}

void ReadCommand(_lists *head, char *name, char *command){
    _lists *p;
    p=head;
    while (!strcmp(name,p->name)){
        p=p->right;
    }
    PrintNode(p);
    for(int i=0;i< strlen(command);i++) {
        switch (command[i]) {
            case '+':
                PrintNode(p->right);
                break;
            case '-':
                PrintNode(p->left);
                break;
            default:
                printf("only - and + are accepted");
                break;
        }
    }
    return;
}

void PrintNode(_lists *node){
    printf("%s \t %s \t %s \t %d", node->name, node->id, node->hiring_date, node->salary);
    return;
}