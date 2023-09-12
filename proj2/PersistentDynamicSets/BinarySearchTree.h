#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <iostream>    
#include <vector>
#include <stack>
using namespace std;


template <typename Comparable>
class BinarySearchTree
{
private:  // this private BinaryNode is within BST
  struct BinaryNode
  {
    Comparable element;
    BinaryNode* left;
    BinaryNode* right;
    bool status;     // status = 0 if the node belongs to the tree with root r1 (it can also be in the tree with root r2); 
    //status = 1 means that the node only belongs to the tree with root r2

    BinaryNode(const Comparable& theElement, BinaryNode *lt, BinaryNode *rt, bool st) : element( theElement ), left( lt ), right( rt ), status( st ) {}
  };

  BinaryNode* r1;    //r1 is the root of the BST for the persistent dynamic set
  BinaryNode* r2;

  /**
    * Internal method to insert into a subtree.
    * x is the item to insert.
    * t is the node that roots the subtree.
    * Set the new root of the subtree.
    * if st=0, insert an element from the persistent dynamic set; st=1,otherwise
    */
  void insert(const Comparable& x, BinaryNode*& t, bool st) {
    // impplement here
    if(st == 0) {
      if (!t) {
        t = new BinaryNode(x, nullptr, nullptr, st);
        return;
      } else if (t->element > x) {
        insert(x, t->left, st);
      } else if (t->element < x) {
        insert(x, t->right, st);
      }
    } else if(st == 1){
      if(!r2) {
        r2 = elementClone(r1, st);
      }

      BinaryNode* green = r1;
      BinaryNode* red = r2;

      while(true) {
        if(green->element > x) {
          // go to left side
          if(!red->right) {
            red->right = green->right;
          }
          if(!green->left) {
            break;
          }
          if(!red->left || red->left->status == 0) {
            red->left = elementClone(green->left, st);
          }
          green = green->left;
          red = red->left;
        } else if(green->element < x) {
          // go to right side
          if(!red->left) {
            red->left = green->left;
          } 
          if(!green->right) {
            break;
          }
          if(!red->right || red->right->status == 0) {
            red->right = elementClone(green->right, st);
          }
          green = green->right;
          red = red->right;
        } else {
          return;
        }
      }
      // reached end of green tree

      while(true) {
        if(red->element > x) {
          // go to left
          if(!red->left) {
            break;
          }
          red = red->left;
        } else if(red->element < x) {
          // go to right
          if(!red->right) {
            break;
          }
          red = red->right;
        } else {
          throw new IllegalArgumentException;
        }
      }
      // reached end of red tree

      if(red->element > x) {
        red->left = new BinaryNode(x, nullptr, nullptr, st);
      } else if(red->element < x) {
        red->right = new BinaryNode(x, nullptr, nullptr, st);
      } else {
        throw new IllegalArgumentException;
      }
    }
  }

  /**
    * Internal method to remove from a subtree.
    * x is the item to remove.
    * t is the node that roots the subtree.
    * Set the new root of the subtree.
    * this function is only for the elements not in the persistent dynamic set
    */
  void remove(const Comparable& x, BinaryNode*& t) {
    //implement here
    if(!t) {
      return;
    }
    if(t->element > x && t->left->element != x) {
      remove(x, t->left);
    } else if(t->element < x && t->right->element != x) {
      remove(x, t->right);
    } else {

      if(t->left) {
        if(t->left->element == x) { // left child
          BinaryNode* temp = t->left;
          if(t->left->left && t->left->right) { // two children
            BinaryNode* temp2 = search(findMin(t->left->right), r2);
            temp2->left = t->left->left;
            t->left = temp2;
          } else if(t->left->left) { // just left
            t->left = t->left->left;
          } else if(t->left->right) { // just right
            t->left = t->left->right;
          }
          delete temp;
        }
      } else if(t->right) {
        if(t->right->element == x) { // right child
          BinaryNode* temp = t->right;
          if(t->right->left && t->right->right) { // two children
            BinaryNode* temp2 = search(findMin(t->right->right), r2);
            temp2->left = t->right->left;
            t->right = temp2;
          } else if(t->right->left) {
            t->right = t->right->left;
          } else if(t->right->right) {
            t->right = t->right->right;
          }
          delete temp;
        }
      }
    }
  }

  /**
    * Internal method to make subtree empty.
    * if st = 1, 't' is a node in the tree with root r2; otherwise, 
    * 't' is a node in the tree with root r1 
    * think about how to deal with 't' if 't' is a common node of the two
    * trees
    */
  void makeEmpty(BinaryNode * & t, bool st) {
    if(!t) {
      return;
    }
    if(!st) {
      makeEmpty(t->left, st);
      makeEmpty(t->right, st);
    } else if(st) {
      if(t->left) {
        if(t->left->status) {
          makeEmpty(t->left, st);
        } 
      } 
      if(t->right) {
        if(t->right->status) {
          makeEmpty(t->right, st);
        }
      }
    }
    delete t;
    t = nullptr;
  }

  /**
    * Internal method to clone subtree.
    * if st = 1, t is a node in the BST with root r1;
    * if st = 0, otherwise
    */
  BinaryNode * elementClone(BinaryNode *t, bool st) const {
    if(!t) {
      return t;
    }
    BinaryNode* cloneCopy = new BinaryNode(t->element, nullptr, nullptr, st);
    return cloneCopy;
  }

