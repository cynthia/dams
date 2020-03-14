#include <memory.h>
#include <assert.h>
#include <stdio.h>
#include "tmplvect.h"
#include "try.h"

/* PtrTry */
PtrTry::PtrTry(char letter)
{
  _letter = letter;
  _list = NULL;
  _next = NULL;
}

PtrTry::~PtrTry()
{
  if (_next) {
    int count = _next->Elements();
    for (int i = 0; i < count; i++) {
      delete _next->Element(i);
    }
    _next->Clear();
  }
  if (_list != NULL) _list->Clear();
}

/* 文字列を指定してデータを追加する */
void PtrTry::Add(void* newobj, char* key)
{
  if (! *key) {
    // 文字列終端 ここにデータをストアする
    if (_list == NULL) _list = new PtrVect<void*>;
    if (_list->Find(newobj) < 0) _list->Add(newobj);
  } else {
    // 次の文字を探す
    if (!_next) {
      _next = new PtrVect<PtrTry*>;
    } else {
      int count = _next->Elements();
      for (int i = 0; i < count; i++) {
	if (_next->Element(i)->_letter == *key) {
	  key++;
	  _next->Element(i)->Add(newobj, key);
	  return;
	}
      }
    }
    PtrTry* newTry = new PtrTry(*key);
    key++;
    _next->Add(newTry);
    newTry->Add(newobj, key);
  }
}

/* key を探し、該当するリストを返す
   リストが空の場合、 NULL が返る
   帰り値は一致した文字数
*/
int PtrTry::Find(char* key, PtrVect<void*>& result, char cond) const
{
  int matchlen = 0;
  if (! *key) {
    // ここでマッチした
    if (_list != NULL) {
      result = *_list;
      return matchlen;
    }
    if (cond != MATCH_LONGER) {
      result.Clear();
      return matchlen;
    }
    result.Clear();
    if (!_next) return matchlen;
    int count = _next->Elements();
    PtrVect<void*> tmplist;
    for (int i = 0; i < count; i++) {
      _next->Element(i)->Find(key, tmplist, cond);
      result += tmplist;
    }
    return matchlen;
  }
  if (_next == NULL) {
    // これ以上一致するリストは存在しない
    if (cond == MATCH_EXACT) {
      result.Clear();
      return 0;
    } else {
      if (_list) {
	result = *_list;
      } else {
	result.Clear();
      }
      return 0;
    }
  }
  // まだ一致するデータがある
  int count = _next->Elements();
  PtrVect<void*> list;
  for (int i = 0; i < count; i++) {
    if (_next->Element(i)->_letter == *key) {
      key++;
      matchlen = _next->Element(i)->Find(key, list, cond) + 1;
      if (list.Elements() > 0 || cond == MATCH_EXACT) {
	result = list;
	return matchlen;
      }
      if (_list != NULL) {
	result = *_list;
	return matchlen;
      }
      break;
    }
  }
  if (_list) result = *_list;
  else result.Clear();
  return matchlen; // これ以上一致しないので、最長一致を返す
}

void PtrTry::Remove(void* obj, char* key)
{
  if (! *key) {
    if (_list) {
      _list->Remove(obj);
    }
    return;
  }
  if (_next == NULL) return;
  int count = _next->Elements();
  for (int i = 0; i < count; i++) {
    if (_next->Element(i)->_letter == *key) {
      key++;
      return _next->Element(i)->Remove(obj, key);
    }
  }
  return; // 該当するデータ無し
}

void PtrTry::Clear(void)
{
  _letter = 0;
  delete _list;
  _list = NULL;
  if (_next) {
    _next->ClearElements();
  }
  delete _next;
  _next = NULL;
}

unsigned int statics[STATICS_SIZE];

void PtrTry::MakeStatics(void)
{
  if (!_next) {
    statics[0]++;
    return;
  }
  int count = _next->Elements();
  if (count < STATICS_SIZE - 1) statics[count]++;
  else statics[STATICS_SIZE - 1]++;
  for (int i = 0; i < count; i++) {
    _next->Element(i)->MakeStatics();
  }
}

void PtrTry::QSort(int (*fcmp)(const void*, const void*))
{
  if (_list) _list->QSort(fcmp);
  if (_next) {
    int count = _next->Elements();
    for (int i = 0; i < count; i++) {
      _next->Element(i)->QSort(fcmp);
    }
  }
}

/* StaticPtrTry */
static void* offset(void* p, long base) {
  return (void*)((char*)p + base);
}

StaticPtrTry::StaticPtrTry(PtrTry* key) {
  int i;
  _letter = key->_letter;
  if (key->_list) {
    _nList = key->_list->Elements();
    _pList = (long*)malloc(sizeof(long) * _nList);
  } else {
    _nList = 0;
    _pList = NULL;
  }
  if (key->_next) {
    _nNext = key->_next->Elements();
    _pNext = (StaticPtrTry**)malloc(sizeof(StaticPtrTry*) * _nNext);
  } else {
    _nNext = 0;
    _pNext = NULL;
  }
  for (i = 0; i < _nList; i++) {
    _pList[i] = long(key->_list->Element(i));
  }
  for (i = 0; i < _nNext; i++) {
    _pNext[i] = new StaticPtrTry(key->_next->Element(i));
  }
}

