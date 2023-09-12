#ifndef STEAMANDLEAF_H_
#define STEAMANDLEAF_H_

#include "Stem.h"

class StemAndLeaf {
private:
	int leafUnit;  // increment of each leaf in this particular structure
	int stemUnit;  // increment of each stem in this particular structure
	Stem* head; 
  	Stem* tail;

public:
  	StemAndLeaf();
  	~StemAndLeaf();
	Stem* createStem(int term);
	int getLeafUnit() const; 
	void setLeafUnit(int leafUnit);
	int getStemUnit() const; 
	void setStemUnit(int stemUnit); 
	void addTerm(int); // adds term to StemAndPlot, IN ORDER
	bool removeTerm(int); // removes term to StemAndPlot, returns true if found and removed

	friend std::ostream& operator<< (std::ostream &out, const StemAndLeaf &x);
	/*
	 * Used to display/debug the StemAndLeaf diagram
	 * will look exactly like this (using example in project):
	 *
	 * 0 | 0:1
	 * ...
	 * 2 |
	 * 3 | 6:2 9:1
	 *
	 * We will not give them too much data to overrun 80 characters
	 */
};


#endif /* STEAMANDLEAF_H_ */
