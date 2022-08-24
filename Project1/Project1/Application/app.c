/*
 * app.c
 *
 *  Created on: Aug 23, 2022
 *      Author: HP
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "app.h"


//app start function 
//takes a pointer to an array of pointers to 100 locaiton in heap.
void appStart (ST_Accounts_DB_t* Accounts_DB[100])
{
ST_cardData_t * cardData = (ST_cardData_t *) malloc(sizeof(ST_cardData_t));
ST_terminalData_t * terminalData = (ST_terminalData_t*) malloc(sizeof(ST_transaction_t));
ST_transaction_t * trnsData = (ST_transaction_t*)malloc(sizeof(ST_transaction_t));
EN_trnsState_t transstate;
EN_cardError_t cardError;
EN_serError_t serverError;
EN_terError_t terminalError;

	uint8_t PAN[20];
	float Amount;
	{
	printf("Reading AccountsDB");
	FILE* fp;
	fp = fopen("AccountsDB.txt", "r");
	int i = 0;
	while (fscanf(fp, "%f %s", &Amount, PAN))
	{
		Accounts_DB[i]->Balance = Amount;
		for (int j = 0; j < 20; j++)
		{
			Accounts_DB[i]->primaryAccountNumber[j] = PAN[j];
		}
		i++;
	}
	fclose(fp);

	/**** Card module *****/
	//read card data and loop till input is correct.

	//read card holder name
	do{
	cardError = getCardHolderName(cardData);
	}while(cardError != OK);


	//read card expirations date.
	do{
	cardError = getCardExpiryDate(cardData);
	}while(cardError != OK);

	
	//read primary account number.
	do{
	cardError = getCardPAN(cardData);
	}while(cardError != OK);

	/***    Terminal module   ***/
	do{
		terminalError = getCardPAN(terminalData);
	}while(cardError != OK_terError);

	terminalError = isCardExpired(cardData,terminalData);
	
	if(terminalError == EXP_CARD){
		printf("expired card\n");
		return;
	}
	
	do{
		terminalError = getTransactionAmount(terminalData);
	}while(terminalError != OK_terError);
	
	terminalError = isBelowMaxAmount(terminalData);
	if(terminalError == INVALID_AMOUNT){
		printf("amount exceeding amount\n");
		return;
	}

	/*** Server module ***/

	transstate = recieveTransactionData(trnsData);
	if(transstate == Approved){
		transstate = saveTransaction(trnsData);
	}



}


}










