/* writebin.c */
#include "headers.h"

static void conv_try_damp_to_long(PtrTry* node, PtrVect<long>& table);
long base = 0;

// バイナリデータの出力
void write_to_binary(char* lpdatafilename, char* lptryfilename) {
  dam* d, *tmpd;
  void* pbase;
  char bufname[MAXSTRLEN];
  char bufkey[MAXSTRLEN];
  char bufparent[MAXSTRLEN];
  int count = damsArray.Elements();
  int wrote, i, j;
  long pos;
  PtrVect<long> fposlist(count);

  // pass 1
  // データファイルの書き込み位置計算
  pos = 0L;
  for (i = 0; i < count; i++) {
    // インデックス作成
    fposlist.Add(pos);
    d = damsArray[i];
    d->_id = i;
    pos += sizeof(dam);
    pos += strlen(d->_name) + strlen(d->_parent);
    if (d->_key) pos += strlen(d->_key);
    if (d->_pchildren) {
      pos += sizeof(long) * (d->_pchildren->Elements());
    }
  }

  // pass 2
  // データファイルの書き込み
  FILE* ofpdat;
  tmpd = new dam();
  ofpdat = fopen(lpdatafilename, "w+");
  for (i = 0; i < count; i++) {
    d = damsArray[i];
    memcpy(tmpd, d, sizeof(dam));
    memcpy(bufname, d->_name, strlen(d->_name));
    tmpd->_namelen = strlen(d->_name);
    if (d->_key) {
      memcpy(bufkey, d->_key, strlen(d->_key));
      tmpd->_keylen = strlen(d->_key);
    } else {
      tmpd->_keylen = 0;
    }
    memcpy(bufparent, d->_parent, strlen(d->_parent));
    tmpd->_parentlen = strlen(d->_parent);
    // 親へのリンクをファイル位置に変更
    if (d->_pparent) {
      tmpd->_posparent = fposlist[(d->_pparent->_id)];
    } else {
      tmpd->_posparent = -1; // 親が存在しない場合-1
    }
    // 子へのリンクをファイル位置リストに置換
    if (!(d->_pchildren)) {
      tmpd->_numchildren = 0;
    } else {
      tmpd->_numchildren = d->_pchildren->Elements();
    }
    /*    wrote = fwrite(tmpd, sizeof(dam), 1, ofpdat);*/
    wrote = fwrite(tmpd, sizeof(dam), 1, ofpdat);
    assert(wrote == 1);
    wrote = fwrite(bufname, sizeof(char), tmpd->_namelen, ofpdat);
    assert(wrote == tmpd->_namelen);
    wrote = fwrite(bufkey, sizeof(char), tmpd->_keylen, ofpdat);
    assert(wrote == tmpd->_keylen);
    wrote = fwrite(bufparent, sizeof(char), tmpd->_parentlen, ofpdat);
    assert(wrote == tmpd->_parentlen);
    for (j = 0; j < tmpd->_numchildren; j++) {
      fwrite(&fposlist[d->_pchildren->Element(j)->_id], sizeof(long), 1, ofpdat);
    }
  }
  fclose(ofpdat);

  // pass 3
  // トライの保存
  conv_try_damp_to_long(&damsTryName, fposlist);
  StaticPtrTry* sttry = new StaticPtrTry(&damsTryName);

  unlink(lptryfilename);
  int fildes = open(lptryfilename, O_RDWR | O_CREAT, 0666);
  unsigned long len = sttry->packedSize();
  char buf[256];
  for (int i = 0; i < len / 256; i++) write(fildes, buf, 256);
  write(fildes, buf, len % 256);
  pbase = mmap((caddr_t)0, len, (PROT_READ | PROT_WRITE), MAP_SHARED, fildes, 0);
  base = (long)pbase;
  fprintf(stderr, "pbase = %p, base = %l(%p)\n", pbase, base, base);
  sttry->pack(0, base);
  delete sttry;

  fposlist.Clear();
  tmpd->_name = NULL;
  tmpd->_key = NULL;
  tmpd->_parent = NULL;
  tmpd->_pparent = NULL;
  tmpd->_pchildren = NULL;
  delete tmpd;
}

// トライの _list 要素を(dam*)から対応するファイルポジションへ変更
void conv_try_damp_to_long(PtrTry* node, PtrVect<long>& table) {
  int i, nlist, nchildren;
  dam* dp;
  if (node->_list) nlist = node->_list->Elements(); else nlist = 0;
  if (node->_next) nchildren = node->_next->Elements(); else nchildren = 0;

  for (i = 0; i < nlist; i++) {
    dp = (dam*)(node->_list->Element(i));
    node->_list->Element(i) = (void*)(table.Element(dp->_id));
  }
  for (i = 0; i < nchildren; i++) {
    conv_try_damp_to_long(node->_next->Element(i), table);
  }
  return;
}
