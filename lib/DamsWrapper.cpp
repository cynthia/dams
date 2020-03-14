/*--*-coding:utf-8-*--*/
#include <iostream>
#include <map>
#include <iconv.h>
#include <time.h>
#include <sys/time.h>
#include <dams.h>
#include "libdams.h"
#include "MatchNodeResult.h"
#include "iconv_converter.h"

int debug;
int timeoutsec;
int limits;
int onmemory;
int exact_match_level;
int flag_checknew;

StaticPtrTry* damsTry = NULL;
ObjVect<long> tmpvect(100);

extern "C" {
  int dams_is_present(void) {
    return 1;
  }
}

namespace damswrapper {

  static long elapsed = -1;
  static iconv_converter *iconv_to_euc = NULL;
  static iconv_converter *iconv_to_utf8 = NULL;
	
  void init_converters(void) {
    if (iconv_to_euc && iconv_to_utf8) return;
    // 文字コードコンバータ
    iconv_to_euc = new iconv_converter(CHARSET_EUC_JP_MS, CHARSET_UTF_8);
    if (iconv_to_euc->isvalid() > 0) {
      iconv_to_utf8 = new iconv_converter(CHARSET_UTF_8, CHARSET_EUC_JP_MS);
    } else {
      iconv_to_euc = new iconv_converter(CHARSET_EUC_JP, CHARSET_UTF_8);
      iconv_to_utf8 = new iconv_converter(CHARSET_UTF_8, CHARSET_EUC_JP);
    }
  }

  void final(void) {
    // 文字コード変換モジュールを終了
    if (iconv_to_euc) {
      delete iconv_to_euc;
      iconv_to_euc = NULL;
    }
    if (iconv_to_utf8) {
      delete iconv_to_utf8;
      iconv_to_utf8 = NULL;
    }
    // 開いている辞書ファイルを閉じる
    closefile();
  }
	
  // 辞書ファイルを開く
  void init(const std::string& damsFileName) {
    _init();
    std::string filepath = damsFileName;
    FILE* fp;
    fp = fopen((filepath + ".dat").c_str(), "r");
    if (!fp) {
      filepath = std::string(DEFAULT_DIC_PATH) + damsFileName;
      fp = fopen((filepath + ".dat").c_str(), "r");
      if (!fp) {
	std::string msg = "Can't open file: " + damsFileName;
	throw std::runtime_error(msg.c_str());
      }
    }
    fclose(fp);

    if (openfile(filepath.c_str())) {
      std::string msg = "Can't open file: " + filepath;
      throw std::runtime_error(msg.c_str());
    }

  }

  // デフォルト辞書ファイルがあれば開く
  void init(void) {
    _init();
    FILE* fp;
    std::string filepath = std::string(DEFAULT_DIC_PATH) + "dams";
    fp = fopen((filepath + ".dat").c_str(), "r");
    if (fp) {
      openfile(filepath.c_str());
      fclose(fp);
    }
  }

  // 辞書ファイル以外の初期化
  void _init(void) {
    debug = 0;
    timeoutsec = 0;
    limits = 10;
    onmemory = 0;
    exact_match_level = 5;
    flag_checknew = 0;
		
    init_itaiji();
  }

  // デフォルトの辞書ディレクトリ
  const char* default_dic_path(void) {
    return DEFAULT_DIC_PATH;
  }

  std::string utf8_to_euc(const std::string& utf_string) {
    init_converters();
    iconv_to_euc->convert(utf_string);
    std::string euc_string = iconv_to_euc->getConverted();
    return euc_string;
  }

  std::string euc_to_utf8(const std::string& euc_string) {
    init_converters();
    iconv_to_utf8->convert(euc_string);
    std::string utf_string = iconv_to_utf8->getConverted();
    return utf_string;
  }

