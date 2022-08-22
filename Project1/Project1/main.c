#include "Card/card.h"
#include <stdio.h>

void main(void) {
	ST_cardData_t s1;
	int i = getCardHolderName(&s1);
	printf("%d", i);
	return;
}