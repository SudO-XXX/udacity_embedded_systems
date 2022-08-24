/*
 * Terminal.h
 *
 *  Created on: Aug 22, 2022
 *      Author: HP
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_
#include "card.h"


 //EN_terminalError_t

typedef enum
{
	OK_terError,
	WRONG_DATE,
	EXP_CARD,
	INVALID_CARD,
	INVALID_AMOUNT,
	EXCEED_MAX_AMOUNT,
	INVALID_MAX_AMOUNT
}EN_terError_t;
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;



EN_terError_t getTransactionDate(ST_terminalData_t*);
EN_terError_t isCardExpired(ST_cardData_t*, ST_terminalData_t* );
EN_terError_t isValidCardPAN(ST_cardData_t*);
EN_terError_t getTransactionAmount(ST_terminalData_t*);
EN_terError_t isBelowMaxAmount(ST_terminalData_t*);
EN_terError_t setMaxAmount(ST_terminalData_t*);

#endif /* TERMINAL_H_ */
