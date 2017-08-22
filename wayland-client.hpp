#ifndef INCLUDE_WAYLAND_CLIENT_HPP_6E8C5DC8_1FE5_40D9_95F1_FD32DE74492C
#define INCLUDE_WAYLAND_CLIENT_HPP_6E8C5DC8_1FE5_40D9_95F1_FD32DE74492C

#include <functional>

#include "wayland-client-core.hpp"

namespace wayland_client
{
  using namespace wayland_client_core::details;

  class wl_display_t;
  class wl_registry_t;
  class wl_callback_t;
  class wl_compositor_t;
  class wl_shm_pool_t;
  class wl_shm_t;
  class wl_buffer_t;
  class wl_data_offer_t;
  class wl_data_source_t;
  class wl_data_device_t;
  class wl_data_device_manager_t;
  class wl_shell_t;
  class wl_shell_surface_t;
  class wl_surface_t;
  class wl_seat_t;
  class wl_pointer_t;
  class wl_keyboard_t;
  class wl_touch_t;
  class wl_output_t;
  class wl_region_t;
  class wl_subcompositor_t;
  class wl_subsurface_t;

  class wl_display_t : public interface_core<wl_display, 1> {
  public:
    using core_type = interface_core<wl_display, 1>;
    static constexpr wl_interface const& interface = wl_display_interface;

  public:
    wl_display_t(wl_display* src = nullptr)
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
    uint32_t get_version() {
      return wl_display_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_display_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_display_set_user_data(this->pointer, data);
    }

  public:
    wl_callback_t sync();
    wl_registry_t get_registry();
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
    static constexpr wl_interface const& interface = wl_registry_interface;

  public:
    wl_registry_t(wl_registry* src = nullptr)
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
    uint32_t get_version() {
      return wl_registry_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_registry_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_registry_set_user_data(this->pointer, data);
    }

  public:
    void* bind(uint32_t name, wl_interface const* interface, uint32_t version);
    std::function<void (uint32_t, char const*, uint32_t)> global;
    std::function<void (uint32_t)> global_remove;
  };
  class wl_callback_t : public interface_core<wl_callback, 1> {
  public:
    using core_type = interface_core<wl_callback, 1>;
    static constexpr wl_interface const& interface = wl_callback_interface;

  public:
    wl_callback_t(wl_callback* src = nullptr)
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
    uint32_t get_version() {
      return wl_callback_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_callback_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_callback_set_user_data(this->pointer, data);
    }

  public:
    std::function<void (uint32_t)> done;
  };
  class wl_compositor_t : public interface_core<wl_compositor, 4> {
  public:
    using core_type = interface_core<wl_compositor, 4>;
    static constexpr wl_interface const& interface = wl_compositor_interface;

  public:
    wl_compositor_t(wl_compositor* src = nullptr)
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
    uint32_t get_version() {
      return wl_compositor_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_compositor_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_compositor_set_user_data(this->pointer, data);
    }

  public:
    wl_surface_t create_surface();
    wl_region_t create_region();
  };
  class wl_shm_pool_t : public interface_core<wl_shm_pool, 1> {
  public:
    using core_type = interface_core<wl_shm_pool, 1>;
    static constexpr wl_interface const& interface = wl_shm_pool_interface;

  public:
    wl_shm_pool_t(wl_shm_pool* src = nullptr)
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
    uint32_t get_version() {
      return wl_shm_pool_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_shm_pool_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_shm_pool_set_user_data(this->pointer, data);
    }

  public:
    wl_buffer_t create_buffer(int32_t offset, int32_t width, int32_t height, int32_t stride, uint32_t format);
    void destroy();
    void resize(int32_t size);
  };
  class wl_shm_t : public interface_core<wl_shm, 1> {
  public:
    using core_type = interface_core<wl_shm, 1>;
    static constexpr wl_interface const& interface = wl_shm_interface;

  public:
    wl_shm_t(wl_shm* src = nullptr)
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
    uint32_t get_version() {
      return wl_shm_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_shm_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_shm_set_user_data(this->pointer, data);
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
    wl_shm_pool_t create_pool(int fd, int32_t size);
    std::function<void (uint32_t)> format;
  };
  class wl_buffer_t : public interface_core<wl_buffer, 1> {
  public:
    using core_type = interface_core<wl_buffer, 1>;
    static constexpr wl_interface const& interface = wl_buffer_interface;

