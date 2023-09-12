#ifndef STEM_H_
#define STEM_H_

#include "Leaf.h"

class Stem {
private:
	Leaf *front, *back;
public:
	Stem();
	virtual ~Stem();

	int value;  // stem value
	int frequency; // how MANY leaves this stem contains!!
	Stem* next; // link to next Stem

	Leaf* createLeaf(int value);
	bool insert(int value);  // return true if a leaf is created   
	bool remove(int target);  // return true is a leaf is deleted 
  
  friend std::ostream &operator << (std::ostream &out, const Stem &x);
};


#endif /* STEM_H_ */
