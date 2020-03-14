/* maketree.c */
#include "headers.h"

// 全ての TREE を作り直し
void make_all_tree(void) {
  int index, count = damsArray.Elements(), proc = 1;
  dam* d;
  for (int i = 0; i < count; i++) {
    if (i + 1 >= proc * count / 10) {
      fprintf(stderr, "%d%% ", proc * 10);
      proc++;
    }
    d = damsArray[i];
    if (d) {
      make_tree(d);
    }
  }
  fputc('\n', stderr);
}

// 親子関係の作成
void make_tree(dam* key) {
  PtrVect<void*> list, children;
  dam* parent, *added;

  if (debug) {
    //    fprintf(stderr, "%s/%s の親子関係を修正します\n", key->_parent, key->_name);
  }
    
  // 未接続リンクの結合
  if (! key->_pparent) {
    parent = get_parent(key);
    if (debug) fprintf(stderr, "  親へのポインタが設定されていません。");
    if (parent) {
      key->_pparent = parent;
      added = parent->AddChild(key);
      if (added != key) {
	fprintf(stderr, "  make_tree: key(%s/%s) is deleted.\n", key->_parent, key->_name);
	delete key;
      }
      if (debug) fprintf(stderr, "  親がみつかりました。('%s')\n", parent->_name);
    } else {
      if (debug) fprintf(stderr, "  親がみつかりませんでした。\n");
    }
  } else {
    //    if (debug) fprintf(stderr, "  親へのポインタが既に設定されています。('%s')\n", key->_pparent->_name);
  }
}
