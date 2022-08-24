#include <stdio.h>
#include "Server.h"
#include<ctype.h>
#include<stdlib.h>

 ST_Accounts_DB_t Accounts_DB[100];
int count=0;


/*{
isValidAccount
Dicribtion:checks if  the account is valid.
argument:transmation Data
return:EN_serverError_t
}*/

EN_serError_t isValidAccount(ST_cardData_t*cardData)
{
	uint8_t* PAN =cardData->primaryAccountNumber;
for(int i=0;i<100;i++)
	{
		if(Accounts_DB[i].primaryAccountNumber!= PAN)

		return Account_NOT_Found;
	else
	{ count=i;
		return OK_serError;}
	}
}
/*{
isAmountAvailable
Dicribtion:checks if  the transmation Amount find in balance
argument:transmation Data
return:EN_serverError_t
}*/
EN_serError_t isAmountAvailable(ST_terminalData_t* terminalData)
{
	float AccsBalance=Accounts_DB[count].Balance;
	float TerAmount=terminalData->transAmount;
	if(AccsBalance >=TerAmount)
	{
			return OK_serError;
		}
	else
		return Low_Balance;
}
/*{
saveTransaction
Dicribtion:save the transaction
argument:transmation Data
return:EN_serverError_t
}*/
EN_serError_t saveTransaction(ST_transaction_t*trnsData)
{    char trnsStat[100];
	if (trnsData->trnsState== Declined_Insuffecient_FUND || trnsData->trnsState ==Declined_Stolen_CARD)
	 {trnsStat[count]=trnsData->trnsState;
	 return trnsData->trnsState;}

	 else
	 {
		fprintf(trnsStat[count], "Approved \n the Transaction Sequence Number: %d\n\n", trnsData->trnsactionSequenceNumber);
		return OK_serError;
	 }

}
/*{
recieveTransactionData
Dicribtion:checks the account detailsand amount availability.
argument:transmation Data
return:EN_transmationState_t
}*/
EN_trnsState_t recieveTsactionData(ST_transaction_t* trnsData)
{
	if (isValidAccount(&trnsData->cardHolderData) == Account_NOT_Found)
	{
		trnsData->trnsState = Declined_Stolen_CARD;
		return Declined_Stolen_CARD;}

		else if (isAmountAvailable(&trnsData->terminalData)==Low_Balance)
		{
		trnsData->trnsState = Declined_Insuffecient_FUND;
		return Declined_Insuffecient_FUND;
	}
		else if (saveTransaction(trnsData) == Saving_Failed)
	{
			return Internal_Server_ERROR;
		}
		else
	{
	Accounts_DB[count].Balance -= trnsData->terminalData.transAmount;
	trnsData->trnsState = Approved;
	return Approved;
	}
}















