/* dam.c */
#include <strings.h>
#include <stdlib.h>
#include <assert.h>
#include <dams.h>
#include "dam.h"

extern int debug;
extern char* standardize(const char*);

/* コンストラクタ */
dam::dam(void)
  :_name(NULL), _key(NULL), _parent(NULL), _x(.0), _y(.0), _level(0),
   _pparent(NULL), _pchildren(NULL)
{
}

dam::dam(char* name, char* parent, float x, float y, long int level)
  :_x(x), _y(y), _level(level), _pparent(NULL), _pchildren(NULL)
{
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
  if (_name) {
    delete[] _name;
    if (_key) delete[] _key;
    delete[] _parent;
    if (_pchildren) {
      _pchildren->Clear();
    }
    delete _pchildren;
  }
}

/* ファイルから読み込み */
dam* read_from_file(FILE* fp, long fpos) {
  static dam tmpdam;
  static char buf[BUFSIZ];
  int bytes;
  dam* newdam = new dam;
  if (debug) fprintf(stderr, "DEBUG: --read_from_file--\nseek to %ld\n", fpos);
  fseek(fp, fpos, SEEK_SET);
  /*  fread(newdam, sizeof(dam), 1, fp); */
  memset(&tmpdam, '\0', sizeof(dam));
  bytes = fread(&tmpdam, sizeof(dam), 1, fp);
  if (debug) fprintf(stderr, "DEBUG: bytes = %d\n", bytes);
  //  assert(bytes == 1);
  *newdam = tmpdam;
  if (debug) fprintf(stderr, "DEBUG: dam %d: posparent = %ld, _numchildren = %d\n", newdam->_id, newdam->_posparent, newdam->_numchildren);
  if (newdam->_posparent == fpos) {
    fputs("ERR: in read_from_file, pointer to parent directs itself\n", stderr);
    abort();
  }
  bytes = fread(buf, sizeof(char), newdam->_namelen, fp);
  assert(bytes == newdam->_namelen);
  buf[newdam->_namelen] = '\0';
  newdam->_name = new char[newdam->_namelen + 1];
  strcpy(newdam->_name, buf);
  if (debug) fprintf(stderr, "DEBUG: dam %d: name = %s\n", newdam->_id, damswrapper::euc_to_utf8(newdam->_name).c_str());
  if (newdam->_keylen) {
    bytes = fread(buf, sizeof(char), newdam->_keylen, fp);
    assert(bytes == newdam->_keylen);
    buf[newdam->_keylen] = '\0';
    newdam->_key = new char[newdam->_keylen + 1];
    strcpy(newdam->_key, buf);
    if (debug) fprintf(stderr, "DEBUG: dam %d: key = %s\n", newdam->_id, damswrapper::euc_to_utf8(newdam->_key).c_str());
  } else {
    newdam->_key = NULL;
    if (debug) fprintf(stderr, "DEBUG: dam %d: key = (null)\n", newdam->_id);
  }
  bytes = fread(buf, sizeof(char), newdam->_parentlen, fp);
  assert(bytes == newdam->_parentlen);
  buf[newdam->_parentlen] = '\0';
  newdam->_parent = new char[newdam->_parentlen + 1];
  strcpy(newdam->_parent, buf);
  if (debug) fprintf(stderr, "DEBUG: dam %d: parent = %s\n", newdam->_id, damswrapper::euc_to_utf8(newdam->_parent).c_str());
  if (newdam->_numchildren > 0) {
    int nc = newdam->_numchildren;
    if (debug) fprintf(stderr, "DEBUG: dam %d: has %d sibling nodes.\n", newdam->_id, nc);
    newdam->_pchildren = new ObjVect<long>(nc);
    for (int i = 0; i < nc; i++) {
      long p;
      bytes = fread(&p, sizeof(long), 1, fp);
      assert(bytes == 1);
      newdam->_pchildren->Add(p);
      //      if (debug)  fprintf(stderr, "dam %d: %d のファイル位置 = %ld\n", newdam->_id, i, *p);
    }
  } else {
    newdam->_pchildren = NULL;
    if (debug) fprintf(stderr, "DEBUG: dam %d: has no sibling nodes.\n", newdam->_id);
  }
  tmpdam._name = NULL;
  return newdam;
}
