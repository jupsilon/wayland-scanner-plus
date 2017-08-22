
#include <string>

extern std::string const client = R"(
#ifndef INCLUDE_$(CAP_PROTOCOL_NAME)_CLIENT_HPP_$(UUID)
#define INCLUDE_$(CAP_PROTOCOL_NAME)_CLIENT_HPP_$(UUID)

#include <functional>

#include "wayland-client-core.hpp"

namespace $(PROTOCOL_NAME)_client
{
  using namespace wayland_client_core::details;

$(INTERFACE_DECLARATIONS)

$(INTERFACES)

$(IMPLEMENTATIONS)
}

#endif/*INCLUDE_$(CAP_PROTOCOL_NAME)_CLIENT_HPP_$(UUID)*/
)" + 1;

extern std::string const client_interface = R"(
  class $(INTERFACE_NAME)_t : public interface_core<$(INTERFACE_NAME), $(INTERFACE_VERSION)> {
  public:
    using core_type = interface_core<$(INTERFACE_NAME), $(INTERFACE_VERSION)>;
    static constexpr wl_interface const& interface = $(INTERFACE_NAME)_interface;

  public:
    $(INTERFACE_NAME)_t($(INTERFACE_NAME)* src = nullptr)
      : core_type(src)
    {
    }
    $(INTERFACE_NAME)_t($(INTERFACE_NAME)_t&& other)
      : core_type(std::move(other))
    {
    }
    ~$(INTERFACE_NAME)_t() override
    {
      if (this->pointer) {
        $(INTERFACE_NAME)_$(DELETER)(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    uint32_t get_version() {
      return $(INTERFACE_NAME)_get_version(this->pointer);
    }
    void* get_user_data() {
      return $(INTERFACE_NAME)_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      $(INTERFACE_NAME)_set_user_data(this->pointer, data);
    }

  public:
$(INTERFACE_MEMBERS)
  };
)" + 1;

extern std::string const client_interface_declarations = R"(
  class $(INTERFACE_NAME)_t;
)" + 1;

extern std::string const client_interface_enum = R"(
    enum class $(ENUM_NAME) : uint32_t {
$(ENUM_ENTRIES)
    };
)" + 1;

extern std::string const client_interface_request = R"(
    $(REQUEST_RESULT) $(REQUEST_NAME)($(REQUEST_PARAMS));
)" + 1;

extern std::string const client_interface_request_impl = R"(
  inline $(REQUEST_RESULT) $(INTERFACE_NAME)_t::$(REQUEST_NAME)($(REQUEST_PARAMS))
  {
    return ($(REQUEST_RESULT)) $(INTERFACE_NAME)_$(REQUEST_NAME)($(REQUEST_ARGS));
  }
)" + 1;

extern std::string const client_interface_event = R"(
    std::function<void ($(EVENT_ARGS))> $(EVENT_NAME);
)" + 1;