  public:
    wl_buffer_t(wl_buffer* src = nullptr)
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
    uint32_t get_version() {
      return wl_buffer_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_buffer_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_buffer_set_user_data(this->pointer, data);
    }

  public:
    void destroy();
    std::function<void ()> release;
  };
  class wl_data_offer_t : public interface_core<wl_data_offer, 3> {
  public:
    using core_type = interface_core<wl_data_offer, 3>;
    static constexpr wl_interface const& interface = wl_data_offer_interface;

  public:
    wl_data_offer_t(wl_data_offer* src = nullptr)
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
    uint32_t get_version() {
      return wl_data_offer_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_data_offer_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_data_offer_set_user_data(this->pointer, data);
    }

  public:
    enum class error : uint32_t {
      error_invalid_finish = 0,
      error_invalid_action_mask = 1,
      error_invalid_action = 2,
      error_invalid_offer = 3,
    };
    void accept(uint32_t serial, char const* mime_type);
    void receive(char const* mime_type, int fd);
    void destroy();
    std::function<void (char const*)> offer;
    void finish();
    void set_actions(uint32_t dnd_actions, uint32_t preferred_action);
    std::function<void (uint32_t)> source_actions;
    std::function<void (uint32_t)> action;
  };
  class wl_data_source_t : public interface_core<wl_data_source, 3> {
  public:
    using core_type = interface_core<wl_data_source, 3>;
    static constexpr wl_interface const& interface = wl_data_source_interface;

  public:
    wl_data_source_t(wl_data_source* src = nullptr)
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
    uint32_t get_version() {
      return wl_data_source_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_data_source_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_data_source_set_user_data(this->pointer, data);
    }

  public:
    enum class error : uint32_t {
      error_invalid_action_mask = 0,
      error_invalid_source = 1,
    };
    void offer(char const* mime_type);
    void destroy();
    std::function<void (char const*)> target;
    std::function<void (char const*, int)> send;
    std::function<void ()> cancelled;
    void set_actions(uint32_t dnd_actions);
    std::function<void ()> dnd_drop_performed;
    std::function<void ()> dnd_finished;
    std::function<void (uint32_t)> action;
  };
  class wl_data_device_t : public interface_core<wl_data_device, 3> {
  public:
    using core_type = interface_core<wl_data_device, 3>;
    static constexpr wl_interface const& interface = wl_data_device_interface;

  public:
    wl_data_device_t(wl_data_device* src = nullptr)
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
    uint32_t get_version() {
      return wl_data_device_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_data_device_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_data_device_set_user_data(this->pointer, data);
    }

  public:
    enum class error : uint32_t {
      error_role = 0,
    };
    void start_drag(wl_data_source* source, wl_surface* origin, wl_surface* icon, uint32_t serial);
    void set_selection(wl_data_source* source, uint32_t serial);
    std::function<void ()> data_offer;
    std::function<void (uint32_t, wl_surface*, fixed, fixed, wl_data_offer*)> enter;
    std::function<void ()> leave;
    std::function<void (uint32_t, fixed, fixed)> motion;
    std::function<void ()> drop;
    std::function<void (wl_data_offer*)> selection;
    void release();
  };
  class wl_data_device_manager_t : public interface_core<wl_data_device_manager, 3> {
  public:
    using core_type = interface_core<wl_data_device_manager, 3>;
    static constexpr wl_interface const& interface = wl_data_device_manager_interface;

  public:
    wl_data_device_manager_t(wl_data_device_manager* src = nullptr)
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
    uint32_t get_version() {
      return wl_data_device_manager_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_data_device_manager_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_data_device_manager_set_user_data(this->pointer, data);
    }

  public:
    wl_data_source_t create_data_source();
    wl_data_device_t get_data_device(wl_seat* seat);
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
    static constexpr wl_interface const& interface = wl_shell_interface;

  public:
    wl_shell_t(wl_shell* src = nullptr)
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
    uint32_t get_version() {
      return wl_shell_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_shell_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_shell_set_user_data(this->pointer, data);
    }

  public:
    enum class error : uint32_t {
      error_role = 0,
    };
    wl_shell_surface_t get_shell_surface(wl_surface* surface);
  };
  class wl_shell_surface_t : public interface_core<wl_shell_surface, 1> {
  public:
    using core_type = interface_core<wl_shell_surface, 1>;
    static constexpr wl_interface const& interface = wl_shell_surface_interface;

