#include <iostream>
#include "BinarySearchTree.h"
#include <fstream>


using namespace std;


int main( )
{
    // the firt test  
    int i, j;
    int test1[6] = {89, 91, 63 , 100,  70,  98}; //persistent dynamic set 
    int test1r[3] = {17, 5, 36};   //not persistent
    BinarySearchTree<int> t1;

    for ( i = 0; i < 6; i++ )
      t1.insert( test1[i], 0 );   //build the BST for test1[6]
    for ( i =0; i < 3; i++ )
      t1.insert( test1r[i], 1 );   //insert the data from test1r[3]
  
    cout << "Test 1: instance t1" << endl;
    t1.printTree();              //output the tree 


    // the second test

    int test2[10] = {23,  96,  80,  35,  59,  54,  16,  21,  50,  70};  // persistent dynamic set
    int test2r[4] = {36, 10, 37, 60};    //not persistent 10, 37, 60
    BinarySearchTree<int> t2;


    for ( i = 0; i < 10; i++ )
      t2.insert( test2[i], 0 );   //build the BST for test2[10]
    for ( i =0; i < 4; i++ )
      t2.insert( test2r[i], 1 );   //insert the data from test2r[4]

    cout << "\nTest 2: instance t2" << endl;
    t2.printTree();               //output the tree 


    // the third test

    int test3[8] = {29, 28, 68, 16, 3, 27, 36, 71};   //persistent dynamic set  
    int test3r[4] = {87,  66,  29,  38};       //not persistent 
    BinarySearchTree<int> t3;

    for ( i = 0; i < 8; i++ )     //build the BST for test3[8]
      t3.insert( test3[i], 0 );
    for ( i =0; i < 4; i++ )      //insert the data from test3r[4]
      t3.insert( test3r[i], 1 );
  
    cout << "\nTest 3: instance t3" << endl;
    t3.printTree();            //output the tree 


    // test the function remove
    cout << "\nTest 4: remove data 3 and 66 from instance t3 " << endl;

    //since 3 is from the persistent dynamic set, 3 will not be removed, i.e., t3.remove(3) will be ignored
    t3.remove(3); 
    t3.remove(66);   
    t3.printTree();

    // deep copy test

    cout << "\nTest 5: let t3 = t2, output t3 " << endl;
    t3 = t2; 
    t3.printTree();

    return 0;
}