
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <tuple>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>

#include "utilities/misc.hpp"

template <typename T>
using linked_ordered_set =
  boost::multi_index::multi_index_container<
    T,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_unique<
        boost::multi_index::identity<T>>,
      boost::multi_index::sequenced<>
    >
  >;

/*
template <typename ...Args>
struct configuration :
  public std::tuple<Args...>,
  public linked_ordered_set<configuration<Args...>>
{
  using self_type = configuration;
  using tuple_type = std::tuple<Args...>;
  using container_type = linked_ordered_set<configuration>;

public:
  friend bool operator < (configuration const& lhs, configuration const& rhs) {
    return static_cast<tuple_type const&>(lhs) < static_cast<tuple_type const&>(rhs);
  }
};
*/

template <typename Ch, typename Node>
inline void dump(std::basic_ostream<Ch>& output, Node const& children, size_t level = 0) {
  auto indent = [&](size_t level) -> auto& {
    for (auto i = level; i != 0; --i) output.put(' ');
    return output;
  };
  for (auto child : children) {
    auto data = child.first.data();
    if (0 == std::strcmp("<xmlattr>", data)) {
      for (auto attr : child.second.get_child("")) {
	auto label = attr.first.data();
	auto value = child.second.template get_optional<std::string>(label).get();
	indent(level) << ":" << label << "=" << value << std::endl;
      }
    }
    else {
      indent(level) << data << std::endl;
      auto value = child.second.template get_value<std::string>();
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
}

// template <typename Ch, typename Node>
// inline auto& operator << (std::basic_ostream<Ch>& output, Node const& node) {
//   dump(output, node, 0);
//   return output;
// }

template <typename Node>
inline bool operator == (char const* name, Node const& node) {
  return 0 == std::strcmp(name, node.first.data());
}
template <typename Node>
inline bool operator != (char const* name, Node const& node) {
  return !(name == node);
}

int main() {
  //   using configuration = configuration<
  //   std::string, std::map<std::string, std::string>>;

  // configuration a;
  // for (int i = 0; i < 10; ++i) {
  //   a.insert(a);
  // }

  // for (auto i : a) {
  //   std::cerr << i.size() << std::endl;
  // }

  linked_ordered_set<int> v;

  for (int i = 10; i != 0; --i) {
    v.insert(i);
  }

  for (auto item : v) {
    std::cerr << item << std::endl;
  }
  for (auto item : v.get<1>()) {
    std::cerr << item << std::endl;
  }

  try {
    namespace pt = boost::property_tree;
    pt::ptree tree;
    pt::read_xml(std::cin, tree);

    auto protocol = tree.get_child("protocol");
    assert(!protocol.empty());

    auto protocol_attrs = protocol.get_child("<xmlattr>");
    assert(!protocol_attrs.empty());
    auto protocol_name = protocol_attrs.find("name");
    assert(protocol_name != protocol_attrs.not_found());
    auto protocol_name_value = protocol_name->second.get_value<std::string>();
    assert(!protocol_name_value.empty());

    std::cerr << protocol_name_value << std::endl;

    std::cerr << protocol_attrs.get_child("").size() << std::endl;

    return 0;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0; // handled
}
