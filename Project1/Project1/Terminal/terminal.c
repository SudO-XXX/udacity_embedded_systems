/*
 * Terminal.c
 *
 *  Created on: Aug 22, 2022
 *      Author: HP
 */

#include "terminal.h"
#include "card.h"
#include <stdio.h>
#include <time.h>



/*{
getTransactionDate
Dicribtion:ask for the transaction date and store it in terminal date
argument:terminalDate is 10 characters string in the format DD / MM / YYYY
return:EN_terminalError_t
}*/
EN_terError_t getTransactionDate(ST_terminalData_t* terminalDate)
{
	printf("Retreiving transaction date from system\n");
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Retrieved system date is  %02d/%02d/%02d \n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	terminalDate->transactionDate[0] = tm.tm_mday / 10 + '0';
	terminalDate->transactionDate[1] = tm.tm_mday % 10 + '0';
	terminalDate->transactionDate[2] = '/';
	terminalDate->transactionDate[3] = (tm.tm_mon + 1) / 10 + '0';
	terminalDate->transactionDate[4] = (tm.tm_mon + 1) % 10 + '0';
	terminalDate->transactionDate[5] = '/';
	terminalDate->transactionDate[6] = '0' + (tm.tm_year + 1900) / 1000;
	terminalDate->transactionDate[7] = '0' + ((tm.tm_year + 1900) % 1000) / 100;
	terminalDate->transactionDate[8] = '0' + ((tm.tm_year + 1900) % 100) / 10;
	terminalDate->transactionDate[9] = '0' + (tm.tm_year + 1900) % 10;
	terminalDate->transactionDate[10] = '\0';
	return OK_terError;
}

/*{
isCardExpired
Dicribtion:compares the card expiry date with the transaction date
argument:cardDate ,terminalDate
return:EN_terminalError_t
}*/

EN_terError_t isCardExpired(ST_cardData_t* cardDate, ST_terminalData_t* terminalDate)
{   //for card Data
	int card_month = (cardDate->cardExpirationDate[0] - '0') * 10 + cardDate->cardExpirationDate[1] - '0';
	int card_year = (cardDate->cardExpirationDate[3] - '0') * 10 + cardDate->cardExpirationDate[4] - '0' + 2000;
	//for terminalDate
	int ter_month = (terminalDate->transactionDate[3] - '0') * 10 + terminalDate->transactionDate[4] - '0';
	int ter_year = (terminalDate->transactionDate[6] - '0') * 1000 + (terminalDate->transactionDate[7] - '0') * 100 + (terminalDate->transactionDate[8] - '0') * 10 + +terminalDate->transactionDate[9] - '0';
	if ((ter_year == card_year && ter_month > card_month) || ter_year > card_year)
		return EXP_CARD;


	return OK_terError;
}

/*{
isValidCardPAN
Dicribtion:checks if the PAN is a true  number or not.
argument:cardDate
return:EN_terminalError_t
}*/

EN_terError_t isValidCardPAN(ST_cardData_t* cardDate)
{
	if (strlen(cardDate) != 20)
		return INVALID_CARD;
	int card_PAN[20];
	int i = 0;
	while (i < 20) {
		card_PAN[i] = cardDate->primaryAccountNumber[i];
		i++;
	}
	for (int i = 0; i < 20; i++)

		if ((card_PAN[i] > 9 || card_PAN[i]<0))
			return INVALID_CARD;

		else
			return OK_terError;
}
/*{
getTransactionAmount
Dicribtion:asks for the transaction amount and saves it into terminal data.
argument:terminalData
return:EN_terminalError_t
}*/


EN_terError_t getTransactionAmount(ST_terminalData_t* terminalDate)
{
	float Amount = 0;
	printf("Enter the cost price of the product: ");
	scanf("%f", &Amount);
	if (Amount > 0) {
		terminalDate->transAmount = Amount;
		return OK_terError;

	}
	return INVALID_AMOUNT;
}

/*{
getTransactionAmount
Dicribtion:compares the transaction amount with the terminal max amount
argument:terminalData
return:EN_terminalError_t
}*/
EN_terError_t isBelowMaxAmount(ST_terminalData_t* terminalDate)
{
	if (terminalDate->transAmount < terminalDate->maxTransAmount)
	{
		return OK_terError;

	}
	return EXCEED_MAX_AMOUNT;
}
/*{
getTransactionAmount
Dicribtion:set the maximum allowed amount into terminal data.
argument:terminalData
return:EN_terminalError_t
}*/
EN_terError_t setMaxAmount(ST_terminalData_t* terminalData)
{
	float maxAmount;
	printf("The maxAmount for a transaction is : ");
	scanf("%f", &maxAmount);
	if (maxAmount > 0)
	{
		terminalData->maxTransAmount = maxAmount;
		return OK_terError;
	}

	return INVALID_MAX_AMOUNT;

}


