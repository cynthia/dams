/* lmatch.c */
#include "libdams.h"
#include "strlib.h"
#include <iostream>
#include <dams.h>

#include "MatchNodeResult.h"

static MatchNodeResult _getmatchnode(const char* keystring, long od, const ObjVect<long>& parent_res, int exactmatch);

// 最大一致アドレスを検索する
MatchNodeResult get_longestmatch(const char* keystring) {
  int i, j, elements, keylen = strlen(keystring);
  MatchNodeResult result;
  char buf[BUFSIZ], c0[3], c1[3];
  
  //  score = 0;
  c0[2] = c1[2] = '\0';
  StaticPtrTry* curTry = damsTry;
  StaticPtrTry* preTry = NULL;
  ObjVect<long> matches;
  ObjVect<long> longer;
  
  // 先頭がハイフンの場合、何もしないで返す
  if (_isHihun(keystring) >= 0) {
    result.rest = std::string(keystring);
    return result;
  }
  
  // 最長一致検索
  for (i = 0; i < keylen; i++) {
    char c = *(keystring + i);
    if (!curTry->_nNext) {
      // 文字列終端
      break;
    }
    matches.Clear();
    elements = curTry->_nNext;
    for (j = 0; j < elements; j++) {
      if (curTry->next(j, base)->_letter == c) {
	preTry = curTry;
	curTry = curTry->next(j, base);
	break;
      }
    }
    if (j == elements) {
      // 一致する文字がもうないので、例外的な文字を調査する
      //      int wpos = _getWcharIndex(keystring, i);
      //      if (wpos != i) curTry = preTry;

      // ハイフンの処理
      if (_isHihun(keystring + i) < 0) break;
      curTry->Find("", longer, MATCH_LONGER, base);
      elements = longer.Elements();
      for (j = 0; j < elements; j++) {
	long d = longer[j];
	dam* tmpd;
	tmpd = read_from_file(f_data, d);
	if (debug) {
	  fprintf(stderr, "DEBUG: tmpd = (%s/%s)\n", damswrapper::euc_to_utf8(tmpd->_name).c_str(), damswrapper::euc_to_utf8(tmpd->_parent).c_str());
	}
	const char* dp = tmpd->key();
	if ('0' <= *dp && *dp <= '9') {
	  longer.RemoveAt(j);
	  j--;
	  elements--;
	}
	delete tmpd;
      }
      while (curTry->_nNext) {
	curTry = curTry->next(0, base);
      }
      matches = longer;
    } else if (curTry->_nList) {
      curTry->copy(matches, base);
    }
    if (matches.Elements() > 0) {
      // この文字で終わるデータがある
      elements = matches.Elements();
      for (j = 0; j < elements; j++) {
	if (debug) fprintf(stderr, "Processing %d/%d.\n", j, elements);
	long d = matches.Element(j);
	tmpvect.Add(d);
	if (i + 1 > result.maxlen) {
	  result.res.Clear();
	  result.res.Add(d);
	  result.maxlen = i + 1;
	  result.score = 2;
	  if (debug) fprintf(stderr, "DEBUG: partial match %d characters, 2 points\n", i + 1);
	} else if (i + 1 == result.maxlen) {
	  int k;
	  for (k = 0; k < result.res.Elements(); k++) {
	    if (result.res[k] == d) break;
	  }
	  if (k == result.res.Elements()) result.res.Add(d);
	  if (debug) fprintf(stderr, "DEBUG: partial match %d characters, 2 points\n", i + 1);
	  result.score = 2;
	}
	// 子ノード中から最長一致するものを検索
	int len, exactmatch, wi;
	//ObjVect<long> res;
	MatchNodeResult node_result;
	wi = _getWcharIndex(keystring, i + 1);
	if (wi == i) wi += 2; // 次の文字が漢字の場合、１文字分進める
	//matchnodelen = _getmatchnode(keystring + wi, d, res, exactmatch);
	node_result = _getmatchnode(keystring + wi, d, result.res, exactmatch);
	if (debug) fprintf(stderr, "_getmatchnode(\"%s\", %ld) returns maxlen:%d, rest:'%s'\n", damswrapper::euc_to_utf8(keystring + wi).c_str(), d, node_result.maxlen, damswrapper::euc_to_utf8(node_result.rest).c_str());
	len = wi + node_result.maxlen;
	if (len > result.maxlen) {
	  result.score = 0;
	  result.res.Clear();
	  for (int k = 0; k < node_result.res.Elements(); k++) {
	    d = node_result.res[k];
	    result.res.Add(d);
	    dam* tmpd;
	    tmpd = read_from_file(f_data, d);
	    if (node_result.maxlen > 0) { //*(tmpd->key()) != *keystring) {
	      result.score = 4;
	      if (debug) fprintf(stderr, "DEBUG: case1: %d > %d: %s and %s make 4 points, exactmatch = %d, rest = '%s'\n", len, result.maxlen, damswrapper::euc_to_utf8(tmpd->key()).c_str(), damswrapper::euc_to_utf8(keystring).c_str(), exactmatch, damswrapper::euc_to_utf8(node_result.rest).c_str());
	    }
	    delete tmpd;
	  }
	  result.maxlen = len;
	  result.rest = node_result.rest;
	  if (result.score < 4) {
	    result.score = 2;
	  }
	} else if (len == result.maxlen) {
	  for (int k = 0; k < node_result.res.Elements(); k++) {
	    d = node_result.res[k];
	    int l;
	    for (l = 0; l < result.res.Elements(); l++) {
	      if (result.res[l] == d) break;
	    }
	    if (l == result.res.Elements()) {
	      result.res.Add(d);
	      dam* tmpd;
	      tmpd = read_from_file(f_data, d);
	      if (node_result.maxlen > 0) { //*(tmpd->key()) != *keystring) {
		result.score = 4;
		if (debug) fprintf(stderr, "DEBUG: case2: %d = %d: %s and %s make 4 points, exactmatch = %d\n", len, result.maxlen, damswrapper::euc_to_utf8(tmpd->key()).c_str(), damswrapper::euc_to_utf8(keystring).c_str(), exactmatch);
	      }
	      delete tmpd;
	    }
	  }
	  if (result.score < 4) {
	    result.score = 2;
	  }
	}
      }
    }
  }
  if (debug) fprintf(stderr, "DEBUG: result: %d points\n", result.score);
  if (result.score >= 4 || (result.score == 2 && curTry->_nList > 0)) {
    if (result.res.Elements() == 1) result.score++;
#if 0
    if (*(keystring + result.maxlen - 1) == '\0') {
      result.rest = std::string("");
    } else {
      int wi;
      wi = _getWcharIndex(keystring, result.maxlen); // 全角を考慮し、変換した文字数を取得
      if (debug) fprintf(stderr, "_tail was set to '%s'\n", _tail);
      strcpy(_tail, keystring + wi);
      if (debug) fprintf(stderr, "_tail set to '%s'\n", _tail);
    }
#endif
    return result;
  }
  // 部分一致を探す
  ObjVect<long> find;
  int wi;
  wi = _getWcharIndex(keystring, result.maxlen); // 全角を考慮し、変換した文字数を取得
  if (wi == 0) { // 全角の先頭1バイトしか一致していない場合は無効
    result.maxlen = 0;
    result.rest = std::string("");
    result.res.Clear();
    result.score = 0;
    return result;
  }
  memcpy(buf, keystring, wi);
  buf[wi] = '\0';
  //  result.maxlen = damsTry->Find(buf, find, MATCH_LONGER, base);
  result.maxlen = damsTry->Find(buf, find, MATCH_EXACT, base);
  result.rest = std::string(keystring + result.maxlen);
  result.res.Clear();
  elements = find.Elements();
  if (elements == 0) return result;
  for (j = 0; j < elements; j++) {
    result.res.Add(find[j]);
  }
  if (elements == 1) result.score = 3;
  else result.score = 2;
  return result;
}

