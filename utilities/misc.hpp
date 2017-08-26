#ifndef INCLUDE_MISC_HPP_C0E7EB68_A73F_4507_A740_E4359DDCAAC9_
#define INCLUDE_MISC_HPP_C0E7EB68_A73F_4507_A740_E4359DDCAAC9_

#include <string>
#include <typeinfo>

namespace utilities
{
  std::string friendly_name(std::type_info const& info);

  template <typename T>
  std::string demangled_id = friendly_name(typeid (T));

  inline auto concat() {
    return std::string();
  }
  template <typename First, typename ...Rest>
  inline auto concat(First first, Rest... rest) {
    return first + concat(rest...);
  }

  std::string trim_last(std::string const& src, size_t n = 1);
  std::string upper(std::string src);
}

#endif/*INCLUDE_MISC_HPP_C0E7EB68_A73F_4507_A740_E4359DDCAAC9_*/
