/* lmatch.c */
#include "headers.h"

static int _getmatchnode(const char* keystring, dam* od, PtrVect<dam*>& res);

const char c_hihun[] = "−";

// 最大一致アドレスを検索する
int get_longestmatch(const char* keystring, PtrVect<dam*>& result) {
  PtrVect<void*> longer;
  int i, j, elements, keylen = strlen(keystring);
  result.Clear();
  int maxmatchlen = 0, score = 0, kansuji_idx;
  char buf[BUFSIZ];

  PtrTry* curTry = &damsTryName;
  PtrVect<void*>* matches;
  for (i = 0; i < keylen; i++) {
    char c = *(keystring + i);
    if (!curTry->_next) {
      // 文字列終端
      break;
    }
    matches = NULL;
    elements = curTry->_next->Elements();
    for (j = 0; j < elements; j++) {
      if (curTry->_next->Element(j)->_letter == c) {
	curTry = curTry->_next->Element(j);
	break;
      }
    }
    if (j == elements) {
      // 一致する文字がもうない
      if (c != c_hihun[0] || *(keystring + i + 1) != c_hihun[1]) break;
      i++;
      curTry->Find("", longer, MATCH_LONGER);
      elements = longer.Elements();
      for (j = 0; j < elements; j++) {
	dam* d = (dam*)(longer[j]);
	char* dp = d->_name;
	if (*dp == -93 && (*(dp + 1) >= -80 && *(dp + 1) <= -71)) {
	  longer.RemoveAt(j);
	  j--;
	}
      }
      while (curTry->_next) {
	curTry = curTry->_next->Element(0);
      }
      matches = &longer;
    } else if (curTry->_list) {
      matches = curTry->_list;
    }
    if (matches) {
      // この文字で終わるデータがある
      elements = matches->Elements();
      for (j = 0; j < elements; j++) {
	dam* d = (dam*)(matches->Element(j));
	if (i > maxmatchlen) {
	  result.Clear();
	  result.Add(d);
	  maxmatchlen = i;
	  score = 2;
	} else if (i == maxmatchlen) {
	  if (result.Find(d) < 0) result.Add(d);
	  score = 2;
	}
	int len;
	PtrVect<dam*> res;
	len = i + _getmatchnode(keystring + i + 1, d, res);
	if (len > maxmatchlen) {
	  score = 0;
	  maxmatchlen = len;
	  result.Clear();
	  for (int k = 0; k < res.Elements(); k++) {
	    d = res[k];
	    result.Add(d);
	    if (d->_name[0] != keystring[0]) score = 4;
	  }
	  if (score < 4) {
	    score = 2;
	  }
	} else if (len == maxmatchlen) {
	  for (int k = 0; k < res.Elements(); k++) {
	    d = res[k];
	    if (result.Find(d) < 0) {
	      result.Add(d);
	      if (d->_name[0] != keystring[0]) score = 4;
	    }
	  }
	  if (score < 4) {
	    score = 2;
	  }
	}
      }
    }
  }

  if (score >= 4 || (score == 2 && curTry->_list)) {
    if (result.Elements() == 1) score++;
    return score;
  }
  // 部分一致を探す
  PtrVect<void*> find;
  memcpy(buf, keystring, i);
  buf[i] = '\0';
  damsTryName.Find(buf, find, MATCH_LONGER);
  elements = find.Elements();
  if (elements == 0) return score;
  result.Clear();
  for (j = 0; j < elements; j++) {
    result.Add((dam*)(find[j]));
  }
  return 1;
}

