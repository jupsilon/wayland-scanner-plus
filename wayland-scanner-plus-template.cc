
char const* SRC_CLIENT = R"(
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

char const* SRC_CLIENT_INTERFACE = R"(
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

char const* SRC_CLIENT_INTERFACE_DECLARATIONS = R"(
  class $(INTERFACE_NAME)_t;
)" + 1;

char const* SRC_CLIENT_INTERFACE_ENUM = R"(
    enum class $(ENUM_NAME) : uint32_t {
$(ENUM_ENTRIES)
    };
)" + 1;

char const* SRC_CLIENT_INTERFACE_REQUEST = R"(
    $(REQUEST_RESULT) $(REQUEST_NAME)($(REQUEST_PARAMS));
)" + 1;

char const* SRC_CLIENT_INTERFACE_REQUEST_IMPL = R"(
  inline $(REQUEST_RESULT) $(INTERFACE_NAME)_t::$(REQUEST_NAME)($(REQUEST_PARAMS))
  {
    return ($(REQUEST_RESULT)) $(INTERFACE_NAME)_$(REQUEST_NAME)($(REQUEST_ARGS));
  }
)" + 1;

char const* SRC_CLIENT_INTERFACE_EVENT = R"(
    std::function<void ($(EVENT_TYPE_ARGS))> $(EVENT_NAME);
)" + 1;

char const* SRC_CLIENT_INTERFACE_LISTENER = R"(

  public:
    void connect(void* userdata) {
      listener = $(INTERFACE_NAME)_listener 
      {
$(EVENT_CONNECTORS)
      };
      $(INTERFACE_NAME)_add_listener(this->pointer, &this->listener, static_cast<void*>(this));
    }

  private:
    $(INTERFACE_NAME)_listener listener;
)" + 1;

char const* SRC_CLIENT_INTERFACE_EVENT_CONNECTOR = R"(
        [](void* data, auto... args) {
          auto self = reinterpret_cast<$(INTERFACE_NAME)_t*>(data);
          std::cerr << "$(EVENT_NAME) fired..." << self << std::endl;
          std::cerr << "  " << utilities::demangled_id<decltype (std::make_tuple(args...))> << std::endl;
          return self->$(EVENT_NAME)(data, args...);
        },
)" + 1;
