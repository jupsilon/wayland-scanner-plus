
#include <iostream>
#include <string>
#include <regex>
#include <tuple>
#include <algorithm>
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

inline auto concat() {
  return std::string();
}
template <typename First, typename ...Rest>
inline auto concat(First first, Rest... rest) {
  return first + concat(rest...);
}

inline std::string chop(std::string const& value) {
  if (!std::regex_match(value, std::regex("^[ \t\n]*$"))) {
    std::istringstream stream(value);
    std::ostringstream output;
    while (stream) {
      std::string line;
      std::getline(stream, line);
      auto chopped = std::regex_replace(line, std::regex("^[ \t]*(.*)$"), "$1");
      if (chopped.empty() == false) {
	output << chopped << std::endl;
      }
    }
    return output.str();
  }
  return std::string();
}

template <size_t N = 1>
inline std::string trim_last(std::string src) {
  return src.substr(0, src.size() - N);
}

inline std::string upper(std::string src) {
  std::transform(src.begin(), src.end(), src.begin(), [](auto ch) { return std::toupper(ch); });
  return src;
}

inline std::string subst(std::string source, std::string label, std::string value) {
  return std::regex_replace(source, std::regex("\\$\\(" + label + "\\)"), value);
}

inline std::string attr(boost::property_tree::ptree const& tree, char const* key) {
  return tree.get_child("<xmlattr>").get_optional<std::string>(key) ?
    tree.get_child("<xmlattr>").get_optional<std::string>(key).get() : "nil";
}

inline std::string uuid() {
  uuid_t value; uuid_generate(value);

  char buf[32] = { };
  uuid_unparse_upper(value, buf);

  return std::regex_replace(buf, std::regex("-"), "_");
}

extern std::string const client;
extern std::string const client_interface;
extern std::string const client_interface_enum;
extern std::string const client_interface_request;
extern std::string const client_interface_request_impl;
extern std::string const client_interface_event;

