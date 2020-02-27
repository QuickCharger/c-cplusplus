#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <time.h>

using namespace std;

class ObsObj {
public:
	virtual void update(int n) = 0;
};

class Observer1 {
	vector<class ObsObj *> views;
	int value;
public:
	void attach(ObsObj *obs)
	{
		views.push_back(obs);
	}
	void setVal(int val)
	{
		value = val;
	}
	int getVal()
	{
		return value;
	}
	void notify(int n)
	{
		for (auto it = views.begin(); it != views.end(); ++it)
		{
			(*it)->update(n);
		}
	}
};

class Diver: public ObsObj {
public:
	Diver(int a_div) : div(a_div) {}
	void update(int v) {
		cout << v << " div " << div << " is " << v / div << endl;
	}
private:
	int div = 0;
};

class Moder : public ObsObj {
public:
	Moder(int a_div) : div(a_div) {}
	void update(int v)
	{
		cout << v << " mod " << div << " is " << v%div << endl;
	}
private:
	int div;
};
















class Subject
{
	vector<class Observer*> views;
	int value;
public:
	void attach(Observer* obs)
	{
		views.push_back(obs);
	}
	void setVal(int val)
	{
		value = val;
		//notify();
	}
	int getVal()
	{
		return value;
	}
	void notify();
};

class Observer
{
	Subject *model;
	int denom;
public:
	Observer(Subject* mod, int div) {
		model = mod;
		denom = div;
		model->attach(this);
	}
	virtual void update() = 0;
protected:
	Subject *getSubject() {
		return model;
	}
	int getDivisor() {
		return denom;
	}
};

void Subject::notify()
{
	for (auto it = views.begin(); it != views.end(); ++it)
	{
		(*it)->update();
	}
}

class DivObserver : public Observer
{
public:
	DivObserver(Subject* mod, int div) : Observer(mod, div) {}
	void update()
	{
		int v = getSubject()->getVal(), d = getDivisor();
		cout << v << " div " << d << " is " << v / d << endl;
	}
};

class ModObserver : public Observer
{
public:
	ModObserver(Subject* mod, int div) : Observer(mod, div) {}
	void update()
	{
		int v = getSubject()->getVal(), d = getDivisor();
		cout << v << " mod " << d << " is " << v%d << endl;
	}
};











class AlarmListener
{
public:
	virtual void alarm() = 0;
};

class SensorSystem
{
	vector<AlarmListener*> listeners;
public:
	void attach(AlarmListener* l) { listeners.push_back(l); }
	void soundTheAlarm() { for (auto it = listeners.begin(); it != listeners.end(); ++it) (*it)->alarm(); }
};

class Lighting : public AlarmListener
{
public:
	void alarm() { cout << "lights up" << endl; }
};

class Gates : public AlarmListener
{
public:
	void alarm() { cout << "gates close" << endl; }
};

class CheckList
{
	virtual void localize() { cout << " establist a perimeter" << endl; }
	virtual void isolate() { cout << " ioslate the grid" << endl; }
	virtual void identify() { cout << " identify the source" << endl; }
public:
	void byTheNumbers() { localize(); isolate(); identify(); }
};

class Surveillance : public CheckList, public AlarmListener
{
	void isolate() { cout << " train the cameras" << endl; }
public:
	void alarm()
	{
		cout << "Surveillance - by the numbers:" << endl;
		byTheNumbers();
	}
};






int main(int argc, char **argv)
{
	Observer1 obs;
	obs.attach(&Diver(3));
	obs.attach(&Diver(4));
	obs.attach(&Moder(3));
	obs.notify(14);


	Subject subj;
	DivObserver div1(&subj, 4);
	DivObserver div2(&subj, 3);
	ModObserver mod1(&subj, 3);
	subj.setVal(14);
	subj.notify();

	SensorSystem ss;
	ss.attach(&Gates());
	ss.attach(&Lighting());
	ss.attach(&Surveillance());
	ss.soundTheAlarm();

	getchar();
}


