#include <iostream>
#include <list>
#include <algorithm>
#include <memory>

class IText {

public:
	typedef std::shared_ptr<IText> SPtr;

	virtual void draw() = 0;

	virtual void add(const SPtr&) {
		throw std::runtime_error("Ошибочка");
	}

	virtual void remove(const SPtr&) {
		throw std::runtime_error("Ошибочка");
	}
};

class CompositeText : public IText {

public:
	void add(const SPtr& sptr) {
		children_.push_back(sptr);
	}

	void remove(const SPtr& sptr) {
		children_.remove(sptr);
	}

	void replace(const SPtr& oldValue, const SPtr& newValue) {
		std::replace(children_.begin(), children_.end(), oldValue, newValue);
	}

	virtual void draw() {
		for (SPtr& sptr : children_) {
			sptr->draw();
		}
	}

private:
	std::list<SPtr> children_;
};

class Letter : public IText {
public:
	Letter(char c) :c_(c) {}

	virtual void draw() {
		std::cout << c_;
	}

private:
	char c_;
};


int main() {

	CompositeText sentence;

	IText::SPtr v(new Letter(' '));
	IText::SPtr p(new Letter('!'));
	IText::SPtr q(new Letter(','));
	IText::SPtr z(new Letter('\n'));
	IText::SPtr H(new Letter('H')); 
	IText::SPtr e(new Letter('e')); 
	IText::SPtr l(new Letter('l')); 
	IText::SPtr o(new Letter('o')); 
	IText::SPtr W(new Letter('W')); 
	IText::SPtr r(new Letter('r')); 
	IText::SPtr d(new Letter('d')); 
	IText::SPtr i(new Letter('i')); 

	IText::SPtr Hello(new CompositeText);
	Hello->add(H);
	Hello->add(e);
	Hello->add(l);
	Hello->add(l);
	Hello->add(o);

	IText::SPtr World(new CompositeText); // word "World"
	World->add(W);
	World->add(o);
	World->add(r);
	World->add(l);
	World->add(d);

	sentence.add(Hello);
	sentence.add(q);
	sentence.add(v);
	sentence.add(World);
	sentence.add(p);
	sentence.add(z);

	sentence.draw();  

	IText::SPtr wHi(new CompositeText); 
	wHi->add(H);
	wHi->add(i);

	sentence.replace(Hello, wHi);
	sentence.draw();  

	sentence.remove(World);
	sentence.remove(v);
	sentence.remove(q);
	sentence.draw();  

	return 0;
}