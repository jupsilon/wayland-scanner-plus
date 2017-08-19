#ifndef INCLUDE_WAYLAND_CLIENT_HPP_744AF533_069C_4A65_97CA_9F11CB059DC9
#define INCLUDE_WAYLAND_CLIENT_HPP_744AF533_069C_4A65_97CA_9F11CB059DC9

namespace wayland_client
{
  using namespace details;

  class wl_display_t : public interface_core<wl_display, 1> {
  public:
    using core_type = interface_core<wl_display, 1>;

  public:
    wl_display_t(wl_display* src)
      : core_type(src)
    {
    }
    wl_display_t(wl_display_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_display_t() override
    {
      if (this->pointer) {
        wl_display_disconnect(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    wl_callback* sync()
    {
      return wl_display_sync(pointer);
    }
    wl_registry* get_registry()
    {
      return wl_display_get_registry(pointer);
    }
    std::function<void (void*, uint32_t, char const*)> error;
    enum class error : uint32_t {
      error_invalid_object = 0,
      error_invalid_method = 1,
      error_no_memory = 2,
    };
    std::function<void (uint32_t)> delete_id;
  };
  class wl_registry_t : public interface_core<wl_registry, 1> {
  public:
    using core_type = interface_core<wl_registry, 1>;

  public:
    wl_registry_t(wl_registry* src)
      : core_type(src)
    {
    }
    wl_registry_t(wl_registry_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_registry_t() override
    {
      if (this->pointer) {
        wl_registry_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    void* bind(uint32_t name, wl_interface const* interface, uint32_t version)
    {
      return wl_registry_bind(pointer, name, interface, version);
    }
    std::function<void (uint32_t, char const*, uint32_t)> global;
    std::function<void (uint32_t)> global_remove;
  };
  class wl_callback_t : public interface_core<wl_callback, 1> {
  public:
    using core_type = interface_core<wl_callback, 1>;

  public:
    wl_callback_t(wl_callback* src)
      : core_type(src)
    {
    }
    wl_callback_t(wl_callback_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_callback_t() override
    {
      if (this->pointer) {
        wl_callback_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    std::function<void (uint32_t)> done;
  };
  class wl_compositor_t : public interface_core<wl_compositor, 4> {
  public:
    using core_type = interface_core<wl_compositor, 4>;

  public:
    wl_compositor_t(wl_compositor* src)
      : core_type(src)
    {
    }
    wl_compositor_t(wl_compositor_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_compositor_t() override
    {
      if (this->pointer) {
        wl_compositor_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    wl_surface* create_surface()
    {
      return wl_compositor_create_surface(pointer);
    }
    wl_region* create_region()
    {
      return wl_compositor_create_region(pointer);
    }
  };
  class wl_shm_pool_t : public interface_core<wl_shm_pool, 1> {
  public:
    using core_type = interface_core<wl_shm_pool, 1>;

  public:
    wl_shm_pool_t(wl_shm_pool* src)
      : core_type(src)
    {
    }
    wl_shm_pool_t(wl_shm_pool_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_shm_pool_t() override
    {
      if (this->pointer) {
        wl_shm_pool_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    wl_buffer* create_buffer(int32_t offset, int32_t width, int32_t height, int32_t stride, uint32_t format)
    {
      return wl_shm_pool_create_buffer(pointer, offset, width, height, stride, format);
    }
    void destroy()
    {
      return wl_shm_pool_destroy(pointer);
    }
    void resize(int32_t size)
    {
      return wl_shm_pool_resize(pointer, size);
    }
  };
  class wl_shm_t : public interface_core<wl_shm, 1> {
  public:
    using core_type = interface_core<wl_shm, 1>;

  public:
    wl_shm_t(wl_shm* src)
      : core_type(src)
    {
    }
    wl_shm_t(wl_shm_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_shm_t() override
    {
      if (this->pointer) {
        wl_shm_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class error : uint32_t {
      error_invalid_format = 0,
      error_invalid_stride = 1,
      error_invalid_fd = 2,
    };
    enum class format : uint32_t {
      format_argb8888 = 0,
      format_xrgb8888 = 1,
      format_c8 = 0X20203843,
      format_rgb332 = 0X38424752,
      format_bgr233 = 0X38524742,
      format_xrgb4444 = 0X32315258,
      format_xbgr4444 = 0X32314258,
      format_rgbx4444 = 0X32315852,
      format_bgrx4444 = 0X32315842,
      format_argb4444 = 0X32315241,
      format_abgr4444 = 0X32314241,
      format_rgba4444 = 0X32314152,
      format_bgra4444 = 0X32314142,
      format_xrgb1555 = 0X35315258,
      format_xbgr1555 = 0X35314258,
      format_rgbx5551 = 0X35315852,
      format_bgrx5551 = 0X35315842,
      format_argb1555 = 0X35315241,
      format_abgr1555 = 0X35314241,
      format_rgba5551 = 0X35314152,
      format_bgra5551 = 0X35314142,
      format_rgb565 = 0X36314752,
      format_bgr565 = 0X36314742,
      format_rgb888 = 0X34324752,
      format_bgr888 = 0X34324742,
      format_xbgr8888 = 0X34324258,
      format_rgbx8888 = 0X34325852,
      format_bgrx8888 = 0X34325842,
      format_abgr8888 = 0X34324241,
      format_rgba8888 = 0X34324152,
      format_bgra8888 = 0X34324142,
      format_xrgb2101010 = 0X30335258,
      format_xbgr2101010 = 0X30334258,
      format_rgbx1010102 = 0X30335852,
      format_bgrx1010102 = 0X30335842,
      format_argb2101010 = 0X30335241,
      format_abgr2101010 = 0X30334241,
      format_rgba1010102 = 0X30334152,
      format_bgra1010102 = 0X30334142,
      format_yuyv = 0X56595559,
      format_yvyu = 0X55595659,
      format_uyvy = 0X59565955,
      format_vyuy = 0X59555956,
      format_ayuv = 0X56555941,
      format_nv12 = 0X3231564E,
      format_nv21 = 0X3132564E,
      format_nv16 = 0X3631564E,
      format_nv61 = 0X3136564E,
      format_yuv410 = 0X39565559,
      format_yvu410 = 0X39555659,
      format_yuv411 = 0X31315559,
      format_yvu411 = 0X31315659,
      format_yuv420 = 0X32315559,
      format_yvu420 = 0X32315659,
      format_yuv422 = 0X36315559,
      format_yvu422 = 0X36315659,
      format_yuv444 = 0X34325559,
      format_yvu444 = 0X34325659,
    };
    wl_shm_pool* create_pool(int fd, int32_t size)
    {
      return wl_shm_create_pool(pointer, fd, size);
    }
    std::function<void (uint32_t)> format;
  };
  class wl_buffer_t : public interface_core<wl_buffer, 1> {
  public:
    using core_type = interface_core<wl_buffer, 1>;

  public:
    wl_buffer_t(wl_buffer* src)
      : core_type(src)
    {
    }
    wl_buffer_t(wl_buffer_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_buffer_t() override
    {
      if (this->pointer) {
        wl_buffer_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    void destroy()
    {
      return wl_buffer_destroy(pointer);
    }
    std::function<void ()> release;
  };
  class wl_data_offer_t : public interface_core<wl_data_offer, 3> {
  public:
    using core_type = interface_core<wl_data_offer, 3>;

  public:
    wl_data_offer_t(wl_data_offer* src)
      : core_type(src)
    {
    }
    wl_data_offer_t(wl_data_offer_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_data_offer_t() override
    {
      if (this->pointer) {
        wl_data_offer_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class error : uint32_t {
      error_invalid_finish = 0,
      error_invalid_action_mask = 1,
      error_invalid_action = 2,
      error_invalid_offer = 3,
    };
    void accept(uint32_t serial, char const* mime_type)
    {
      return wl_data_offer_accept(pointer, serial, mime_type);
    }
    void receive(char const* mime_type, int fd)
    {
      return wl_data_offer_receive(pointer, mime_type, fd);
    }
    void destroy()
    {
      return wl_data_offer_destroy(pointer);
    }
    std::function<void (char const*)> offer;
    void finish()
    {
      return wl_data_offer_finish(pointer);
    }
    void set_actions(uint32_t dnd_actions, uint32_t preferred_action)
    {
      return wl_data_offer_set_actions(pointer, dnd_actions, preferred_action);
    }
    std::function<void (uint32_t)> source_actions;
    std::function<void (uint32_t)> action;
  };
  class wl_data_source_t : public interface_core<wl_data_source, 3> {
  public:
    using core_type = interface_core<wl_data_source, 3>;

  public:
    wl_data_source_t(wl_data_source* src)
      : core_type(src)
    {
    }
    wl_data_source_t(wl_data_source_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_data_source_t() override
    {
      if (this->pointer) {
        wl_data_source_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class error : uint32_t {
      error_invalid_action_mask = 0,
      error_invalid_source = 1,
    };
    void offer(char const* mime_type)
    {
      return wl_data_source_offer(pointer, mime_type);
    }
    void destroy()
    {
      return wl_data_source_destroy(pointer);
    }
    std::function<void (char const*)> target;
    std::function<void (char const*, int)> send;
    std::function<void ()> cancelled;
    void set_actions(uint32_t dnd_actions)
    {
      return wl_data_source_set_actions(pointer, dnd_actions);
    }
    std::function<void ()> dnd_drop_performed;
    std::function<void ()> dnd_finished;
    std::function<void (uint32_t)> action;
  };
  class wl_data_device_t : public interface_core<wl_data_device, 3> {
  public:
    using core_type = interface_core<wl_data_device, 3>;

  public:
    wl_data_device_t(wl_data_device* src)
      : core_type(src)
    {
    }
    wl_data_device_t(wl_data_device_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_data_device_t() override
    {
      if (this->pointer) {
        wl_data_device_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class error : uint32_t {
      error_role = 0,
    };
    void start_drag(wl_data_source* source, wl_surface* origin, wl_surface* icon, uint32_t serial)
    {
      return wl_data_device_start_drag(pointer, source, origin, icon, serial);
    }
    void set_selection(wl_data_source* source, uint32_t serial)
    {
      return wl_data_device_set_selection(pointer, source, serial);
    }
    std::function<void ()> data_offer;
    std::function<void (uint32_t, wl_surface*, fixed, fixed, wl_data_offer*)> enter;
    std::function<void ()> leave;
    std::function<void (uint32_t, fixed, fixed)> motion;
    std::function<void ()> drop;
    std::function<void (wl_data_offer*)> selection;
    void release()
    {
      return wl_data_device_release(pointer);
    }
  };
  class wl_data_device_manager_t : public interface_core<wl_data_device_manager, 3> {
  public:
    using core_type = interface_core<wl_data_device_manager, 3>;

  public:
    wl_data_device_manager_t(wl_data_device_manager* src)
      : core_type(src)
    {
    }
    wl_data_device_manager_t(wl_data_device_manager_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_data_device_manager_t() override
    {
      if (this->pointer) {
        wl_data_device_manager_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    wl_data_source* create_data_source()
    {
      return wl_data_device_manager_create_data_source(pointer);
    }
    wl_data_device* get_data_device(wl_seat* seat)
    {
      return wl_data_device_manager_get_data_device(pointer, seat);
    }
    enum class dnd_action : uint32_t {
      dnd_action_none = 0,
      dnd_action_copy = 1,
      dnd_action_move = 2,
      dnd_action_ask = 4,
    };
  };
  class wl_shell_t : public interface_core<wl_shell, 1> {
  public:
    using core_type = interface_core<wl_shell, 1>;

  public:
    wl_shell_t(wl_shell* src)
      : core_type(src)
    {
    }
    wl_shell_t(wl_shell_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_shell_t() override
    {
      if (this->pointer) {
        wl_shell_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class error : uint32_t {
      error_role = 0,
    };
    wl_shell_surface* get_shell_surface(wl_surface* surface)
    {
      return wl_shell_get_shell_surface(pointer, surface);
    }
  };
  class wl_shell_surface_t : public interface_core<wl_shell_surface, 1> {
  public:
    using core_type = interface_core<wl_shell_surface, 1>;

  public:
    wl_shell_surface_t(wl_shell_surface* src)
      : core_type(src)
    {
    }
    wl_shell_surface_t(wl_shell_surface_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_shell_surface_t() override
    {
      if (this->pointer) {
        wl_shell_surface_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    void pong(uint32_t serial)
    {
      return wl_shell_surface_pong(pointer, serial);
    }
    void move(wl_seat* seat, uint32_t serial)
    {
      return wl_shell_surface_move(pointer, seat, serial);
    }
    enum class resize : uint32_t {
      resize_none = 0,
      resize_top = 1,
      resize_bottom = 2,
      resize_left = 4,
      resize_top_left = 5,
      resize_bottom_left = 6,
      resize_right = 8,
      resize_top_right = 9,
      resize_bottom_right = 10,
    };
    void resize(wl_seat* seat, uint32_t serial, uint32_t edges)
    {
      return wl_shell_surface_resize(pointer, seat, serial, edges);
    }
    void set_toplevel()
    {
      return wl_shell_surface_set_toplevel(pointer);
    }
    enum class transient : uint32_t {
      transient_inactive = 0X1,
    };
    void set_transient(wl_surface* parent, int32_t x, int32_t y, uint32_t flags)
    {
      return wl_shell_surface_set_transient(pointer, parent, x, y, flags);
    }
    enum class fullscreen_method : uint32_t {
      fullscreen_method_default = 0,
      fullscreen_method_scale = 1,
      fullscreen_method_driver = 2,
      fullscreen_method_fill = 3,
    };
    void set_fullscreen(uint32_t method, uint32_t framerate, wl_output* output)
    {
      return wl_shell_surface_set_fullscreen(pointer, method, framerate, output);
    }
    void set_popup(wl_seat* seat, uint32_t serial, wl_surface* parent, int32_t x, int32_t y, uint32_t flags)
    {
      return wl_shell_surface_set_popup(pointer, seat, serial, parent, x, y, flags);
    }
    void set_maximized(wl_output* output)
    {
      return wl_shell_surface_set_maximized(pointer, output);
    }
    void set_title(char const* title)
    {
      return wl_shell_surface_set_title(pointer, title);
    }
    void set_class(char const* class_)
    {
      return wl_shell_surface_set_class(pointer, class_);
    }
    std::function<void (uint32_t)> ping;
    std::function<void (uint32_t, int32_t, int32_t)> configure;
    std::function<void ()> popup_done;
  };
  class wl_surface_t : public interface_core<wl_surface, 4> {
  public:
    using core_type = interface_core<wl_surface, 4>;

  public:
    wl_surface_t(wl_surface* src)
      : core_type(src)
    {
    }
    wl_surface_t(wl_surface_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_surface_t() override
    {
      if (this->pointer) {
        wl_surface_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class error : uint32_t {
      error_invalid_scale = 0,
      error_invalid_transform = 1,
    };
    void destroy()
    {
      return wl_surface_destroy(pointer);
    }
    void attach(wl_buffer* buffer, int32_t x, int32_t y)
    {
      return wl_surface_attach(pointer, buffer, x, y);
    }
    void damage(int32_t x, int32_t y, int32_t width, int32_t height)
    {
      return wl_surface_damage(pointer, x, y, width, height);
    }
    wl_callback* frame()
    {
      return wl_surface_frame(pointer);
    }
    void set_opaque_region(wl_region* region)
    {
      return wl_surface_set_opaque_region(pointer, region);
    }
    void set_input_region(wl_region* region)
    {
      return wl_surface_set_input_region(pointer, region);
    }
    void commit()
    {
      return wl_surface_commit(pointer);
    }
    std::function<void (wl_output*)> enter;
    std::function<void (wl_output*)> leave;
    void set_buffer_transform(int32_t transform)
    {
      return wl_surface_set_buffer_transform(pointer, transform);
    }
    void set_buffer_scale(int32_t scale)
    {
      return wl_surface_set_buffer_scale(pointer, scale);
    }
    void damage_buffer(int32_t x, int32_t y, int32_t width, int32_t height)
    {
      return wl_surface_damage_buffer(pointer, x, y, width, height);
    }
  };
  class wl_seat_t : public interface_core<wl_seat, 6> {
  public:
    using core_type = interface_core<wl_seat, 6>;

  public:
    wl_seat_t(wl_seat* src)
      : core_type(src)
    {
    }
    wl_seat_t(wl_seat_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_seat_t() override
    {
      if (this->pointer) {
        wl_seat_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class capability : uint32_t {
      capability_pointer = 1,
      capability_keyboard = 2,
      capability_touch = 4,
    };
    std::function<void (uint32_t)> capabilities;
    wl_pointer* get_pointer()
    {
      return wl_seat_get_pointer(pointer);
    }
    wl_keyboard* get_keyboard()
    {
      return wl_seat_get_keyboard(pointer);
    }
    wl_touch* get_touch()
    {
      return wl_seat_get_touch(pointer);
    }
    std::function<void (char const*)> name;
    void release()
    {
      return wl_seat_release(pointer);
    }
  };
  class wl_pointer_t : public interface_core<wl_pointer, 6> {
  public:
    using core_type = interface_core<wl_pointer, 6>;

  public:
    wl_pointer_t(wl_pointer* src)
      : core_type(src)
    {
    }
    wl_pointer_t(wl_pointer_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_pointer_t() override
    {
      if (this->pointer) {
        wl_pointer_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class error : uint32_t {
      error_role = 0,
    };
    void set_cursor(uint32_t serial, wl_surface* surface, int32_t hotspot_x, int32_t hotspot_y)
    {
      return wl_pointer_set_cursor(pointer, serial, surface, hotspot_x, hotspot_y);
    }
    std::function<void (uint32_t, wl_surface*, fixed, fixed)> enter;
    std::function<void (uint32_t, wl_surface*)> leave;
    std::function<void (uint32_t, fixed, fixed)> motion;
    enum class button_state : uint32_t {
      button_state_released = 0,
      button_state_pressed = 1,
    };
    std::function<void (uint32_t, uint32_t, uint32_t, uint32_t)> button;
    enum class axis : uint32_t {
      axis_vertical_scroll = 0,
      axis_horizontal_scroll = 1,
    };
    std::function<void (uint32_t, uint32_t, fixed)> axis;
    void release()
    {
      return wl_pointer_release(pointer);
    }
    std::function<void ()> frame;
    enum class axis_source : uint32_t {
      axis_source_wheel = 0,
      axis_source_finger = 1,
      axis_source_continuous = 2,
      axis_source_wheel_tilt = 3,
    };
    std::function<void (uint32_t)> axis_source;
    std::function<void (uint32_t, uint32_t)> axis_stop;
    std::function<void (uint32_t, int32_t)> axis_discrete;
  };
  class wl_keyboard_t : public interface_core<wl_keyboard, 6> {
  public:
    using core_type = interface_core<wl_keyboard, 6>;

  public:
    wl_keyboard_t(wl_keyboard* src)
      : core_type(src)
    {
    }
    wl_keyboard_t(wl_keyboard_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_keyboard_t() override
    {
      if (this->pointer) {
        wl_keyboard_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class keymap_format : uint32_t {
      keymap_format_no_keymap = 0,
      keymap_format_xkb_v1 = 1,
    };
    std::function<void (uint32_t, int, uint32_t)> keymap;
    std::function<void (uint32_t, wl_surface*, chunk)> enter;
    std::function<void (uint32_t, wl_surface*)> leave;
    enum class key_state : uint32_t {
      key_state_released = 0,
      key_state_pressed = 1,
    };
    std::function<void (uint32_t, uint32_t, uint32_t, uint32_t)> key;
    std::function<void (uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)> modifiers;
    void release()
    {
      return wl_keyboard_release(pointer);
    }
    std::function<void (int32_t, int32_t)> repeat_info;
  };
  class wl_touch_t : public interface_core<wl_touch, 6> {
  public:
    using core_type = interface_core<wl_touch, 6>;

  public:
    wl_touch_t(wl_touch* src)
      : core_type(src)
    {
    }
    wl_touch_t(wl_touch_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_touch_t() override
    {
      if (this->pointer) {
        wl_touch_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    std::function<void (uint32_t, uint32_t, wl_surface*, int32_t, fixed, fixed)> down;
    std::function<void (uint32_t, uint32_t, int32_t)> up;
    std::function<void (uint32_t, int32_t, fixed, fixed)> motion;
    std::function<void ()> frame;
    std::function<void ()> cancel;
    void release()
    {
      return wl_touch_release(pointer);
    }
    std::function<void (int32_t, fixed, fixed)> shape;
    std::function<void (int32_t, fixed)> orientation;
  };
  class wl_output_t : public interface_core<wl_output, 3> {
  public:
    using core_type = interface_core<wl_output, 3>;

  public:
    wl_output_t(wl_output* src)
      : core_type(src)
    {
    }
    wl_output_t(wl_output_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_output_t() override
    {
      if (this->pointer) {
        wl_output_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    enum class subpixel : uint32_t {
      subpixel_unknown = 0,
      subpixel_none = 1,
      subpixel_horizontal_rgb = 2,
      subpixel_horizontal_bgr = 3,
      subpixel_vertical_rgb = 4,
      subpixel_vertical_bgr = 5,
    };
    enum class transform : uint32_t {
      transform_normal = 0,
      transform_90 = 1,
      transform_180 = 2,
      transform_270 = 3,
      transform_flipped = 4,
      transform_flipped_90 = 5,
      transform_flipped_180 = 6,
      transform_flipped_270 = 7,
    };
    std::function<void (int32_t, int32_t, int32_t, int32_t, int32_t, char const*, char const*, int32_t)> geometry;
    enum class mode : uint32_t {
      mode_current = 0X1,
      mode_preferred = 0X2,
    };
    std::function<void (uint32_t, int32_t, int32_t, int32_t)> mode;
    std::function<void ()> done;
    std::function<void (int32_t)> scale;
    void release()
    {
      return wl_output_release(pointer);
    }
  };
  class wl_region_t : public interface_core<wl_region, 1> {
  public:
    using core_type = interface_core<wl_region, 1>;

  public:
    wl_region_t(wl_region* src)
      : core_type(src)
    {
    }
    wl_region_t(wl_region_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_region_t() override
    {
      if (this->pointer) {
        wl_region_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    void destroy()
    {
      return wl_region_destroy(pointer);
    }
    void add(int32_t x, int32_t y, int32_t width, int32_t height)
    {
      return wl_region_add(pointer, x, y, width, height);
    }
    void subtract(int32_t x, int32_t y, int32_t width, int32_t height)
    {
      return wl_region_subtract(pointer, x, y, width, height);
    }
  };
  class wl_subcompositor_t : public interface_core<wl_subcompositor, 1> {
  public:
    using core_type = interface_core<wl_subcompositor, 1>;

  public:
    wl_subcompositor_t(wl_subcompositor* src)
      : core_type(src)
    {
    }
    wl_subcompositor_t(wl_subcompositor_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_subcompositor_t() override
    {
      if (this->pointer) {
        wl_subcompositor_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    void destroy()
    {
      return wl_subcompositor_destroy(pointer);
    }
    enum class error : uint32_t {
      error_bad_surface = 0,
    };
    wl_subsurface* get_subsurface(wl_surface* surface, wl_surface* parent)
    {
      return wl_subcompositor_get_subsurface(pointer, surface, parent);
    }
  };
  class wl_subsurface_t : public interface_core<wl_subsurface, 1> {
  public:
    using core_type = interface_core<wl_subsurface, 1>;

  public:
    wl_subsurface_t(wl_subsurface* src)
      : core_type(src)
    {
    }
    wl_subsurface_t(wl_subsurface_t&& other)
      : core_type(std::move(other))
    {
    }
    ~wl_subsurface_t() override
    {
      if (this->pointer) {
        wl_subsurface_destroy(this->pointer);
	this->pointer = nullptr;
      }
    }

  public:
    void destroy()
    {
      return wl_subsurface_destroy(pointer);
    }
    enum class error : uint32_t {
      error_bad_surface = 0,
    };
    void set_position(int32_t x, int32_t y)
    {
      return wl_subsurface_set_position(pointer, x, y);
    }
    void place_above(wl_surface* sibling)
    {
      return wl_subsurface_place_above(pointer, sibling);
    }
    void place_below(wl_surface* sibling)
    {
      return wl_subsurface_place_below(pointer, sibling);
    }
    void set_sync()
    {
      return wl_subsurface_set_sync(pointer);
    }
    void set_desync()
    {
      return wl_subsurface_set_desync(pointer);
    }
  };
}

#endif/*INCLUDE_WAYLAND_CLIENT_HPP_744AF533_069C_4A65_97CA_9F11CB059DC9*/
