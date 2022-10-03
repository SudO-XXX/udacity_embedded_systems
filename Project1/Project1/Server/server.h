/*
 * Serval.h
 *
 *  Created on: Aug 23, 2022
 *      Author: HP
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "../Terminal/terminal.h"
#include "../Card/card.h"


typedef enum EN_serError_t
{
	OK_serError,
	Account_NOT_Found,
	Low_Balance,
	Transaction_NOT_Found,
	Saving_Failed
}EN_serError_t;
typedef struct ST_Accounts_DB_t
{
	float Balance;
	uint8_t primaryAccountNumber[21];
}ST_Accounts_DB_t;
typedef enum EN_trnsState_t
{
	Approved,
	Declined_Stolen_CARD,
	Declined_Insuffecient_FUND,
	Internal_Server_ERROR
}EN_trnsState_t;

typedef struct ST_transaction_t
{
	ST_cardData_t* cardHolderData;
	ST_terminalData_t* terminalData;
	EN_trnsState_t trnsState;
	uint32_t trnsactionSequenceNumber;
}ST_transaction_t;


void DataBaseGenerator(void);
void readAccountDB(void);
void updateAccountDB(void);

EN_serError_t isValidAccount(ST_cardData_t*);
EN_serError_t isAmountAvailable(ST_terminalData_t*);
EN_serError_t saveTransaction(ST_transaction_t*);
EN_trnsState_t recieveTransactionData(ST_transaction_t*);
EN_trnsState_t isDeclinedAccount(ST_cardData_t*);

#endif /* SERVER_H_ */