unsigned long StaticPtrTry::packedSize(void) {
  unsigned long size = sizeof(StaticPtrTry);
  size += sizeof(long) * this->_nList;
  size += sizeof(StaticPtrTry*) * this->_nNext;
  for (int i = 0; i < this->_nNext; i++) {
    size += this->_pNext[i]->packedSize();
  }
  return size;
}

StaticPtrTry* StaticPtrTry::pack(StaticPtrTry* newaddress, long base) {
  int i;
  char* cp = (char*)newaddress;
  StaticPtrTry* newnode = (StaticPtrTry*)(offset(newaddress, base));
  memcpy(newnode, this, sizeof(StaticPtrTry));
  cp += sizeof(StaticPtrTry);
  memcpy(offset(cp, base), this->_pList, sizeof(long) * this->_nList);
  newnode->_pList = (long*)cp;
  cp += sizeof(long) * this->_nList;
  newnode->_pNext = (StaticPtrTry**)cp;
  cp += sizeof(StaticPtrTry*) * this->_nNext;

  StaticPtrTry** pp;
  for (i = 0; i < this->_nNext; i++) {
    pp = (StaticPtrTry**)(offset(newnode->_pNext + i, base));
    *pp = (StaticPtrTry*)cp;
    cp = (char*)(this->_pNext[i]->pack((StaticPtrTry*)cp, base));
  }
  return (StaticPtrTry*)cp;
}

/* key を探し、該当するリストを返す
   リストが空の場合、 NULL が返る */
int StaticPtrTry::Find(char* key, ObjVect<long>& result, char cond, long base)
{
  int matchlen = 0;
  int i;
  StaticPtrTry* node;
  if (! *key) {
    // ここでマッチした
    if (_nList > 0) {
      result.Clear();
      for (i = 0; i < _nList; i++) {
	result.Add(this->list(i, base));
      }
      return matchlen;
    }
    if (cond != MATCH_LONGER) {
      result.Clear();
      return matchlen;
    }
    result.Clear();
    if (_nNext == 0) return matchlen;
    int count = _nNext;
    ObjVect<long> tmplist;
    for (i = 0; i < count; i++) {
      node = next(i, base);
      node->Find(key, tmplist, cond, base);
      result += tmplist;
    }
    return matchlen;
  }
  if (_nNext == 0) {
    // これ以上一致するリストは存在しない
    if (cond == MATCH_EXACT) {
      result.Clear();
      return matchlen;
    } else {
      if (_nList > 0) {
	result.Clear();
	for (i = 0; i < _nList; i++) {
	  result.Add(this->list(i, base));
	}
      } else {
	result.Clear();
      }
      return matchlen;
    }
  }
  int count = _nNext;
  ObjVect<long> list;
  StaticPtrTry** pp;
  for (int i = 0; i < count; i++) {
    node = this->next(i, base);
    if (node->_letter == *key) {
      key++;
      matchlen = node->Find(key, list, cond, base) + 1;
      if (list.Elements() > 0 || cond == MATCH_EXACT) {
	result = list;
	return matchlen;
      }
      if (_nList > 0) {
	result.Clear();
	for (i = 0; i < _nList; i++) {
	  result.Add(this->list(i, base));
	}
	return matchlen;
      }
      break;
    }
  }
  result.Clear();
  if (_nList > 0) {
    for (i = 0; i < _nList; i++) {
      result.Add(this->list(i, base));
    }
  }
  return matchlen; // これ以上一致しないので、最長一致を返す
}

long StaticPtrTry::list(int i, long base) {
  long l;
  l = *(long*)(offset(_pList + i, base));
  return l;
}

StaticPtrTry* StaticPtrTry::next(int i, long base) {
  StaticPtrTry* p;
  p = *(StaticPtrTry**)(offset(_pNext + i, base));
  p = (StaticPtrTry*)(offset(p, base));
  return p;
}

int StaticPtrTry::copy(ObjVect<long>& to, long base) {
  to.Clear();
  for (int i = 0; i < _nList; i++) {
    to.Add(list(i, base));
  }
  return _nList;
}

/* key を探し、該当するメンバーがあるかないかを返す */
int StaticPtrTry::hasMember(char* key, long base)
{
  int matchlen = 0;
  int i;
  StaticPtrTry* node;
  if (! *key) {
    return -1;
  }
  if (_nNext == 0) {
    // これ以上一致するリストは存在しない
    return 0;
  }
  int count = _nNext;
  ObjVect<long> list;
  StaticPtrTry** pp;
  for (int i = 0; i < count; i++) {
    node = this->next(i, base);
    if (node->_letter == *key) {
      key++;
      return node->hasMember(key, base);
    }
  }
  return 0;
}

