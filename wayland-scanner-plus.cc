
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <regex>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <cxxabi.h>

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

template <typename Children>
inline void dump(Children const& children, size_t level = 0) {
  static auto indent = [](size_t level) -> auto& {
    for (auto i = level; i != 0; --i) std::cerr.put(' ');
    return std::cerr;
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
	std::cerr << "{{{" << std::endl;
	///indent(level) << value << std::endl;
	std::istringstream stream(value);
	while (stream) {
	  std::string line;
	  std::getline(stream, line);
	  auto choped = std::regex_replace(line, std::regex("^[ \t]*(.*)$"), "$1");
	  if (choped.empty() == false) {
	    std::cerr << choped << std::endl;
	  }
	}
	std::cerr << "}}}" << std::endl;
      }
      dump(child.second, level + 1);
    }
  }
}

int main() {
  try {
    namespace pt = boost::property_tree;
    pt::ptree tree;
    pt::read_xml(std::cin, tree);

    for (auto interface : tree.get_child("protocol.interface")) {
      std::cerr << interface.first.data() << std::endl;
    }

    std::cerr << "===================================" << std::endl;

    for (auto interface_attr : tree.get_child("protocol.interface.<xmlattr>")) {
      std::string attr;
      std::cerr << (attr = interface_attr.first.data()) << std::endl;
      auto value = tree.get_optional<std::string>("protocol.interface.<xmlattr>." + attr);
      if (value) {
	std::cerr << "  " << value.get() << std::endl;
      }
    }

    std::cerr << "===================================" << std::endl;

    for (auto iter = tree.find(""); iter != tree.not_found(); ++iter) {
      std::cerr << iter->first.data() << std::endl;
    }

    std::cerr << "===================================" << std::endl;

    for (auto protocol : tree.get_child("protocol")) {
      auto data = protocol.first.data();
      std::cerr << data << std::endl;

      for (auto interface : protocol.second.get_child("")) {
	auto data = interface.first.data();

	std::cerr << "  " << data << std::endl;
	if (true || 0 == std::strcmp("description", data)) {
	  std::cerr << "---------!!!--------" << std::endl;
	  std::cerr << interface.second.get_value<std::string>();
	}
      }
    }

    std::cerr << "===================================" << std::endl;

    dump(tree.get_child(""));

    return 0;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0; // handled
}