int main() { 
  using boost::property_tree::ptree;

  try {
    //
    // code generators
    //
    static auto enum_entry = [](ptree const& tree, std::string enum_name) {
      return concat("      ",
		    concat(enum_name, "_", attr(tree, "name")),
		    " = ",
		    upper(attr(tree, "value")),
		    ",\n");
    };

    static auto enumeration = [](ptree const& tree) {
      auto text = client_interface_enum;
      auto enum_name = attr(tree, "name");

      text = subst(text, "ENUM_NAME", enum_name);

      std::string enum_entries;
      for (auto const& child : tree.get_child("")) {
	if (0 == std::strcmp(child.first.data(), "entry")) {
	  enum_entries += enum_entry(child.second, enum_name);
	}
      }
      text = subst(text, "ENUM_ENTRIES", trim_last(enum_entries));

      return text;
    };

    static auto request_param = [](ptree const& tree) {
      auto param_type = attr(tree, "type");
      auto param_name = attr(tree, "name");

      if ("new_id" == param_type) {
	assert(!"never occurs");
	return std::string();
      }
      else if ("object" == param_type) {
	param_type = attr(tree, "interface") + "*";
      }
      else if ("int" == param_type) {
	param_type = "int32_t";
      }
      else if ("uint" == param_type) {
	param_type = "uint32_t";
      }
      else if ("string" == param_type) {
	param_type = "char const*";
      }
      else if ("fd" == param_type) {
	param_type = "int";
      }
      else {
	assert(!"not supported.");
      }

      return concat(param_type, " ", param_name, ", ");
    };

    static auto request_arg = [](ptree const& tree) {
      auto arg_name = attr(tree, "name");
      return concat(arg_name, ", ");
    };

    static std::string implementations;

    static auto request = [](ptree const& tree, std::string interface_name) {
      auto text = client_interface_request;
      auto request_name = attr(tree, "name");

      text = subst(text, "REQUEST_NAME", request_name);

      std::string request_result = "void";
      std::string request_params;               //<! types and formal parameters,
      std::string request_args = "pointer, ";   //<! actual arguments
      for (auto const& child : tree.get_child("")) {
	if (0 == std::strcmp(child.first.data(), "arg")) {
	  if (attr(child.second, "type") == "new_id") {
	    request_result = attr(child.second, "interface");
	    request_result.push_back('*');
	  }
	  else {
	    request_args   += request_arg(child.second);
	    request_params += request_param(child.second);
	  }
	}
      }

      if (request_result == "nil*") {
	request_result = "void*";

	// e.g., wl_registry.bind (needs special params)
	request_params += "wl_interface const* interface, ";
	request_params += "uint32_t version, ";
	request_args   += "interface, ";
	request_args   += "version, ";
      }

      text = subst(text, "REQUEST_RESULT", request_result);
      text = subst(text, "REQUEST_PARAMS", trim_last<2>(request_params));
      text = subst(text, "REQUEST_ARGS",   trim_last<2>(request_args));
      text = subst(text, "INTERFACE_NAME", interface_name);

      {
	std::string text = client_interface_request_impl;

	text = subst(text, "REQUEST_NAME",   request_name);
	text = subst(text, "REQUEST_RESULT", request_result);
	text = subst(text, "REQUEST_PARAMS", trim_last<2>(request_params));
	text = subst(text, "REQUEST_ARGS",   trim_last<2>(request_args));
	text = subst(text, "INTERFACE_NAME", interface_name);

	implementations += text;
      }

      return text;
    };

    static auto event_arg = [](ptree const& tree) {
      auto arg_type = attr(tree, "type");

      if ("new_id" == arg_type) {
	return std::string();
      }
      else if ("object" == arg_type) {
	auto interface = attr(tree, "interface");
	if ("nil" == interface) {
	  interface = "void";
	}
	arg_type = interface + "*";
      }
      else if ("int" == arg_type) {
	arg_type = "int32_t";
      }
      else if ("uint" == arg_type) {
	arg_type = "uint32_t";
      }
      else if ("string" == arg_type) {
	arg_type = "char const*";
      }
      else if ("fd" == arg_type) {
	arg_type = "int";
      }
      else if ("fixed" == arg_type) {
	arg_type = "fixed";
      }
      else if ("array" == arg_type) {
	arg_type = "chunk";
      }
      else {
	std::cerr << "----------" << arg_type << std::endl;
	assert(!"not supported.");
      }
      return arg_type + ", ";
    };

    static auto event = [](ptree const& tree) {
      auto text = client_interface_event;
      auto event_name = attr(tree, "name");

      text = subst(text, "EVENT_NAME", event_name);

      std::string event_args;
      for (auto const& child : tree.get_child("")) {
	if (0 == std::strcmp(child.first.data(), "arg")) {
	  event_args += event_arg(child.second);
	}
      }
      text = subst(text, "EVENT_ARGS", trim_last<2>(event_args));

      return text;
    };
    
    static auto interface = [](ptree const& tree) {
      auto text = client_interface;
      auto interface_name    = attr(tree, "name");
      auto interface_version = attr(tree, "version");

      text = subst(text, "INTERFACE_NAME",    interface_name);
      text = subst(text, "INTERFACE_VERSION", interface_version);
      if (interface_name == "wl_display") {
	text = subst(text, "DELETER", "disconnect");
      }
      else {
	text = subst(text, "DELETER", "destroy");
      }

      std::string interface_members;
      for (auto const& child : tree.get_child("")) {
	if (0 == std::strcmp(child.first.data(), "enum")) {
	  interface_members += enumeration(child.second);
	}
	else if (0 == std::strcmp(child.first.data(), "request")) {
	  interface_members += request(child.second, interface_name);
	}
	else if (0 == std::strcmp(child.first.data(), "event")) {
	  interface_members += event(child.second);
	}
      }
      text = subst(text, "INTERFACE_MEMBERS", trim_last(interface_members));

      return text;
    };

    static auto protocol = [](ptree const& tree) {
      auto text = client;
      auto protocol_name = attr(tree, "name");

      text = subst(text, "PROTOCOL_NAME", protocol_name);
      text = subst(text, "CAP_PROTOCOL_NAME", upper(protocol_name));
      text = subst(text, "UUID", uuid());

      std::string interfaces;
      for (auto const& child : tree.get_child("")) {
	if (0 == std::strcmp(child.first.data(), "interface")) {
	  interfaces += interface(child.second);
	}
      }
      text = subst(text, "INTERFACES", trim_last(interfaces));
      text = subst(text, "IMPLEMENTATIONS", implementations);

      return text;
    };

    ptree root;
    read_xml(std::cin, root);

    std::cout << protocol(root.get_child("protocol"));

    return 0;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return -1;
}
