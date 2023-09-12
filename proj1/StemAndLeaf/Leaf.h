#ifndef LEAF_H_
#define LEAF_H_

struct Leaf
{
	int value;
	int count; // used to save memory, always default to 1
	Leaf* next;

	// Don't modify
	friend std::ostream &operator << (std::ostream &out, const Leaf &x)
  {
    out << x.value << ":" << x.count;
    return out;
  }

};

#endif /* LEAF_H_ */