  public:
    wl_shell_surface_t(wl_shell_surface* src = nullptr)
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
    uint32_t get_version() {
      return wl_shell_surface_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_shell_surface_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_shell_surface_set_user_data(this->pointer, data);
    }

  public:
    void pong(uint32_t serial);
    void move(wl_seat* seat, uint32_t serial);
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
    void resize(wl_seat* seat, uint32_t serial, uint32_t edges);
    void set_toplevel();
    enum class transient : uint32_t {
      transient_inactive = 0X1,
    };
    void set_transient(wl_surface* parent, int32_t x, int32_t y, uint32_t flags);
    enum class fullscreen_method : uint32_t {
      fullscreen_method_default = 0,
      fullscreen_method_scale = 1,
      fullscreen_method_driver = 2,
      fullscreen_method_fill = 3,
    };
    void set_fullscreen(uint32_t method, uint32_t framerate, wl_output* output);
    void set_popup(wl_seat* seat, uint32_t serial, wl_surface* parent, int32_t x, int32_t y, uint32_t flags);
    void set_maximized(wl_output* output);
    void set_title(char const* title);
    void set_class(char const* class_);
    std::function<void (uint32_t)> ping;
    std::function<void (uint32_t, int32_t, int32_t)> configure;
    std::function<void ()> popup_done;
  };
  class wl_surface_t : public interface_core<wl_surface, 4> {
  public:
    using core_type = interface_core<wl_surface, 4>;
    static constexpr wl_interface const& interface = wl_surface_interface;

  public:
    wl_surface_t(wl_surface* src = nullptr)
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
    uint32_t get_version() {
      return wl_surface_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_surface_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_surface_set_user_data(this->pointer, data);
    }

  public:
    enum class error : uint32_t {
      error_invalid_scale = 0,
      error_invalid_transform = 1,
    };
    void destroy();
    void attach(wl_buffer* buffer, int32_t x, int32_t y);
    void damage(int32_t x, int32_t y, int32_t width, int32_t height);
    wl_callback_t frame();
    void set_opaque_region(wl_region* region);
    void set_input_region(wl_region* region);
    void commit();
    std::function<void (wl_output*)> enter;
    std::function<void (wl_output*)> leave;
    void set_buffer_transform(int32_t transform);
    void set_buffer_scale(int32_t scale);
    void damage_buffer(int32_t x, int32_t y, int32_t width, int32_t height);
  };
  class wl_seat_t : public interface_core<wl_seat, 6> {
  public:
    using core_type = interface_core<wl_seat, 6>;
    static constexpr wl_interface const& interface = wl_seat_interface;

  public:
    wl_seat_t(wl_seat* src = nullptr)
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
    uint32_t get_version() {
      return wl_seat_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_seat_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_seat_set_user_data(this->pointer, data);
    }

  public:
    enum class capability : uint32_t {
      capability_pointer = 1,
      capability_keyboard = 2,
      capability_touch = 4,
    };
    std::function<void (uint32_t)> capabilities;
    wl_pointer_t get_pointer();
    wl_keyboard_t get_keyboard();
    wl_touch_t get_touch();
    std::function<void (char const*)> name;
    void release();
  };
  class wl_pointer_t : public interface_core<wl_pointer, 6> {
  public:
    using core_type = interface_core<wl_pointer, 6>;
    static constexpr wl_interface const& interface = wl_pointer_interface;

  public:
    wl_pointer_t(wl_pointer* src = nullptr)
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
    uint32_t get_version() {
      return wl_pointer_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_pointer_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_pointer_set_user_data(this->pointer, data);
    }

  public:
    enum class error : uint32_t {
      error_role = 0,
    };
    void set_cursor(uint32_t serial, wl_surface* surface, int32_t hotspot_x, int32_t hotspot_y);
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
    void release();
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
    static constexpr wl_interface const& interface = wl_keyboard_interface;

  public:
    wl_keyboard_t(wl_keyboard* src = nullptr)
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
    uint32_t get_version() {
      return wl_keyboard_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_keyboard_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_keyboard_set_user_data(this->pointer, data);
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
    void release();
    std::function<void (int32_t, int32_t)> repeat_info;
  };
  class wl_touch_t : public interface_core<wl_touch, 6> {
  public:
    using core_type = interface_core<wl_touch, 6>;
    static constexpr wl_interface const& interface = wl_touch_interface;

  public:
    wl_touch_t(wl_touch* src = nullptr)
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
    uint32_t get_version() {
      return wl_touch_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_touch_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_touch_set_user_data(this->pointer, data);
    }

