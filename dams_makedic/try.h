#ifndef tryH
#define tryH

#include <memory.h>
#include <assert.h>
#include "tmplvect.h"

#define MATCH_EXACT      0 // 完全一致のみ
#define MATCH_LONGER     1 // 指定した文字列で始まる長い文字列
#define MATCH_SHORTER    2 // 指定した文字列に含まれる短い文字列

#define STATICS_SIZE    10 // 統計を取るサイズ
extern unsigned int statics[STATICS_SIZE];

typedef unsigned short int wchar;

/* トライ */
class PtrTry
{
public:
  char _letter;
  PtrVect<void*> *_list; // この文字で終るデータのリスト
  PtrVect<PtrTry*> *_next; // 次の文字へのリスト
public:
  PtrTry(char letter = '\0');
  ~PtrTry(void);
  void Add(void*, char* name);
  void Find(const char* key, PtrVect<void*>& result, char cond = MATCH_EXACT) const;
  void Remove(void*, char* key);
  void Clear(void);
  void MakeStatics(void);
  void QSort(int (*)(const void*, const void*));
};

/* 静的トライ */
/* Add や Remove はできない */
class StaticPtrTry
{
public:
  char _letter;
  int _nList;
  int _nNext;
  long* _pList;
  StaticPtrTry** _pNext;
public:
  StaticPtrTry(PtrTry*);
  void Find(const char* key, PtrVect<long>& result, char cond = MATCH_EXACT, long base = 0);
  StaticPtrTry* pack(StaticPtrTry* newaddress, long base = 0);
  unsigned long packedSize(void);
  long list(int i, long base = 0);
  StaticPtrTry* next(int i, long base = 0);
};

#endif /* tryH */
