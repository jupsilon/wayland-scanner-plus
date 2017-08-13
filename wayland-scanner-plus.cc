
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <regex>


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "utilities/misc.hpp"

struct node : public std::map<std::string, node> {
public:
  node()
    : parent(nullptr)
  {
  }

  node(node* parent)
    : parent(parent)
  {
  }

  auto& operator += (node&& other) {
    other.parent = this;
    return *this;
  }

public:
  std::map<std::string, std::string> attributes;

private:
  node* parent;
};

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
