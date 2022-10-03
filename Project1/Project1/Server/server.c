#include <stdio.h>
#include "server.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define DB_SIZE 255
ST_Accounts_DB_t *Accounts_DB[DB_SIZE] ;
ST_Accounts_DB_t *Declined_Accouns[DB_SIZE];
ST_transaction_t *Transaction_DB [DB_SIZE];
uint8_t AccountIndex = 0;
uint8_t TransactionSequenceNumber = 0;
void DataBaseGenerator(void)
{
	srand(0);
	FILE *filepointer;
	filepointer = fopen("DataBase.txt", "w");
	char pan[21];
	for (int i = 0; i < 255; i++)
	{
		for (int u = 0; u < 20; u++)
			pan[u] = rand() % 10 + '0';
		pan[20] = '\0';
		fprintf(filepointer, "%f,%s\n", rand()%10000 / 7.1, pan);
	}
	fclose(filepointer);
}
/*****************************/
void readAccountDB(void)
{
	FILE *filepointer = fopen("DataBase.txt", "r");
	for (int i = 0; i < DB_SIZE; i++){
		Accounts_DB[i] = (ST_Accounts_DB_t *) malloc(sizeof(ST_Accounts_DB_t));
		fscanf(filepointer, "%f,%s", &(Accounts_DB[i]->Balance), Accounts_DB[i]->primaryAccountNumber);
	}

	fclose(filepointer);
	filepointer = fopen("Declined_accounts.txt","r");
	for(int i = 0;i<DB_SIZE||filepointer==EOF;i++){
		Declined_Accouns[i] = (ST_Accounts_DB_t*) malloc(sizeof(ST_Accounts_DB_t));
		fscanf(filepointer, "%s", Declined_Accouns[i]->primaryAccountNumber);
	}
	fclose(filepointer);
}
/*****************************/
void updateAccountDB(void)
{
	FILE *filepointer = fopen("DataBase.txt", "w");
	for (int i = 0; i < DB_SIZE; i++)
	{
		fprintf(filepointer, "%f,%s\n", Accounts_DB[i]->Balance, Accounts_DB[i]->primaryAccountNumber);
	}
	fclose(filepointer);
}
/*****************************/
EN_serError_t isValidAccount(ST_cardData_t *cardData)
{
	uint8_t *PAN = cardData->primaryAccountNumber;
	for (int i = 0; i < 100; i++)
		if (!strcmp(Accounts_DB[i]->primaryAccountNumber, PAN))
		{
			AccountIndex = i;
			return OK_serError;
		}
	return Account_NOT_Found;
}

/*****************************/

EN_serError_t isAmountAvailable(ST_terminalData_t *terminalData)
{
	if (Accounts_DB[AccountIndex]->Balance >= terminalData->transAmount)
	{
		return OK_serError;
	}
	else
		return Low_Balance;
}

/*****************************/

EN_serError_t saveTransaction(ST_transaction_t *TransactionData)
{
	// if (trnsData->trnsState== Declined_Insuffecient_FUND || trnsData->trnsState ==Declined_Stolen_CARD){
	// 	trnsStat[count]=trnsData->trnsState;
	// 	return trnsData->trnsState;
	// }

	// else
	// {
	// 	fprintf(trnsStat[count], "Approved \n the Transaction Sequence Number: %d\n\n", trnsData->trnsactionSequenceNumber);
	// 	return OK_serError;
	// }

	TransactionData->trnsactionSequenceNumber = TransactionSequenceNumber;

	Transaction_DB[TransactionSequenceNumber] = TransactionData;
	if(Transaction_DB[TransactionSequenceNumber]==NULL)
		return Saving_Failed;

	TransactionSequenceNumber++;
	return OK_serError;
	
}

EN_trnsState_t isDeclinedAccount(ST_cardData_t* cardData){
	for(int i = 0;i<DB_SIZE;i++){
		if(!strcmp(Declined_Accouns[i]->primaryAccountNumber,cardData->primaryAccountNumber))
			return Declined_Stolen_CARD;
	}
	return OK_serError;
}
/*****************************/
EN_trnsState_t recieveTransactionData(ST_transaction_t *TransactionData)
{

	if (isValidAccount(TransactionData->cardHolderData) == Account_NOT_Found)
	{
		TransactionData->trnsState = Internal_Server_ERROR;
		return Internal_Server_ERROR;
	}
	else if(isDeclinedAccount(TransactionData->cardHolderData)==Declined_Stolen_CARD){
		TransactionData->trnsState = Declined_Stolen_CARD;
		return Declined_Stolen_CARD;
	}
	else if (isAmountAvailable(TransactionData->terminalData) == Low_Balance)
	{
		TransactionData->trnsState = Declined_Insuffecient_FUND;
		return Declined_Insuffecient_FUND;
	}
	else if (saveTransaction(TransactionData) == Saving_Failed)
	{
		return Internal_Server_ERROR;
	}
	else
	{
		Accounts_DB[AccountIndex]->Balance -= TransactionData->terminalData->transAmount;
		TransactionData->trnsState = Approved;
		updateAccountDB();
		return Approved;
	}
}
