#inlcude <stdio.h>
#inlcude <stdlib.h>
#inlcude <string.h>


#define MAX_STR_LEN 100+1

//struct data type for words
typedef struct word_{
    char *str;
}_words;

//pre def of functions
_words* ReadFile1(char *filename, int n);
_words* SortWords(int *n, _words *words);
void WriteToFile(char *filename, int *n);

int main(int argc, char *argv[]){
    _words *words;
    inr n;
    if(argc<3){
        fprintf(stderr,"Please enter 2 file names and a program name correctly");
        return EXIT_FAILURE;
    }
    words=ReadFile1(argv[1],&n);
    words=SortWords(n, words);
    WriteToFile(argv[2],n);

    for(int i=0;i<n;i++){
        free(words[i].str);
    }
    free(words);

    return 1;
}
// function to read the number of the words and content
 _words* ReadFile1(char *filename, int n){
    FILE *fp;
    _words *words
    int numoflines;
    char temp[MAX_STR_LEN];

    fp=fopen(filename, "r");
    if(fp==NULL){
        fprintf(stderr,"error reading the first file");
       return EXIT_FAILURE;
    }

    if (fscanf(fp,"%d",n)==EOF){
         fprintf(stderr,"error reading the first file first line");
       return EXIT_FAILURE;
    }
    n=numoflines;
    words=malloc(n * sizeof(_words));
    if(words==NULL){
        fprintf(stderr,"error while dynamic allocation");
       return EXIT_FAILURE;
    }
    int i=0;
    while(fscanf(fp,"%s", temp) && i<n){
            words[i].str=strdup(temp); //dynamic allocation of local strings of structures
    }
    fclose(fp);
    return words;
}
// bubble sort on the words
_words* SortWords(int *n, _words *words){ //is it correct? is there any need for it?
char temp[MAX_STR_LEN];
int i=0;
    for(i=0;i<n-1;i++){
        for(int j=0;j<(n-1-i);j++){
            if(strcmp(words[j+1].str, words[j].str)){
                 strcpy(temp,words[j+1].str);
                 strcpy(words[j+1].str,words[j].str);
                 strcpy(words[j].str,temp);
            }
        }
    }
     return words;
}
//writing the words on the new file
void WriteToFile(char *filename, int *n, _words *words){
    FILE *fp;
    fp=fopen(filename, "w");
    if(fp==NULL){
        fprintf(stderr,"error on the wiritng of second file");
      return EXIT_FAILURE;
    }
    int i=0;
    while(i<n){
        fprintf(fp,"%s",words[i].str);
    }
    fclose(fp);
    return;
    }