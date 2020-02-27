/*
* Define an interface for creating an object, but let subclasses decide whitch class to instantiate
* Factory Method lets a class defer instantiation to subclasses
*/

#include <iostream>
#include <vector>

using namespace std;

#ifdef BEFORE
class Stooge {
public:
	virtual void slap_stick() = 0;
};

class Larry : public Stooge {
public:
	void slap_stick() {
		cout << "Larry: poke eyes" << endl;
	}
};

class Moe : public Stooge {
public:
	void slap_stick() {
		cout << "Moe: slap head" << endl;
	}
};

class Curly : public Stooge {
public:
	void slap_stick() {
		cout << "Curly: suffer abuse" << endl;
	}
};

int main()
{
	vector<Stooge*> roles;
	int choice;

	while (true) {
		cout << "Larry(1) Moe(2) Curly(3) Go(0)" << endl;
		cin >> choice;
		if (choice == 0)
			break;
		else if (choice = 1)
			roles.push_back(new Larry);
		else if (choice == 2)
			roles.push_back(new Moe);
		else if (choice == 3)
			roles.push_back(new Curly);
	}

	for (int i = 0; i < roles.size(); ++i)
		roles[i]->slap_stick();
	for (int i = 0; i < roles.size(); ++i)
		delete roles[i];
}
#endif

#ifdef AFTER
class Stooge {
public:
	static Stooge *make_stooge(int choice);
	virtual void slap_stick() = 0;
};

class Larry : public Stooge {
public:
	void slap_stick() {
		cout << "Larry: poke eyes" << endl;
	}
};

class Moe : public Stooge {
public:
	void slap_stick() {
		cout << "Moe: slap head" << endl;
	}
};

class Curly : public Stooge {
public:
	void slap_stick() {
		cout << "Curly: suffer abuse" << endl;
	}
};

Stooge * Stooge::make_stooge(int choice)
{
	if (choice == 1)
		return new Larry;
	else if (choice == 2)
		return new Moe;
	else if (choice == 3)
		return new Curly;
}

int main()
{
	vector<Stooge*> roles;
	int choice;
	while (true) {
		cout << "Larry(1) Moe(2) Curly(3) Go(0)" << endl;
		cin >> choice;
		if(choice == 0)
			break;
		roles.push_back(Stooge::make_stooge(choice));
	}
	for (int i = 0; i < roles.size(); ++i)
		roles[i]->slap_stick();
	for (int i = 0; i < roles.size(); ++i)
		delete roles[i];
}
#endif

class Document {
	char name[20] = { 0 };
public:
	Document(char *fn) {
		strcpy(name, fn);
	}
	virtual void Open() = 0;
	virtual void Close() = 0;
	char *GetName() {
		return name;
	}
};

class MyDocument : public Document {
public:
	MyDocument(char* fn) : Document(fn) {}
	void Open() {
		cout << "MyDocument: Open()" << endl;
	}
	void Close() {
		cout << "MyDocument: Close()" << endl;
	}
};

class Application {
	int m_index = 0;
	Document *m_docs[10];
public:
	Application() {
		cout << "Application: ctor" << endl;
	}
	void NewDocument(char* name) {
		cout << "Application: NewDocument()" << endl;
		m_docs[m_index] = CreateDocument(name);
		m_docs[m_index++]->Open();
	}
	void OpenDocument() {}
	void ReportDocs() {
		cout << "Application: ReportDocs()" << endl;
		for (int i = 0; i < m_index; ++i)
			cout << " " << m_docs[i]->GetName() << endl;
	}
	virtual Document *CreateDocument(char*) = 0;
};

class MyApplication : public Application {
public:
	MyApplication() {
		cout << "MyApplication: ctor" << endl;
	}
	Document* CreateDocument(char* fn) {
		cout << "  MyApplication: CreateDocument()" << endl;
		return new MyDocument(fn);
	}
};

int main() {
	MyApplication myApp;
	myApp.NewDocument("foo");
	myApp.NewDocument("bar");
	myApp.ReportDocs();

	getchar();
}
