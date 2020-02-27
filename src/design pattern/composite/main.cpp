#include <iostream>
#include <vector>

using namespace std;

#define EXP2

#ifdef EXP1
/************************************************************************/
/* EXP1                                                                     */
/************************************************************************/
class Component {
public:
	virtual void traverse() = 0;
};

class Leaf : public Component {
	int value;
public:
	Leaf(int val) {
		value = val;
	}
	void traverse() {
		cout << value << ' ';
	}
};

class Composite : public Component {
	vector<Component*> children;
public:
	void add(Component* ele) {
		children.push_back(ele);
	}
	void traverse() {
		for (auto it = children.begin(); it != children.end(); ++it) {
			(*it)->traverse();
		}
	}
};

int main() {
	Composite containers[4];

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 3; ++j)
			containers[i].add(new Leaf(i * 3 + j));

	for (int i = 1; i < 4; ++i)
		containers->add(&(containers[i]));

	for (int i = 0; i < 4; ++i) {
		containers[i].traverse();
		cout << endl;
	}

	getchar();
}
#endif

#ifdef EXP2
/************************************************************************/
/* EXP2                                                                     */
/************************************************************************/

class Component {
public:
	virtual void traverse() = 0;
};

class Primitive : public Component {
	int value;
public:
	Primitive(int val) {
		value = val;
	}
	void traverse() {
		cout << value << " ";
	}
};

class Composite : public Component {
	vector<Component*> children;
	int value;
public:
	Composite(int val) {
		value = val;
	}
	void add(Component* c) {
		children.push_back(c);
	}
	void traverse() {
		cout << value << " ";
		for (int i = 0; i < children.size(); ++i)
			children[i]->traverse();
		cout << endl;
	}
};

class Row : public Composite {
public:
	Row(int val) : Composite(val) {}
	void traverse() {
		cout << "Row";
		Composite::traverse();
	}
};

class Column : public Composite {
public:
	Column(int val) : Composite(val) {}
	void traverse() {
		cout << "Col";
		Composite::traverse();
	}
};

int main() {
	Row first(1);
	Column second(2);
	Column third(3);
	Row fourth(4);
	Row fifth(5);
	first.add(&second);
	first.add(&third);
	third.add(&fourth);
	third.add(&fifth);
	first.add(&Primitive(6));
	second.add(&Primitive(7));
	third.add(&Primitive(8));
	fourth.add(&Primitive(9));
	fifth.add(&Primitive(10));
	first.traverse();
	cout << endl;

	getchar();
	return 0;
}
#endif
