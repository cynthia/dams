/* headers.h */
#ifndef _HEADERS_H_
#define _HEADERS_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>

#include <dams.h>
#include "dam.h"
#include "tmplvect.h"
#include "try.h"
#include "strlib.h"

#define E2U(str) damswrapper::euc_to_utf8(str).c_str()

#define MAXSTRLEN 256
#define FD_STDIN  0
#define FD_STDOUT 1
#define FD_STDERR 2
#define C_DISCON '.'

extern void dams(void);
extern int  proc(const char* msg);
extern void read_from_csv(FILE*);
extern void read_aliases(FILE*);
extern void write_to_binary(char*, char*);
extern void write_tree(FILE*);
extern void write_hook(FILE*);
extern void make_try(void);
extern void make_tree(dam*);
extern PtrVect<char*>* get_args(char* stream, char separator);
extern void make_alias(PtrVect<char*>*, PtrVect<char*>*);
extern void cut_alias(PtrVect<char*>*);
extern void make_all_tree(void);
extern void retrieve(const char*);
extern void check(void);
extern void clear_all(void);
extern void clean(void);
extern void make_statics(void);
extern dam* get_parent(dam* key);
extern int get_longestmatch(const char*, PtrVect<dam*>&);
extern char* addressmatch(char*);
extern int parentHF(const void* key);
extern char* standardize(const char*);

extern PtrVect<dam*> damsArray;
extern PtrTry damsTryName, damsTryParent;
extern long base;
extern int debug;
extern const char* kansuji[];
extern const char* arabic;
const char version[] = "4.20";

#endif /* _HEADERS_H_ */
