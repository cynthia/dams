/* readcsv.c */
#include <ctype.h>
#include <stdio.h>
#include "headers.h"

/* CSV データの読み込み */

/*
 CSV データは次の形式とする
<top-placename>\t<child>\t<grandchild>\t...\t<longitude>\t<latitude>\t<level>
<top-placename>\t<child>\t<grandchild>\t...\t<longitude>\t<latitude>\t<level>
 直前の行と同じ親に属する場合、親名を省略してもよい
 例)
 東京都,豊島区,雑司が谷二丁目,13番地,15号,139.46823,35.73123,7
 ,,高田一丁目,1番地,1号,139.84023,35.74485,7
 は
 東京都,豊島区,雑司が谷二丁目,13番地,15号,139.46823,35.73123,7
 東京都,豊島区,高田一丁目,1番地,1号,139.84023,35.74485,7
 と同じ

 空白は無視される
 セパレータは TAB または ',' とする
 level は以下のとおり
 0 -> 未定義
 1 -> 都道府県
 2 -> 郡・支庁
 3 -> 市町村、特別区
 4 -> 政令指定市の区
 5 -> 大字
 6 -> 字・丁目
 7 -> 街区・通り・地番
 8 -> 号・枝番
 9 -> ビル名
 10 -> 部屋番号
 11 -> 鉄道路線名
 12 -> 駅名
*/

static PtrVect<char*>* args = new PtrVect<char*>(10); // 属性値保存用配列

void read_from_csv(FILE* ifp) {
  dam* d, *pparent, *added;
  PtrVect<dam*> last;
  PtrVect<char*>* args;
  char buf[BUFSIZ];
  char name[MAXSTRLEN];
  float x, y, x0, y0, x1, y1;
  int index, ele;
  long int level;
  last.Clear();
  while (fgets(buf, BUFSIZ, ifp)) {
    // longitude, latitude の読み込み
    args = get_args(buf, ',');
    if (args->Elements() <= 1) { // 改行があるので必ず1にはなる
      args = get_args(buf, '\t');
    }
    ele = args->Elements();
    if (ele > 3) {
      for (int i = 0; i < ele - 3; i++) {
	char* p = args->Element(i);
	if (debug > 0) {
	  fprintf(stderr, "(%d:'%s') ", i, p);
	}
  	if (*p == '\0') {
  	  args->RemoveAt(i);
  	  i--;
  	  ele--;
	  if (debug > 0) {
	    fprintf(stderr, ":deleted ");
	  }
  	}
      }
      x = strtod(args->Element(ele - 3), NULL);
      y = strtod(args->Element(ele - 2), NULL);
      level = atol(args->Element(ele - 1));
      pparent = NULL;
      for (int i = 0; i < ele - 3; i++) {
	strcpy((char*)name, args->Element(i));
	if (last.Elements() > i && (name[0] == '\0' || !strcmp(name, "-") || !strcmp(name, last[i]->_name))) {
	  // １行前と同じデータ系列
	  pparent = last[i];
	} else {
	  long int lv;
	  if (i < ele - 4) {
	    lv = 0;
	  } else {
	    lv = level;
	  }
	  if (name[0] == '\0') {
	    fprintf(stderr, "at readcsv.c, name = NULL (wrong format csv?)\n while reading \"%s\"", buf);
	    abort();
	  }
	    
	  /*
	    if (pparent) {
	    d = new dam(name, pparent->_name, x, y, lv);
	  } else {
	    d = new dam(name, (char*)"", x, y, lv);
	  }
	  */
	  if (i > 0) {
	    d = new dam(name, args->Element(i - 1), x, y, lv);
	  } else {
	    d = new dam(name, (char*)"", x, y, lv);
	  }
	  d->_pparent = pparent;
	  if (pparent) added = pparent->AddChild(d);
	  else added = d;
	  if (last.Elements() > i) {
	    last[i] = added;
	    for (int j = last.Elements() - 1; j > i; j--) {
	      last.RemoveAt(j);
	    }
	  } else {
	    last.Add(added);
	  }
	  if (debug > 0) {
	    fprintf(stderr, "%08d: Add '%s'\n", damsArray.Elements(), d->_name);
	  }
	  pparent = added;
	  if (added == d) {
	    damsArray.Add(d);
	  } else {
	    delete d;
	    d = added;
	  }
	}
      }
      if (debug > 0) {
	fprintf(stderr, "READ %s", buf);
      }
    } else {
      if (debug > 0) {
	fprintf(stderr, "SKIP: %s", buf);
      }
    }
    args->ClearElements();
  }
}

/*
   文字列からセパレータで区切られた属性値を取り出す
   パラメータ stream    属性値が含まれている文字列
              separator 区切り文字
   戻り値     PtrVect<char*>* retval
              retval->Element(0) = "arg0";
	      retval->Element(1) = "arg1";
	      ...
   注意 使用後、retval->ClearElements(); を呼び出すこと
*/
PtrVect<char*>* get_args(char* stream, char separator) {
  static char buf[BUFSIZ];
  char* sp = stream, *dp, *pp;
  char* newarg;
  int len;
  args->ClearElements();
  while (*sp) {
    dp = buf;
    pp = sp;
    while(*sp && *sp != separator) {
      int kanjitype = _isKanji(sp);
      switch (kanjitype) {
      case 0:
	if (!isspace(*sp)) {
	  *dp = *sp;
	  sp++;
	  dp++;
	}
	break;
      case 1:
      case 2:
      case 4:
      case 5:
	*dp = *sp;
	dp++; sp++;
	*dp = *sp;
	dp++; sp++;
	break;
      default:
	sp++;
      }
    }
    len = dp - buf;
    newarg = new char[len + 1]; // +1 for EOS
    memcpy(newarg, buf, len);
    newarg[len] = '\0';
    args->Add(newarg);
    if (*sp == separator) sp++; // セパレータをスキップ
  }
  return args;
}
