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

int isPrime(int n){
    // Corner cases
    if (n <= 1){
        return -1;
    }
    if (n <= 3){
        return 1;
    }
   
    // This is checked so that we can skip 
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0){
        return -1;
    }
   
    for (int i=5; i*i<=n; i=i+6){
        if (n%i == 0 || n%(i+2) == 0){
            return -1;
        }
    }
    return 1;
}
 
// Function to return the smallest
// prime number greater than number
int nextPrime(int number){
    // Loop continuously until isPrime returns
    // true for a number greater than number
    while (isPrime(number) == -1) {
        number++;
    }
    return number;
}

int isInTable(TABLE* hashTable, int Id){

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

int numberOfMailsInHashTable(TABLE* hashTable){
    int i,counter=0;
    for(i=0;i<hashTable->size;i++){
        if(hashTable->mails[i].mailID != -1){
            counter++;
        }
    }
    return counter;
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
void rehash(TABLE* oldTable, TABLE* newTable, int technique){
    int i;
    for(i=0;i<oldTable->size;i++){
        if(oldTable->mails[i].mailID != -1){
            addToTheHashTable(newTable,oldTable->mails[i],technique);
        }
    }
}

TABLE* createHashTable(int size){
    int i;
    TABLE* hashTable = (TABLE*) malloc (sizeof(TABLE));
    hashTable->mails = (MAIL*)malloc(size * sizeof(MAIL));
    hashTable->size = size;
    for(i=0;i<size;i++){
        hashTable->mails[i].mailID = -1;
    }
    return hashTable;
}

void readMails(TABLE** hashTableAddress,char* path,int numberOfMails, int technique){
    int i;
    char* temp = (char*)malloc(51*sizeof(char));
    char* name = (char*)malloc(51*sizeof(char));
    TABLE* hashTable = *hashTableAddress;
    TABLE* newTable;
    MAIL mail;
    for(i=1;i<=numberOfMails;i++){
        strcpy(temp,path);
        sprintf(name, "%s/%d.txt", temp,i);
        mail = readFromFile(name);
        if(isInTable(*hashTableAddress, mail.mailID) == 0){ // if it's already in the hashTable
            printf("mail with Id %d is already in the hashTable\n",mail.mailID);
        }
        else{
            addToTheHashTable(*hashTableAddress,mail,technique);
            printMails(*hashTableAddress);
        }
        if((float) (numberOfMailsInHashTable(*hashTableAddress)) / (*hashTableAddress)->size > 0.5){
            //do
            hashTable = *hashTableAddress;
            printf("-----------------Buraya dikkat--------------");
            printMails(hashTable);
            newTable = createHashTable(nextPrime(hashTable->size * 2));
            rehash(*hashTableAddress,newTable,technique);
            *hashTableAddress = newTable;
            free(hashTable);
            printMails(newTable);
        }
    }

    free(temp);
    free(name);
}

void searchMail(TABLE* hashTable ,int Id, char* sender, int technique){
    int counter=0;
    int key = Id + ((int)(*sender)) - 65;
    int index = HASH1(key,hashTable->size);
    int i=1;

    while(hashTable->mails[index].mailID != Id && counter < 50){
        if(technique == 1){
            index = (HASH1(key,hashTable->size) + i * HASH2(key)) % hashTable->size;
        }
        else{
            index = (HASH1(key,hashTable->size) + i) % hashTable->size;
        }
        i++;
        counter++;
    }
    if(counter==50){
        printf("mail with given ID couldn't have been found in the hash table\n");
    }
    else{
        printf("Recipient: %s\n",hashTable->mails[index].recipient);
        printf("Date: %d\n",hashTable->mails[index].day);
        printf("Number of words: %d\n",hashTable->mails[index].wordCount);
    }

    return;
}

int main(){
    int choice,technique,numberOfMails,Id;
    TABLE* hashTable = createHashTable(11);
    char* path = (char*)malloc(51*sizeof(char));
    char* sender = (char*)malloc(51*sizeof(char));
    printf("which open addressing technique would you like to use?\n");
    printf("to select double hashing press 1...\n");
    printf("to select linear probing press 2...\n");
    scanf("%d",&technique);
    while(1){
	    printf("\n--MAIN MENU--\n");
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
                readMails(&hashTable,path,numberOfMails,technique);
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