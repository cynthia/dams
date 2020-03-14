#ifndef __ICONV_CONVERTER_H__
#define __ICONV_CONVERTER_H__

#include <iostream>
#include <iconv.h>

#define CHARSET_UTF_8 "UTF-8"
#define CHARSET_EUC_JP "EUC-JP"
#define CHARSET_EUC_JP_MS "EUC-JP-MS"

namespace damswrapper {

  class iconv_converter {
  private:
    iconv_t _ict;
    std::string _input;
    std::string _converted;
    std::string _rest;
  public:
    iconv_converter(const char* to_code, const char* from_code);
    ~iconv_converter();
    int isvalid(void);
    bool convert(const std::string& input);
    inline std::string getInput(void) { return this->_input; }
    inline std::string getConverted(void) { return this->_converted; }
    inline std::string getRest(void) { return this->_rest; }
  };

}

#endif /* __ICONV_CONVERTER_H__ */

