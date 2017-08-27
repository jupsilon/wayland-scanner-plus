
#include <iostream>
#include <iomanip>
#include <functional>

#include <cstring>

#include <wayland-client.h>

#include "utilities/misc.hpp"

#include "wayland-client-core.hpp"
#include "wayland-client.hpp"

#include "wayland-egl-helper.hpp"

#include <GL/gl.h>

int main() {
  using namespace wayland_client;

  try {
    wl_display_t    display(wl_display_connect(nullptr));
    wl_compositor_t compositor;
    wl_shell_t      shell;
    wl_seat_t       seat;
    wl_output_t     output;
    {
      wl_registry_t registry = display.get_registry();

      registry.global = [&](auto, auto, auto name, auto interface, auto version) {
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
	if (0 == std::strcmp(interface, wl_seat_t::interface.name)) {
	  void* bound = registry.bind(name, &wl_seat_t::interface, version);
	  std::cerr << bound << std::endl;
	  seat.assign(reinterpret_cast<wl_seat*>(bound));
	}
	if (0 == std::strcmp(interface, wl_output_t::interface.name)) {
	  void* bound = registry.bind(name, &wl_output_t::interface, version);
	  std::cerr << bound << std::endl;
	  output.assign(reinterpret_cast<wl_output*>(bound));
	}
      };
      registry.global_remove = [&](auto, auto, auto) {
	std::cerr << "removed." << std::endl;
      };

      registry.connect(nullptr);
      wl_display_roundtrip(display);
    }

    auto surface = compositor.create_surface();
    wl_shell_surface_t shell_surface = shell.get_shell_surface(surface);

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

    shell_surface.ping = [&](auto, auto, auto serial) {
      std::cerr << "Ping captured by the closure!" << std::endl;
      shell_surface.pong(serial);
    };
    shell_surface.configure = [&](auto, auto, auto, auto width, auto height) {
      wl_egl_window_resize(egl_window, width, height, 0, 0);
      glViewport(0, 0, width, height);
    };
    shell_surface.popup_done = [&](auto, auto) {
      std::cerr << "Popup done" << std::endl;
    };

    shell_surface.connect(nullptr);
    shell_surface.set_toplevel();

    seat.capabilities = [&](auto, auto, auto capabilities) {
      std::cerr << "seat caps:" << capabilities << std::endl;
    };
    seat.name = [&](auto, auto, auto name) {
      std::cerr << "seat name:" << name << std::endl;
    };
    seat.connect(nullptr);
    wl_display_roundtrip(display);

    std::cerr << WL_SEAT_CAPABILITY_POINTER << std::endl;
    std::cerr << WL_SEAT_CAPABILITY_KEYBOARD << std::endl;
    std::cerr << WL_SEAT_CAPABILITY_TOUCH << std::endl;

    bool escape = false;
    wl_keyboard_t keyboard = seat.get_keyboard();
    keyboard.keymap = [&](auto, auto, auto, auto, auto) {
      std::cerr << "keyboard keymap" << std::endl;
    };
    keyboard.enter = [&](auto, auto, auto, auto, auto) {
      std::cerr << "keyboard enter" << std::endl;
    };
    keyboard.leave = [&](auto, auto, auto, auto) {
      std::cerr << "keyboard leave" << std::endl;
    };
    keyboard.key = [&](auto, auto, auto, auto, auto key, auto) {
      std::cerr << "keyboard key: " << key << std::endl;
      if (key == 1)
	escape = true;
    };
    keyboard.modifiers = [&](auto, auto, auto, auto, auto, auto, auto) {
      std::cerr << "keyboard modifiers" << std::endl;
    };
    keyboard.repeat_info = [&](auto, auto, auto, auto) {
      std::cerr << "keyboard repeat_info" << std::endl;
    };
    keyboard.connect(nullptr);

    do {
      if (escape)
      	break;
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