  public:
    std::function<void (uint32_t, uint32_t, wl_surface*, int32_t, fixed, fixed)> down;
    std::function<void (uint32_t, uint32_t, int32_t)> up;
    std::function<void (uint32_t, int32_t, fixed, fixed)> motion;
    std::function<void ()> frame;
    std::function<void ()> cancel;
    void release();
    std::function<void (int32_t, fixed, fixed)> shape;
    std::function<void (int32_t, fixed)> orientation;
  };
  class wl_output_t : public interface_core<wl_output, 3> {
  public:
    using core_type = interface_core<wl_output, 3>;
    static constexpr wl_interface const& interface = wl_output_interface;

  public:
    wl_output_t(wl_output* src = nullptr)
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
    uint32_t get_version() {
      return wl_output_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_output_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_output_set_user_data(this->pointer, data);
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
    void release();
  };
  class wl_region_t : public interface_core<wl_region, 1> {
  public:
    using core_type = interface_core<wl_region, 1>;
    static constexpr wl_interface const& interface = wl_region_interface;

  public:
    wl_region_t(wl_region* src = nullptr)
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
    uint32_t get_version() {
      return wl_region_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_region_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_region_set_user_data(this->pointer, data);
    }

  public:
    void destroy();
    void add(int32_t x, int32_t y, int32_t width, int32_t height);
    void subtract(int32_t x, int32_t y, int32_t width, int32_t height);
  };
  class wl_subcompositor_t : public interface_core<wl_subcompositor, 1> {
  public:
    using core_type = interface_core<wl_subcompositor, 1>;
    static constexpr wl_interface const& interface = wl_subcompositor_interface;

  public:
    wl_subcompositor_t(wl_subcompositor* src = nullptr)
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
    uint32_t get_version() {
      return wl_subcompositor_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_subcompositor_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_subcompositor_set_user_data(this->pointer, data);
    }

  public:
    void destroy();
    enum class error : uint32_t {
      error_bad_surface = 0,
    };
    wl_subsurface_t get_subsurface(wl_surface* surface, wl_surface* parent);
  };
  class wl_subsurface_t : public interface_core<wl_subsurface, 1> {
  public:
    using core_type = interface_core<wl_subsurface, 1>;
    static constexpr wl_interface const& interface = wl_subsurface_interface;

  public:
    wl_subsurface_t(wl_subsurface* src = nullptr)
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
    uint32_t get_version() {
      return wl_subsurface_get_version(this->pointer);
    }
    void* get_user_data() {
      return wl_subsurface_get_user_data(this->pointer);
    }
    void set_user_data(void* data) {
      wl_subsurface_set_user_data(this->pointer, data);
    }

  public:
    void destroy();
    enum class error : uint32_t {
      error_bad_surface = 0,
    };
    void set_position(int32_t x, int32_t y);
    void place_above(wl_surface* sibling);
    void place_below(wl_surface* sibling);
    void set_sync();
    void set_desync();
  };

