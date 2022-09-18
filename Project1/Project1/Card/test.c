#include "card.h"
#include <stdio.h>
#include <string.h>

void main(){
    while(1){
    ST_cardData_t card ;
    while(getCardHolderName(&card) != OK){
        printf("Name must be between 20 and 24 chars!\n");
    }
    printf("%s\n",card.cardHolderName);


    while(getCardExpiryDate(&card) != OK){
        printf("Expiration date should be in the following form: mm/yy !\n");
    }
    printf("%s\n",card.cardExpirationDate);

    while(getCardPAN(&card) != OK){
        printf("wrong PAN, PAN IS 20 NUMBERS!\n");
    }
    printf("%s\n",card.primaryAccountNumber);
    getchar();
    }
}