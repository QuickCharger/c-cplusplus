/*
* The client uses the factory object instead of "new" to request instances
* and, the client "hard-wires" the family, or class, of that factory only once
* and throughout the remainder of the application only relies on the abstract base class
*/

#include <iostream>

using namespace std;

#define EXP2

#ifdef EXP1
/************************************************************************/
/* before                                                                     */
/************************************************************************/
class Widget {
public:
	virtual void draw() = 0;
};

class LinuxButton : public Widget {
public:
	void draw() { cout << "LinuxButton" << endl; }
};

class LinuxMenu : public Widget {
public:
	void draw() { cout << "LinuxMenu" << endl; }
};

class WindowButton : public Widget {
public:
	void draw() { cout << "WindowButton" << endl; }
};

class WindowMenu : public Widget {
public:
	void draw() { cout << "WindowMenu" << endl; }
};

class Client {
public:
	void draw() {
#ifdef LINUX
		Widget *w = new LinuxButton;
#else // WINDOWS
		Widget *w = new WindowButton;
#endif
		w->draw();
		display_window_one();
		display_window_two();
	}

private:
	void display_window_one() {
#ifdef LINUX
		Widget *w[] = {
			new LinuxButton,
			new LinuxMenu
		};
#else // WINDOWS
		Widget *w[] = {
			new WindowButton,
			new WindowMenu
		};
#endif
		w[0]->draw();
		w[1]->draw();
	}

	void display_window_two() {
#ifdef LINUX
		Widget *w[] = {
			new LinuxMenu,
			new LinuxButton
		};
#else // WINDOWS
		Widget *w[] = {
			new WindowMenu,
			new WindowButton
		};
#endif
		w[0]->draw();
		w[1]->draw();
	}
};

/************************************************************************/
/* after                                                                     */
/************************************************************************/
class Widget {
public:
	virtual void draw() = 0;
};

class LinuxButton : public Widget {
public:
	void draw() { cout << "LinuxButton" << endl; }
};

class LinuxMenu : public Widget {
public:
	void draw() { cout << "LinuxMenu" << endl; }
};

class WindowsButton : public Widget {
public:
	void draw() { cout << "WindowsButton" << endl; }
};

class WindowsMenu : public Widget {
public:
	void draw() { cout << "WindowMenu" << endl; }
};

class Factory {
public:
	virtual Widget *create_button() = 0;
	virtual Widget *create_menu() = 0;
};

class LinuxFactory : public Factory {
public:
	Widget *create_button() {
		return new LinuxButton;
	}
	Widget *create_menu() {
		return new LinuxMenu;
	}
};

class WindowsFactory : public Factory {
public:
	Widget *create_button() {
		return new WindowsButton;
	}
	Widget *create_menu() {
		return new WindowsMenu;
	}
};

class Client {
private:
	Factory *factory;
	void display_window_one() {
		Widget *w[] = {
			factory->create_button(),
			factory->create_menu()
		};
		w[0]->draw();
		w[1]->draw();
	}
	void display_window_two() {
		Widget *w[] = {
			factory->create_menu(),
			factory->create_button()
		};
		w[0]->draw();
		w[1]->draw();
	}

public:
	Client(Factory *f) {
		factory = f;
	}
	void draw() {
		Widget *w = factory->create_button();
		w->draw();
		display_window_one();
		display_window_two();
	}
};
#endif

#ifdef EXP2
/************************************************************************/
/* exp2                                                                     */
/************************************************************************/
class Shape {
protected:
	int m_id;
	static int m_total;
public:
	Shape() {
		m_id = m_total++;
	}
	virtual void draw() = 0;
};

int Shape::m_total = 0;

class Circle : public Shape {
public:
	void draw() {
		cout << "circle " << m_id << ": draw" << endl;
	}
};

class Square : public Shape {
public:
	void draw() {
		cout << "square " << m_id << ": draw" << endl;
	}
};

class Ellipse : public Shape {
public:
	void draw() {
		cout << "ellipse " << m_id << ": draw" << endl;
	}
};

class Rectangle : public Shape {
public:
	void draw() {
		cout << "rectangle " << m_id << ": draw" << endl;
	}
};

class Factory {
public:
	virtual Shape* createCurvedInstance() = 0;
	virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public Factory {
public:
	Shape* createCurvedInstance() {
		return new Circle;
	}
	Shape* createStraightInstance() {
		return new Square;
	}
};

class RobustShapeFactory : public Factory {
public:
	Shape* createCurvedInstance() {
		return new Ellipse;
	}
	Shape* createStraightInstance() {
		return new Rectangle;
	}
};
#endif

int main()
{
#ifdef EXP1
	Factory *factory;
#ifdef LINUX
	factory = new LinuxFactory;
#else
	factory = new WindowsFactory;
#endif
	Client *c = new Client(factory);
	c->draw();
#endif

#ifdef EXP2
	Shape* shape[4];
	Factory* factory = new SimpleShapeFactory;
	shape[0] = factory->createCurvedInstance();
	shape[1] = factory->createStraightInstance();
	delete factory;
	factory = new RobustShapeFactory;
	shape[2] = factory->createCurvedInstance();
	shape[3] = factory->createStraightInstance();
	delete factory;

	for (int i = 0; i < 4; ++i) {
		shape[i]->draw();
	}
#endif
	getchar();
}