// 指定した dam エレメントから子ノードを辿り、
// 文字列に最大一致するデータのリストを探す
MatchNodeResult _getmatchnode(const char* keystring, long pl, const ObjVect<long>& parent_res, int exactmatch) {
  dam* od, *el;
  const char* sp;
  char* dp, *standard;
  long d, fpos, d_exactmatch;
  int i, count, from, hihuntype, a, n, c, h;
  int maxlen, hasexactmatch, fullmatch;
  char buf[BUFSIZ], query[BUFSIZ];
  MatchNodeResult result;

  hasexactmatch = 0;

  if (debug) {
    fprintf(stderr, "DEBUG: Entering _getmatchnode(%s,%ld,%d)\n", damswrapper::euc_to_utf8(keystring).c_str(), pl, exactmatch);
  }

  result.res = parent_res;

  while (*keystring == '-') keystring++;
  if (*keystring == '\0') return result;
  od = read_from_file(f_data, pl);
  if (!od->_pchildren) {
    delete od;
    return result;
  }
  count = od->_pchildren->Elements();

  /* 先頭の１文字が一致する子ノードからスタート */
  {
    standard = standardize(keystring);
    strcpy(query, standard);
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
      break;
    }
    *dp = '\0';
    if (dp == buf) {
      // 先頭がハイフンの場合の処理
      delete od;
      return result;
    }
    /* buf <= 簡約化された検索文字列ハイフンの前まで */
    /* バイナリサーチ */
    a = 0;
    n = count;
    for (;;) { /* 先に範囲チェック */
      fpos = od->_pchildren->Element(0);
      el = read_from_file(f_data, fpos);
      if (debug) {
	fprintf(stderr, "%d: %s, comparing with '%s'\n", 0, damswrapper::euc_to_utf8(el->key()).c_str(), damswrapper::euc_to_utf8(buf).c_str());
      }
      c = strncmp(buf, el->key(), strlen(buf));
      delete el;
      if (c < 0) { /* 範囲外：リストの先頭よりも前 */
	if (debug) fprintf(stderr, "Skip since the retrieval key is smaller than the first element of the list.\n");
	delete od;
	result.maxlen = 0;
	result.rest = std::string(query);
	return result;
      }	else if (c == 0) { /* リストの先頭と一致 */
	a = 0;
	n = 1;
	break;
      }
      fpos = od->_pchildren->Element(count - 1);
      el = read_from_file(f_data, fpos);
      if (debug) {
	fprintf(stderr, "%d: %s\n", count - 1, damswrapper::euc_to_utf8(el->key()).c_str());
      }
      c = strncmp(buf, el->key(), strlen(el->key()));
      delete el;
      if (c > 0) { /* 範囲外：リストの最後よりも後 */
	if (debug) fprintf(stderr, "Skip since the retrieval key is larger than the last element of the list.\n");
	delete od;
	result.maxlen = 0;
	result.rest = std::string(query);
	return result;
      } else if (c == 0) { /* リストの最後と一致 */
	a = count - 1;
	n = count;
      }
      break;
    }
    for (;;) {
      if (n == a) {
	from = n;
	break;
      }
      h = a + (n - a) / 2;
      fpos = od->_pchildren->Element(h);
      el = read_from_file(f_data, fpos);
      if (debug) {
	fprintf(stderr, "%d: %s <-> %s :", h, damswrapper::euc_to_utf8(el->key()).c_str(), buf);
      }
      c = strncmp(buf, el->key(), strlen(el->key()));
      if (debug) {
	fprintf(stderr, "%d\n", c);
      }
      delete el;
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
  /* 残りを総当たり */
  ObjVect<long> curmatch;
  for (i = from; i < count; i++) {
    dam* tmpd;
    d = od->_pchildren->Element(i);
    tmpd = read_from_file(f_data, d);
    if (debug) fprintf(stderr, "Comparing %d:'%s' and '%s'\n", i, damswrapper::euc_to_utf8(tmpd->key()).c_str(), damswrapper::euc_to_utf8(query).c_str());

    tmpvect.Add(d);
    curmatch.Clear();
    curmatch.Add(d);
    int len = 0;
    const char* sp, * dp, * wp, * dwp;
    if (debug) fprintf(stderr, "DEBUG: Comparing %s and %s.\n", damswrapper::euc_to_utf8(tmpd->key()).c_str(), damswrapper::euc_to_utf8(query).c_str());
    for (sp = query, dp = tmpd->key(); *sp != '\0' && *dp != '\0';) {
      if ('0' <= *sp && *sp <= '9') {
	int b0, b1;
	b0 = b1 = 0;
	if (getNumber(sp, b0) == getNumber(dp, b1)) {
	  b0++; /* 数値の後の'.'の分を増やす */
	  len += b0;
	  sp += b0;
	  dp += b0;
	  continue;
	} else {
	  break;
	}
      }
      switch (_isKanji(sp)) {
      case 1:
      case 2:
      case 4:
      case 5:
	if (*sp == *dp && *(sp + 1) == *(dp + 1)) {
	  len += 2;
	  sp += 2;
	  dp += 2;
	  continue;
	}
	break;
      case 3:
	if (*sp == *dp && *(sp + 1) == *(dp + 1) && *(sp + 2) == *(dp + 2)) {
	  len += 3;
	  sp += 3;
	  dp += 3;
	  continue;
	}
	break;
      default:
	if (*sp == *dp) {
	  len++;
	  sp++;
	  dp++;
	  continue;
	}
	break;
      }
	  
      hihuntype = _isHihun(sp);
      if (hihuntype >= 0) {
	// 住所表記が'−'(ハイフン)で省略されている場合の処理
	int bytes, wait_digits, expect, val;
	if (hihuntype == 99) { /* '-' */
	  sp++;
	} else {
	  sp += 2;
	}
	// ハイフンの後に現れる値をチェック
	bytes = -1;
	expect = getNumber(sp, bytes);
	if (bytes == 0) { // 数値以外の文字が来る場合
	  wait_digits = 0;
	  if (_isKanji(sp)) expect = hexval(sp);
	  else expect = *sp;
	} else { // 数値が来る場合
	  wait_digits = 1;
	}
	// 期待される文字または値が現れるまでスキップ
	while (*dp) {
	  if (wait_digits == 1) { // 値待ち
	    bytes = expect;
	    val = getNumber(dp, bytes);
	    if (bytes > 0) break; // 数値がきた場合
	    if (_isKanji(dp)) {
	      dp += 2;
	    } else {
	      dp++;
	    }
	  } else { // 文字待ち
	    if (_isKanji(dp)) {
	      if (hexval(dp) == expect) break;
	      len += 2;
	      dp += 2;
	    } else {
	      if (*dp == expect) break;
	      len++;
	      dp++;
	    }
	  }
	}
	break;
      }
      break;
    }
    len = sp - query;
    MatchNodeResult node_result;
    std::string cur_rest;
    if (debug) fprintf(stderr, "debug, result.rest = '%s', sp = '%s'\n", damswrapper::euc_to_utf8(result.rest).c_str(), damswrapper::euc_to_utf8(sp).c_str());
    if (*dp == '\0') {
      fullmatch = 1;
      if (*sp != '\0') {
	node_result = _getmatchnode(sp, d, curmatch, exactmatch);
	if (debug) fprintf(stderr, "_getmatchnode(\"%s\", %ld) returns maxlen:%d, rest:'%s'\n", damswrapper::euc_to_utf8(sp).c_str(), d, node_result.maxlen, damswrapper::euc_to_utf8(node_result.rest).c_str());
	if (node_result.maxlen == 0) {
	  exactmatch = 1;
	  cur_rest = std::string(sp);
	} else {
	  exactmatch = 0;
	  len = len + node_result.maxlen;
	  cur_rest = node_result.rest;
	  curmatch = node_result.res;
	}
      } else {
	exactmatch = 1;
	cur_rest = std::string("");
      }
    } else {
      fullmatch = 0;
      exactmatch = 0;
      len = len + node_result.maxlen;
      cur_rest = std::string(sp);
      curmatch = node_result.res;
      curmatch.Add(d);
    }
    if (len > result.maxlen) {
      result.rest = cur_rest;
      result.maxlen = len;
      if (debug) fprintf(stderr, "DEBUG: %s matches %d characters(update),fullmatch=%d,exactmatch=%d,maxlen=%d,rest='%s'\n", damswrapper::euc_to_utf8(tmpd->key()).c_str(), len, fullmatch, exactmatch, result.maxlen, damswrapper::euc_to_utf8(result.rest).c_str());
      if (exactmatch) {
	result.res.Clear();
	d_exactmatch = d;
	hasexactmatch = 1;
	for (int j = 0; j < curmatch.Elements(); j++) {
	  result.res.Add(curmatch[j]);
	}
      } else {
	hasexactmatch = 0;
	if (exact_match_level <= 0 || fullmatch == 1) {
	  result.res.Clear();
	  for (int j = 0; j < curmatch.Elements(); j++) {
	    result.res.Add(curmatch[j]);
	  }
	} else {
	  el = read_from_file(f_data, curmatch[0]);
	  if (debug) fprintf(stderr, "el->_level = %d, exact_match_level = %d\n", el->_level, exact_match_level);
	  if (el->_level > exact_match_level) {
	    result.res.Clear();
	    for (int j = 0; j < curmatch.Elements(); j++) {
	      result.res.Add(curmatch[j]);
	    }
	  } else {
	    result.maxlen = 0;
	    if (debug) fprintf(stderr, "DEBUG: %s is rejected since it matches partially, maxlen = 0\n", damswrapper::euc_to_utf8(tmpd->key()).c_str());
	  }
	  delete el;
	}
      }
    } else if (len > 0 && len == result.maxlen) {
      if (exactmatch == 1) {
	d_exactmatch = d;
	hasexactmatch = 1;
	result.res.Clear();
	for (int j = 0; j < curmatch.Elements(); j++) {
	  result.res.Add(curmatch[j]);
	}
      } else if (hasexactmatch == 0) {
	for (int j = 0; j < curmatch.Elements(); j++) {
	  long d = curmatch[j];
	  int k;
	  for (k = 0; k < result.res.Elements(); k++) {
	    if (result.res[k] == d) break;
	  }
	  if (k == result.res.Elements()) {
	    result.res.Add(d);
	  }
	}
      }
    }
    if (strncmp(buf, tmpd->key(), strlen(buf)) < 0) {
      if (debug) fprintf(stderr, "  '%s' is larger than '%s', break.\n", damswrapper::euc_to_utf8(tmpd->key()).c_str(), buf);
      delete tmpd;
      break;
    }
    delete tmpd;
  }
  delete od;

  if (debug) fprintf(stderr, "return maxlen:%d, rest:'%s'\n", result.maxlen, damswrapper::euc_to_utf8(result.rest).c_str());
  return result;
}

#if 0
/* 変換できなかった残りの文字列 */
const char* tail(void) {
  return (const char*)_tail;
}
#endif

/* 変換できたバイト数をカウントする */
int nconverted(const char* keystring, const char* tail) {
  int i, len;
  const char *sp, *match, *standard, *candidate;
  char *standardbuf, *tailbuf;

  len = strlen(tail);
  if (len == 0) return strlen(keystring);
  /* if (len < 0 || len > strlen(keystring)) return 0; */
  standardbuf = (char*)malloc(len + 1);
  memcpy(standardbuf, tail, len + 1);
  sp = standardize(standardbuf);
  tailbuf = (char*)malloc(strlen(sp) + 1);
  strcpy(tailbuf, sp);
  free(standardbuf);
  len = strlen(tailbuf);
#ifdef DEBUG
  fprintf(stderr, "pass2: current tail = '%s', standardized tail = '%s(%d)'\n", tail, tailbuf, len);
#endif

  match = NULL;
  for (i = 0, sp = keystring; *sp && i < 40; i++) {
    standard = standardize(sp);
    trimming((char*)standard);
#ifdef DEBUG
    fprintf(stderr, "sp = %p, checking: '%s'=>'%s'(%d), tail:'%s'\n", sp, sp, standard, strlen(standard), tailbuf);
#endif
    
    if (strlen(standard) <= len) {
      if (!strcmp(standard, tailbuf)) {
	/* 一致 */
#ifdef DEBUG
	fprintf(stderr, "  -> match\n");
#endif
	match = sp;
      } else {
#ifdef DEBUG
	fprintf(stderr, "  -> not match\n");
#endif
	if (match) break;
      }
    }
    switch (_isKanji(sp)) {
    case 0:
#ifdef DEBUG
      fprintf(stderr, "0:(%c)\n", *sp);
#endif
      sp ++;
      break;
    case 3:
#ifdef DEBUG
      fprintf(stderr, "3:(xxx)\n");
#endif
      sp += 3;
      break;
    case -1:
#ifdef DEBUG
      fprintf(stderr, "?:(%c)\n", *sp);
#endif
      sp++;
      break;
    default:
#ifdef DEBUG
      fprintf(stderr, "%d:(%s)\n", _isKanji(sp), sp);
#endif
      sp += 2;
      break;
    }
  }
  free(tailbuf);
  return match - keystring;
}

/* 検索文字列から空白の除去とカンマの置換 */
/* 破壊的 */
char* trimming(char* standard) {
  int len;
  char *cp;
  char buf[3];

  len = strlen(standard);
  for (cp = standard; *cp;) {
    //    fprintf(stderr, "trimming: '%s'", standard);
    switch (_isKanji(cp)) {
    case 0:
      //      fprintf(stderr, "(%c)", *cp);
      if (*cp == ' ' || *cp == '/') {
	//	fprintf(stderr, "0: '%c' found.\n", *cp);
	memmove(cp, cp + 1, len);
	cp--;
	len--;
#if 0
      } else if (*cp == ',') {
	//	fprintf(stderr, "0: '%c' found.\n", *cp);
	cp++;
#endif
      } else {
	//	fprintf(stderr, "0: forward 1 byte.\n");
      }
      cp++;
      break;
    case 3:
      //      fprintf(stderr, "3: forward 3 bytes\n");
      cp += 3;
      break;
    case -1:
      memmove(cp, cp + 1, len);
      len--;
      break;
    default:
      strncpy(buf, cp, 2);
      //      fprintf(stderr, "(%s)", buf);
      /* if (!strncmp(cp, "，", 2)) {
	//	fprintf(stderr, "x: '%s' found.\n", cp);
	memcpy(cp, "−", 2);
	cp += 2;
	} else */
      if (!strncmp(cp, "　", 2)) {
	//	fprintf(stderr, "x: '%s' found.\n", cp);
	memmove(cp, cp + 2, len - 1);
	len -= 2;
      } else {
	//	fprintf(stderr, "x: forward 2 bytes.\n");
	cp += 2;
      }
    }
  }
  /* 検索文字列が数字で終わっている場合の処理 */
  if (*(cp - 1) >= '0' && *(cp - 1) <= '9') {
    *cp = '-';
    cp++;
  }
  *cp = '\0';
  //  fprintf(stderr, "'%s'\n", standard);
  return standard;
}
