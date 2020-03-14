/* dam.h */
#ifndef __DAM_H__

#include "tmplvect.h"

#define NODE_STATISTICS_SIZE 200
extern unsigned int node_statistics[NODE_STATISTICS_SIZE];

class dam {
// member_vars
public:
  unsigned int _id;
  union {
    char* _name;
    unsigned int _namelen;
  };
  union {
    char* _key;
    unsigned int _keylen;
  };
  union {
    char* _parent;
    unsigned int _parentlen;
  };
  union {
    dam* _pparent;
    long _posparent;
  };
  union {
    unsigned int _numchildren;
    PtrVect<dam*>* _pchildren;
  };
  float _x, _y;
  long int _level;
// members_funcs;
public:
  dam(void);
  dam(char*, char*, float, float, long int);
  virtual ~dam(void);
  int num_children(void);
  char* key(void) { if (_key) return _key; else return _name; }
  void print(int indent, FILE* = stdout);
  dam* GetChild(int);
  dam* AddChild(dam*);
  void RemoveChild(dam*);
  dam* SearchChild(char*);
};

#define __DAM_H__
#endif
