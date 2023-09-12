/*
 * This program is based on Dr. Shawn Lupoli's idea
 */

#include <iostream>
#include <fstream>
#include "StemAndLeaf.h"

using namespace std;

// Don't modify main function
int main() {
    ifstream fin("input.txt");
    int x;
    int leafunit, stemunit;
    fin >> leafunit >> stemunit;
    StemAndLeaf one;
    one.setLeafUnit(leafunit);
    one.setStemUnit(stemunit);

    while (fin >> x) 
        one.addTerm(x);
    
    cout << "StemAndPlot: " << endl;
    cout << one << endl;
    
    one.removeTerm(34);
    one.removeTerm(35);
    one.removeTerm(30);

    cout << "After removing 34, 35, 30: " << endl;
    cout << "StemAndPlot: " << endl;
    cout << one << endl;

    one.removeTerm(5);
    one.removeTerm(6);
    one.removeTerm(5);

    cout << "After removing 5, 6, 5: " << endl;
    cout << "StemAndPlot: " << endl;
    cout << one << endl;

    one.removeTerm(165);
    cout << "After removing 165: " << endl;
    cout << "StemAndPlot: " << endl;
    cout << one << endl;

	  return 0;
}
