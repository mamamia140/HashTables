#include <stdio.h>
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
void addToTheHashTable(MAIL* table, MAIL mail,int technique){
    //table[index] = mail;
    int Id = mail.mailID;
    char sender = *(mail.recipient);
}
MAIL readFromFile(char* path){
    int counter=0,i=0;
    char* temp = (char*)malloc(51*sizeof(char));
    FILE* fptr;
    MAIL mail;
    fptr = fopen(path,"rb");
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
    fclose(fptr);
    return mail;
}
MAIL* readMails(MAIL* mails,char* path,int numberOfMails, int technique){
    int i;
    char* temp = (char*)malloc(51*sizeof(char));
    char *name;
    MAIL mail;
    for(i=1;i<=numberOfMails;i++){
        strcpy(temp,path);
        asprintf(name, "/%d", i);
        strcat(temp,name);
        mail = readFromFile(temp);
        addToTheHashTable(mails,mail,technique);
    }

    free(temp);
    return mails;
}

int main(){
    int choice,technique,numberOfMails;
    MAIL* mails = (MAIL*)malloc(11 * sizeof(MAIL));
    char* path = (char*)malloc(51*sizeof(char));
    printf("which open addressing technique would you like to use?\n");
    printf("to select double hashing press 1...\n");
    printf("to select linear probing press 2...\n");
    scanf("%d",&technique);
    while(1){
	    printf("\nSelect the thing you want to do operations on.\n");
	    printf("to read an email press 1...\n");
	    printf("to search an email press 2...\n");
	    printf("to print table press 3...\n");
	    printf("To quit press 4...\n");
	    scanf("%d",&choice);
	    switch(choice){
		    case 1:
                printf("enter the directory path: \n");
                scanf("%s",path);
                printf("how many mails are there in given directory\n");
                scanf("%d",&numberOfMails);
                mails = readMails(mails,path,numberOfMails,technique);
                printMails(mails,numberOfMails);
			    break;
			
		    case 2:

			    break;
		    case 3:
			    break;	
			
		    case 4:
			    return 0;
		    }
	
	}
    return 0;   
}