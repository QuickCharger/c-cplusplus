#pragma once

#include "commonH.h"

enum	RequestType { ZERO_BALANCE = 1, CREDIT_BALANCE, DEBIT_BALANCE, END };
int		getRequest();
bool	shouldDisplay(int, double);
void	outputLine(int, const string, double);

void	example1();
int		getRequest();
bool	shouldDisplay(int type, double balance);
void	outputLine(int account, const string name, double balance);
