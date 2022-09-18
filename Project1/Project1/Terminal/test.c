#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Card/card.h"

void main(void){
    ST_terminalData_t * terminalData = (ST_terminalData_t*) malloc(sizeof(ST_terminalData_t));
    ST_cardData_t * card = (ST_cardData_t*) malloc(sizeof(ST_cardData_t));

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
    if(isBelowMaxAmount(terminalData) ==  EXCEED_MAX_AMOUNT){
        printf("exceeded max amount!!\n");
        return;
    }


}