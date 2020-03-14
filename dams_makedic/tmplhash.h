#ifndef tmplhashH
#define tmplhashH

#include <memory.h>
#include <assert.h>
#include "tmplvect.h"

#define DEFAULT_SIZE 10

/* ポインタハッシュのテンプレート */
template <class T> class PtrHash
{
protected:
  PtrVect<T> *_slots;
  int _size;
  int (*_hashfunc)(const void* key);
public:
  PtrHash(int (*hashfunc)(const void* key), int initsize = DEFAULT_SIZE);
  ~PtrHash(void);
  int Add(T, const void* key);
  PtrVect<T> * Find(const void* key) const;
  void Remove(T, const void* key);
  void Clear(void);
};

template <class T>
PtrHash<T>::PtrHash(int (*hashfunc)(const void*), int n)
{
  _hashfunc = hashfunc;
  _size = n;
  _slots = new PtrVect<T>[_size];
  memset(_slots, 0, sizeof(void*) * _size);
}

template <class T>
PtrHash<T>::~PtrHash()
{
  delete[] _slots;
}

/* key を指定してデータをスロットに追加する */
template <class T>
int PtrHash<T>::Add(T newobj, const void* key)
{
  int index = _hashfunc(key);
  assert(0 <= index && index < _size);
  PtrVect<T>* pslot = _slots + index;
  if (!pslot) {
    /* スロットの作成 */
    pslot = new PtrVect<T>;
    pslot->Add(newobj);
  } else if (pslot->Find(newobj) < 0) {
    pslot->Add(newobj);
  }
  return index;
}

/* key を探し、該当するリストを返す
   リストが空の場合、 NULL が返る */
template <class T>
PtrVect<T>* PtrHash<T>::Find(const void* key) const
{
  int index = _hashfunc(key);
  assert(0 <= index && index < _size);
  return _slots + index;
}

/* objを探して、リストから削除する。
   注意： obj が指すインスタンスは delete されない */
template <class T>
void PtrHash<T>::Remove(T obj, const void* key)
{
  int index = _hashfunc(key);
  assert(0 <= index && index < _size);
  PtrVect<T> *pslot = _slots[index];
  if (pslot) {
    pslot->Remove(obj);
    if (pslot->Elements() == 0) {
      delete pslot;
      _slots[index] = NULL;
    }
  }
}

template <class T>
void PtrHash<T>::Clear(void)
{
  int i;
  for (i = 0; i < _size; i++) {
    if (_slots[i]) delete _slots[i];
  }
}

#endif /* tmplhashH */
