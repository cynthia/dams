#ifndef damH
#define damH

/* dam.h */
#include <stdio.h>
#include "tmplvect.h"

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
    ObjVect<long>* _pchildren;
  };
  float _x, _y;
  long int _level;
// members_funcs;
public:
  dam(void);
  dam(char*, char*, float, float, long int);
  const char* key(void) { if (_key) return _key; else return _name; }
  virtual ~dam(void);
};

extern dam* read_from_file(FILE* fp, long fpos);

#endif /* damH */
