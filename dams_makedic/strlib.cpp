/* strlib.c */
/* 全角数字や漢数字の処理などを行う関数群 */
#include <stdio.h>
#include <string.h>
#include "strlib.h"

const char* hihun[] = {"−", "‐", "ー", "・"};
const char* kansuji[] = {"〇", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
const char* arabic = {"０１２３４５６７８９−"};

unsigned short int hexval(const char* str) {
  int h, l;
  l = (int)(unsigned char)(str[0]);
  h = (int)(unsigned char)(str[1]);
  return (unsigned short int)(h << 8 | l);
}

void set_hexval(char* buf, unsigned short int val) {
  int h, l;
  h = (val & 0xff00) >> 8;
  l = val & 0xff;
  buf[0] = l;
  buf[1] = h;
  /*  buf[2] = '\0'; */
}

int _isHihun(const char* string) {
  if (*string == '-') return 99;
  for (int i = 0; i < 3; i++) {
    if (*string == hihun[i][0] && *(string + 1) == hihun[i][1]) {
      return i;
    }
  }
#if 0
  if (!strncmp(string, "ノ", 2) // の, 乃 が異体字で変換されている可能性あり
      && (_isNumeric(string + 2) >= 0)) { // || _isKanji(string + 2) == 5)) {
    /* 'ノ’の後に数字 */ /* またはカタカナの場合ハイフンと見なす */
    return 4;
  }
#endif /* 0 */
  return -1;
}

int _isKansuji(const char* string) {
  for (int i = 0; i < 10; i++) {
    if (*string == kansuji[i][0] && *(string + 1) == kansuji[i][1]) {
      return i;
    }
  }
  return -1;
}

int _isArabsuji(const char* string) {
  for (int i = 0; i < 10; i++) {
    if (*string == *(arabic + i * 2) && *(string + 1) == *(arabic + i * 2 + 1)) {
      return i;
    }
  }
  return -1;
}

int _isNumeric(const char* string) {
  int res;
  if ('0' <= *string && *string <= '9') return *string - '0';
  res = _isArabsuji(string);
  if (res >= 0) return res;
  res = _isKansuji(string);
  if (res >= 0) return res;
  if (!strncmp(string, "十", 2)) return 10;
  else if (!strncmp(string, "百", 2)) return 100;
  else if (!strncmp(string, "千", 2)) return 1000;
#ifdef DEFINE_MAN
  else if (!strncmp(string, "万", 2)) return 10000;
#endif /* DEFINE_MAN */
  return -1;
}
 
/* 漢字判定 */
/* 0->ascii, 1->漢字, 2->半角かな, 3->補助漢字, 4->ひらがな, 5->カタカナ */
/* -1 の場合 EUC コードの外 */
int _isKanji(const char* string) {
  int c0, c1, c2;
  c0 = (*string) & 0xff;
  if (0x21 <= c0 && c0 <= 0x7e) return 0;  /* ASCII */
  c1 = (*(string + 1)) & 0xff;
  if (0x8e == c0 && 0xa0 <= c1 && c1 <= 0xff) return 2; /* 半角カナ */
  if ((0x8e == c0 && 0xa1 <= c1 && c1 <= 0xdf) || (0xa4 == c0 && 0xa1 <= c1 && c1 <= 0xf3)) return 4; /* 全角ひらがな */
  if ((0x8f == c0 && 0xa1 <= c1 && c1 <= 0xfe) || (0xa5 == c0 && 0xa1 <= c1 && c1 <= 0xf6)) return 5; /* 全角カタカナ */
  if ((0xa0 <= c0 && c0 <= 0xff) && (0xa0 <= c1 && c1 <= 0xff)) return 1; /* 新JIS */
  c2 = (*(string + 2)) & 0xff;
  if (c0 == 0x8f && 0xa0 <= c1 && c1 <= 0xff && 0xa0 <= c2 && c2 <= 0xff) return 3; /* 補助漢字 */
  /* if (*string < 0 && *(string + 1) < 0) return 1; */
  return -1; /* not EUC */
}

int _getWcharIndex(const char* string, int pos) {
  int wpos, ppos;
  ppos = 0;
  for (wpos = 0; wpos < pos;) {
    ppos = wpos;
    if (_isKanji(string + wpos)) wpos += 2;
    else wpos++;
  }
  if (wpos > pos) return ppos;
  return wpos;
}

const char* indexof(const char* key, const char* string) {
  const char* cp, *sp;
  sp = key;
  for (cp = string; *cp; cp++) {
    if (*cp != *sp) {
      sp = key;
      continue;
    }
    sp++;
    if (!*sp) {
      return cp - strlen(string);
    }
  }
  return NULL;
}

int getNumber(const char* string, int& bytes) {
  int total, curval, expect;
  int i, k, mode;
  char *p = (char*) string;

  mode = -1; /* -1: 未定, 0:アラビア数字（全半角）, 1:漢数字 */
  total = 0;
  curval = 0;
  expect = bytes;
  bytes = 0;
  
  while (*p != '\0') {
    if (*p >= '0' && *p <= '9' && mode != 1) {
      curval = curval * 10 + (*p - '0');
      mode = 0;
    } else if ((k = _isArabsuji(p)) >= 0 && mode != 1) {
      //      if (total + curval == 0 && k == 0) break;
      curval = curval * 10 + k;
      p++; bytes++;
      mode = 0;
    } else if (mode == 0) {
      break;
    } else if ((k = _isKansuji(p)) >= 0) {
      if (total + curval == 0 && k == 0) break;
      curval = curval * 10 + k;
      p++; bytes++;
      mode = 1;
    } else if (!strncmp(p, "十", 2)) {
      if (curval == 0) curval = 1;
      total = total + curval * 10;
      curval = 0;
      p++; bytes++;
      mode = 1;
    } else if (!strncmp(p, "百", 2)) {
      if (curval == 0) curval = 1;
      if (total % 100 > 0) total *= 100;
      total = total + curval * 100;
      curval = 0;
      p++; bytes++;
      mode = 1;
    } else if (!strncmp(p, "千", 2)) {
      if (curval == 0) curval = 1;
      if (total % 1000 > 0) total *= 1000;
      total = total + curval * 1000;
      curval = 0;
      p++; bytes++;
      mode = 1;
    }
#ifdef DEFINE_MAN
     else if (!strncmp(p, "万", 2)) {
      if (curval == 0) curval = 1;
      if (total % 10000 > 0) total *= 10000;
      total = total + curval * 10000;
      curval = 0;
      p++; bytes++;
      mode = 1;
    }
#endif /* DEFINE_MAN */
    else {
      break; /* not numeric character */
    }
    p++;
    bytes++;
    if (total + curval == expect) {
      return expect;
    }
  }
  total = total + curval;
  return total;
}

/* 全角まじり文字列の文字数制限付きコピー */
int kstrncpy(char* dst, const char* src, int max) {
  int j, len, done;

  len = 0;
  j = 0;
  done = 0;
  if (src) {
    while (*(src + len) && (done == 0)) {
      switch(_isKanji(src + len)) {
      case 1:
      case 2:
      case 4:
      case 5:
	j = 2;
	break;
      case 3: /* 補助漢字 = 3bytes */
	j = 3;
	break;
      case 0: /* ASCII = 1 byte */
	j = 1;
	break;
      default:
	j = 1;
	break;
      }
      if (j + len <= max) {
	len += j;
      } else {
	done = 1;
	break;
      }
    }
  }
  if (len > 0) memcpy(dst, src, len);
  dst[len] = '\0';
  return len;
}
