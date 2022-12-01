#include<stdio.h>
#include<dirent.h>
#include <stdlib.h>
#include <string.h>

typedef struct mail{
    int mailID;
    char sender[51];
    char recipient[51];
    int day;
    int wordCount;

}MAIL;



void readFile(){

    return;

}

void printMails(MAIL* mails,int numberOfMails){

    int i;
    printf("Index\t\tID\t\tSender\t\tRecipient\tDate\tWords\n");
    for(i=0;i<numberOfMails;i++){
        printf("%d\t\t%d\t\t%s\t\t%s\t\t%d\t%d\n",i,mails[i].mailID,mails[i].sender,mails[i].recipient,mails[i].day,mails[i].wordCount);
    }

}
int word_counter(char* name){
    FILE *fptr;
    int counter=0;
    char* string = (char*)malloc(50 * sizeof(char));
    fptr = fopen(name,"r+");
	while(fscanf(fptr,"%s",string) != EOF){
  		counter++;
  	}
    return counter;
}
MAIL* readMails(char* path,int numberOfMails){
    int counter=0,i=0;
    char* temp = (char*)malloc(51*sizeof(char));
    MAIL* mails = (MAIL*)malloc(numberOfMails * sizeof(MAIL));
    FILE* fptr;
    MAIL mail;
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d){
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
                counter=0;
                strcpy(temp,path);
                strcat(temp,"/");
                strcat(temp,dir->d_name);
                fptr = fopen(temp,"rb");
                fscanf(fptr,"%d",&mail.mailID);
                fscanf(fptr,"%s",temp);
                fscanf(fptr,"%s",temp);
                strcpy(mail.sender,temp);
                fscanf(fptr,"%s",temp);
                fscanf(fptr,"%s",temp);
                strcpy(mail.recipient,temp);
                fscanf(fptr,"%s",temp);
                fscanf(fptr,"%*c");
                fscanf(fptr,"%s",temp);
                mail.day = atoi(temp);
                while(fscanf(fptr,"%s",temp) != EOF){
  	            	counter++;
  	            }
                mail.wordCount =  counter;
                mails[i++] = mail;
                fclose(fptr);
            }
        }
        closedir(d);
    }

    free(temp);
    return mails;
}
int main(){
    MAIL* mails = readMails("files",6);
    printMails(mails,6);
    return 0;
}