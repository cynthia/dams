#include "iconv_converter.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

namespace damswrapper {
  
  // constructor
  iconv_converter::iconv_converter(const char* to_code, const char* from_code) {
    this->_ict = iconv_open(to_code, from_code);
    this->_input = std::string("");
    this->_converted = std::string("");
    this->_rest = std::string("");
  }

  // destructor
  iconv_converter::~iconv_converter() {
    if (this->isvalid()) iconv_close(this->_ict);
  }

  int iconv_converter::isvalid(void) {
    if (this->_ict == (iconv_t)(-1))
      return 0;
    else
      return 1;
  }

  // convert
  // @param  input: the input string which want to be converted.
  // @return boolean
  //     true  ,if whole string has been converted.
  //            The converted string can be obtained by getConverted().
  //     false ,if some string has not been converted.
  //            The remained string can be obtained by getRest().
  bool iconv_converter::convert(const std::string& input) {
    const char* p_in = input.c_str();
    size_t in_len = strlen(p_in);
    size_t out_len = in_len * MB_LEN_MAX;
    size_t converted = 0;

    this->_input = input;
    char *ibufp_top, *ibufp;
    ibufp_top = ibufp = (char*)malloc(sizeof(char) * in_len + 1);
    char *obufp_top, *obufp;
    obufp_top = obufp = (char*)malloc(sizeof(char) * out_len + 1);
    memset(ibufp, 0, in_len + 1);
    memset(obufp, 0, out_len + 1);
    memcpy(ibufp, p_in, in_len);

    converted = iconv(this->_ict, &ibufp, &in_len, &obufp, &out_len);
    if (converted == (size_t)(-1)) {
      this->_converted = std::string(obufp_top);
      this->_rest = std::string(ibufp);
    } else {
      this->_converted = std::string(obufp_top);
      this->_rest = std::string("");
    }
    free(ibufp_top);
    free(obufp_top);
    return (converted != (size_t)(-1));
  }

}

