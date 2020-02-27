#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Strategy;

class TestBed {
private:
	Strategy *strategy;
public:
	enum StrategyType {
		Dummy, Left, Right, Center
	};
	TestBed() {
		strategy = nullptr;
	}
	void setStrategy(int type, int width);
	void doIt();
};

class Strategy {
public:
	Strategy(int a_width) : width(a_width) {}
	void format() {
		char line[80], word[30];
		ifstream inFile("quote.txt", ios::in);
		line[0] = '\0';

		inFile >> word;
		strcat(line, word);
		while (inFile >> word) {
			if (strlen(line) + strlen(word) + 1 > width)
				justify(line);
			else
				strcat(line, " ");
			strcat(line, word);
		}
		justify(line);
	}
protected:
	int width;
private:
	virtual void justify(char* line) = 0;
};

class LeftStrategy : public Strategy {
public:
	LeftStrategy(int a_width) : Strategy(width) {}
private:
	void justify(char* line) {
		cout << line << endl;
		line[0] = '\0';
	}
};

class RightStrategy : public Strategy {
public:
	RightStrategy(int width) : Strategy(width) {}
private:
	void justify(char* line) {
		char buf[80];
		int offset = width - strlen(line);
		memset(buf, ' ', 80);
		strcpy(&(buf[offset]), line);
		cout << buf << endl;
		line[0] = '\0';
	}
};

class CenterStrategy : public Strategy {
public:
	CenterStrategy(int width) : Strategy(width) {}
private:
	void justify(char* line) {
		char buf[80];
		int offset = (width - strlen(line)) / 2;
		memset(buf, ' ', 80);
		strcpy(&(buf[offset]), line);
		cout << buf << endl;
		line[0] = '\0';
	}
};

void TestBed::setStrategy(int type, int width) {
	delete strategy;
	if (type == Left)
		strategy = new LeftStrategy(width);
	else if (type == Right)
		strategy = new RightStrategy(width);
	else if (type == Center)
		strategy = new CenterStrategy(width);
}

void TestBed::doIt() {
	strategy->format();
}

int main()
{
	TestBed test;
	int answer, width;
	cout << "Exit(0) Left(1) Right(2) Center(3):";
	cin >> answer;
	while (answer) {
		cout << "Width: ";
		cin >> width;
		test.setStrategy(answer, width);
		test.doIt();
		cout << "Exit(0) Left(1) Right(2) Center(3):";
		cin >> answer;
	}

	getchar();
	return 0;
}
