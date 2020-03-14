/* aliastree.h */
#include "headers.h"
#include "aliastree.h"

aliasTree::aliasTree(char* name) {
  char* standard = standardize(name);
  _name = new char[strlen(standard) + 1];
  strcpy(_name, standard);
  _children = NULL;
}

aliasTree::~aliasTree(void) {
  if (_children) {
    for (int i = 0; i < _children->Elements(); i++) {
      delete _children->Element(i);
    }
    delete _children;
  }
}

aliasTree* aliasTree::addChild(char* name) {
  char* key = standardize(name);
  aliasTree* newnode;
  if (!_children) {
    _children = new PtrVect<aliasTree*>;
  }
  newnode = searchChild(key);
  if (!newnode) {
    newnode = new aliasTree(key);
    _children->Add(newnode);
  }
  return newnode;
}

aliasTree* aliasTree::searchChild(char* name) {
  char* key = standardize(name);
  aliasTree* child;
  if (!_children) return NULL;
  for (int i = 0; i < _children->Elements(); i++) {
    child = _children->Element(i);
    if (!strcmp(child->_name, key)) return child;
  }
  return NULL;
}

void aliasTree::addDescendant(PtrVect<char*>* names) {
  int i, n;
  aliasTree *node = this, *nextnode;
  n = names->Elements();
  for (i = 0; i < n; i++) {
    node = node->addChild(names->Element(i));
  }
}

aliasTree* aliasTree::searchDescendant(PtrVect<char*>* names) {
  int i, n;
  aliasTree *node = this;
  n = names->Elements();
  for (i = 0; i < n; i++) {
    node = node->searchChild(names->Element(i));
    if (!node) return NULL;
  }
  return node;
}
