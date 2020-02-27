#include <iostream>

using namespace std;

#ifdef EXP1
typedef int Coordinate;
typedef int Dimension;

class Rectangle {
public:
	virtual void draw() = 0;
};

class LegacyRectangle {
	Coordinate m_x1, m_y1, m_x2, m_y2;
public:
	LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2) {
		m_x1 = x1; m_y1 = y1; m_x2 = x2; m_y2 = y2;
		cout << "LegacyRectangle: create. (" << m_x1 << "," << m_y1 << ") => (" << m_x2 << "," << m_y2 << ")" << endl;
	}
	void oldDraw() {
		cout << "LegacyRentangle: oldDraw. (" << m_x1 << ","<< m_y1 << ") => (" << m_x2 << "," << m_y2 << ")" << endl;
	}
};

class RectangleAdapter : public Rectangle, private LegacyRectangle {
public:
	RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h) : LegacyRectangle(x, y, x + w, y + h) {
		cout << "RectangleAdapter: create. (" << x << ", " << y << "), width = " << w << ", height = " << h << endl;
	}
	virtual void draw() {
		cout << "RectangleAdapter: draw." << endl;
		oldDraw();
	}
};

int main() {
	Rectangle *r = new RectangleAdapter(120, 200, 60, 40);
	r->draw();

	getchar();
	return 0;
}
#endif

//#ifdef EXP2
class ExecuteInterface {
public:
	virtual ~ExecuteInterface() {}
	virtual void execute() = 0;
};

template <class T>
class ExecuteAdapter : public ExecuteInterface {
	T *t;
	void(T::*m)();
public:
	ExecuteAdapter(T *a_t, void(T::*a_m)()) {
		t = a_t;
		m = a_m;
	}
	~ExecuteAdapter() {
		delete t;
	}
	void execute() {
		(o->*m)();
	}
};

class Fea {
public:
	~Fea() {
		cout << "Fea:dtor" << endl;
	}
	void doThis() {
		cout << "Fea:doThis()" << endl;
	}
};

class Feye {
public:
	~Feye() {
		cout << "Feye::dtor" << endl;
	}
	void doThat() {
		cout << "Feye::doThat()" << endl;
	}
};

class Pheau {
public:
	~Pheau() {
		cout << "Pheau::dtor" << endl;
	}
	void doTheOther() {
		cout << "Pheau::doTheOther" << endl;
	}
};

ExecuteInterface **initialize() {
	ExecuteInterface **array = new ExecuteInterface *[3];
	array[0] = new ExecuteAdapter<Fea>(new Fea(), &Fea::doThis);
	array[1] = new ExecuteAdapter<Feye>(new Feye(), &Feye::doThat);
	array[2] = new ExecuteAdapter<Pheau>(new Pheau(), &Pheau::doTheOther);
	return array;
}

int main() {
	ExecuteInterface **obj = initialize();
	for (int i = 0; i < 3; ++i) {
		obj[i]->execute();
	}
	for (int i = 0; i < 3; ++i) {
		delete obj[i];
	}
	delete obj;

	getchar();
	return 0;
}
//#endif