  inline wl_callback_t wl_display_t::sync()
  {
    return (wl_callback_t) wl_display_sync(pointer);
  }
  inline wl_registry_t wl_display_t::get_registry()
  {
    return (wl_registry_t) wl_display_get_registry(pointer);
  }
  inline void* wl_registry_t::bind(uint32_t name, wl_interface const* interface, uint32_t version)
  {
    return (void*) wl_registry_bind(pointer, name, interface, version);
  }
  inline wl_surface_t wl_compositor_t::create_surface()
  {
    return (wl_surface_t) wl_compositor_create_surface(pointer);
  }
  inline wl_region_t wl_compositor_t::create_region()
  {
    return (wl_region_t) wl_compositor_create_region(pointer);
  }
  inline wl_buffer_t wl_shm_pool_t::create_buffer(int32_t offset, int32_t width, int32_t height, int32_t stride, uint32_t format)
  {
    return (wl_buffer_t) wl_shm_pool_create_buffer(pointer, offset, width, height, stride, format);
  }
  inline void wl_shm_pool_t::destroy()
  {
    return (void) wl_shm_pool_destroy(pointer);
  }
  inline void wl_shm_pool_t::resize(int32_t size)
  {
    return (void) wl_shm_pool_resize(pointer, size);
  }
  inline wl_shm_pool_t wl_shm_t::create_pool(int fd, int32_t size)
  {
    return (wl_shm_pool_t) wl_shm_create_pool(pointer, fd, size);
  }
  inline void wl_buffer_t::destroy()
  {
    return (void) wl_buffer_destroy(pointer);
  }
  inline void wl_data_offer_t::accept(uint32_t serial, char const* mime_type)
  {
    return (void) wl_data_offer_accept(pointer, serial, mime_type);
  }
  inline void wl_data_offer_t::receive(char const* mime_type, int fd)
  {
    return (void) wl_data_offer_receive(pointer, mime_type, fd);
  }
  inline void wl_data_offer_t::destroy()
  {
    return (void) wl_data_offer_destroy(pointer);
  }
  inline void wl_data_offer_t::finish()
  {
    return (void) wl_data_offer_finish(pointer);
  }
  inline void wl_data_offer_t::set_actions(uint32_t dnd_actions, uint32_t preferred_action)
  {
    return (void) wl_data_offer_set_actions(pointer, dnd_actions, preferred_action);
  }
  inline void wl_data_source_t::offer(char const* mime_type)
  {
    return (void) wl_data_source_offer(pointer, mime_type);
  }
  inline void wl_data_source_t::destroy()
  {
    return (void) wl_data_source_destroy(pointer);
  }
  inline void wl_data_source_t::set_actions(uint32_t dnd_actions)
  {
    return (void) wl_data_source_set_actions(pointer, dnd_actions);
  }
  inline void wl_data_device_t::start_drag(wl_data_source* source, wl_surface* origin, wl_surface* icon, uint32_t serial)
  {
    return (void) wl_data_device_start_drag(pointer, source, origin, icon, serial);
  }
  inline void wl_data_device_t::set_selection(wl_data_source* source, uint32_t serial)
  {
    return (void) wl_data_device_set_selection(pointer, source, serial);
  }
  inline void wl_data_device_t::release()
  {
    return (void) wl_data_device_release(pointer);
  }
  inline wl_data_source_t wl_data_device_manager_t::create_data_source()
  {
    return (wl_data_source_t) wl_data_device_manager_create_data_source(pointer);
  }
  inline wl_data_device_t wl_data_device_manager_t::get_data_device(wl_seat* seat)
  {
    return (wl_data_device_t) wl_data_device_manager_get_data_device(pointer, seat);
  }
  inline wl_shell_surface_t wl_shell_t::get_shell_surface(wl_surface* surface)
  {
    return (wl_shell_surface_t) wl_shell_get_shell_surface(pointer, surface);
  }
  inline void wl_shell_surface_t::pong(uint32_t serial)
  {
    return (void) wl_shell_surface_pong(pointer, serial);
  }
  inline void wl_shell_surface_t::move(wl_seat* seat, uint32_t serial)
  {
    return (void) wl_shell_surface_move(pointer, seat, serial);
  }
  inline void wl_shell_surface_t::resize(wl_seat* seat, uint32_t serial, uint32_t edges)
  {
    return (void) wl_shell_surface_resize(pointer, seat, serial, edges);
  }
  inline void wl_shell_surface_t::set_toplevel()
  {
    return (void) wl_shell_surface_set_toplevel(pointer);
  }
  inline void wl_shell_surface_t::set_transient(wl_surface* parent, int32_t x, int32_t y, uint32_t flags)
  {
    return (void) wl_shell_surface_set_transient(pointer, parent, x, y, flags);
  }
  inline void wl_shell_surface_t::set_fullscreen(uint32_t method, uint32_t framerate, wl_output* output)
  {
    return (void) wl_shell_surface_set_fullscreen(pointer, method, framerate, output);
  }
  inline void wl_shell_surface_t::set_popup(wl_seat* seat, uint32_t serial, wl_surface* parent, int32_t x, int32_t y, uint32_t flags)
  {
    return (void) wl_shell_surface_set_popup(pointer, seat, serial, parent, x, y, flags);
  }
  inline void wl_shell_surface_t::set_maximized(wl_output* output)
  {
    return (void) wl_shell_surface_set_maximized(pointer, output);
  }
  inline void wl_shell_surface_t::set_title(char const* title)
  {
    return (void) wl_shell_surface_set_title(pointer, title);
  }
  inline void wl_shell_surface_t::set_class(char const* class_)
  {
    return (void) wl_shell_surface_set_class(pointer, class_);
  }
  inline void wl_surface_t::destroy()
  {
    return (void) wl_surface_destroy(pointer);
  }
  inline void wl_surface_t::attach(wl_buffer* buffer, int32_t x, int32_t y)
  {
    return (void) wl_surface_attach(pointer, buffer, x, y);
  }
  inline void wl_surface_t::damage(int32_t x, int32_t y, int32_t width, int32_t height)
  {
    return (void) wl_surface_damage(pointer, x, y, width, height);
  }
  inline wl_callback_t wl_surface_t::frame()
  {
    return (wl_callback_t) wl_surface_frame(pointer);
  }
  inline void wl_surface_t::set_opaque_region(wl_region* region)
  {
    return (void) wl_surface_set_opaque_region(pointer, region);
  }
  inline void wl_surface_t::set_input_region(wl_region* region)
  {
    return (void) wl_surface_set_input_region(pointer, region);
  }
  inline void wl_surface_t::commit()
  {
    return (void) wl_surface_commit(pointer);
  }
  inline void wl_surface_t::set_buffer_transform(int32_t transform)
  {
    return (void) wl_surface_set_buffer_transform(pointer, transform);
  }
  inline void wl_surface_t::set_buffer_scale(int32_t scale)
  {
    return (void) wl_surface_set_buffer_scale(pointer, scale);
  }
  inline void wl_surface_t::damage_buffer(int32_t x, int32_t y, int32_t width, int32_t height)
  {
    return (void) wl_surface_damage_buffer(pointer, x, y, width, height);
  }
  inline wl_pointer_t wl_seat_t::get_pointer()
  {
    return (wl_pointer_t) wl_seat_get_pointer(pointer);
  }
  inline wl_keyboard_t wl_seat_t::get_keyboard()
  {
    return (wl_keyboard_t) wl_seat_get_keyboard(pointer);
  }
  inline wl_touch_t wl_seat_t::get_touch()
  {
    return (wl_touch_t) wl_seat_get_touch(pointer);
  }
  inline void wl_seat_t::release()
  {
    return (void) wl_seat_release(pointer);
  }
  inline void wl_pointer_t::set_cursor(uint32_t serial, wl_surface* surface, int32_t hotspot_x, int32_t hotspot_y)
  {
    return (void) wl_pointer_set_cursor(pointer, serial, surface, hotspot_x, hotspot_y);
  }
  inline void wl_pointer_t::release()
  {
    return (void) wl_pointer_release(pointer);
  }
  inline void wl_keyboard_t::release()
  {
    return (void) wl_keyboard_release(pointer);
  }
  inline void wl_touch_t::release()
  {
    return (void) wl_touch_release(pointer);
  }
  inline void wl_output_t::release()
  {
    return (void) wl_output_release(pointer);
  }
  inline void wl_region_t::destroy()
  {
    return (void) wl_region_destroy(pointer);
  }
  inline void wl_region_t::add(int32_t x, int32_t y, int32_t width, int32_t height)
  {
    return (void) wl_region_add(pointer, x, y, width, height);
  }
  inline void wl_region_t::subtract(int32_t x, int32_t y, int32_t width, int32_t height)
  {
    return (void) wl_region_subtract(pointer, x, y, width, height);
  }
  inline void wl_subcompositor_t::destroy()
  {
    return (void) wl_subcompositor_destroy(pointer);
  }
  inline wl_subsurface_t wl_subcompositor_t::get_subsurface(wl_surface* surface, wl_surface* parent)
  {
    return (wl_subsurface_t) wl_subcompositor_get_subsurface(pointer, surface, parent);
  }
  inline void wl_subsurface_t::destroy()
  {
    return (void) wl_subsurface_destroy(pointer);
  }
  inline void wl_subsurface_t::set_position(int32_t x, int32_t y)
  {
    return (void) wl_subsurface_set_position(pointer, x, y);
  }
  inline void wl_subsurface_t::place_above(wl_surface* sibling)
  {
    return (void) wl_subsurface_place_above(pointer, sibling);
  }
  inline void wl_subsurface_t::place_below(wl_surface* sibling)
  {
    return (void) wl_subsurface_place_below(pointer, sibling);
  }
  inline void wl_subsurface_t::set_sync()
  {
    return (void) wl_subsurface_set_sync(pointer);
  }
  inline void wl_subsurface_t::set_desync()
  {
    return (void) wl_subsurface_set_desync(pointer);
  }
}

#endif/*INCLUDE_WAYLAND_CLIENT_HPP_6E8C5DC8_1FE5_40D9_95F1_FD32DE74492C*/
