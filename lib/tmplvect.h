#ifndef tmplvectH
#define tmplvectH

#include <memory.h>
#include <strings.h>
#include <stdlib.h>

#define DEFAULT_SIZE 10

/* オブジェクト配列のテンプレート */
template <class T> class ObjVect
{
protected:
  T* _data;
  int _elements;
  int _size;
  int _delta;
public:
  ObjVect(int initsize = DEFAULT_SIZE);
  ~ObjVect(void);
  int Elements(void) const { return _elements; }
  T& Element(int i);
  T& operator [ ](int i);
  void operator =(const ObjVect<T>&);
  void operator +=(const ObjVect<T>&);
  void Add(T);
  void InsertAt(int, T);
  int Find(T) const;
  void Remove(T);
  void RemoveAt(int);
  void Replace(T, T);
  void Clear(void);
  void QSort(int (*fcmp)(const void *, const void *));
};

/* ポインタ配列のテンプレート */
template <class T> class PtrVect
{
protected:
  T* _data;
  int _elements;
  int _size;
  int _delta;
public:
  PtrVect(int initsize = DEFAULT_SIZE);
  ~PtrVect(void);
  int Elements(void) const { return _elements; }
  T& Element(int i);
  T& operator [ ](int i);
  void operator =(const PtrVect<T>&);
  void operator +=(const PtrVect<T>&);
  void Add(T);
  void InsertAt(int, T);
  int Find(T) const;
  void Remove(T);
  void RemoveAt(int);
  void Replace(T, T);
  void Clear(void);
  void ClearElements(void);
  void QSort(int (*fcmp)(const void *, const void *));
};

/* オブジェクト配列の実装 */
template <class T>
ObjVect<T>::ObjVect(int n)
{
  _data = (T*)malloc(sizeof(T) * n);
  _elements = 0;
  _size = n;
  _delta = n;
  memset(_data, 0, sizeof(T) * _size);
}

template <class T>
ObjVect<T>::~ObjVect()
{
  free(_data);
}

template <class T>
T& ObjVect<T>::Element(int i)
{
  if (i < 0 || i >= _elements) throw ("ObjVect: Illegal Array Index.");
  return _data[i];
}

template <class T>
T& ObjVect<T>::operator[](int i)
{
  if (i < 0 || i >= _elements) throw ("ObjVect: Illegal Array Index.");
  return _data[i];
}

template <class T>
void ObjVect<T>::operator =(const ObjVect<T>& d) {
  free(_data);
  _elements = d._elements;
  _size = d._size;
  _delta = d._delta;
  _data = (T*)malloc(sizeof(T) * _size);
  memcpy(_data, d._data, sizeof(T) * _elements);
}

template <class T>
void ObjVect<T>::operator +=(const ObjVect<T>& d) {
  for (int i = 0; i < d._elements; i++)
    Add(d._data[i]);
}

template <class T>
void ObjVect<T>::Add(T newobj)
{
  InsertAt(_elements, newobj);
}

template<class T>
void ObjVect<T>::InsertAt(int index, T newobj)
{
  if (_elements == _size) {
    // サイズを _delta 増やす
    size_t sizeoft = sizeof(T);
    T* newdata;
    newdata = (T*)realloc(_data, sizeoft * (_size + _delta));
    if (!newdata) { // realloc failed
      newdata = (T*)malloc(sizeoft * (_size + _delta));
      memmove(newdata, _data, sizeoft * _elements);
      free(_data);
      _data = newdata;
    } else {
      _data = newdata;
    }
    _size += _delta;
  }
  
  T* src, * dst;
  size_t size = sizeof(T) * (_elements - index);
  src = _data + index;
  dst = src + 1;
  memmove(dst, src, size);
  *src = newobj;
  _elements++;
}

/* objを探し、インデックス番号を返す */
template <class T>
int ObjVect<T>::Find(T obj) const
{
  for (int i = 0; i < _elements; i++)
    {
      if (_data[i] == obj) return i;
    }
  return -1;   // 見つからない
}

/* objを探して、リストから削除する。
   注意： obj が指すインスタンスは delete されない */
template <class T>
void ObjVect<T>::Remove(T obj)
{
  int index = Find(obj);
  if (index < 0) return;
  RemoveAt(index);
}

template <class T>
void ObjVect<T>::RemoveAt(int index)
{
  T* src, * dst;
  size_t size = sizeof(T) * (_elements - index - 1);
  dst = _data + index;
  src = dst + 1;
  memmove(dst, src, size);

  _elements--;
  memset(&_data[_elements], '\0', sizeof(T));
  if (_elements < _size - 2 * _delta) {
    /* 小さくなったのでリサイズ */
    T* newdata = (T*)realloc(_data, sizeof(T) * (_size - 2 * _delta));
    if (!newdata) {
      newdata = (T*)malloc(sizeof(T) * (_size - 2 * _delta));
      memmove(newdata, _data, sizeof(T) * _elements);
      free(_data);
      _data = newdata;
    } else {
      _data = newdata;
    }
    _size -= 2 * _delta;
  }
}

/* oldobj を探して、新しい newobj と置き換える
   注意： oldobj が指すインスタンスは delete されない */
