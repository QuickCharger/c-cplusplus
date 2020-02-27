#include <iostream>
#include <time.h>

using namespace std;

#ifdef EXP1
/************************************************************************/
/* EXP1                                                                     */
/************************************************************************/
class Base {
	void a() {
		cout << "a ";
	}
	void c() {
		cout << "c ";
	}
	void e() {
		cout << "e ";
	}
	virtual void ph1() = 0;
	virtual void ph2() = 0;
public:
	void execute() {
		a();
		ph1();
		c();
		ph2();
		e();
	}
};

class One : public Base {
	void ph1() {
		cout << "b ";
	}
	void ph2() {
		cout << "d ";
	}
};

class Two : public Base {
	void ph1() {
		cout << "2 ";
	}
	void ph2() {
		cout << "4 ";
	}
};

int main()
{
	Base *array[] = {
		&One(), &Two()
	};
	for (int i = 0; i < 2; ++i) {
		array[i]->execute();
		cout << endl;
	}

	getchar();
	return 0;
}
#endif

#ifdef BEFORE
/************************************************************************/
/* BEFORE                                                                     */
/************************************************************************/
class SortUp {
public:
	void sort(int v[], int n) {
		for (int g = n / 2; g > 0; g /= 2)
			for (int i = g; i < n; i++)
				for (int j = i - g; j >= 0; j -= g)
					if (v[j] > v[j + g])
						doSwap(v[j], v[j + g]);
	}
private:
	void doSwap(int &a, int &b) {
		int t = a;
		a = b;
		b = t;
	}
};

class sortDowm {
public:
	void sort(int v[], int n) {
		for (int g = n / 2; g > 0; g /= 2)
			for (int i = g; i < n; i++)
				for (int j = i - g; j >= 0; j -= g)
					if (v[j] < v[j + g])
						doSwap(v[j], v[j + g]);
	}
private:
	void doSwap(int &a, int &b) {
		int t = a;
		a = b;
		b = t;
	}
};

int main() {
	const int NUM = 10;
	int array[NUM];
	srand(time(0));

	for (int i = 0; i < NUM; ++i) {
		array[i] = rand() % 10 + 1;
		cout << array[i] << " ";
	}
	cout << endl;

	SortUp upObj;
	upObj.sort(array, NUM);
	for (int i = 0; i < NUM; ++i)
		cout << array[i] << " ";
	cout << endl;

	sortDowm downObj;
	downObj.sort(array, NUM);
	for (int i = 0; i < NUM; ++i)
		cout << array[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}
#endif

/************************************************************************/
/* AFTER                                                                     */
/************************************************************************/
class AbstractSort {
public:
	void sort(int v[], int n) {
		for (int g = n / 2; g > 0; g /= 2)
			for (int i = g; i < n; i++)
				for (int j = i - g; j >= 0; j -= g)
					if (needSwap(v[j] ,v[j + g]))
						doSwap(v[j], v[j + g]);
	}
	virtual int needSwap(int, int) = 0;
	void doSwap(int &a, int &b) {
		int t = a;
		a = b;
		b = t;
	}
};

class SortUp : public AbstractSort {
	int needSwap(int a, int b){
		return a > b;
	}
};

class SortDown : public AbstractSort {
	int needSwap(int a, int b) {
		return a < b;
	}
};

int main() {
	const int NUM = 10;
	int array[NUM];
	srand(time(0));
	for (int i = 0; i < NUM; ++i) {
		array[i] = rand() % 10 + 1;
		cout << array[i] << " ";
	}
	cout << endl;

	AbstractSort *sortObjects[] = {
		new SortUp, new SortDown
	};
	sortObjects[0]->sort(array, NUM);
	for (int i = 0; i < NUM; ++i)
		cout << array[i] << " ";
	cout << endl;

	sortObjects[1]->sort(array, NUM);
	for (int i = 0; i < NUM; ++i)
		cout << array[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}
