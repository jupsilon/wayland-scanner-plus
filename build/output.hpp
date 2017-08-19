#ifndef INCLUDE_WAYLAND_CLIENT_HPP_EFC109BB_2C3C_4B28_B805_F26C8B22337A
#define INCLUDE_WAYLAND_CLIENT_HPP_EFC109BB_2C3C_4B28_B805_F26C8B22337A

namespace details // WIP
{
  class proxy {
  public:
    virtual ~proxy() { }
  };

  template <typename WL_C_STRUCT, size_t VERSION>
  class interface_core : public proxy {
  public:
    interface_core(WL_C_STRUCT* pointer)
      : pointer(pointer)
    {
    }

    interface_core(interface_core&& other)
      : pointer(other.pointer)
    {
    }

    interface_core(interface_core const&) = delete;
    interface_core& operator = (interface_core const&) = delete;

    ~interface_core() override {
      // should be overrided by "protocol destructor" (WIP)
      if (this->pointer) {
	wl_proxy_destroy(reinterpret_cast<wl_proxy*>(this->pointer));
      }
    }
    operator WL_C_STRUCT*() const { return this->pointer; }

  protected:
    WL_C_STRUCT* pointer;
  };
}

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
    std::function<void (nil*, uint32_t, char const*)> error;
    enum class error : uint32_t {
      invalid_object = 0,
      invalid_method = 1,
      no_memory = 2,
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
    }

  public:
    void* bind(uint32_t name)
    {
      return wl_registry_bind(pointer, name);
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
    }

  public:
    enum class error : uint32_t {
      invalid_format = 0,
      invalid_stride = 1,
      invalid_fd = 2,
    };
    enum class format : uint32_t {
      argb8888 = 0,
      xrgb8888 = 1,
      c8 = 0X20203843,
      rgb332 = 0X38424752,
      bgr233 = 0X38524742,
      xrgb4444 = 0X32315258,
      xbgr4444 = 0X32314258,
      rgbx4444 = 0X32315852,
      bgrx4444 = 0X32315842,
      argb4444 = 0X32315241,
      abgr4444 = 0X32314241,
      rgba4444 = 0X32314152,
      bgra4444 = 0X32314142,
      xrgb1555 = 0X35315258,
      xbgr1555 = 0X35314258,
      rgbx5551 = 0X35315852,
      bgrx5551 = 0X35315842,
      argb1555 = 0X35315241,
      abgr1555 = 0X35314241,
      rgba5551 = 0X35314152,
      bgra5551 = 0X35314142,
      rgb565 = 0X36314752,
      bgr565 = 0X36314742,
      rgb888 = 0X34324752,
      bgr888 = 0X34324742,
      xbgr8888 = 0X34324258,
      rgbx8888 = 0X34325852,
      bgrx8888 = 0X34325842,
      abgr8888 = 0X34324241,
      rgba8888 = 0X34324152,
      bgra8888 = 0X34324142,
      xrgb2101010 = 0X30335258,
      xbgr2101010 = 0X30334258,
      rgbx1010102 = 0X30335852,
      bgrx1010102 = 0X30335842,
      argb2101010 = 0X30335241,
      abgr2101010 = 0X30334241,
      rgba1010102 = 0X30334152,
      bgra1010102 = 0X30334142,
      yuyv = 0X56595559,
      yvyu = 0X55595659,
      uyvy = 0X59565955,
      vyuy = 0X59555956,
      ayuv = 0X56555941,
      nv12 = 0X3231564E,
      nv21 = 0X3132564E,
      nv16 = 0X3631564E,
      nv61 = 0X3136564E,
      yuv410 = 0X39565559,
      yvu410 = 0X39555659,
      yuv411 = 0X31315559,
      yvu411 = 0X31315659,
      yuv420 = 0X32315559,
      yvu420 = 0X32315659,
      yuv422 = 0X36315559,
      yvu422 = 0X36315659,
      yuv444 = 0X34325559,
      yvu444 = 0X34325659,
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
    }

  public:
    enum class error : uint32_t {
      invalid_finish = 0,
      invalid_action_mask = 1,
      invalid_action = 2,
      invalid_offer = 3,
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
    }

  public:
    enum class error : uint32_t {
      invalid_action_mask = 0,
      invalid_source = 1,
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
    }

  public:
    enum class error : uint32_t {
      role = 0,
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
      none = 0,
      copy = 1,
      move = 2,
      ask = 4,
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
    }

  public:
    enum class error : uint32_t {
      role = 0,
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
      none = 0,
      top = 1,
      bottom = 2,
      left = 4,
      top_left = 5,
      bottom_left = 6,
      right = 8,
      top_right = 9,
      bottom_right = 10,
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
      inactive = 0X1,
    };
    void set_transient(wl_surface* parent, int32_t x, int32_t y, uint32_t flags)
    {
      return wl_shell_surface_set_transient(pointer, parent, x, y, flags);
    }
    enum class fullscreen_method : uint32_t {
      default = 0,
      scale = 1,
      driver = 2,
      fill = 3,
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
    }

  public:
    enum class error : uint32_t {
      invalid_scale = 0,
      invalid_transform = 1,
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
    }

  public:
    enum class capability : uint32_t {
      pointer = 1,
      keyboard = 2,
      touch = 4,
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
    }

  public:
    enum class error : uint32_t {
      role = 0,
    };
    void set_cursor(uint32_t serial, wl_surface* surface, int32_t hotspot_x, int32_t hotspot_y)
    {
      return wl_pointer_set_cursor(pointer, serial, surface, hotspot_x, hotspot_y);
    }
    std::function<void (uint32_t, wl_surface*, fixed, fixed)> enter;
    std::function<void (uint32_t, wl_surface*)> leave;
    std::function<void (uint32_t, fixed, fixed)> motion;
    enum class button_state : uint32_t {
      released = 0,
      pressed = 1,
    };
    std::function<void (uint32_t, uint32_t, uint32_t, uint32_t)> button;
    enum class axis : uint32_t {
      vertical_scroll = 0,
      horizontal_scroll = 1,
    };
    std::function<void (uint32_t, uint32_t, fixed)> axis;
    void release()
    {
      return wl_pointer_release(pointer);
    }
    std::function<void ()> frame;
    enum class axis_source : uint32_t {
      wheel = 0,
      finger = 1,
      continuous = 2,
      wheel_tilt = 3,
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
    }

  public:
    enum class keymap_format : uint32_t {
      no_keymap = 0,
      xkb_v1 = 1,
    };
    std::function<void (uint32_t, int, uint32_t)> keymap;
    std::function<void (uint32_t, wl_surface*, chunk)> enter;
    std::function<void (uint32_t, wl_surface*)> leave;
    enum class key_state : uint32_t {
      released = 0,
      pressed = 1,
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
    }

  public:
    enum class subpixel : uint32_t {
      unknown = 0,
      none = 1,
      horizontal_rgb = 2,
      horizontal_bgr = 3,
      vertical_rgb = 4,
      vertical_bgr = 5,
    };
    enum class transform : uint32_t {
      normal = 0,
      90 = 1,
      180 = 2,
      270 = 3,
      flipped = 4,
      flipped_90 = 5,
      flipped_180 = 6,
      flipped_270 = 7,
    };
    std::function<void (int32_t, int32_t, int32_t, int32_t, int32_t, char const*, char const*, int32_t)> geometry;
    enum class mode : uint32_t {
      current = 0X1,
      preferred = 0X2,
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
    }

  public:
    void destroy()
    {
      return wl_subcompositor_destroy(pointer);
    }
    enum class error : uint32_t {
      bad_surface = 0,
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
    }

  public:
    void destroy()
    {
      return wl_subsurface_destroy(pointer);
    }
    enum class error : uint32_t {
      bad_surface = 0,
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

#endif/*INCLUDE_WAYLAND_CLIENT_HPP_EFC109BB_2C3C_4B28_B805_F26C8B22337A*/
