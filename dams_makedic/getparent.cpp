/* getparent.c */
#include "headers.h"

// ¿Æ¤Î¼èÆÀ
dam* get_parent(dam* key) {
  int i, count;
  float dist, min_dist;
  dam* dam0, *nearest = NULL;
  PtrVect<void*> list;
  if (key->_pparent) return key->_pparent; // ´û¤Ë·×»»ºÑ¤ß
  damsTryName.Find(standardize(key->_parent), list);
  count = list.Elements();
  if (count == 0) return NULL;
  min_dist = -1;
  for (i = 0; i < count; i++) {
    dam0 = (dam*)(list[i]);
    dist = (key->_x - dam0->_x) * (key->_x - dam0->_x) + (key->_y - dam0->_y) * (key->_y - dam0->_y);
    if (min_dist < 0 || dist < min_dist) {
      min_dist = dist;
      nearest = dam0;
    }
  }
  key->_pparent = nearest;
  return nearest;
}