template <class T>
void ObjVect<T>::Replace(T oldobj, T newobj)
{
  int index = Find(oldobj);
  if (index < 0) {
    throw ("ObjVect: Replace failed.");
  }
  _data[index] = newobj;
}

/* すべての要素をリストから削除する。インスタンスは delete しない */
template <class T>
void ObjVect<T>::Clear(void)
{
  free(_data);
  _data = (T*)malloc(sizeof(T) * _delta);
  _elements = 0;
  _size = _delta;
  memset(_data, 0, sizeof(T) * _size);
}

// クイックソート
template <class T>
void ObjVect<T>::QSort(int (*fcmp)(const void *, const void *))
{
  qsort(_data, _elements, sizeof(T), fcmp);
}


/* ポインタ配列の実装 */
template <class T>
PtrVect<T>::PtrVect(int n)
{
  _data = (T*)malloc(sizeof(T) * n);
  _elements = 0;
  _size = n;
  _delta = n;
  memset(_data, 0, sizeof(T) * _size);
}

template <class T>
PtrVect<T>::~PtrVect()
{
  free(_data);
}

template <class T>
T& PtrVect<T>::Element(int i)
{
  if (i < 0 || i >= _elements) throw ("PtrVect: Illegal Array Index.");
  return _data[i];
}

template <class T>
T& PtrVect<T>::operator[](int i)
{
  if (i < 0 || i >= _elements) throw ("PtrVect: Illegal Array Index.");
  return _data[i];
}

template <class T>
void PtrVect<T>::operator =(const PtrVect<T>& d) {
  free(_data);
  _elements = d._elements;
  _size = d._size;
  _delta = d._delta;
  _data = (T*)malloc(sizeof(T) * _size);
  memcpy(_data, d._data, sizeof(T) * _elements);
}

template <class T>
void PtrVect<T>::operator +=(const PtrVect<T>& d) {
  for (int i = 0; i < d._elements; i++)
    Add(d._data[i]);
}

template <class T>
void PtrVect<T>::Add(T newobj)
{
  InsertAt(_elements, newobj);
}

template<class T>
void PtrVect<T>::InsertAt(int index, T newobj)
{
  if (_elements == _size) {
    // サイズを _delta 増やす
    size_t sizeoft = sizeof(T);
    T* newdata;
    newdata = (T*)realloc(_data, sizeoft * (_size + _delta));
    if (!newdata) { // realloc failed
      newdata = (T*)malloc(sizeoft * (_size + _delta));
      memmove(newdata, _data, sizeoft * _elements);
      free(_data);
      _data = newdata;
    } else {
      _data = newdata;
    }
    _size += _delta;
  }
  
  T* src, * dst;
  size_t size = sizeof(T) * (_elements - index);
  src = _data + index;
  dst = src + 1;
  memmove(dst, src, size);
  *src = newobj;
  _elements++;
}

/* objを探し、インデックス番号を返す */
template <class T>
int PtrVect<T>::Find(T obj) const
{
  for (int i = 0; i < _elements; i++)
    {
      if (_data[i] == obj) return i;
    }
  return -1;   // 見つからない
}

/* objを探して、リストから削除する。
   注意： obj が指すインスタンスは delete されない */
template <class T>
void PtrVect<T>::Remove(T obj)
{
  int index = Find(obj);
  if (index < 0) return;
  RemoveAt(index);
}

template <class T>
void PtrVect<T>::RemoveAt(int index)
{
  T* src, * dst;
  size_t size = sizeof(T) * (_elements - index - 1);
  dst = _data + index;
  src = dst + 1;
  memmove(dst, src, size);

  _elements--;
  memset(&_data[_elements], '\0', sizeof(T));
  if (_elements < _size - 2 * _delta) {
    /* 小さくなったのでリサイズ */
    T* newdata = (T*)realloc(_data, sizeof(T) * (_size - 2 * _delta));
    if (!newdata) {
      newdata = (T*)malloc(sizeof(T) * (_size - 2 * _delta));
      memmove(newdata, _data, sizeof(T) * _elements);
      free(_data);
      _data = newdata;
    } else {
      _data = newdata;
    }
    _size -= 2 * _delta;
  }
}

/* oldobj を探して、新しい newobj と置き換える
   注意： oldobj が指すインスタンスは delete されない */
template <class T>
void PtrVect<T>::Replace(T oldobj, T newobj)
{
  int index = Find(oldobj);
  if (index < 0) {
    throw ("PtrVect: Replace failed.");
  }
  _data[index] = newobj;
}

/* すべての要素をリストから削除する。インスタンスは delete しない */
template <class T>
void PtrVect<T>::Clear(void)
{
  free(_data);
  _data = (T*)malloc(sizeof(T) * _delta);
  _elements = 0;
  _size = _delta;
  memset(_data, 0, sizeof(T) * _size);
}

/* すべての要素をリストから削除する。インスタンスも delete する */
template <class T>
void PtrVect<T>::ClearElements(void)
{
  int i;
  for (i = 0; i < _elements; i++) delete (_data[i]);
  Clear();
}

// クイックソート
template <class T>
void PtrVect<T>::QSort(int (*fcmp)(const void *, const void *))
{
  qsort(_data, _elements, sizeof(T), fcmp);
}

#endif /* tmplvectH */
