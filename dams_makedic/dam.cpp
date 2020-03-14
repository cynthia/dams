/* dam.c */
#include <string>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "dam.h"
#include "headers.h"

/* コンストラクタ */
dam::dam(void)
  :_name(NULL), _key(NULL), _parent(NULL), _x(.0), _y(.0), _level(0),
  _pparent(NULL), _pchildren(NULL) {}

dam::dam(char* name, char* parent, float x, float y, long int level)
  :_x(x), _y(y), _level(level), _pparent(NULL), _pchildren(NULL) {
  char* standard;
  int len = strlen(name);
  _name = new char[len + 1];
  memcpy(_name, name, len);
  _name[len] = '\0';
  standard = standardize(name);
  if (strcmp(name, standard)) {
    len = strlen(standard);
    _key = new char[len + 1];
    memcpy(_key, standard, len);
    _key[len] = '\0';
  } else {
    _key = NULL;
  }
  len = strlen(parent);
  _parent = new char[len + 1];
  memcpy(_parent, parent, len);
  _parent[len] = '\0';
}

/* デストラクタ */
dam::~dam(void) {
  delete[] _name;
  if (_key) delete[] _key;
  delete[] _parent;
  delete _pchildren;
}

/* デバッグ用表示ルーチン */
void dam::print(int indent, FILE* fp) {
  int i;
  for (i = 0; i < indent; i++) fputc(' ', fp);
  if (_key)
    fprintf(fp, "[%s]\t%s(%s)\t(%f,%f,%d)\n", _parent, _name, _key, _x, _y, _level);
  else
    fprintf(fp, "[%s]\t%s\t(%f,%f,%d)\n", _parent, _name, _x, _y, _level);
  if (!_pchildren) return;
  for (i = 0; i < num_children(); i++) {
    if (i == 100) {
      for (i = 0; i < indent; i++) fputc(' ', fp);
      fprintf(fp, "...(total %d children)\n", num_children());
      break;
    } else {
      GetChild(i)->print(indent + 4, fp);
    }
  }
}

/* 子ノードを取得する */
dam* dam::GetChild(int i) {
  if (!_pchildren || i >= _pchildren->Elements()) return NULL;
  return _pchildren->Element(i);
}

/* 子ノードを追加する */
dam* dam::AddChild(dam* child) {
  int n, a, h, c;
  dam* el;
  a = 0;
  if (!_pchildren) _pchildren = new PtrVect<dam*>;
  // _pchildren->Add(child);
  n = _pchildren->Elements();
  while (n != a) {
    h = a + (n - a) / 2;
    el = _pchildren->Element(h);
    c = strcmp(child->key(), el->key());
    if (c < 0) {
      n = h;
    } else if (c > 0) {
      if (a == h) {
	if (a < n) {
	  a += 1;
	} else {
	  break;
	}
      } else {
	a = h;
      }
    } else {
      if (debug) fprintf(stderr, "%s/'%s(%s)' is already stored.\n", E2U(_name), E2U(child->_name), E2U(child->key()));
      if (el == child) {
	/* すでに登録されている子ノードを追加しようとしている */
	if (debug) fprintf(stderr, "The node %s/'%s(%s)' has been a child.\n", E2U(_name), E2U(child->_name), E2U(child->key()));
	return el;
      }
      if (debug) fprintf(stderr, "%s/'%s(%s)' is already stored.\n", E2U(_name), E2U(child->_name), E2U(child->key()));
      if (child->_pchildren) {
	int i;
	dam* grandchild, *added;
	for (i = 0; i < child->_pchildren->Elements(); i++) {
	  grandchild = child->_pchildren->Element(i);
	  added = el->AddChild(grandchild);
	  if (added != grandchild) {
	    if (debug) fprintf(stderr, "'%s/%s' has been deleted during relinking process of '%s'.\n", E2U(el->_name), E2U(grandchild->_name), E2U(_name));
	    damsTryName.Remove(grandchild, grandchild->key());
	    damsTryParent.Remove(grandchild, grandchild->_parent);
	    if (grandchild->_key) delete[] grandchild->_key;
	    grandchild->_key = new char[8];
	    strcpy(grandchild->_key, "deleted");
	  }
	}
	delete child->_pchildren;
	child->_pchildren = NULL;
      }
      return el;
    }
  }
  _pchildren->InsertAt(a, child);
  //  child->_pparent = this;
  return child;
}

/* 子ノードを削除する */
void dam::RemoveChild(dam* child) {
  if (!_pchildren) return;
  _pchildren->Remove(child);
  if (_pchildren->Elements() == 0) {
    delete _pchildren;
    _pchildren = NULL;
  }
}

/* 子ノードから指定した名前のノードを検索する */
dam* dam::SearchChild(char* name) {
  int i;
  if (!_pchildren) return NULL;
  /*
    for (i = 0; i < _pchildren->Elements(); i++) {
    if (!strcmp(_pchildren->Element(i)->key(), name))
    return _pchildren->Element(i);
    }
    return NULL;
  */
  int n, a, h, c;
  dam* el;
  a = 0;
  n = _pchildren->Elements();
  name = standardize(name);

  while (n != a) {
    h = a + (n - a) / 2;
    el = _pchildren->Element(h);
    c = strcmp(name, el->key());

    if (c < 0) {
      n = h;
    } else if (c > 0) {
      if (a == h) {
	if (a < n) {
	  a += 1;
	} else {
	  break;
	}
      } else {
	a = h;
      }
    } else {
      return _pchildren->Element(h);
    }
  }
  return NULL;
}

unsigned int node_statistics[NODE_STATISTICS_SIZE];
int dam::num_children(void)
{
  if (!_pchildren) {
    return 0;
  }
  return _pchildren->Elements();
}
