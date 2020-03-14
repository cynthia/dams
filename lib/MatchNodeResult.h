#ifndef __MATCH_NODE_RESULT_H__
#define __MATCH_NODE_RESULT_H__

#include <string>
#include "dams.h"

struct MatchNodeResult {
public:
  int score;
  int maxlen;
  std::string rest;
  ObjVect<long> res;
  MatchNodeResult():
    score(0),maxlen(0),rest("") {res.Clear();}
};

#endif /* __MATCH_NODE_RESULT_H__ */
