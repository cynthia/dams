/* main.c */
#include "headers.h"
#include <string>
#define MAXSTRLEN 256

PtrVect<dam*> damsArray(10);
PtrTry damsTryName, damsTryParent;
int debug;

static char buf[MAXSTRLEN];
int main(int argc, char** argv) {
  int verbose = 0;
  FILE *ifp, *ofp;
  char *readfile, *alias, *writefile, *itaiji;
  debug = 0;
  int done = 0;
  int idx;
  readfile = alias = writefile = NULL;

  damsArray.Clear();
  damswrapper::init();

  /* check options */
  for (idx = 1; idx < argc; idx++) {
    if (!strcmp(argv[idx], "-h")) {
      printf("Usage: makedic [-d] [-r inputfile] [-a aliasfile] [-w outputfile]\n");
      exit(0);
    } else if (!strcmp(argv[idx], "-d")) {
      if (debug == 0) {
	fprintf(stderr, "Debug On\n");
	debug = 1;
      }	else {
	fprintf(stderr, "Debug Off\n");
	debug = 0;
      }
    } else if (!strcmp(argv[idx], "-r")) {
      idx++;
      readfile = argv[idx];
    } else if (!strcmp(argv[idx], "-a")) {
      idx++;
      alias = argv[idx];
    } else if (!strcmp(argv[idx], "-w")) {
      idx++;
      writefile = argv[idx];
    } else if (!strcmp(argv[idx], "-v")) {
      verbose = 1;
    }
  }

  // テキストデータ読み込み
  if (!readfile || !verbose) {
    if (!readfile) readfile = "dams.txt";
    ifp = fopen(readfile, "r");
    if (!ifp) {
      fprintf(stderr, "%s が開けません．\n", readfile);
      exit(1);
    } else {
      fprintf(stderr, "データファイル %s を読み込み中．\n", readfile);
      read_from_csv(ifp);
      fclose(ifp);
    }
  }

  if (verbose) {
    while (!done) {
      fputs("? ", stdout);
      fgets(buf, MAXSTRLEN - 1, stdin);
      if (!strncasecmp(buf, "exit", 4)) {
	done = 1;
      } else { 
	if (proc(buf) < 0) done = 1;
      }
    }
    clear_all();
    exit(0);
  }

  // 以下の処理は対話モードではない場合のみ実行される
  
  fprintf(stderr, "地名インデックスを作成中．\n");
  make_try();
  fprintf(stderr, "階層構造木を作成中．\n");
  make_all_tree();
  fprintf(stderr, "不要なデータを整理中．\n");
  clean();

  if (alias) {
    ifp = fopen(alias, "r");
    if (!ifp) {
      fprintf(stderr, "%s が開けません．\n", alias);
      exit(1);
    } else {
      fprintf(stderr, "エイリアスファイル %s を読み込み中．\n", alias);
      read_aliases(ifp);
      fclose(ifp);
    }
  }

  if (!writefile) writefile = "dams";
  char datafilename[MAXSTRLEN], tryfilename[MAXSTRLEN];
  strcpy(datafilename, writefile);
  strcat(datafilename, ".dat");
  strcpy(tryfilename, writefile);
  strcat(tryfilename, ".try");
  write_to_binary(datafilename, tryfilename);
  clear_all();
  fputs("データの書き込みが完了しました．\nプログラムを終了します．\n", stderr);

  return 0;
}
