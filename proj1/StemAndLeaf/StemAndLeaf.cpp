#include <__nullptr>
#include <cstddef>
#include <iostream>
#include "Leaf.h"
#include "Stem.h"
#include "StemAndLeaf.h"

using namespace std;

int StemAndLeaf::getLeafUnit() const { return leafUnit; }

void StemAndLeaf::setLeafUnit(int leafUnit) { this->leafUnit = leafUnit; }

int StemAndLeaf::getStemUnit() const { return stemUnit; }

void StemAndLeaf::setStemUnit(int stemUnit) { this->stemUnit = stemUnit; } 

StemAndLeaf::StemAndLeaf() : leafUnit(0), stemUnit(0), head(nullptr), tail(nullptr) {}

StemAndLeaf::~StemAndLeaf() {
  Stem* node = head;

	while (node) {
		Stem* temp = node;
		node = node->next;
		delete temp;
	}

	head = nullptr;
	tail = nullptr;
	delete node;
}

Stem* StemAndLeaf::createStem(int term) {
  // cout << term << endl;
  Stem* stem = new Stem();
  stem->value = term/10;
  stem->frequency = 0;
  return stem;
}

void StemAndLeaf::addTerm(int term) {

  int svalue = term/10;

  if (head == nullptr) { //no stem
  // cout << svalue << endl;
    Stem* stem = createStem(term);
    head = stem;
    tail = stem;
    if (stem->insert(term % 10)) {
      stem->frequency++;
    }
  } else if (svalue < head->value) { //less than head
    Stem* stem = createStem(term);
    stem->next = head;
    head = stem;
    if (stem->insert(term % 10)) {
      stem->frequency++;
    }
  } else if (tail->value < svalue) { //greater than tail
    Stem* stem = createStem(term);
    tail->next = stem;
    tail = stem;
    if (stem->insert(term % 10)) {
      stem->frequency++;
    }
  } else if (head->value == svalue) {
    if (head->insert(term % 10)) {
      head->frequency++;
    }
  } else if (tail->value == svalue) {
    if (tail->insert(term % 10)) {
      tail->frequency++;
    }
  }
  else {
    Stem* curr = head;
    if (curr->value == svalue) { //first stem
      if (curr->insert(term % 10)) {
        curr->frequency++;
      }
      return;
    }

    Stem* currnext = head->next;

    while (curr->value < svalue && currnext->value < svalue) {
      curr = currnext;
      currnext = currnext->next;
    }

    if (currnext->value == svalue) { //existing stem
      if (currnext->insert(term % 10)) {
        currnext->frequency++;
      }
    } else { //new stem
      Stem* stem = createStem(term);
      stem->next = currnext;
      curr->next = stem;
      if (stem->insert(term % 10)) {
        stem->frequency++;
      }
    }
  }
}

bool StemAndLeaf::removeTerm(int term) {

  Stem* del = head;
  Stem* temp = del;

  while (del->value != term/10 && del != nullptr) { //find stem
    temp = del;
    del = del->next;
  }
  if (!del) {
    return false;
  } else if (del->remove(term%10)) { //leaf deleted
    del->frequency--;
    if (del->frequency == 0) { //stem delete
      if (del == head) {
        if (del->next) {
          head = del->next;
          delete del;
        } else {
          head = nullptr;
          tail = nullptr;
          delete del;
        }
      } else if (!del->next) {
        temp->next = nullptr;
        tail = temp;
        delete del;
      } else {
        temp->next = del->next;
        delete del;
      }
    }
    return true;
  }
  return false;
}

// Don't modify
std::ostream &operator << (std::ostream &out, const StemAndLeaf &x) {
	// needs to go through the StemAndLeaf, one stem, then all leaves, then back to the next stem and it's leaves, and continue
    Stem * CURSTEM_ptr = x.head;
    while ( CURSTEM_ptr != nullptr )
    {
      out << *CURSTEM_ptr; 
      CURSTEM_ptr = CURSTEM_ptr -> next;
    }
    
	return out;
}