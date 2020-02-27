/*
* construct a complex oobject stop by step
* An abstract base class declares the standard construction process
* And concrete derived classes define the appropriate implementation for each stip of the process
*/

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

enum PersistenceType{
	File,
	Queue,
	Pathway
};

struct PersistenceAttribute {
	PersistenceType type;
	char value[30];
};

class DistrWorkPackage {
private:
	char m_desc[200], m_temp[80];
public:
	DistrWorkPackage(char* type) {
		sprintf(m_desc, "Distributed Work Package for: %s", type);
	}
	void setFile(char* f, char* v) {
		sprintf(m_temp, "\n File(%s): %s", f, v);
		strcat(m_desc, m_temp);
	}
	void setQueue(char* q, char* v) {
		sprintf(m_temp, "\n Queue(%s): %s", q, v);
		strcat(m_desc, m_temp);
	}
	void setPathway(char* p, char* v) {
		sprintf(m_temp, "\n Pathway(%s): %s", p, v);
		strcat(m_desc, m_temp);
	}
	const char* getState() {
		return m_desc;
	}
};

class Builder {
protected:
	DistrWorkPackage* m_result;
public:
	virtual void configureFile(char*) = 0;
	virtual void configureQueue(char*) = 0;
	virtual void configurePathway(char*) = 0;
	DistrWorkPackage* getResult() {
		return m_result;
	}
};

class UnixBuilder : public Builder {
public:
	UnixBuilder() {
		m_result = new DistrWorkPackage("Unix");
	}
	void configureFile(char* name) {
		m_result->setFile("flatFile", name);
	}
	void configureQueue(char* queue) {
		m_result->setQueue("FIFO", queue);
	}
	void configurePathway(char* type) {
		m_result->setPathway("thread", type);
	}
};

class VmsBuilder : public Builder {
public:
	VmsBuilder() {
		m_result = new DistrWorkPackage("Vms");
	}
	void configureFile(char* name) {
		m_result->setFile("ISAM", name);
	}
	void configureQueue(char* queue) {
		m_result->setQueue("priority", queue);
	}
	void configurePathway(char* type) {
		m_result->setPathway("LWP", type);
	}
};

class Reader {
private:
	Builder* m_builder;
public:
	void setBuilder(Builder* b) {
		m_builder = b;
	}
	void construct(PersistenceAttribute l[], int num) {
		for (int i = 0; i < num; i++) {
			if (l[i].type == File)
				m_builder->configureFile(l[i].value);
			else if (l[i].type == Queue)
				m_builder->configureQueue(l[i].value);
			else if (l[i].type == Pathway)
				m_builder->configurePathway(l[i].value);
		}
	}
};

const int NUM_ENTRIES = 6;

PersistenceAttribute input[6] = {
	{File, "state.dat"},
	{File, "config.sys"},
	{Queue, "compute"},
	{Queue, "log"},
	{Pathway, "authentication"},
	{Pathway, "error processing"}
};

int main()
{
	UnixBuilder unixBuilder;
	VmsBuilder vmsBuilder;
	Reader reader;

	reader.setBuilder(&unixBuilder);
	reader.construct(input, NUM_ENTRIES);
	cout << unixBuilder.getResult()->getState() << endl;

	reader.setBuilder(&vmsBuilder);
	reader.construct(input, NUM_ENTRIES);
	cout << vmsBuilder.getResult()->getState() << endl;

	getchar();
}
