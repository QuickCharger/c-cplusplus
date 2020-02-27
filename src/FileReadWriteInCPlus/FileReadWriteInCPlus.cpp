/*
*		ios::app	�����������ӵ��ļ��Ľ�β
*		ios::ate	��һ���ļ�����Ϊ����ļ������ƶ����ļ�β���������ļ����κ�λ��д����
*		ios::in		��һ���ļ���Ϊ�����ļ�
*		ios::out	��һ���ļ���Ϊ����ļ�
*		ios::trunc	����ļ����������ļ����ݶ���
*		ios::binary	��һ���ļ����ж�������������
*/

#include "commonH.h"
#include "example.h"

void baseWrite();		//������д�����
void baseRead();

int main(int argc, char* argv[])
{
	//baseWrite();
	//baseRead();

	example1();

	system("pause");

	return 0;
}

void baseWrite()
{
	std::ofstream outClientFile( "c:\\1.txt", ios::out);		//ios::out���ļ��������,ios::app�ļ�ĩβ�������

	if( !outClientFile)
	{
		cerr << "File open FAILED!!!" << endl;
		exit(1);
	}

	int account;
	char name[30];
	double balance;

	while( cin >> account >> name >> balance)		//ctrl+z+�س� ����(windows)  ctrl+d����(linux)
	{
		outClientFile << account << " " << name << " " << balance << endl;
	}

	outClientFile.close();				//ִ������ʱ�Զ�ִ�У����пɲ�д
}


void baseRead()
{
	std::ifstream inClientFile( "c:\\1.txt", ios::in);

	if( !inClientFile)
	{
		cerr << "File coule not be opened" << endl;
		exit(1);
	}

	int account;
	char name[30];
	double balance;

	cout << std::left		//�����
		<< std::setw(10)	//��һ�������ռ������10����λ����,ֻһ����Ч
		<< "Account" <<
		std::setw(13) << "Name"
		<<  "Balance" << endl
		<< std::fixed << std::showpoint;

	while( inClientFile >> account >> name >> balance)
	{
		cout << std::left << std::setw(10) << account
			<< std::setw(13) << name
			<< std::setw(7) << std::setprecision(2)		//��λС��
			<< std::right << balance << endl;
	}
}
