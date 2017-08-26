#ifndef INCLUDE_WESTON_DESKTOP_CLIENT_HPP_7F070C0A_7C20_4956_92DD_A37A21DC4186
#define INCLUDE_WESTON_DESKTOP_CLIENT_HPP_7F070C0A_7C20_4956_92DD_A37A21DC4186

#include <functional>

#include "wayland-client-core.hpp"

namespace weston_desktop_client
{
  using namespace wayland_client_core::details;

  class weston_desktop_shell_t;
  class weston_screensaver_t;

  class weston_desktop_shell_t : public interface_core<weston_desktop_shell, 1> {
  public:
    using core_type = interface_core<weston_desktop_shell, 1>;
    static constexpr wl_interface const& interface = weston_desktop_shell_interface;

  public:
    weston_desktop_shell_t(weston_desktop_shell* src = nullptr)
      : core_type(src)
    {
    }
    weston_desktop_shell_t(weston_desktop_shell_t&& other)
      : core_type(std::move(other))
    {
    }
    ~weston_desktop_shell_t() override
    {
      if (this->pointer) {
        weston_desktop_shell_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    uint32_t get_version() {
      return weston_desktop_shell_get_version(this->pointer);
    }
    void* get_user_data() {
      return weston_desktop_shell_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      weston_desktop_shell_set_user_data(this->pointer, data);
    }

  public:
    void set_background(wl_output* output, wl_surface* surface);
    void set_panel(wl_output* output, wl_surface* surface);
    void set_lock_surface(wl_surface* surface);
    void unlock();
    void set_grab_surface(wl_surface* surface);
    std::function<void (uint32_t, wl_surface*, int32_t, int32_t)> configure;
    std::function<void ()> prepare_lock_surface;
    std::function<void (uint32_t)> grab_cursor;
    enum class cursor : uint32_t {
      cursor_none = 0,
      cursor_resize_top = 1,
      cursor_resize_bottom = 2,
      cursor_arrow = 3,
      cursor_resize_left = 4,
      cursor_resize_top_left = 5,
      cursor_resize_bottom_left = 6,
      cursor_move = 7,
      cursor_resize_right = 8,
      cursor_resize_top_right = 9,
      cursor_resize_bottom_right = 10,
      cursor_busy = 11,
    };
    void desktop_ready();
    enum class panel_position : uint32_t {
      panel_position_top = 0,
      panel_position_bottom = 1,
      panel_position_left = 2,
      panel_position_right = 3,
    };
    enum class error : uint32_t {
      error_invalid_argument = 0,
    };
    void set_panel_position(uint32_t position);
  };
  class weston_screensaver_t : public interface_core<weston_screensaver, 1> {
  public:
    using core_type = interface_core<weston_screensaver, 1>;
    static constexpr wl_interface const& interface = weston_screensaver_interface;

  public:
    weston_screensaver_t(weston_screensaver* src = nullptr)
      : core_type(src)
    {
    }
    weston_screensaver_t(weston_screensaver_t&& other)
      : core_type(std::move(other))
    {
    }
    ~weston_screensaver_t() override
    {
      if (this->pointer) {
        weston_screensaver_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    uint32_t get_version() {
      return weston_screensaver_get_version(this->pointer);
    }
    void* get_user_data() {
      return weston_screensaver_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      weston_screensaver_set_user_data(this->pointer, data);
    }

  public:
    void set_surface(wl_surface* surface, wl_output* output);
  };

  inline void weston_desktop_shell_t::set_background(wl_output* output, wl_surface* surface)
  {
    return (void) weston_desktop_shell_set_background(pointer, output, surface);
  }
  inline void weston_desktop_shell_t::set_panel(wl_output* output, wl_surface* surface)
  {
    return (void) weston_desktop_shell_set_panel(pointer, output, surface);
  }
  inline void weston_desktop_shell_t::set_lock_surface(wl_surface* surface)
  {
    return (void) weston_desktop_shell_set_lock_surface(pointer, surface);
  }
  inline void weston_desktop_shell_t::unlock()
  {
    return (void) weston_desktop_shell_unlock(pointer);
  }
  inline void weston_desktop_shell_t::set_grab_surface(wl_surface* surface)
  {
    return (void) weston_desktop_shell_set_grab_surface(pointer, surface);
  }
  inline void weston_desktop_shell_t::desktop_ready()
  {
    return (void) weston_desktop_shell_desktop_ready(pointer);
  }
  inline void weston_desktop_shell_t::set_panel_position(uint32_t position)
  {
    return (void) weston_desktop_shell_set_panel_position(pointer, position);
  }
  inline void weston_screensaver_t::set_surface(wl_surface* surface, wl_output* output)
  {
    return (void) weston_screensaver_set_surface(pointer, surface, output);
  }
}

#endif/*INCLUDE_WESTON_DESKTOP_CLIENT_HPP_7F070C0A_7C20_4956_92DD_A37A21DC4186*/
