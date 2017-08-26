
#include <iostream>
#include <string>
#include <regex>
#include <tuple>

#include <cctype>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "utilities/misc.hpp"
#include "utilities/uuid.hpp"

extern char const* SRC_CLIENT;
extern char const* SRC_CLIENT_INTERFACE;
extern char const* SRC_CLIENT_INTERFACE_DECLARATIONS;
extern char const* SRC_CLIENT_INTERFACE_ENUM;
extern char const* SRC_CLIENT_INTERFACE_REQUEST;
extern char const* SRC_CLIENT_INTERFACE_REQUEST_IMPL;
extern char const* SRC_CLIENT_INTERFACE_EVENT;

inline std::string subst(std::string source, std::string label, std::string value) {
  return std::regex_replace(source, std::regex("\\$\\(" + label + "\\)"), value);
}

inline std::string attr(boost::property_tree::ptree const& tree, char const* key) {
  return tree.get_child("<xmlattr>").get_optional<std::string>(key) ?
    tree.get_child("<xmlattr>").get_optional<std::string>(key).get() : "nil";
}

inline std::string uuid_identifier() {
  return std::regex_replace(utilities::uuid().to_upper_str(), std::regex("-"), "_");
}

int main() { 
  using boost::property_tree::ptree;
  using namespace utilities;

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
      std::string text = SRC_CLIENT_INTERFACE_ENUM;
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
      std::string text = SRC_CLIENT_INTERFACE_REQUEST;
      auto request_name = attr(tree, "name");

      text = subst(text, "REQUEST_NAME", request_name);

      std::string request_result = "void";
      std::string request_params;               //<! types and formal parameters,
      std::string request_args = "pointer, ";   //<! actual arguments
      for (auto const& child : tree.get_child("")) {
	if (0 == std::strcmp(child.first.data(), "arg")) {
	  if (attr(child.second, "type") == "new_id") {
	    request_result = concat(attr(child.second, "interface"), "_t");
	  }
	  else {
	    request_args   += request_arg(child.second);
	    request_params += request_param(child.second);
	  }
	}
      }

      if (request_result == "nil_t") {
	request_result = "void*";

	// e.g., wl_registry.bind (needs special params)
	request_params += "wl_interface const* interface, ";
	request_params += "uint32_t version, ";
	request_args   += "interface, ";
	request_args   += "version, ";
      }

      text = subst(text, "REQUEST_RESULT", request_result);
      text = subst(text, "REQUEST_PARAMS", trim_last(request_params, 2));
      text = subst(text, "REQUEST_ARGS",   trim_last(request_args, 2));
      text = subst(text, "INTERFACE_NAME", interface_name);

      {
	std::string text = SRC_CLIENT_INTERFACE_REQUEST_IMPL;

	text = subst(text, "REQUEST_NAME",   request_name);
	text = subst(text, "REQUEST_RESULT", request_result);
	text = subst(text, "REQUEST_PARAMS", trim_last(request_params, 2));
	text = subst(text, "REQUEST_ARGS",   trim_last(request_args, 2));
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
      std::string text = SRC_CLIENT_INTERFACE_EVENT;
      auto event_name = attr(tree, "name");

      text = subst(text, "EVENT_NAME", event_name);

      std::string event_args;
      for (auto const& child : tree.get_child("")) {
	if (0 == std::strcmp(child.first.data(), "arg")) {
	  event_args += event_arg(child.second);
	}
      }
      text = subst(text, "EVENT_ARGS", trim_last(event_args, 2));

      return text;
    };

    static std::string declarations;
    
    static auto interface = [](ptree const& tree) {
      std::string text = SRC_CLIENT_INTERFACE;
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

    static auto interface_declaration = [](ptree const& tree) {
      std::string text = SRC_CLIENT_INTERFACE_DECLARATIONS;
      auto interface_name = attr(tree, "name");
      text = subst(text, "INTERFACE_NAME", interface_name);
      return text;
    };

    static auto protocol = [](ptree const& tree) {
      std::string text = SRC_CLIENT;
      auto protocol_name = attr(tree, "name");

      text = subst(text, "PROTOCOL_NAME", protocol_name);
      text = subst(text, "CAP_PROTOCOL_NAME", upper(protocol_name));
      text = subst(text, "UUID", uuid_identifier());

      std::string interface_declarations;
      std::string interfaces;
      for (auto const& child : tree.get_child("")) {
	if (0 == std::strcmp(child.first.data(), "interface")) {
	  interface_declarations += interface_declaration(child.second);
	  interfaces += interface(child.second);
	}
      }
      text = subst(text, "INTERFACE_DECLARATIONS", trim_last(interface_declarations));
      text = subst(text, "INTERFACES", trim_last(interfaces));
      text = subst(text, "IMPLEMENTATIONS", trim_last(implementations));

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
