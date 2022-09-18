#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main(void){

    ST_terminalData_t * terminalData = (ST_terminalData_t*) malloc(sizeof(ST_terminalData_t));
    ST_cardData_t * card = (ST_cardData_t*) malloc(sizeof(ST_cardData_t));
    ST_transaction_t * transaction = (ST_transaction_t*) malloc(sizeof(ST_transaction_t));

    DataBaseGenerator();
    readAccountDB();
    while(getTransactionDate(terminalData)!= OK_terError){
        printf("system date is invalid!\n");
    }
    
    while(getCardHolderName(card) != OK){
        printf("Name must be between 20 and 24 chars!\n");
    }
    printf("%s\n",card->cardHolderName);

/*****************************/

    while(getCardExpiryDate(card) != OK){
        printf("Expiration date should be in the following form: mm/yy !\n");
    }
    printf("%s\n",card->cardExpirationDate);

    if(isCardExpired(card,terminalData)==EXP_CARD){
        printf("card expired!!\n");
        return;
    }

/*****************************/
    while(getCardPAN(card) != OK){
        printf("wrong PAN, PAN IS 20 NUMBERS!\n");
    }
    printf("%s\n",card->primaryAccountNumber);
    if(isValidCardPAN(card)){
        printf("invalid card number!\n");
        return;
    }

/*****************************/
    

    setMaxAmount(terminalData);
    getTransactionAmount(terminalData);
    
    transaction->cardHolderData = card;
    transaction->terminalData = terminalData;
    
    recieveTransactionData(transaction);

	uint8_t state[30];
	switch(transaction->trnsState){
		case Approved: 					 strcpy(state,"Approved");break;
		case Declined_Stolen_CARD:		 strcpy(state,"Declined_Stolen_CARD");break;
		case Declined_Insuffecient_FUND: strcpy(state,"Declined_Insuffecient_FUND");break;
		case Internal_Server_ERROR:		 strcpy(state,"Internal_Server_ERROR");break;
	}
	

    FILE* FilePointer = fopen("TransactionDB.txt","w");
    fseek(FilePointer,-sizeof(uint8_t),SEEK_END);
	fprintf(FilePointer,"%d,%s,%s\n",transaction->trnsactionSequenceNumber,transaction->cardHolderData->primaryAccountNumber,state);
	fclose(FilePointer);
}