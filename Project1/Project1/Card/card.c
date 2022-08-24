#include "card.h"
#include <stdio.h>
EN_cardError_t getCardHolderName(ST_cardData_t* cardData){
    uint8_t name[200];
    uint8_t i = 0,u = 0;
    puts("Enter card holder name: ");
    fgets(name,200,stdin);
    while(name[i++] !='\0');
    if(i<=24&&i>=20){
        for(u = 0;u<i;u++)
            cardData->cardHolderName[u] = name[u];
        return OK;
    }
    else
        return WRONG_NAME;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData){
    uint8_t date[200];
    uint8_t i = 0,u = 0;
    puts("Enter card expiry date:");
    fgets(date,200,stdin);
    while(date[i++] !='\0');
    if(i<=5){
        for(u = 0;u<i;u++)
            cardData->cardExpirationDate[u] = date[u];
        return OK;
    }
    else
        return WRONG_NAME;
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData){
    uint8_t pan[200];
    uint8_t i = 0,u = 0;
    puts("Enter card primary account number: ");
    fgets(pan,200,stdin);
    while(pan[i++] !='\0');
    if(i<=24&&i>=20){
        for(u = 0;u<i;u++)
            cardData->primaryAccountNumber[u] = pan[u];
        return OK;
    }
    else
        return WRONG_NAME;
}