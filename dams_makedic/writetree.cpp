/* writetree.c */
#include "headers.h"
#include "strlib.h"

void write_tree(FILE* ofp) {
  int i, elements;
  elements = damsArray.Elements();
  fprintf(stderr, "%d 個の要素があります\n", elements);
  for (i = 0; i < elements; i++) {
    if (!damsArray[i]->_pparent) {
      damsArray[i]->print(0, ofp);
    }
  }
}

void write_hook_sub(FILE* ofp, dam* cnode) {
  int i, j, len;
  char *buf, *ep;
  dam* child;
  if (cnode->_level == 0 || (cnode->_level > 5 && cnode->_level < 10)) return;
  
  buf = (char*)malloc(sizeof(char) * 10 + 1);
  len = kstrncpy(buf, cnode->_name, 10);
  ep = buf + len;
  
  if (len >= 8) fprintf(ofp, "%s\n", buf);
  if (!cnode->_pchildren || len >= 10) return;
  for (i = 0; i < cnode->num_children(); i++) {
    child = cnode->GetChild(i);
    if (child->_level > 5 && child->_level < 10) {
      if (child->_level == 6) {
	char *cp, *std;
	std= standardize(child->_name);
	for (cp = ep; '0' <= *std && '9' >= *std; cp++, std++) {
	  *cp = *std;
	}
	*cp = '\0';
	fprintf(ofp, "%s\n", buf);
      }
      continue;
    }
    if (len + kstrncpy(ep, child->_name, 10 - len) >= 8) fprintf(ofp, "%s\n", buf);
    write_hook_sub(ofp, child);
  }
  free(buf);
  return;
}

void write_hook(FILE* ofp) {
  int i, elements;
  elements = damsArray.Elements();
  fprintf(stderr, "%d 個の要素があります\n", elements);
  for (i = 0; i < elements; i++) {
    if (!damsArray[i]->_pparent) {
      write_hook_sub(ofp, damsArray[i]);
    }
  }
  return;
}
