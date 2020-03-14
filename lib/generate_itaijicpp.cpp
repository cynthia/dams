/* generate_itaiji_cpp.cpp */
/* read itaiji table and create itaiji.cpp file */

#include <fstream>
#include <string>
#include <iostream>
#include <map>

#include "config.h"
#ifdef HAVE_STRING_H
#include <string.h>
#endif /* HAVE_STRING_H */

static unsigned short int hexval(const char* str) {
  int h, l;
  l = (int)(unsigned char)(str[0]);
  h = (int)(unsigned char)(str[1]);
  return (unsigned short int)(h << 8 | l);
}

static std::string val2str(const unsigned short int val) {
  char buf[3];
  unsigned char h, l;
  l = (unsigned char)(val & 0xff);
  h = (unsigned char)((val & 0xff00) >> 8);
  buf[0] = l;
  buf[1] = h;
  buf[2] = '\0';
  return std::string(buf, 2);
}

std::map<int, int> init_itaiji(const char* fname) {
  const char* p;
  std::map<int, int> itaiji;
  std::pair<int, int> kv;
  std::map<int, int>::iterator it;
  char buf[256];
  int midashi, itai;

  std::ifstream ifs(fname);
  while (!ifs.eof()) {
    ifs.getline(buf, 256);
    p = buf;

    /* midashi-go */
    midashi = hexval(p);
    if ((it = itaiji.find(midashi)) != itaiji.end()) {
      midashi = it->second;
    } else {
      kv.first = midashi;
      kv.second = midashi;
      itaiji.insert(kv);
    }

    /* hasei-go */
    for (unsigned int i = 2; i < strlen(buf); i += 2) {
      itai = hexval(p + i);
      kv.first = itai;
      // kv.second = midashi;
      itaiji.insert(kv);
    }
  }
  ifs.close();

  return itaiji;
}

void write_itaiji_table(const std::map<int, int>& itaiji, std::ofstream& ofs) {
  for(std::map<int, int>::const_iterator it = itaiji.begin(); it != itaiji.end(); it++) {
    ofs << "  kv.first = " << it->first << "; kv.second = " << it->second << "; itaiji.insert(kv);" 
	<< " // " << val2str(it->first) << "->" << val2str(it->second)<< std::endl;
  }
  return;
}

int main(int argc, char** argv) {
  // generate itaiji map on the memory from the itaiji.txt file
  std::map<int, int> itaiji;
  itaiji = init_itaiji("itaiji.euc");

  // read template line by line
  char buf[1024];
  std::ifstream ifs("itaiji.cpp.in");
  std::ofstream ofs("itaiji.cpp");
  while (!ifs.eof()) {
    ifs.getline(buf, 1024);
    if (!strncmp(buf, "%ITAIJI_TABLE%", 14)) {
      // replace MACRO
      write_itaiji_table(itaiji, ofs);
    } else {
      ofs << buf << std::endl;
    }
  }
  ofs.close();
  ifs.close();
}
