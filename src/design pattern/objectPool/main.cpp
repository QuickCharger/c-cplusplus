/*
* A pool
*/

#include <string>
#include <iostream>
#include <list>

using namespace std;

class Resource {
	int value;
public:
	Resource() {
		value = 0;
	}
	void reset() {
		value = 0;
	}
	int getValue() {
		return value;
	}
	void setValue(int n) {
		value = n;
	}
};

// singleton
class ObjectPool {
	list<Resource*> resources;
	static ObjectPool *instance;
	ObjectPool() { }
public:
	static ObjectPool* getInstance() {
		if (!instance)
			instance = new ObjectPool;
		return instance;
	}
	Resource* getResource() {
		if (resources.empty()) {
			cout << "Create new." << endl;
			return new Resource;
		} else {
			cout << "Reusing existing." << endl;
			Resource* resource = resources.front();
			resources.pop_front();
			return resource;
		}
	}
	void returnResource(Resource* object) {
		object->reset();
		resources.push_back(object);
	}
};

ObjectPool* ObjectPool::instance = nullptr;

int main() {
	ObjectPool* pool = ObjectPool::getInstance();
	Resource* one;
	Resource* two;

	one = pool->getResource();
	one->setValue(10);
	cout << "one = " << one->getValue() << " [" << one << "]" << endl;
	two = pool->getResource();
	two->setValue(20);
	cout << "two = " << two->getValue() << " [" << two << "]" << endl;
	pool->returnResource(one);
	pool->returnResource(two);

	one = pool->getResource();
	cout << "one = " << one->getValue() << " [" << one << "]" << endl;
	two = pool->getResource();
	cout << "two = " << two->getValue() << " [" << two << "]" << endl;

	getchar();
	return 0;
}
