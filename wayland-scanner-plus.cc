
#include <iostream>
#include <string>
#include <regex>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <iterator>

#include <cctype>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <uuid/uuid.h>

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

inline std::string chop(std::string const& value) {
  if (!std::regex_match(value, std::regex("^[ \t\n]*$"))) {
    std::istringstream stream(value);
    std::ostringstream output;
    while (stream) {
      std::string line;
      std::getline(stream, line);
      auto choped = std::regex_replace(line, std::regex("^[ \t]*(.*)$"), "$1");
      if (choped.empty() == false) {
	output << choped << std::endl;
      }
    }
    return output.str();
  }
  return std::string();
}

inline std::string attr(boost::property_tree::ptree const& tree, char const* key) {
  return tree.get_child("<xmlattr>").get_optional<std::string>(key).get();
}

namespace pt = boost::property_tree;

inline std::string upper(std::string src) {
  std::transform(src.begin(), src.end(), src.begin(), [](auto ch) { return std::toupper(ch); });
  return src;
}

inline std::string subst(std::string source, std::string label, std::string value) {
  return std::regex_replace(source, std::regex("\\$\\(" + label + "\\)"), value);
}

inline std::string uuid() {
  uuid_t value; uuid_generate(value);

  char buf[32] = { };
  uuid_unparse_upper(value, buf);

  return std::regex_replace(buf, std::regex("-"), "_");
}

std::string load_template(char const* filename) {
  std::ifstream input(filename, std::ios::in);
  assert(input.is_open());
  return std::string(std::istreambuf_iterator<char>(input),
		     std::istreambuf_iterator<char>());
}

int main() {
  try {
    auto client_header           = load_template("client_header.txt");
    auto client_header_interface = load_template("client_header.interface.txt");

    pt::ptree root;
    pt::read_xml(std::cin, root);

    auto protocol = root.get_child("protocol");
    auto protocol_name = attr(protocol, "name");

    std::string interfaces;
    for (auto const& interface : protocol.get_child("")) {
      if (0 == std::strcmp("interface", interface.first.data())) {
	auto interface_name = attr(interface.second, "name");
	auto interface_version = attr(interface.second, "version");

	auto text = client_header_interface;
	text = subst(text, "INTERFACE_NAME", interface_name);
	text = subst(text, "INTERFACE_VERSION", interface_version);

	dump(std::cerr, interface.second);
	std::cerr << "-------------------" << std::endl;

	interfaces += text;
      }
    }

    client_header = subst(client_header, "PROTOCOL_NAME", protocol_name);
    client_header = subst(client_header, "CAP_PROTOCOL_NAME", upper(protocol_name));
    client_header = subst(client_header, "UUID", uuid());
    client_header = subst(client_header, "INTERFACES", interfaces);

    std::cerr << "============================================" << std::endl;
    std::cerr << client_header;
    std::cerr << "============================================" << std::endl;

    return 0;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0; // handled
}
