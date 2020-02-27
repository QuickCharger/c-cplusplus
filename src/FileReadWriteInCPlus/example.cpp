#include "example.h"

void	example1()
{
	ifstream inClientFile( "c:\\clients.txt", ios::in);
	if( !inClientFile)
	{
		cerr << "File open FAILED" << endl;
		exit(1);
	}

	int		request;
	int		account;
	char	name[30];
	double	balance;

	request = getRequest();

	while( request != END)
	{
		switch( request)
		{
		case ZERO_BALANCE:
			cout << "Accounts with zero balance: " << endl;
			break;
		case CREDIT_BALANCE:
			cout << "Accounts with credit balances: " << endl;
			break;
		case DEBIT_BALANCE:
			cout << "Accounts with debit balances: " << endl;
			break;
		}

		inClientFile >> account >> name >>balance;

		while( !inClientFile.eof())
		{
			if( shouldDisplay(request, balance))
			{
				outputLine(account, name, balance);
			}
			inClientFile >> account >> name >> balance;
		}
		inClientFile.clear();
		inClientFile.seekg(0);
		request = getRequest();
	}
	cout << "End of run." << endl;
	return ;
}

int getRequest()
{
	int request;
	cout << "Enter request" << endl
	<<" 1 - List accounts with zero balances" << endl
	<< "2 - List accounts with credit balances" << endl
	<< "3 - List accounts with debit balance" << endl
	<< "4 - End of run" << fixed << showpoint;

	do{
		cout << endl << "?";
		cin >> request;
	}while( request << ZERO_BALANCE && request>END);

	return request;
}

bool shouldDisplay(int type, double balance)
{
	if( type == ZERO_BALANCE && balance==0)
		return true;

	if( type == CREDIT_BALANCE && balance<0)
		return true;

	if( type == DEBIT_BALANCE && balance>0)
		return true;

	return false;
}

void outputLine(int account, const string name, double balance)
{
	cout << std::left << setw(10) << account
		<< setw(13) << name
		<< setw(7) << std::setprecision(2) << std::right << balance
		<< endl;
}