// 指定した dam エレメントから子ノードを辿り、
// 文字列に最大一致するデータのリストを探す
int _getmatchnode(const char* keystring, dam* od, PtrVect<dam*>& res) {
  PtrVect<dam*> curmatch;
  dam* d, *el;
  const char *sp;
  char *standard, *dp;
  int i, count, from, n, a, h, c;
  int maxlen = 0;
  int hasexactmatch = 0;
  static char buf[BUFSIZ], query[BUFSIZ];

  if (!od->_pchildren || *keystring == '\0') return 0;
  count = od->_pchildren->Elements();
  //  for (i = 0; i < count; i++)
  //    fprintf(stderr, "%04d: '%s'\n", i, od->_pchildren->Element(i)->key());
  /* 先頭の１文字が一致する子ノードからスタート */
  {
    standard = standardize(keystring);
    strcpy(query, standard);
    if (_isKanji(query)) {
      buf[0] = *query;
      buf[1] = *(query + 1);
      buf[2] = '\0';
    } else {
      buf[0] = *query;
      buf[1] = '\0';
    }
    a = 0;
    n = count;
    for (;;) {
      if (n == a) {
	from = n;
	break;
      }
      h = a + (n - a) / 2;
      el = od->_pchildren->Element(h);
      //      fprintf(stderr, "in _getmatchnode('%s'): comparing with %04d:'%s'\n", keystring, h, el->key());
      c = strcmp(buf, el->key());
      if (c < 0) {
	n = h;
      } else if (c > 0) {
	if (a == h) {
	  if (a < n) a ++;
	  else break;
	} else {
	  a = h;
	}
      } else { /* c == 0 */
	from = h;
	break;
      }
    }
  }
  /* ハイフンの前までの確定文字列を取得 */
  for (sp = query, dp = buf; *sp;) {
    if (_isHihun(sp) >= 0) break;
    if (_isKanji(sp)) {
      *dp = *sp;
      dp++;
      sp++;
      *dp = *sp;
      dp++;
      sp++;
    } else {
      *dp = *sp;
      dp++;
      sp++;
    }
  }
  *dp = '\0';
  
  for (i = from; i < count; i++) {
    d = od->_pchildren->Element(i);
    if (debug) fprintf(stderr, "Comparing %d:'%s' and '%s'\n", i, d->key(), query);
    if (strncmp(buf, d->key(), strlen(buf)) < 0) {
      if (debug) fprintf(stderr, "  '%s' is larger than '%s', break.\n", d->key(), buf);
      break;
    }
    curmatch.Clear();
    curmatch.Add(d);
    int len = 0;
    for (sp = query, dp = d->key(); *sp != '\0';) {
      if ('0' <= *sp && *sp < '9') {
	int b0, b1;
	b0 = b1 = 0;
	if (getNumber(sp, b0) == getNumber(dp, b1)) {
	  len += b0;
	  sp += b0;
	  dp += b0;
	  continue;
	} else {
	  break;
	}
      }
      if (*sp == *dp) {
	len++;
	sp++;
	dp++;
	continue;
      }
      int hihuntype = _isHihun(sp);
      if (hihuntype >= 0) {
	// 住所表記が'−'(ハイフン)で省略されている場合
	if (hihuntype == 99) { /* '-' */
	  sp++;
	  len++;
	} else {
	  sp += 2;
	  len += 2;
	}
	while (*dp) {
	  if ('0' <= *dp && *dp < '9') {
	    // 数字はハイフンでは省略できない (0xa3b0 = '０')
	    break;
	  } else {
	    dp++;
	  }
	}
      }
      break;
    }
    if (*dp == '\0' && *sp != '\0') {
      len = len + _getmatchnode(sp, d, curmatch);
    }
    if (len > maxlen) {
      maxlen = len;
      res.Clear();
      for (int j = 0; j < curmatch.Elements(); j++) {
	res.Add(curmatch[j]);
      }
      if (*dp == '\0') hasexactmatch = 1;
      else hasexactmatch = 0;
    } else if (len > 0 && len == maxlen) {
      if (*dp == '\0' || hasexactmatch == 0) {
	for (int j = 0; j < curmatch.Elements(); j++) {
	  dam* d = curmatch[j];
	  if (res.Find(d) < 0) res.Add(d);
	}
	if (*dp == '\0') hasexactmatch = 1;
      }
    }
  }
  return maxlen;
}
