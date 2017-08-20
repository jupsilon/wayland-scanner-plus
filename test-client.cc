
#include <iostream>
#include <iomanip>
#include <functional>

#include <cstring>

#include <wayland-client.h>

#include "wayland-client-core.hpp"
#include "wayland-client.hpp"

#include "utilities/misc.hpp"

#include "weston-desktop-client.h"
#include "weston-desktop-client.hpp"


int main() {
  using namespace wayland_client;
  using namespace weston_desktop_client;

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
    wl_compositor_t compositor;
    wl_shell_t shell;
    wl_output_t output;
    weston_desktop_shell_t desktop_shell;
    {
      wl_registry_t registry = display.get_registry();

      wl_registry_add_listener(registry, &listener, nullptr);
      global = [&](void*, wl_registry*, uint32_t name,
		   char const* interface, uint32_t version)
      {
	std::cerr << std::setw(4) << name << ':' << interface << std::endl;
	if (0 == std::strcmp(interface, wl_compositor_t::interface.name)) {
	  void* bound = registry.bind(name, &wl_compositor_t::interface, version);
	  std::cerr << bound << std::endl;
	  compositor.assign(reinterpret_cast<wl_compositor*>(bound));
	}
	if (0 == std::strcmp(interface, wl_shell_t::interface.name)) {
	  void* bound = registry.bind(name, &wl_shell_t::interface, version);
	  std::cerr << bound << std::endl;
	  shell.assign(reinterpret_cast<wl_shell*>(bound));
	}
	if (0 == std::strcmp(interface, weston_desktop_shell_t::interface.name)) {
	  void* bound = registry.bind(name, &weston_desktop_shell_t::interface, version);
	  std::cerr << bound << std::endl;
	  desktop_shell.assign(reinterpret_cast<weston_desktop_shell*>(bound));
	}
	if (0 == std::strcmp(interface, wl_output_t::interface.name)) {
	  void* bound = registry.bind(name, &weston_desktop_shell_t::interface, version);
	  std::cerr << bound << std::endl;
	  output.assign(reinterpret_cast<wl_output*>(bound));
	}
      };
      wl_display_roundtrip(display);
    }

    std::cerr << display << std::endl;
    std::cerr << compositor << std::endl;
    std::cerr << shell << std::endl;

    auto surface = compositor.create_surface();

    std::cerr << utilities::demangled_id<decltype (surface)> << std::endl;
    std::cerr << surface << std::endl;
    std::cerr << utilities::demangled_id<decltype (desktop_shell)> << std::endl;
    std::cerr << desktop_shell << std::endl;

    desktop_shell.set_background(output, surface);
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}
