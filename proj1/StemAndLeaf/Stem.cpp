#include <iostream>
#include "Leaf.h"
#include "Stem.h"

using namespace std;

Stem::Stem() : front(nullptr), back(nullptr) {}

Stem::~Stem() {
	while (front) {
		Leaf* temp = front;
		front = front->next;
		delete temp;
	}

	front = nullptr;
	back = nullptr;
}

Leaf* Stem::createLeaf(int value) {
  Leaf* leaf = new Leaf;
  leaf->value = value;
  leaf->count = 1;
  return leaf;
}

bool Stem::insert(int value) {

  if (front == nullptr) { //no leafs
    Leaf* leaf = createLeaf(value);
    front = leaf;
    back = leaf;
    return true;
  } else if (value < front->value) { //less than front
    Leaf* leaf = createLeaf(value);
    leaf->next = front;
    front = leaf;
    return true;
  } else if (back->value < value) { //greater than back
    Leaf* leaf = createLeaf(value);
    back->next = leaf;
    back = leaf;
    return true;
  } else if (front->value == value) {
    front->count++;
    return false;
  } else if (back->value == value) {
    back->count++;
    return false;
  }

  // Leaf* curr = front;
  // bool insert = false;

  // while (curr) {
  //   if (curr->value == value) {
  //     curr->count++;
  //     break;
  //   } else if (curr->next->value > value) {
  //     Leaf* leaf = createLeaf(value);
  //     leaf->next = curr->next;
  //     curr->next = leaf;
  //     insert = true;
  //     break;
  //   }
  //   curr = curr->next;
  // }

  // return insert;
  else {

    Leaf* curr = front;
    
    if (curr->value == value) {
      curr->count++;
      return false;
    }

    Leaf* currnext = front->next;

    while (curr->value < value && currnext->value < value) {
      curr = currnext;
      currnext = currnext->next;
    }

    if (currnext->value == value) {
      currnext->count++;
      return false;
    } else {
      Leaf* leaf = createLeaf(value);
      leaf->next = currnext;
      curr->next = leaf;
      return true;
    }
  }
}

// return true is a leaf is deleted 
bool Stem::remove(int target) {
  Leaf* del = front;
  Leaf* temp = del;

  while (del->value != target && del) {
    temp = del;
    del = del->next;
  }

  if (!del) {
    return false;
  } else if (del->count == 1) {
    if (del == front) { //first leaf
      if (del->next) {
        front = del->next;
        delete del;
      } else {
        front = nullptr;
        back = nullptr;
        delete del;
      }
      return true;
    } else if (!del->next) { //last leaf
        temp->next = nullptr;
        back = temp;
        delete del;
        return true;
    } else { //middle leaf
      temp->next = del->next;
      delete del;
      return true;
    }
  } else {
    del->count--;
    return false;
  }
}

// Don't modify
std::ostream &operator << (std::ostream &out, const Stem &x) {
  out << x.value <<" | ";
  Leaf *CURLEAF_ptr = x.front;  

  while ( CURLEAF_ptr != nullptr )
  {
    out << *CURLEAF_ptr <<" ";
    CURLEAF_ptr = CURLEAF_ptr -> next;
  }
  out << std::endl;

  return out;
}