#include "card.h"
#include <stdio.h>

typedef unsinged char uint8_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t name[200];
	uint8_t i = 0;
	fgets(name);
	while (name[i++] != '\0');
	i--;
	if (i < 20||i>24)
		return WRONG_NAME;
	else
		return OK;
}