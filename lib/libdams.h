/* libdams.h */
#ifndef _LIBDAMS_H_
#define _LIBDAMS_H_

#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#include "tmplvect.h"
#include "dam.h"
#include "try.h"
#include "MatchNodeResult.h"
//#include "serv.h"

//#define DAMS_PORT 8615

extern void ams(const char* fname);
extern void dams(const char* dummy);
extern void fams(const char* fname, char* fin, char* fout);
extern void cleanup(int);
extern int openfile(const char* fname);
extern int closefile(void);
extern void retrieve(const char* key, FILE* fout);
extern int nconverted(const char* query, const char* tail);
extern MatchNodeResult get_longestmatch(const char* key);
//extern int socksvr(int, void (const char*), const char*);
extern int get_args(PtrVect<char*>& args, const char* stream, char separator);
extern void free_args(PtrVect<char*>& args);
extern int readconf(const char* confname);
extern int d_retrieve(char*);
extern void d_init_srvs(const char* confname);
extern void d_final_srvs(void);
extern void chomp(char*);
extern void init_itaiji(void);
extern int is_itaiji(const char*, const char*);
extern int init_querylog(const char*);
extern int puts_querylog(const char*);
extern char* standardize(const char*);
extern char* trimming(char*);

extern StaticPtrTry* damsTry;
extern FILE *f_data;
extern int debug;
extern int timeoutsec;
extern int limits;
extern int flag_checknew;
extern int exact_match_level;
extern int onmemory;
const char version[] = "4.20";
extern const char* itaiji_path;
extern ObjVect<long> tmpvect;
//extern PtrVect<serv*> servers;
extern int* score;
extern long base;

#endif /* _LIBDAMS_H_ */
