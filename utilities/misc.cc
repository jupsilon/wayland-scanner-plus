
#include "misc.hpp"

#include <string>
#include <memory>
#include <algorithm>
#include <typeinfo>

#include <cctype>

#include <cxxabi.h>

namespace utilities
{
  std::string friendly_name(std::type_info const& info) {
    static auto enscope = [](char* buf) {
      static auto deleter = [](char* p) { std::free(p); };
      return std::unique_ptr<char, decltype (deleter)>(buf, deleter);
    };
    return std::string(enscope(abi::__cxa_demangle(info.name(),
						   nullptr,
						   nullptr,
						   nullptr)).get());
  }

  std::string trim_last(std::string const& src, size_t n) {
    return src.substr(0, src.size() - n);
  }
  std::string upper(std::string src)  {
    std::transform(src.begin(), src.end(), src.begin(), [](auto ch) { return std::toupper(ch); });
    return src;
  }
}