  void retrieve(
		int& score,
		std::string& tail,
		std::vector<Candidate>& candidates, 
		const std::string& q) {
    // 時間計測開始
    struct timeval tv_start;
    struct timeval tv_end;
    gettimeofday(&tv_start, NULL);

    // 結果をクリア
    candidates.clear();

    // クエリをEUCに変換
    init_converters();
    iconv_to_euc->convert(q);
    std::string euc_query = iconv_to_euc->getConverted();
    std::string utf_unconvertable = iconv_to_euc->getRest();
		
    MatchNodeResult result;
    static char buf[BUFSIZ];
    dam* d;
    char* query;
    int matchlen;

    tmpvect.Clear();
    if (euc_query.length() > BUFSIZ - 1) {
      throw std::runtime_error("Query too long");
    }
#ifdef DEBUG
    fprintf(stderr, "original   : '%s'\n", euc_query.c_str());
#endif
    strcpy(buf, standardize(euc_query.c_str()));
#ifdef DEBUG
    fprintf(stderr, "standardize: '%s', %p\n", buf, buf);
#endif
    query = trimming(buf);
#ifdef DEBUG
    fprintf(stderr, "trim       : '%s', %p\n", query, query);
#endif

    // 一致文字列の検索
#ifdef DEBUG
    fprintf(stderr, "get_longestmatch('%s', ...)\n", query);
#endif
    result = get_longestmatch(query);
#ifdef DEBUG
    fprintf(stderr, "nconverted('%s')\n", query);
#endif
    matchlen = nconverted(euc_query.c_str(), result.rest.c_str()); // original
    if (result.maxlen < 0 || result.maxlen - abs(matchlen) < 0) {
      throw std::runtime_error("Unexpected return value detected from nconverted, match length is negative value when processing '" + q + "'");
    }
#ifdef DEBUG
    fprintf(stderr, "maxlen = %d, query + maxlen = '%s'\n", result.maxlen, euc_query.c_str() + result.maxlen);
#endif
    // 結果のセット
    if (result.score == 0) {
      tail = q;
      score = 0;
    } else {
      score = result.score;
      std::string euc_tail = std::string((char*)(euc_query.c_str() + matchlen));
      iconv_to_utf8->convert(euc_tail);
      tail = iconv_to_utf8->getConverted();
      for (int i = 0; i < result.res.Elements() && i < limits; i++) {
	d = read_from_file(f_data, result.res[i]);
	if (flag_checknew && d->_pchildren) {
	  // 新しい地名のチェック
	  if (d->_pchildren->Elements() > 0) {
	    for (int j = 0; j < d->_pchildren->Elements(); j++) {
	      long poschild = d->_pchildren->Element(j);
	      dam* dchild = read_from_file(f_data, poschild);
	      if (dchild->_posparent != result.res[i]) {
		d = read_from_file(f_data, dchild->_posparent);
		break;
	      }
	    }
	  }
	}
			
	PtrVect<dam*> familytree;
	familytree.Clear();
	for (;;) {
	  familytree.Add(d);
	  if (d->_posparent >= 0) {
	    d = read_from_file(f_data, d->_posparent);
	  } else {
	    break;
	  }
	}
	Candidate candidate;
	int n = familytree.Elements();
	for (int j = n - 1; j >= 0; j--) {
	  d = familytree[j];
	  AddressElement element;
	  iconv_to_utf8->convert(std::string(d->_name));
	  std::string dname_s = iconv_to_utf8->getConverted();
	  element.set_name(dname_s);
	  element.set_level(d->_level);
	  element.set_x(d->_x);
	  element.set_y(d->_y);
	  candidate.push_back(element);
	  familytree[j] = NULL;
	  delete d;
	}
	candidates.push_back(candidate);
	familytree[0] = NULL;
      }
    }
    result.res.Clear();
    tail += utf_unconvertable;

    // コンバータ解放
    // delete iconv_to_euc;
    // delete iconv_to_utf8;
		
    // 時間計測終了
    gettimeofday(&tv_end, NULL);
    elapsed = (tv_end.tv_sec - tv_start.tv_sec) * 1000
      + (tv_end.tv_usec - tv_start.tv_usec) / 1000;
  }

  void debugmode(bool flag) {
    debug = flag ? 1 : 0;
  }

  void set_check_new_address(bool flag) {
    flag_checknew = flag ? 1 : 0;
  }

  void set_limit(int limit) {
    limits = limit;
  }

  void set_exact_match_level(int level) {
    exact_match_level = level;
  }

  int get_exact_match_level() {
    return exact_match_level;
  }

  long elapsedtime() {
    return elapsed;
  }

  std::string get_standardized_string(const std::string& str) {
    init_itaiji();
    init_converters();

    // クエリをEUCに変換
    iconv_to_euc->convert(str);
    std::string euc_query = iconv_to_euc->getConverted();

    // 標準化
    char* result_euc = standardize(euc_query.c_str());

    // 結果を UTF-8 に変換
    iconv_to_utf8->convert(std::string(result_euc));
    std::string result = iconv_to_utf8->getConverted();

    return result;
  }

}
