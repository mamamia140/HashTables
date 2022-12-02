#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH1(K,S)  K%S
#define HASH2(K)    5-(K%5) 

typedef struct mail{
    int mailID;
    char sender[51];
    char recipient[51];
    int day;
    int wordCount;

}MAIL;

typedef struct table{
    MAIL* mails;
    int size;
}TABLE;



int checkId(TABLE* hashTable, int Id){

    int i=0;
    int size = hashTable->size;
    while(hashTable->mails[i].mailID != Id && i < size){
        i++;
    }
    if(i==size){
        return -1; //it isn' in the hash table
    }
    return 0; //it is in the hash table

}

void printMails(TABLE* hashTable){

    int i;
    int size = hashTable->size;

    printf("\nIndex\t\tID\t\tSender\t\tRecipient\tDate\tWords\n");
    for(i=0;i<size;i++){
        if(hashTable->mails[i].mailID != -1){
            printf("%d\t\t%d\t\t%s\t\t%s\t\t%d\t%d\n",i,hashTable->mails[i].mailID,hashTable->mails[i].sender,hashTable->mails[i].recipient,hashTable->mails[i].day,hashTable->mails[i].wordCount);
        }
        else{
            printf("%d\n",i);
        }
    }
    printf("\n");
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
void addToTheHashTable(TABLE* hashTable, MAIL mail,int technique){
    int Id = mail.mailID;
    int sender = *(mail.sender);
    int key = Id + sender - 65;
    int index = HASH1(key,hashTable->size);
    int i=1;
    while(hashTable->mails[index].mailID != -1){
        if(technique == 1){
            index = (HASH1(key,hashTable->size) + i * HASH2(key)) % hashTable->size;
        }
        else{
            index = (HASH1(key,hashTable->size) + i) % hashTable->size;
        }
        i++;
    }
    hashTable->mails[index] = mail;
    return;
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
void readMails(TABLE* hashTable,char* path,int numberOfMails, int technique){
    int i;
    char* temp = (char*)malloc(51*sizeof(char));
    char* name = (char*)malloc(51*sizeof(char));
    MAIL mail;
    for(i=1;i<=numberOfMails;i++){
        strcpy(temp,path);
        sprintf(name, "%s/%d.txt", temp,i);
        mail = readFromFile(name);
        if(checkId(hashTable, mail.mailID) == 0){ // if it's already in the hashTable
            printf("mail with Id %d is already in the hashTable\n",mail.mailID);
        }
        else{
            addToTheHashTable(hashTable,mail,technique);
            printMails(hashTable);
        }
        
    }

    free(temp);
    free(name);
}
TABLE* creatHashTable(int size){
    int i;
    TABLE* hashTable = (TABLE*) malloc (sizeof(TABLE));
    hashTable->mails = (MAIL*)malloc(size * sizeof(MAIL));
    hashTable->size = size;
    for(i=0;i<size;i++){
        hashTable->mails[i].mailID = -1;
    }
    return hashTable;
}
void searchMail(TABLE* hashTable ,int Id, char* sender, int technique){

    int key = Id + ((int)(*sender)) - 65;
    int index = HASH1(key,hashTable->size);
    int i=1;

    while(hashTable->mails[index].mailID != Id){
        if(technique == 1){
            index = (HASH1(key,hashTable->size) + i * HASH2(key)) % hashTable->size;
        }
        else{
            index = (HASH1(key,hashTable->size) + i) % hashTable->size;
        }
        i++;
    }
    printf("Recipient: %s\n",hashTable->mails[index].recipient);
    printf("Date: %d\n",hashTable->mails[index].day);
    printf("Number of words: %d\n",hashTable->mails[index].wordCount);

    return;
}

int main(){
    int choice,technique,numberOfMails,Id;
    TABLE* hashTable = creatHashTable(11);
    char* path = (char*)malloc(51*sizeof(char));
    char* sender = (char*)malloc(51*sizeof(char));
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
                readMails(hashTable,path,numberOfMails,technique);
			    break;
			
		    case 2:
                printf("enter the emailID: ");
                scanf("%d",&Id);
                printf("enter the sender's name: ");
                scanf("%s",sender);
                searchMail(hashTable, Id, sender, technique);
			    break;
		    case 3:
                printMails(hashTable);
			    break;	
			
		    case 4:
			    return 0;
		    }
	
	}
    return 0;   
}