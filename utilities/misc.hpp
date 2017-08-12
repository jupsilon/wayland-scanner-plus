#ifndef INCLUDE_MISC_HPP_C0E7EB68_A73F_4507_A740_E4359DDCAAC9_
#define INCLUDE_MISC_HPP_C0E7EB68_A73F_4507_A740_E4359DDCAAC9_

#include <string>
#include <memory>

#include <cxxabi.h>

namespace utilities
{
  template <typename T>
  inline auto demangled_id = [](){
    static auto enscope = [](char* buf) {
      static auto deleter = [](char* p) { std::free(p); };
      return std::unique_ptr<char, decltype (deleter)>(buf, deleter);
    };
    return std::string(enscope(abi::__cxa_demangle(typeid (T).name(),
						   nullptr,
						   nullptr,
						   nullptr)).get());
  }();
}

#endif/*INCLUDE_MISC_HPP_C0E7EB68_A73F_4507_A740_E4359DDCAAC9_*/
