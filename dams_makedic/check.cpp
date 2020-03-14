/* check.c */
#include "headers.h"

char key[MAXSTRLEN];
char buf[MAXSTRLEN];
// データチェック
void check() {
  int i, j;
  PtrVect<void*> list;
  dam* d, *child;
  char done;
  int count;
  do {
    done = 0;
    fputs("検索キーを入力してください(exitでモード解除): ", stdout);
    fgets(key, MAXSTRLEN - 1, stdin);
    for (i = strlen(key) -1; i > 0; i--) {
      if (key[i] >= 0x0 && key[i] < 0x20) {
	key[i] = '\0';
      } else {
	break;
      }
    }
    if (!strncasecmp(key, "exit", 4)) break;
    damsTryName.Find(standardize(key), list);
    while (!done && list.Elements() == 0) {
      fputs("該当するデータはありません\n", stdout);
      fputs("部分検索しますか?(1-最長一致, 2-部分一致, 0-しない: ", stdout);
      fgets(buf, MAXSTRLEN - 1, stdin);
      switch (buf[0]) {
      case '1':
	damsTryName.Find(key, list, MATCH_SHORTER);
	break;
      case '2':
	damsTryName.Find(key, list, MATCH_LONGER);
	break;
      case '0':
	done = 1;
	break;
      }
    }
    count = list.Elements();
    if (!done && count > 0) {
      for (i = 0; i < count; i++) {
	d = (dam*) list[i];
	static PtrVect<dam*> ancestors;
	ancestors.Clear();
	do {
	  ancestors.InsertAt(0, d);
	} while ((d = d->_pparent));
	for (j = 0; j < ancestors.Elements(); j++) {
	  d = ancestors[j];
	  fprintf(stdout, "%s:0x%x(%lf,%lf,%d)\n", d->_name, d, d->_x, d->_y, d->_level);
	}
	d = (dam*) list[i];
	if (d->_pchildren) {
	  for (j = 0; j < d->_pchildren->Elements(); j++) {
	    child = d->_pchildren->Element(j);
	    fprintf(stdout, "[%02d] %s:0x%x(%lf,%lf,%d)\n", j, child->_name, child, child->_x, child->_y, child->_level);
	    if (j >= 100) {
	      fprintf(stdout, "... (total %d children)\n", d->_pchildren->Elements());
	      break;
	    }
	  }
	}
	fputs("\n", stdout);
      }
    }
  } while (1);
}
