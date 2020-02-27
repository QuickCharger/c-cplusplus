#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

class TimeImp {
public:
	TimeImp(int hr, int min) {
		m_hr = hr;
		m_min = min;
	}
	virtual void tell() {
		cout << "time is " << setw(2) << setfill('0') << m_hr << ":" << setw(2) << setfill('0') << m_min << endl;
	}
protected:
	int m_hr, m_min;
};

class CivilianTimeImp : public TimeImp {
protected:
	char whichM_[4];
public:
	CivilianTimeImp(int hr, int min, int pm) : TimeImp(hr, min) {
		strcpy(whichM_, pm ? " PM" : " AM");
	}
	void tell() {
		cout << "time is " << setw(2) << setfill('0') << m_hr << ":" << setw(2) << setfill('0') << m_min << whichM_ << endl;
	}
};

class ZuluTimeImp : public TimeImp {
protected:
	char zone_[30];
public:
	ZuluTimeImp(int hr, int min, int zone) : TimeImp(hr, min) {
		strcpy(zone_, zone == 5 ? " Eastern Standard Time" : zone == 6 ? " Central Standard Time" : "");
	}
	void tell() {
		cout << "time is " << setw(2) << setfill('0') << m_hr << ":"<< setw(2) << setfill('0') << m_min << zone_ << endl;
	}
};

class Time {
protected:
	TimeImp *m_imp;
public:
	Time() {}
	Time(int hr, int min) {
		m_imp = new TimeImp(hr, min);
	}
	virtual void tell() {
		m_imp->tell();
	}
};

class CivilianTime : public Time {
public:
	CivilianTime(int hr, int min, int pm) {
		m_imp = new CivilianTimeImp(hr, min, pm);
	}
};

class ZuluTime : public Time {
public:
	ZuluTime(int hr, int min, int zone) {
		m_imp = new ZuluTimeImp(hr, min, zone);
	}
};

int main() {
	Time *times[3];
	times[0] = new Time(14, 3);
	times[1] = new CivilianTime(2, 30, 1);
	times[2] = new ZuluTime(14, 30, 6);

	for (int i = 0; i < 3; ++i) {
		times[i]->tell();
	}

	getchar();
	return 0;
}
