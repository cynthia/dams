/* retrieve.c */
#include "headers.h"

// ¸¡º÷
void retrieve(const char* keystring) {
  char buf[BUFSIZ], *standard, lastchar;
  int i, j;
  dam* d;
  PtrVect<dam*> result;
  PtrVect<dam*> familytree;
  standard = standardize(keystring);
  strcpy(buf, standard);
  lastchar = buf[strlen(buf) - 1];
  if ('0' <= lastchar && lastchar <= '9') {
    strcat(buf, "-");
  }
  int matchscore = get_longestmatch(buf, result);
  if (result.Elements() > 0) {
    fprintf(stdout, "SCORE: %d\n", matchscore);
    for (i = 0; i < result.Elements(); i++) {
      d = result[i];
      familytree.Clear();
      do {
	familytree.Add(d);
      } while ((d = d->_pparent));
      fputs("RESULT: ", stdout);
      for (j = familytree.Elements() - 2; j > 0; j--) {
	if (familytree[j]->_parent) {
	  if (debug) fprintf(stdout, "(%s/%s) ", familytree[j]->_parent, familytree[j]->_name);
	  else fprintf(stdout, "%s/", familytree[j]->_parent);
	}
      }
      d = familytree[0];
      if (d->_parent && *(d->_parent) != '\0') {
	if (debug) fprintf(stdout, "(%s/) ", d->_parent);
	else fprintf(stdout, "%s/", d->_parent);
      }
      fprintf(stdout, "%s (%lf,%lf) %d\n", d->_name, d->_x, d->_y, d->_level);
    }
  } else {
    fputs("NONE\n", stdout);
  }
}
