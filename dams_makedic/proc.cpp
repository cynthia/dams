/* proc.c */

#include "headers.h"

// メッセージの処理
// 失敗 0
// 成功 1
// 成功&終了 -1
int proc(const char* utf_msg) {
  std::string euc_msg = damswrapper::utf8_to_euc(utf_msg);
  const char* msg = euc_msg.c_str();

  PtrVect<char*> args;
  char buf[MAXSTRLEN];
  char* sp, *dp;
  dp = buf;
  int retval = 0;

  for (sp = (char*)msg; *sp != '\0'; sp++) {
    switch (*sp) {
    case ' ':
    case '\n':
    case '\r':
      if (dp != buf) {
	*dp = '\0';
	char* np = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
	strcpy(np, buf);
	args.Add(np);
	dp = buf;
      }
      break;
    default:
      *dp = *sp;
      dp++;
      break;
    }
  }
  
  if (args.Elements() == 0) {
    char *help = new char[5];
    strcpy(help, "HELP");
    args.Add(help);
  }

  if (!strcasecmp(args[0], "DEBUG")) {
    debug = !debug;
    fputs("debug mode changed.\n", stderr);
    retval = 1;
  } else if (!strcasecmp(args[0], "RETR")) {
    if (args.Elements() < 2) {
      fputs("Usage: RETR <retrieve string>\n", stderr);
    } else {
      retrieve(args[1]);
      retval = 1;
    }
  } else if (!strcasecmp(args[0], "READ")) {
    if (args.Elements() < 2) {
      fputs("Usage: READ <read filename>\n", stderr);
    } else {
//      clear_all();
      FILE *ifp;
      ifp = fopen(args[1], "r");
      if (!ifp) {
	fprintf(stderr, "%s が開けません\n", args[1]);
      } else {
	fputs("ファイルを読み込んでいます\n", stderr);
	read_from_csv(ifp);
	fclose(ifp);
      }
      retval = 1;
    }
  } else if (!strcasecmp(args[0], "ALIAS")) {
    if (args.Elements() < 2) {
      fputs("Usage: ALIAS <alias filename>\n", stderr);
    } else {
      FILE *ifp;
      ifp = fopen(args[1], "r");
      if (!ifp) {
	fprintf(stderr, "%s が開けません\n", args[1]);
      } else {
	fputs("ファイルを読み込んでいます\n", stderr);
	read_aliases(ifp);
	fclose(ifp);
      }
      retval = 1;
    }
  } else if (!strcasecmp(args[0], "WRITE")) {
    if (args.Elements() < 2) {
      fputs("Usage: WRITE <write filename>\n", stderr);
    } else {
      fputs("ファイルに書き込んでいます。", stderr);
      char datafilename[MAXSTRLEN], tryfilename[MAXSTRLEN];
      strcpy(datafilename, args[1]);
      strcat(datafilename, ".dat");
      strcpy(tryfilename, args[1]);
      strcat(tryfilename, ".try");
      write_to_binary(datafilename, tryfilename);
      clear_all();
      fputs("データの書き込みが完了しました。プログラムを終了します。\n", stderr);
      retval = -1;
    }
  } else if (!strcasecmp(args[0], "TREE")) {
    if (args.Elements() < 2) {
      fputs("Usage: TREE <write filename>\n", stderr);
    } else {
      fputs("ファイルに書き込んでいます。", stderr);
      FILE* ofp = fopen(args[1], "w");
      write_tree(ofp);
      fputs("木構造の書き込みが完了しました。", stderr);
      fclose(ofp);
    }
  } else if (!strcasecmp(args[0], "HOOK")) {
    if (args.Elements() < 2) {
      fputs("Usage: HOOK <write filename>\n", stderr);
    } else {
      fputs("ファイルに書き込んでいます。", stderr);
      FILE* ofp = fopen(args[1], "w");
      write_hook(ofp);
      fputs("hook データの書き込みが完了しました。", stderr);
      fclose(ofp);
    }
  } else if (!strcasecmp(args[0], "CHECK")) {
    check();
    retval = 1;
  } else if (!strcasecmp(args[0], "CLEAR")) {
    clear_all();
    retval = 1;
  } else if (!strcasecmp(args[0], "MAKE")) {
    fputs("トライを作成しています。\n", stderr);
    make_try();
    fputs("階層木構造を作成しています。\n", stderr);
    make_all_tree();
    retval = 1;
  } else if (!strcasecmp(args[0], "CLEAN")) {
    fputs("データを整理します。\n", stderr);
    clean();
  } else if (!strcasecmp(args[0], "STATIC")) {
    fputs("統計を作成しています\n", stderr);
    make_statics();
    retval = 1;
  } else {
    puts("Proc can handle these commands:\n");
    puts("  RETR <retrieve string>   地名の検索");
    puts("  READ <read filename>     CSV ファイルを読み込み");
    puts("  WRITE <write filename>   データファイルを保存して終了");
    puts("  TREE <write filename>    階層木構造をファイルに保存");
    puts("  HOOK <write filename>    芭蕉用hookデータをファイルに保存");
    puts("  CHECK                    地名データのチェック");
    puts("  CLEAN                    地名データの整理");
    puts("  CLEAR                    地名データのクリア");
    puts("  MAKE                     地名検索テーブルの作成");
    puts("  ALIAS <alias filename>   エイリアスデータの読み込みと作成");
    puts("  EXIT                     プログラムの終了");
  }
  if (args.Elements()) args.ClearElements();
  return retval;
}
