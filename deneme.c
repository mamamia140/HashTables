#include <stdio.h>
#include <stdlib.h>

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

int main() {
    
    return 0;
}