  BinaryNode * clone(BinaryNode *t, bool st) const { //deep copy, clone from root down
    //implement here
    if(!t) { // base case
      return nullptr;
    }
    BinaryNode* newNode = new BinaryNode(t->element, t->left, t->right, t->status);

    if(st == 0) {
      if(t->left) { // left child clone
        newNode->left = clone(t->left, t->status);
      }
      if(t->right) { // right child clone
        newNode->right = clone(t->right, t->status);
      }

    } else if(st == 1) {
      if(t->left) {
        if(t->left->status == 1) {
          newNode->left = clone(t->left, t->status);
        } else {
          newNode->left = search(t->left->element, r1);
        }
      } 
      if(t->right) {
        if(t->right->status == 1) {
          newNode->right = clone(t->right, t->status);
        } else {
          newNode->right = search(t->right->element, r1);
        }
      }
    }
    return newNode;
  }

public:
  BinarySearchTree() :r1( NULL ), r2( NULL ) {}

  BinarySearchTree(const BinarySearchTree & rhs) {
    *this = rhs;
  }

  /**
    * Destructor for the tree
    */
  ~BinarySearchTree() {
    makeEmpty();
  }

  /**
    * Find the smallest item in the tree.
    * Throw UnderflowException if empty.
    */
  const Comparable& findMin(BinaryNode* t) const {
    //implement here
    if(!t) {
      throw new UnderflowException;
    }
    if(t->left == nullptr) {
      return t->element;
    }
    return findMin(t->left);
  }

  /**
    * Find the largest item in the tree.
    * Throw UnderflowException if empty.
    */
  const Comparable& findMax(BinaryNode* t) const {
    //implement here
    if(!t) {
      throw new UnderflowException;
    }
    if(t->right == nullptr) {
      return t->element;
    }
    return findMax(t->right);
  }

  /**
    * Returns true if x is found in the subtree with root t.
    */
  bool contains(const Comparable& x, BinaryNode* t) const { 
    //implement here
    if(!t) {
      return false;
    } else {
      if(t->element == x) {
        return true;
      } else if(t->element > x) {
        return contains(x, t->left);
      } else if(t->element < x) {
        return contains(x, t->right);
      }
    }
    return false;
  }

  /**
   * returns the node with element = x in the subtree with root t
   * to make sure that x is always here, call contains(x, t) first
   */
  BinaryNode* search(const Comparable& x, BinaryNode* t) const {
    //implement here
    if (!t || t->element == x) {
      return t;
    } else if (t->element < x) {
      return search(x, t->right);
    }
    return search(x, t->left);
  }

  /**
    * Test if the tree is logically empty.
    * Return true if empty, false otherwise.
    */
  bool isEmpty() const {
    return r1 == NULL;
  }

  /**
    * Make the tree logically empty.
    * remove all items
    * pay attention to the common nodes in r1 and r2
    */
  void makeEmpty() {
    makeEmpty(r2, 1);
    makeEmpty(r1, 0);
  }

  /**
    * Insert x into the tree; duplicates are ignored.
    * if st = 0, insert into the tree with root r1; if st=1, insert into the
    * tree with root r2
    */
  void insert(const Comparable& x, bool st) {
    //implement here
    if(st == 0) {
      insert(x, r1, st);
    } else if(st == 1) {
      insert(x, r2, st);
    }
  } 

  /**
    * Remove x from the tree with root r2. Nothing is done if x is not found
    * or if x is from the persistent dynamic set.
    */
  void remove(const Comparable& x) {
    //implement here
    if(contains(x, r2) && !contains(x, r1)) {
      remove(x, r2);
    }
  }

  /**
    * Deep copy.
    * notice the common nodes in both trees
    */
  const BinarySearchTree& operator=(const BinarySearchTree& rhs) {
    if( this != &rhs ) {
      makeEmpty();
      r1 = clone( rhs.r1, 0 );
      r2 = clone( rhs.r2, 1 );
    }
    return *this;
  }

  /* in-order tree walk and the result is stored in v
    * the root is r
    */
  void inOrder(vector <BinaryNode*>& v, BinaryNode* r) {
    //implement here
    if(!r) {
      return;
    }
    inOrder(v, r->left);
    v.push_back(r);
    inOrder(v, r->right);
  }

  /* this function is to test
   * please do not change
   */
  void printTree() {    // Print tree in sorted order
    vector <BinaryNode*> v1, v2;

    inOrder (v1, r1);   //inorder traverse
    inOrder (v2, r2);  //inorder traverse

    cout << "print BST for persistent dynamic set   " << endl;

    int i, j;
    for ( i = 0; i < v1.size(); i++) {
      cout <<  v1.at (i) -> element << "  ";
    }
    cout << endl;

    cout << "print BST for the whole input set   " << endl;

    for ( i = 0; i < v2.size(); i++) {
      cout << v2.at(i) -> element << "  ";
    }
    cout << endl;

    i=0; j=0;

    // output the common nodes with the same address in both trees
    // a common node in both trees must have the same address 
    cout << "Common nodes: ";
    while (i < v1.size()) {
      if (v1.at(i)->element == v2.at(j)->element) {
        if (v1.at(i) == v2.at(j)) {  // if the address are equal
          cout << v1.at(i) -> element << "  "; 
        }
        i++; j++;
      } else if (v2.at(j)->element < v1.at(i)->element) {
        j++;
      }
    }
    cout << endl;
  }
};


#endif
