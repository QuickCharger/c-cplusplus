#include <iostream>
#include <string>

using namespace std;

#ifdef BEFORE
/************************************************************************/
/* BEFORE                                                                     */
/************************************************************************/

class Image {
	int m_id;
	static int s_next;
public:
	Image() {
		m_id = s_next++;
		cout << "    $$ ctor: " << m_id << endl;
	}
	~Image() {
		cout << "    dtor: " << m_id << endl;
	}
	void draw() {
		cout << "    drawing image " << m_id << endl;
	}
};

int Image::s_next = 1;

int main()
{
	Image images[5];

	int i = 0;
	while (true) {
		cout << "Exit[0], Image[1-5]: ";
		cin >> i;
		if (i == 0)
			break;
		images[i - 1].draw();
	}
}
#endif

#ifdef AFTER
/************************************************************************/
/* AFTER                                                                     */
/************************************************************************/
class RealImage {
	int m_id;
public:
	RealImage(int i) {
		m_id = i;
		cout << "    $$ ctor: " << m_id << endl;
	}
	~RealImage() {
		cout << "    dtor: " << m_id << endl;
	}
	void draw() {
		cout << "    drawing image " << m_id << endl;
	}
};

class Image {
	RealImage *m_TheRealThing;
	int m_id;
	static int s_next;
public:
	Image() {
		m_id = s_next++;
		m_TheRealThing = new RealImage(m_id);
	}
	~Image() {
		delete m_TheRealThing;
	}
	void draw() {
		m_TheRealThing->draw();
	}
};

int Image::s_next = 1;

int main() {
	Image images[5];

	int i = 0;
	while (true) {
		cout << "Exit[0], Image[1-5]: ";
		cin >> i;
		if (i == 0)
			break;
		images[i - 1].draw();
	}
}
#endif

#ifdef EXP2
/************************************************************************/
/* EXP2                                                                     */
/************************************************************************/
class Subject {
public:
	virtual void execute() = 0;
};

class RealSubject : public Subject {
	string str;
public:
	RealSubject(string s) {
		str = s;
	}
	void execute() {
		cout << str << endl;
	}
};

class ProxySubject : public Subject {
	string first, second, third;
	RealSubject *ptr;
public:
	ProxySubject(string s) {
		int num = s.find_first_of(' ');
		first = s.substr(0, num);
		s = s.substr(num + 1);
		num = s.find_first_of(' ');
		second = s.substr(0, num);
		s = s.substr(num + 1);
		num = s.find_first_of(' ');
		third = s.substr(0, num);
		s = s.substr(num + 1);
		ptr = new RealSubject(s);
	}
	~ProxySubject() {
		delete ptr;
	}
	RealSubject* operator->() {
		cout << first << ' ' << second << ' ';
		return ptr;
	}
	void execute() {
		cout << first << ' ' << third << ' ';
		ptr->execute();
	}
};

int main() {
	ProxySubject obj(string("the quick brown fox jumped over the dog"));
	obj->execute();
	obj.execute();

	getchar();
	return 0;
}
#endif

/************************************************************************/
/* EXP3                                                                     */
/************************************************************************/
class Person {
	string nameString;
	static string list[];
	static int next;
public:
	Person() {
		nameString = list[next++];
	}
	string name() {
		return nameString;
	}
};

string Person::list[] = {
	"Tom", "Dick", "Harry", "Bubba"
};

int Person::next = 0;

class PettyCashProtected {
	int balance;
public:
	PettyCashProtected() {
		balance = 500;
	}
	bool withdraw(int amount) {
		if (amount > balance)
			return false;
		balance -= amount;
		return true;
	}
	int getBalance() {
		return balance;
	}
};

class PettyCash {
	PettyCashProtected realThing;
public:
	bool withDraw(Person& p, int amount) {
		if (p.name() == "Tom" || p.name() == "Harry" || p.name() == "Bubba")
			return realThing.withdraw(amount);
		else
			return false;
	}
	int getBalance() {
		return realThing.getBalance();
	}
};

int main() {
	PettyCash pc;
	Person workers[4];
	for (int i = 0, amount = 100; i < 4; i++, amount += 100)
		if (!pc.withDraw(workers[i], amount))
			cout << "No money for " << workers[i].name() << endl;
		else
			cout << amount << " dollars for " << workers[i].name() << endl;
	cout << "Remaining balance is " << pc.getBalance() << endl;

	getchar();
	return 0;
}
