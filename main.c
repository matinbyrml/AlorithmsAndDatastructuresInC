#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STR_LONG 4+1
#define MAX_NUM_RECT 100


typedef struct{
    char name[MAX_STR_LONG];
    float x1,x2,y1,y2;
    float perimeter, area;
    }_rectangle;

    void readRectangle (char *, _rectangle [], int *);
    void CalculareArea(_rectangle [],int );
    void SortbyAREA(_rectangle [], int ,char *);
    void sortbyPERIMETER(_rectangle [], int ,char *);


int main(int argc, char *argv[])
{
    _rectangle rectangle[MAX_NUM_RECT];
    if(argc<2){
        fprintf(stderr,"Wrong number of inputs on cmd");
        exit(EXIT_FAILURE);
    }
    int n;
    int i=0;
    readRectangle(argv[1],rectangle,&n);
    for(i=0;i<n;i++){
        fprintf(stdout, "%s %f %f %f %f \n",rectangle[i].name,rectangle[i].x1,rectangle[i].y1,rectangle[i].x2,rectangle[i].y2);
    }

    CalculareArea(rectangle,n);
    SortbyAREA(rectangle,n,argv[2]);
    sortbyPERIMETER(rectangle,n,argv[3]);

    return 0;
}

void readRectangle (char *name, _rectangle rectangle[], int *num_ptr){


    FILE *fp;
    fp=fopen(name,"r");
    if(fp==NULL){
        fprintf(stderr,"Can not open the file");
        exit(EXIT_FAILURE);
    }
    int i;
    i=0;
        char buffer[256];
        char rect[MAX_STR_LONG];
        float x,y;
    while(fgets(buffer,256,fp)!=NULL){
            int flag=1;
        sscanf(buffer,"%s %f %f", rect, &x,&y);
        for(int j=0;j<i && flag;j++){
        if(strcmp(rect,rectangle[j].name)==0){
            rectangle[j].x2=x;
            rectangle[j].y2=y;
        flag=0;
        }
        }
        if(flag){
            strcpy(rectangle[i].name,rect);
            rectangle[i].x1=x;
            rectangle[i].y1=y;
            i++;
        }

    }
    *num_ptr=i;

    fclose(fp);
}

void CalculareArea(_rectangle rectangle[],int n){
    int i;
    int a, b;
    for(i=0;i<n;i++){
        if((rectangle[i].x1>0 && rectangle[i].x2>0) || (rectangle[i].x1<0 && rectangle[i].x2<0))
           {
               a=abs(abs(rectangle[i].x1-abs(rectangle[i].x2)));
           }
        else{
            a=abs(rectangle[i].x1)+abs(rectangle[i].x2);
        }

        if((rectangle[i].y1>0 && rectangle[i].y2>0) || (rectangle[i].y1<0 && rectangle[i].y2<0))
           {
               b=abs(abs(rectangle[i].y1-abs(rectangle[i].y2)));
           }
           else{
            b=abs(rectangle[i].y1)+abs(rectangle[i].y2);
           }
        rectangle[i].area=a*b;
        rectangle[i].perimeter=(a+b)*2;
    }



}

void SortbyAREA(_rectangle rectangle[], int n,char *filename ){
        _rectangle TEMTEMP;
        int i;
        int j;

        for(i=0;i<n-1;i++){
            for(j=0;j<n-i-1;j++){
                    if(rectangle[j].area<rectangle[j+1].area){
                        TEMTEMP=rectangle[j];
                        rectangle[j]=rectangle[j+1];
                        rectangle[j+1]=TEMTEMP;
            }

            }
        }
        FILE *fout;
        fout=fopen(filename ,"w");
        if(fout==NULL){
            fprintf(stderr,"Cann not create and write for sorted by area \n");
            exit(EXIT_FAILURE);
        }

        for(i=0;i<n;i++){
            fprintf(fout,"%s \n",rectangle[i].name);
        }

        fclose(fout);
}


void sortbyPERIMETER(_rectangle rectangle[], int n,char *filename ){
        _rectangle TEMTEMP;
        int i;
        int j;

        for(i=0;i<n-1;i++){
            for(j=0;j<n-i-1;j++){
                    if(rectangle[j].perimeter<rectangle[j+1].perimeter){
                        TEMTEMP=rectangle[j];
                        rectangle[j]=rectangle[j+1];
                        rectangle[j+1]=TEMTEMP;
            }

            }
        }
        FILE *fout2;
        fout2=fopen(filename ,"w");
        if(fout2==NULL){
            fprintf(stderr,"Cann not create and write for sorted by area \n");
            exit(EXIT_FAILURE);
        }

        for(i=0;i<n;i++){
            fprintf(fout2,"%s \n",rectangle[i].name);
        }

        fclose(fout2);
}
