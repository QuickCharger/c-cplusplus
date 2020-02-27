#include <iostream>
#include <vector>

using namespace std;

#ifdef EXP1
/************************************************************************/
/* EXP1                                                                     */
/************************************************************************/
class FileSelectionDialog;

class Widget {
	FileSelectionDialog *_mediator;
public:
	Widget(FileSelectionDialog* mediator, char* name) {
		_mediator = mediator;
		strcpy(_name, name);
	}
	virtual void changed();
	virtual void updateWidget() = 0;
	virtual void queryWidget() = 0;
protected:
	char _name[20];
};

class List : public Widget {
public:
	List(FileSelectionDialog* dir, char* name) : Widget(dir, name) {}
	void queryWidget() {
		cout << " " << _name << " list queried" << endl;
	}
	void updateWidget() {
		cout << " " << _name << " list updated" << endl;
	}
};

class Edit : public Widget {
public:
	Edit(FileSelectionDialog* dir, char* name) : Widget(dir, name) {}
	void queryWidget() {
		cout << " " << _name << "edit queried" << endl;
	}
	void updateWidget() {
		cout << " " << _name << "edit updated" << endl;
	}
};

class FileSelectionDialog {
	Widget *_components[4];
public:
	enum Widgets {
		FilterEdit, DirList, FileList, SelectionEdit
	};
	FileSelectionDialog() {
		_components[FilterEdit] = new Edit(this, "filter");
		_components[DirList] = new List(this, "dir");
		_components[FileList] = new List(this, "file");
		_components[SelectionEdit] = new Edit(this, "selection");
	}
	virtual ~FileSelectionDialog() {
		for (int i = 0; i < 4; ++i)
			delete _components[i];
	}
	void handleEvent(int which) {
		_components[which]->changed();
	}
	virtual void widgetChanged(Widget* theChangedWidget) {
		if (theChangedWidget == _components[FilterEdit]) {
			_components[FilterEdit]->queryWidget();
			_components[DirList]->updateWidget();
			_components[FileList]->updateWidget();
			_components[SelectionEdit]->updateWidget();
		}
		else if (theChangedWidget == _components[DirList]) {
			_components[DirList]->queryWidget();
			_components[FileList]->updateWidget();
			_components[FilterEdit]->updateWidget();
			_components[SelectionEdit]->updateWidget();
		}
		else if (theChangedWidget == _components[FileList]) {
			_components[FileList]->queryWidget();
			_components[SelectionEdit]->updateWidget();
		}
		else if (theChangedWidget == _components[SelectionEdit]) {
			_components[SelectionEdit]->queryWidget();
			cout << "    file opened" << endl;
		}
	}
};

void Widget::changed() {
	_mediator->widgetChanged(this);
}

int main()
{
	FileSelectionDialog fileDialog;
	int i;

	cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]:";
	cin >> i;

	while (i) {
		fileDialog.handleEvent(i - 1);
		cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]:";
		cin >> i;
	}

	getchar();
	return 0;
}
#endif

#ifdef BEFORE
/************************************************************************/
/* BEFORE                                                                     */
/************************************************************************/
class Node {
	int m_val;
	Node *m_next;
public:
	Node(int v) {
		m_val = v;
		m_next = nullptr;
	}
	void add_node(Node *n) {
		if (m_next)
			m_next->add_node(n);
		else
			m_next = n;
	}
	void traverse() {
		cout << m_val << " ";
		if (m_next)
			m_next->traverse();
		else
			cout << endl;
	}
	void remove_node(int v) {
		if (m_next)
			if (m_next->m_val == v)
				m_next = m_next->m_next;
			else
				m_next->remove_node(v);
	}
};

int main() {
	Node lst(11);
	Node two(22), thr(33), fou(44);
	lst.add_node(&two);
	lst.add_node(&thr);
	lst.add_node(&fou);
	lst.traverse();
	lst.remove_node(44);
	lst.traverse();
	lst.remove_node(22);
	lst.traverse();
	lst.remove_node(11);
	lst.traverse();

	getchar();
	return 0;
}
#endif

/************************************************************************/
/* AFTER                                                                     */
/************************************************************************/
class Node {
	int m_val;
public:
	Node(int v) {
		m_val = v;
	}
	int get_val() {
		return m_val;
	}
};

class List {
	vector<Node*> m_arr;
public:
	void add_node(Node *n) {
		m_arr.push_back(n);
	}
	void traverse() {
		for (int i = 0; i < m_arr.size(); ++i)
			cout << m_arr[i]->get_val() << " ";
		cout << endl;
	}
	void remove_node(int v) {
		for(auto it = m_arr.begin(); it != m_arr.end(); ++it)
			if ((*it)->get_val() == v) {
				m_arr.erase(it);
				break;
			}
	}
};

int main() {
	List lst;
	Node one(11), two(22), thr(33), fou(44);
	lst.add_node(&one);
	lst.add_node(&two);
	lst.add_node(&thr);
	lst.add_node(&fou);
	lst.traverse();
	lst.remove_node(44);
	lst.traverse();
	lst.remove_node(22);
	lst.traverse();
	lst.remove_node(11);
	lst.traverse();

	getchar();
	return 0;
}
