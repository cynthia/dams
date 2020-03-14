/* maketry.c */
#include "headers.h"

// try §Œ∫Ó¿Æ
void make_try() {
  int index, count = damsArray.Elements(), proc = 1;
  dam* d;
  PtrVect<void*>* list;
  PtrVect<void*> retr;
  for (int i = 0; i < count; i++) {
    if (i + 1 >= proc * count / 10) {
      fprintf(stderr, "%d%% ", proc * 10);
      proc++;
    }
    d = damsArray[i];
    if (d->_level > 5 && d->_level < 9) { /*  _isNumeric(d->key()) >= 0) { */
      /*      if (debug) {
	fprintf(stderr, "Skipping %s (Numeric)\n", d->key());
	} */
    } else {
      damsTryName.Add(d, d->key());
    }
    if ((d->_parent)[0] != '\0') {
      if (d->_level > 6 && d->_level < 9) { // _isNumeric(d->_parent) >= 0) {
	if (debug > 0) {
	  fprintf(stderr, "Skipping %s (Numeric), level = %d\n", d->_parent, d->_level);
	}
      } else {
	damsTryParent.Add(d, standardize(d->_parent));
      }
    }
  }
  fputc('\n', stderr);
}

