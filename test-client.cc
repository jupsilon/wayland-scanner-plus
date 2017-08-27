
#include <iostream>
#include <iomanip>
#include <functional>

#include <cstring>

#include <wayland-client.h>

#include "utilities/misc.hpp"

#include "wayland-client-core.hpp"
#include "wayland-client.hpp"

#include "weston-desktop-client.h"
#include "weston-desktop-client.hpp"
#include "wayland-egl-helper.hpp"

#include <GL/gl.h>

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
    //weston_desktop_shell_t desktop_shell;
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
	// if (0 == std::strcmp(interface, weston_desktop_shell_t::interface.name)) {
	//   void* bound = registry.bind(name, &weston_desktop_shell_t::interface, version);
	//   std::cerr << bound << std::endl;
	//   desktop_shell.assign(reinterpret_cast<weston_desktop_shell*>(bound));
	// }
	if (0 == std::strcmp(interface, wl_output_t::interface.name)) {
	  void* bound = registry.bind(name, &wl_output_t::interface, version);
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
    wl_shell_surface_t shell_surface = shell.get_shell_surface(surface);

    shell_surface.connect(nullptr);
    shell_surface.ping = [&](auto, auto, auto serial) {
      std::cerr << "Ping captured by the closure!" << std::endl;
      shell_surface.pong(serial);
    };

    std::cerr << utilities::demangled_id<decltype (surface)> << std::endl;
    std::cerr << surface << std::endl;
    // std::cerr << utilities::demangled_id<decltype (desktop_shell)> << std::endl;
    // std::cerr << desktop_shell << std::endl;

    //desktop_shell.set_background(output, surface);
    //desktop_shell.desktop_ready();

    std::cerr << compositor.get_version() << std::endl;

    std::cerr << "-----------------------------------------" << std::endl;

    egl_display_t egl_display(display);
    auto egl_window = wl_egl_window_create(surface, 640, 480);
    EGLint attr[] = {
      EGL_RED_SIZE,   8,
      EGL_GREEN_SIZE, 8,
      EGL_BLUE_SIZE,  8,
      EGL_ALPHA_SIZE, 8,
      EGL_NONE,
    };
    auto egl_config = egl_display.choose_config(attr);
    egl_context_t egl_context(egl_display, egl_config, EGL_NO_CONTEXT, nullptr);
    egl_surface_t egl_surface(egl_display, egl_config, egl_window, nullptr);

    shell_surface.set_toplevel();

    do {
      eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context);
      glClearColor(0.0, 0.0, 1.0, 0.5);
      glClear(GL_COLOR_BUFFER_BIT);
      eglSwapBuffers(egl_display, egl_surface);
    }
    while (-1 != wl_display_dispatch(display));

    wl_egl_window_destroy(egl_window);
  }
  catch (std::exception& ex) {
    std::cerr << utilities::demangled_id<decltype (ex)> << ' ' << ex.what() << std::endl;
  }
  return 0;
}
