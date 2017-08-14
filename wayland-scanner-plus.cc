
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <tuple>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "utilities/misc.hpp"


template <typename Ch>
inline auto dump(std::basic_ostream<Ch>& output,
		 boost::property_tree::ptree const& children,
		 size_t level = 0)
  -> std::basic_ostream<Ch>&
{
  auto indent = [&](size_t level) -> auto& {
    for (auto i = level; i != 0; --i) output.put(' ');
    return output;
  };
  for (auto child : children) {
    auto data = child.first.data();
    if (0 == std::strcmp("<xmlattr>", data)) {
      for (auto attr : child.second.get_child("")) {
	auto label = attr.first.data();
	auto value = child.second.get_optional<std::string>(label).get();
	indent(level) << ":" << label << "=" << value << std::endl;
      }
    }
    else {
      indent(level) << data << std::endl;
      auto value = child.second.get_value<std::string>();
      if (!std::regex_match(value, std::regex("^[ \t\n]*$"))) {
	output << "{{{" << std::endl;
	///indent(level) << value << std::endl;
	std::istringstream stream(value);
	while (stream) {
	  std::string line;
	  std::getline(stream, line);
	  auto choped = std::regex_replace(line, std::regex("^[ \t]*(.*)$"), "$1");
	  if (choped.empty() == false) {
	    output << choped << std::endl;
	  }
	}
	output << "}}}" << std::endl;
      }
      dump(output, child.second, level + 1);
    }
  }
  return output;
}

template <typename Ch>
inline auto& operator << (std::basic_ostream<Ch>& output,
			  boost::property_tree::ptree const& node)
{
  return dump(output, node, 0);
}

// <<< (WIP)
#if 1
template <typename Ch, typename K, typename V>
inline auto& operator << (std::basic_ostream<Ch>& output, std::pair<K, V> const& pair) {
  output.put('(');
  output << pair.first << " . " << pair.second;
  output.put(')');
  return output;
}

template <typename Ch, typename K, typename V, typename A>
inline auto& operator << (std::basic_ostream<Ch>& output, std::map<K, V, A> const& assoc) {
  output.put('(');
  int i = 0;
  for (auto const& pair : assoc) {
    if (0 == i) {
      ++i;
    }
    else {
      output.put(' ');
    }
    output << pair;
  }
  output.put(')');
  return output;
}

namespace details
{
  template <typename Ch, typename Tuple, size_t... I>
  inline auto& print(std::basic_ostream<Ch>& output,
		     Tuple const& tpl,
		     std::index_sequence<I...>)
  {
    output.put('[');
    (..., (output << (I == 0 ? "" : " ") << std::get<I>(tpl)));
    output.put(']');
    return output;
  }

  template <typename Ch, typename... T>
  inline auto& print(std::basic_ostream<Ch>& output, std::tuple<T...> const& tpl) {
    return print(output, tpl, std::make_index_sequence<sizeof... (T)>());
  }
}

template <typename Ch, typename... T>
inline auto& operator << (std::basic_ostream<Ch>& output, std::tuple<T...> const& tpl) {
  return details::print(output, tpl);
}

template <typename ...Args>
struct configuration : public std::tuple<Args...>,
		       public std::vector<configuration<Args...>>
{
  using self_type = configuration;
  using data_type = std::tuple<Args...>;
  using sequence_type = std::vector<configuration<Args...>>;

public:
  auto&       data()           { return static_cast<data_type&>          (*this); }
  auto const& data()     const { return static_cast<data_type const&>    (*this); }
  auto&       sequence()       { return static_cast<sequence_type&>      (*this); }
  auto const& sequence() const { return static_cast<sequence_type const&>(*this); }

public:
  friend bool operator < (configuration const& lhs, configuration const& rhs) {
    return static_cast<data_type const&>(lhs) < static_cast<data_type const&>(rhs);
  }

private:
  template <typename Ch>
  static void print(std::basic_ostream<Ch>& output, configuration const& self, size_t level) {
    for (int i = 0; i < level; ++i) output.put(' ');
    output << self.data() << std::endl;
    for (auto const& child : self.sequence()) {
      print(output, child, 1+level);
    }
  }

public:
  template <typename Ch>
  friend auto& operator << (std::basic_ostream<Ch>& output, configuration const& self) {
    print(output, self, 0);
    return output;
  }
};

inline auto reconfigure(boost::property_tree::ptree const& tree)
  -> configuration<std::string, std::map<std::string, std::string>>
{
  using configuration = configuration<std::string, std::map<std::string, std::string>>;

  configuration conf;

  for (auto const& child : tree) {
    auto data = child.first.data();
    // if (0 == std::strcmp("<xmlattr>", data)) {
    //   for (auto const& attr : child.second.get_child("")) {
    //   	auto label = attr.first.data();
    // 	auto value = child.second.template get_optional<std::string>(label).get();
	
    // 	indent(level) << ":" << label << "=" << value << std::endl;

    auto child_conf = reconfigure(child.second);
    std::get<0>(child_conf.data()) = child.first.data();

    conf.push_back(child_conf);
  }

  return conf;
}
#endif
// >>> (WIP)

int main() {
  using configuration = configuration<std::string, std::map<std::string, std::string>>;
  namespace pt = boost::property_tree;

  try {
    pt::ptree root;
    pt::read_xml(std::cin, root);

    std::cerr << reconfigure(root) << std::endl;

    return 0;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0; // handled
}
