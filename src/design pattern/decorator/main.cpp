#include <string>
#include <iostream>
using namespace std;

////人
//class Person
//{
//private:
//	string m_strName;
//public:
//	Person(string strName)
//	{
//		m_strName = strName;
//	}
//	Person(){}
//	virtual void Show()
//	{
//		cout << "装扮的是:" << m_strName << endl;
//	}
//};
////装饰类
//class Finery :public Person
//{
//protected:
//	Person* m_component;
//public:
//	void Decorate(Person* component)
//	{
//		m_component = component;
//	}
//	virtual void Show()
//	{
//		m_component->Show();
//	}
//};
////T 恤
//class TShirts : public Finery
//{
//public:
//	virtual void Show()
//	{
//		cout << "T Shirts" << endl;
//		Finery::m_component->Show();
//	}
//};
////裤子
//class BigTrouser :public Finery
//{
//public:
//	virtual void Show()
//	{
//		cout << " Big Trouser" << endl;
//		Finery::m_component->Show();
//	}
//};
////客户端
//int main()
//{
//	Person *p = new Person("小李");
//	BigTrouser *pTrouser = new BigTrouser();    //pTrouser->Show() = p->Show()
//	TShirts *pTShirt = new TShirts();
//	pTrouser->Decorate(p);
//	pTShirt->Decorate(pTrouser);	//pTShirt->Show() = pTrouser->Show
//	pTShirt->Show();
//
//	getchar();
//	return 0;
//}

#ifdef BEFORE
/************************************************************************/
/* BEFORE                                                                     */
/************************************************************************/
class A {
public:
	virtual void do_it() {
		cout << "A";
	}
};

class AwithX : public A {
	void do_X() {
		cout << "X";
	}
public:
	void do_it() {
		A::do_it();
		do_X();
	}
};

class AwithY : public A {
public:
	void do_it() {
		A::do_it();
		do_Y();
	}
protected:
	void do_Y() {
		cout << "Y";
	}
};

class AwithZ : public A {
public:
	void do_it() {
		A::do_it();
		do_Z();
	}
protected:
	void do_Z() {
		cout << "Z";
	}
};

class AwithXY : public AwithX, public AwithY {
public:
	void do_it() {
		AwithX::do_it();
		AwithY::do_Y();
	}
};

class AwithXYZ : public AwithX, public AwithY, public AwithZ {
public:
	void do_it() {
		AwithX::do_it();
		AwithY::do_Y();
		AwithZ::do_Z();
	}
};

int main() {
	AwithX anX;
	AwithXY anXY;
	AwithXYZ anXYZ;
	anX.do_it();
	cout << endl;
	anXY.do_it();
	cout << endl;
	anXYZ.do_it();
	cout << endl;

	getchar();
	return 0;
}
#endif

#ifdef AFTER
/************************************************************************/
/* AFTER                                                                     */
/************************************************************************/
class I {
public:
	virtual ~I() {}
	virtual void do_it() = 0;
};

class A : public I {
public:
	~A() {
		cout << "A dtor" << endl;
	}
	void do_it() {
		cout << "A";
	}
};

class D : public I {
	I *m_wrappee;
public:
	D(I *inner) {
		m_wrappee = inner;
	}
	~D() {
		delete m_wrappee;
	}
	void do_it() {
		m_wrappee->do_it();
	}
};

class X : public D {
public:
	X(I *core) : D(core) {}
	~X() {
		cout << "X dtor" << " ";
	}
	void do_it() {
		D::do_it();
		cout << "X";
	}
};

class Y : public D {
public:
	Y(I *core) : D(core) {}
	~Y() {
		cout << "Y dtor" << " ";
	}
	void do_it() {
		D::do_it();
		cout << "Y";
	}
};

class Z : public D {
public:
	Z(I *core) : D(core) {}
	~Z() {
		cout << "Z dtor" << " ";
	}
	void do_it() {
		D::do_it();
		cout << "Z";
	}
};

int main() {
	I *anX = new X(new A);
	I *anXY = new Y(new X(new A));
	I *anXYZ = new Z(new Y(new X(new A)));

	anX->do_it();
	cout << endl;
	anXY->do_it();
	cout << endl;
	anXYZ->do_it();
	cout << endl;

	delete anX;
	delete anXY;
	delete anXYZ;

	getchar();
	return 0;
}
#endif

#ifdef EXP2
/************************************************************************/
/* EXP2                                                                     */
/************************************************************************/
class Widget {
public:
	virtual void draw() = 0;
};

class TextField : public Widget {
	int width, height;
public:
	TextField(int w, int h) {
		width = w;
		height = h;
	}
	void draw() {
		cout << "TextField: " << width << ", " << height << endl;
	}
};

class Decorator : public Widget {
	Widget *wid;
public:
	Decorator(Widget *w) {
		wid = w;
	}
	void draw() {
		wid->draw();
	}
};

class BorderDecorator : public Decorator {
public:
	BorderDecorator(Widget *w) : Decorator(w) {}
	void draw() {
		Decorator::draw();
		cout << " BorderDecorator" << endl;
	}
};

class ScrollDecorator : public Decorator {
public:
	ScrollDecorator(Widget *w) : Decorator(w) {}
	void draw() {
		Decorator::draw();
		cout << " ScrollDecorator" << endl;
	}
};

int main() {
	Widget *aWidget = new BorderDecorator(new BorderDecorator(new ScrollDecorator(new TextField(80, 24))));
	aWidget->draw();

	getchar();
	return 0;
}
#endif

/************************************************************************/
/* EXP3                                                                     */
/************************************************************************/
class Interface {
public:
	virtual ~Interface() {}
	virtual void write(string&) = 0;
	virtual void read(string&) = 0;
};

class Core : public Interface {
public:
	~Core() {
		cout << "dtor-Core" << endl;
	}
	void write(string& b) {
		b += "MESSAGE|";
	}
	void read(string& b) {
		b += "Core: MESSAGE\n";
	};
};

class Decorator : public Interface {
	Interface *inner;
public:
	Decorator(Interface* c) {
		inner = c;
	}
	~Decorator() {
		delete inner;
	}
	void write(string& b) {
		inner->write(b);
	}
	void read(string& b) {
		inner->read(b);
	}
};

class Wrapper : public Decorator {
	string forward, backward;
	Interface *m_Dec;
public:
	Wrapper(Interface* c, string str) : Decorator(c) {
		m_Dec = c;
		forward = str;
		for (auto it = str.rbegin(); it != str.rend(); ++it)
			backward += *it;
	}
	~Wrapper() {
		cout << "dtor-" << forward << " ";
	}
	void write(string& dst) {
		dst += forward + "]";
		m_Dec->write(dst);
		dst += backward + "]";
	};
	void read(string& dst) {
		dst += "Wrapper: ";
		dst += forward;
		dst += '\n';
		m_Dec->read(dst);
		dst += "Warpper: ";
		dst += backward;
		dst += "\n";
	};
};

int main() {
	Interface *object = new Wrapper(new Wrapper(new Wrapper(new Core(), "123"), "abc"), "987");
	string buf;
	object->write(buf);
	cout << "main: " << buf << endl;
	buf = "";
	object->read(buf);
	cout << buf;
	delete object;

	getchar();
	return 0;
}
