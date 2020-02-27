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

int main() {
	vector<Stooge*> roles;
	int choice;

	while (true) {
		cin >> choice;
		if (choice == 0)
			break;
		else if (choice == 1)
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
	virtual Stooge* clone() = 0;
	virtual void slap_stick() = 0;
};

class Factory {
	static Stooge* s_prototypes[4];
public:
	static Stooge* make_stooge(int choice) {
		return s_prototypes[choice]->clone();
	}
};

class Larry : public Stooge {
public:
	Stooge* clone() { return new Larry; }
	void slap_stick() {
		cout << "Larry: poke eyes" << endl;
	}
};

class Moe : public Stooge {
public:
	Stooge* clone() { return new Moe; }
	void slap_stick() {
		cout << "Moe: slap head" << endl;
	}
};

class Curly : public Stooge {
public:
	Stooge* clone() { return new Curly; }
	void slap_stick() {
		cout << "Curly: suffer abuse" << endl;
	}
};

Stooge* Factory::s_prototypes[] = { 0, new Larry, new Moe, new Curly };

int main() {
	vector<Stooge*> roles;
	int choice;

	while (true) {
		cout << "Larry(1) Moe(2) Curly(3) Go(0)";
		cin >> choice;
		if (choice == 0) {
			break;
		}
		roles.push_back(Factory::make_stooge(choice));
	}
	for (int i = 0; i < roles.size(); ++i)
		roles[i]->slap_stick();
	for (int i = 0; i < roles.size(); ++i)
		delete roles[i];
}
#endif

enum imageType {
	LSAT, SPOT
};

class Image {
	static Image* m_prototypes[10];
	static int m_nextSlot;
public:
	virtual void draw() = 0;
	static Image* findAndClone(imageType type) {
		for (int i = 0; i < m_nextSlot; ++i)
			if (m_prototypes[i]->returnType() == type)
				return m_prototypes[i]->clone();
		return nullptr;
	}
protected:
	virtual imageType returnType() = 0;
	virtual Image* clone() = 0;
	static void addPrototype(Image* image) {
		m_prototypes[m_nextSlot++] = image;
	}
};

Image* Image::m_prototypes[];
int Image::m_nextSlot = 0;

class LandSatImage : public Image {
	static LandSatImage m_landSatImage;
	LandSatImage() {
		addPrototype(this);
	}
	int m_id;
	static int m_count;
public:
	imageType returnType() {
		return LSAT;
	}
	void draw() {
		cout << "LandSatImage::draw" << m_id << endl;
	}
	Image* clone() {
		return new LandSatImage(1);
	}
protected:
	LandSatImage(int) {
		m_id = m_count++;
	}
};

LandSatImage LandSatImage::m_landSatImage;
int LandSatImage::m_count = 1;

class SpotImage : public Image {
	SpotImage() {
		addPrototype(this);
	}
	static SpotImage m_spotImage;
	int m_id;
	static int m_count;
public:
	imageType returnType() {
		return SPOT;
	}
	void draw() {
		cout << "SpotImage:draw" << m_id << endl;
	}
	Image* clone() {
		return new SpotImage(1);
	}
protected:
	SpotImage(int) {
		m_id = m_count++;
	}
};

SpotImage SpotImage::m_spotImage;
int SpotImage::m_count = 1;

const int NUM_IMAGES = 8;
imageType input[NUM_IMAGES] = { LSAT, LSAT, LSAT, SPOT, LSAT, SPOT, SPOT, LSAT };

int main() {
	Image* image[NUM_IMAGES];
	for (int i = 0; i < NUM_IMAGES; i++)
		image[i] = Image::findAndClone(input[i]);
	for (int i = 0; i < NUM_IMAGES; i++)
		image[i]->draw();
	for (int i = 0; i < NUM_IMAGES; i++)
		delete image[i];
}
