#include <iostream>

using namespace std;

#ifdef BEFORE
/************************************************************************/
/* BEFORE                                                                     */
/************************************************************************/

class Gazillion {
public:
	Gazillion() {
		m_value_one = m_num / Y;
		m_value_two = m_num % Y;
		++m_num;
	}
	void report() {
		cout << m_value_one << m_value_two << ' ';
	}
	static int X, Y;
private:
	int m_value_one;
	int m_value_two;
	static int m_num;
};

int Gazillion::X = 6;
int Gazillion::Y = 10;
int Gazillion::m_num = 0;

int main()
{
	Gazillion matrix[6][10];
	for (int i = 0; i < Gazillion::X; ++i)
	{
		for (int j = 0; j < Gazillion::Y; ++j)
			matrix[i][j].report();
		cout << endl;
	}

	getchar();
	return 0;
}
#endif

#ifdef AFTER
/************************************************************************/
/* AFTER                                                                     */
/************************************************************************/

class Gazillion {
	int m_value_one;
public:
	Gazillion(int value_one) {
		m_value_one = value_one;
		cout << "ctor: " << m_value_one << endl;
	}
	~Gazillion() {
		cout << m_value_one << ' ';
	}
	void report(int value_two) {
		cout << m_value_one << value_two << ' ';
	}
};

class Factory {
	static Gazillion *s_pool[];
public:
	static int X, Y;
	static Gazillion * get_fly(int in) {
		if (!s_pool[in])
			s_pool[in] = new Gazillion(in);
		return s_pool[in];
	}
	static void clean_up() {
		cout << "dtors: ";
		for (int i = 0; i < X; ++i)
			if (s_pool[i])
				delete s_pool[i];
		cout << endl;
	}
};

int Factory::X = 6;
int Factory::Y = 10;
Gazillion *Factory::s_pool[] = {
	0,0,0,0,0,0
};

int main() {
	for (int i = 0; i < Factory::X; ++i)
		for (int j = 0; j < Factory::Y; ++j)
			Factory::get_fly(i)->report(j);
	cout << endl;
	Factory::clean_up();

	getchar();
}
#endif

/************************************************************************/
/* EXP2                                                                     */
/************************************************************************/
class Icon {
	char m_pName[20];
	int m_nWidth;
	int m_nHeight;
public:
	Icon(char* fileName) {
		strcpy(m_pName, fileName);
		if (!strcmp(fileName, "go")) {
			m_nWidth = 20;
			m_nHeight = 20;
		}
		if (!strcmp(fileName, "stop")) {
			m_nWidth = 40;
			m_nHeight = 40;
		}
		if (!strcmp(fileName, "select")) {
			m_nWidth = 60;
			m_nHeight = 60;
		}
		if (!strcmp(fileName, "undo")) {
			m_nWidth = 30;
			m_nHeight = 30;
		}
	}
	const char* getName() {
		return m_pName;
	}
	void draw(int x, int y) {
		cout << " drawing " << m_pName << ": upper left (" << x << "," << y << ") - lower right (" << x + m_nWidth << "," << y + m_nHeight << ")" << endl;
	}
};

class FlyweightFactory {
	enum {
		MAX_ICONS = 5
	};
	static int m_nNumIcons;
	static Icon *m_pIcons[MAX_ICONS];
public:
	static Icon* getIcon(char* name) {
		for (int i = 0; i < m_nNumIcons; ++i)
			if (!strcmp(name, m_pIcons[i]->getName()))
				return m_pIcons[i];
		m_pIcons[m_nNumIcons] = new Icon(name);
		return m_pIcons[m_nNumIcons++];
	}
	static void reportTheIcons() {
		cout << "Active Flyweights: ";
		for (int i = 0; i < m_nNumIcons; ++i)
			cout << m_pIcons[i]->getName() << " ";
		cout << endl;
	}
};

int FlyweightFactory::m_nNumIcons = 0;
Icon* FlyweightFactory::m_pIcons[];

class DialogBox {
public:
	DialogBox(int x, int y, int incr) : m_nIconsOriginX(x), m_nIconsOriginY(y), m_nIconsXIncrement(incr) {
	}
	virtual void draw() = 0;
protected:
	Icon *m_pIcons[3];
	int m_nIconsOriginX;
	int m_nIconsOriginY;
	int m_nIconsXIncrement;
};

class FileSelection : public DialogBox {
public:
	FileSelection(Icon *first, Icon *second, Icon *third) : DialogBox(100, 100, 100) {
		m_pIcons[0] = first;
		m_pIcons[1] = second;
		m_pIcons[2] = third;
	}
	void draw() {
		cout << "drawing FileSelection: " << endl;
		for (int i = 0; i < 3; ++i) {
			m_pIcons[i]->draw(m_nIconsOriginX + (i * m_nIconsXIncrement), m_nIconsOriginY);
		}
	}
};

class CommitTransaction : public DialogBox {
public:
	CommitTransaction(Icon *first, Icon *second, Icon *third) : DialogBox(150, 150, 150) {
		m_pIcons[0] = first;
		m_pIcons[1] = second;
		m_pIcons[2] = third;
	}
	void draw() {
		cout << "drawing ComitTransaction: " << endl;
		for (int i = 0; i < 3; ++i) {
			m_pIcons[i]->draw(m_nIconsOriginX + (i * m_nIconsXIncrement), m_nIconsOriginY);
		}
	}
};

int main() {
	DialogBox *dialogs[2];
	dialogs[0] = new FileSelection(FlyweightFactory::getIcon("go"),
		FlyweightFactory::getIcon("stop"), FlyweightFactory::getIcon("select"));
	dialogs[1] = new CommitTransaction(FlyweightFactory::getIcon("select"),
		FlyweightFactory::getIcon("stop"), FlyweightFactory::getIcon("undo"));

	for (int i = 0; i < 2; ++i)
		dialogs[i]->draw();

	FlyweightFactory::reportTheIcons();

	getchar();
	return 0;
}
