
#include <iostream>
#include <iomanip>
#include <functional>

#include <wayland-client.h>

#include "wayland-client-core.hpp"
#include "wayland-client.hpp"

int main() {
  using namespace wayland_client;

  try {
    static std::function<void (void*, wl_registry*, uint32_t, char const*, uint32_t)> global;
    static std::function<void (void*, wl_registry*, uint32_t)> global_remove;

    wl_registry_listener listener = {
      .global = [](void *data, struct wl_registry *registry,
		   uint32_t name, const char *interface, uint32_t version)
      {
	global(data, registry, name, interface, version);
      },
      .global_remove = [](void* data, wl_registry* registry, uint32_t name) {
	global_remove(data, registry, name);
      },
    };

    wl_display_t display(wl_display_connect(nullptr));
    auto registry = display.get_registry();

    wl_registry_add_listener(registry, &listener, nullptr);
    global = [&](void*, wl_registry* registry, uint32_t name,
		 char const* interface, uint32_t version)
      {
	std::cerr << std::setw(4) << name << ':' << interface << std::endl;
      };
    wl_display_dispatch(display);

    std::cerr << typeid (display).name() << std::endl;
    std::cerr << typeid (registry).name() << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}
