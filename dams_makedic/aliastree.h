/* aliastree.h */
#ifndef _ALIASTREE_H_
#define _ALIASTREE_H_

#include "tmplvect.h"

class aliasTree {
public:
  char* _name;
  PtrVect<aliasTree*> *_children;
public:
  aliasTree(char* name);
  ~aliasTree(void);
  aliasTree* addChild(char* name);
  aliasTree* searchChild(char* name);
  void addDescendant(PtrVect<char*>* names);
  aliasTree* searchDescendant(PtrVect<char*>* names);
};

#endif
