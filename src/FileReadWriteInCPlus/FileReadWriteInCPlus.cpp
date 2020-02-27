/*
*		ios::app	将输出数据添加到文件的结尾
*		ios::ate	讲一个文件打开作为输出文件，并移动到文件尾。可以在文件的任何位置写数据
*		ios::in		打开一个文件作为输入文件
*		ios::out	打开一个文件作为输出文件
*		ios::trunc	如果文件有内容则将文件内容丢弃
*		ios::binary	打开一个文件进行二进制输入或输出
*/

#include "commonH.h"
#include "example.h"

void baseWrite();		//基本的写入操作
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
	std::ofstream outClientFile( "c:\\1.txt", ios::out);		//ios::out向文件输出数据,ios::app文件末尾添加数据

	if( !outClientFile)
	{
		cerr << "File open FAILED!!!" << endl;
		exit(1);
	}

	int account;
	char name[30];
	double balance;

	while( cin >> account >> name >> balance)		//ctrl+z+回车 结束(windows)  ctrl+d结束(linux)
	{
		outClientFile << account << " " << name << " " << balance << endl;
	}

	outClientFile.close();				//执行析构时自动执行，本行可不写
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

	cout << std::left		//左对齐
		<< std::setw(10)	//下一个输出将占用至少10个单位长度,只一次有效
		<< "Account" <<
		std::setw(13) << "Name"
		<<  "Balance" << endl
		<< std::fixed << std::showpoint;

	while( inClientFile >> account >> name >> balance)
	{
		cout << std::left << std::setw(10) << account
			<< std::setw(13) << name
			<< std::setw(7) << std::setprecision(2)		//两位小数
			<< std::right << balance << endl;
	}
}
