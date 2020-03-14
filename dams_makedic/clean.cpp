/* clean.c */
#include "headers.h"

static void clean_children(dam* node);

void clean(void) {
  int i, elements;
  elements = damsArray.Elements();
  fprintf(stderr, "%d 個の要素があります\n", elements);
  for (i = 0; i < elements; i++) {
    if (!damsArray[i]->_pparent) {
      clean_children(damsArray[i]);
    }
  }
  for (i = 0; i < elements; i++) {
    if (!damsArray[i]->_name) {
      damsArray.RemoveAt(i);
      // delete damsArray[i];
      i--;
      elements--;
    }
  }
  fprintf(stderr, "%d 個に整理しました\n", elements);
}

int damcmp(const void* p1, const void* p2) {
  dam* pd1, * pd2;
  pd1 = *((dam**)p1);
  pd2 = *((dam**)p2);
  return strcmp(pd1->key(), pd2->key());
}

void clean_children(dam* node) {
  int i, j, count;
  dam* p1, *p2;
  if (!node->_pchildren) return;
  count = node->_pchildren->Elements();
  for (i = 0; i < count; i++) {
    clean_children(node->_pchildren->Element(i));
  }
  node->_pchildren->QSort(damcmp);
  for (i = 0; i < count - 1; i++) {
    p1 = node->_pchildren->Element(i);
    if (!p1->_name) continue;
    p2 = node->_pchildren->Element(i + 1);
    if (!strcmp(p1->key(), p2->key())) {
      // delete p2
      damsTryName.Remove(p2, p2->key());
      if (p2->_parent) damsTryParent.Remove(p2, p2->_parent);
      if (p2->_pchildren) {
	for (j = 0; j < p2->_pchildren->Elements(); j++) {
	  p2->_pchildren->Element(j)->_pparent = p1;
	}
	if (!p1->_pchildren) p1->_pchildren = new PtrVect<dam*>;
	*(p1->_pchildren) += *(p2->_pchildren);
	p2->_pchildren->Clear();
      }
      node->_pchildren->RemoveAt(i + 1);
      delete[] p2->_name;
      if (p2->_key) delete[] p2->_key;
      p2->_name = NULL;
      p2->_key = NULL;
      p2->_parent = NULL;
      p2->_pparent = NULL;
      i--;
      count--;
    }
  }
}
